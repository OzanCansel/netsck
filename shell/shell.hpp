#pragma once

#include <QObject>
#include <QThread>
#include <replxx.hxx>

class shell : public QObject
{

    Q_OBJECT

public:

    shell();
    ~shell();

public slots:

    void read_line();

signals:

    void input( QString );

private:

    static constexpr auto PROMPT = "\x1b[0;32mnetsck\x1b[0m> ";

    void print_welcome_prompt();
    void start();
    bool check_if_exit_entered( const QString& input );
    void configure_terminal();
    std::string history_file_path();

    void hook_highlighter(
        std::string const& context ,
        replxx::Replxx::colors_t& colors ,
        std::vector<std::pair<std::string, replxx::Replxx::Color>> const& regex_color
    ) const;

    using highlight_entry = std::pair<std::string , replxx::Replxx::Color>;

    std::vector<highlight_entry> m_highlights;
    replxx::Replxx m_terminal;
    QThread m_thread;
};