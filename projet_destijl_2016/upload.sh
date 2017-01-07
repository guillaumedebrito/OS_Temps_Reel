#!/bin/sh

# Script for uploading using sftp
if [ $# -ne 0 ]; then
        echo "Connection a GEITP-TRS"$1" "
        rm -rf sftp_cmd.txt
        touch sftp_cmd.txt
        echo "cd tp_trs" >> sftp_cmd.txt
        echo "put "$2"" >> sftp_cmd.txt

	sftp -o "batchmode no" -b sftp_cmd.txt insa@geitp-trs$1
fi;
