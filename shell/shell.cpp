#include "shell.hpp"
#include <QMetaObject>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>
#include <regex>
#include <iostream>

static auto function_call = R"(\w+\(*\))";
static auto var_keyword   = R"(\bvar\b)";
static auto new_keyword   = R"(\bnew\b)";
static auto string_literal= R"(\"([^\\\"]|\\.)*\")";

shell::shell()
    :   m_highlights 
        {
            { function_call  , replxx::Replxx::Color::BROWN } ,
            { var_keyword    , replxx::Replxx::Color::BLUE } ,
            { new_keyword    , replxx::Replxx::Color::BLUE } ,
            { string_literal , replxx::Replxx::Color::MAGENTA }
        }
{
    configure_terminal();
    print_welcome_prompt();
    start();
}

shell::~shell()
{
    m_thread.quit();
    m_thread.wait();
}

void shell::read_line()
{
    char const* cinput { };

    cinput = m_terminal.input( PROMPT );

    if ( !cinput )
    {
        emit input( QString {} );

        return;
    }

    auto line_str = std::string { cinput };

    m_terminal.history_add( line_str );
    m_terminal.history_save( history_file_path() );

    QString line = QString::fromStdString( line_str );

    if ( check_if_exit_entered( line ) )
    {
        QMetaObject::invokeMethod(
            QCoreApplication::instance() ,
            "quit"
        );
    }
    else
    {
        emit input( line );
    }
}

void shell::print_welcome_prompt()
{
    std::cout << "\x1b[;36m## " 
              << QCoreApplication::applicationName().toStdString()
              << " " << QCoreApplication::applicationVersion().toStdString() << '\n'
              << PROMPT << "shell is active\n"
              << PROMPT << "Type 'help()' to see commands available" << std::endl;
}

void shell::start()
{
    m_thread.start( QThread::LowPriority );
    moveToThread( &m_thread );

    QMetaObject::invokeMethod(
        this ,
        "read_line" ,
        Qt::QueuedConnection
    );
}

bool shell::check_if_exit_entered( const QString& input )
{
    return input == "quit" ||
           input == "exit" ||
           input.contains( "quit()" ) ||
           input.contains( "exit()" );
}

void shell::configure_terminal()
{
    using namespace replxx;

    m_terminal.install_window_change_handler();
    m_terminal.history_load( history_file_path() );
    m_terminal.set_max_history_size( 128 );
    m_terminal.set_word_break_characters( " \t.,-%!;:=*~^'\"/?<>|[](){}" );
    m_terminal.set_highlighter_callback(
        std::bind(
            &shell::hook_highlighter ,
            this ,
            std::placeholders::_1 ,
            std::placeholders::_2 ,
            std::cref( m_highlights )
        )
    );

    m_terminal.bind_key_internal( Replxx::KEY::BACKSPACE,                      "delete_character_left_of_cursor" );
    m_terminal.bind_key_internal( Replxx::KEY::DELETE,                         "delete_character_under_cursor" );
    m_terminal.bind_key_internal( Replxx::KEY::LEFT,                           "move_cursor_left" );
    m_terminal.bind_key_internal( Replxx::KEY::RIGHT,                          "move_cursor_right" );
    m_terminal.bind_key_internal( Replxx::KEY::UP,                             "history_previous" );
    m_terminal.bind_key_internal( Replxx::KEY::DOWN,                           "history_next" );
    m_terminal.bind_key_internal( Replxx::KEY::PAGE_UP,                        "history_first" );
    m_terminal.bind_key_internal( Replxx::KEY::PAGE_DOWN,                      "history_last" );
    m_terminal.bind_key_internal( Replxx::KEY::HOME,                           "move_cursor_to_begining_of_line" );
    m_terminal.bind_key_internal( Replxx::KEY::END,                            "move_cursor_to_end_of_line" );
    m_terminal.bind_key_internal( Replxx::KEY::TAB,                            "complete_line" );
    m_terminal.bind_key_internal( Replxx::KEY::control( Replxx::KEY::LEFT ),   "move_cursor_one_word_left" );
    m_terminal.bind_key_internal( Replxx::KEY::control( Replxx::KEY::RIGHT ),  "move_cursor_one_word_right" );
    m_terminal.bind_key_internal( Replxx::KEY::control( Replxx::KEY::UP ),     "hint_previous" );
    m_terminal.bind_key_internal( Replxx::KEY::control( Replxx::KEY::DOWN ),   "hint_next" );
    m_terminal.bind_key_internal( Replxx::KEY::control( Replxx::KEY::ENTER ),  "commit_line" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'R' ),                 "history_incremental_search" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'W' ),                 "kill_to_begining_of_word" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'U' ),                 "kill_to_begining_of_line" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'K' ),                 "kill_to_end_of_line" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'Y' ),                 "yank" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'L' ),                 "clear_screen" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'T' ),                 "transpose_characters" );
#ifndef _WIN32
    m_terminal.bind_key_internal( Replxx::KEY::control( 'V' ),                 "verbatim_insert" );
    m_terminal.bind_key_internal( Replxx::KEY::control( 'Z' ),                 "suspend" );
#endif
    m_terminal.bind_key_internal( Replxx::KEY::meta( Replxx::KEY::BACKSPACE ), "kill_to_whitespace_on_left" );
    m_terminal.bind_key_internal( Replxx::KEY::meta( 'p' ),                    "history_common_prefix_search" );
    m_terminal.bind_key_internal( Replxx::KEY::meta( 'n' ),                    "history_common_prefix_search" );
    m_terminal.bind_key_internal( Replxx::KEY::meta( 'y' ),                    "yank_cycle" );
    m_terminal.bind_key_internal( Replxx::KEY::meta( 'u' ),                    "uppercase_word" );
    m_terminal.bind_key_internal( Replxx::KEY::meta( 'l' ),                    "lowercase_word" );
    m_terminal.bind_key_internal( Replxx::KEY::meta( 'c' ),                    "capitalize_word" );
    m_terminal.bind_key_internal( 'a',                                         "insert_character" );
    m_terminal.bind_key_internal( Replxx::KEY::INSERT,                         "toggle_overwrite_mode" );
}

std::string shell::history_file_path()
{
    auto locs = QStandardPaths::standardLocations(
        QStandardPaths::AppDataLocation
    );

    if ( std::empty( locs ) )
        return "netsck.shell.history";
    else
    {
        auto app_data_path { locs.front() };

        if ( !QFileInfo::exists( app_data_path ) )
            QDir {}.mkpath( app_data_path );

        return QDir { app_data_path }
                   .filePath( "netsck.shell.history" )
                   .toStdString();
    }
}

void shell::hook_highlighter(
    std::string const& context ,
    replxx::Replxx::colors_t& colors ,
    std::vector<std::pair<std::string, replxx::Replxx::Color>> const& regex_color
) const
{
    for ( const auto& e : regex_color )
    {
        size_t pos {};
        std::string str = context;
        std::smatch match;

        while ( std::regex_search( str , match , std::regex( e.first ) ) )
        {
            std::string c{ match[0] };
            std::string prefix( match.prefix().str() );
            pos += int( prefix.length() );
            int len( int( c.length() ) );

            for ( int i = 0; i < len; ++i )
                colors.at(pos + i) = e.second;

            pos += len;
            str = match.suffix();
        }
    }
}