#!/bin/bash

file1="server"
file2="client"

gcc ${file1}.c src/MYNET.c -o $file1

gcc ${file2}.c src/MYNET.c -o $file2