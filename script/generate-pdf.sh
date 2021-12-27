#!/bin/env bash

ps2pdf_exist=$(which ps2pdf > /dev/null; echo $?)
man_exist=$(which man > /dev/null; echo $?)

if [ "${man_exist}" != "0" ] 
then
    echo "'man' should be installed on the system."
    exit 1
fi

if [ "${ps2pdf_exist}" != "0" ] 
then
    echo "'ps2pdf' should be installed on the system."
    exit 1
fi

man="/bin/env man"
ps2pdf="/bin/env ps2pdf"
pdf_files_dir=$(mktemp -d)

for file in *.7
do
    echo "Processing" ${file}

    ts_file=${pdf_files_dir}/${file//".7"/".ts"}
    pdf_file=${pdf_files_dir}/${file//".7"/".pdf"}

    ${man} -t ./${file} > ${ts_file}
    ${ps2pdf} ${ts_file} ${pdf_file}
done

pdfunite ${pdf_files_dir}/netsck.pdf \
         ${pdf_files_dir}/socket.pdf \
         ${pdf_files_dir}/udp_socket.pdf \
         ${pdf_files_dir}/hex.pdf \
         ${pdf_files_dir}/key.pdf \
         netsck-js-api.pdf
echo "'netsck-js-api.pdf' generated."
echo