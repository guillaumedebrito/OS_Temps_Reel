#!/bin/bash

# Script for connecting using ssh
if [ $# -ne 0 ]; then
        echo "Connection a GEITP-TRS"$1" "
        ssh -X insa@geitp-trs$1
fi;
