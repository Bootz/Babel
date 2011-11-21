#!/bin/sh
## gen.sh for .md to .html script project
## 
## Made by ramnes
## <perso@ramnes.eu>
## 
## Started on  Mon Nov 21 01:05:34 2011 by ramnes
## Last update Mon Nov 21 01:12:09 2011 ramnes
##

if [ -d html ]
then
    echo "Cleaning html directory"
    rm -rf html/*
else
    echo "Creating html directory"
    mkdir html
fi

if [ -x /usr/bin/markdown ]
then
    echo "Generating html files"
    for file in *.md ; do markdown $file > html/$file.html ; done
else
    echo "Can't use markdown (maybe install it ?)"
    exit 1
fi

echo "Success :)"
exit 0