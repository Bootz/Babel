#!/bin/sh
## gen.sh for .html doc gen script project
## 
## Made by ramnes
## <perso@ramnes.eu>
## 
## Started on  Mon Nov 21 01:05:34 2011 by ramnes
## Last update Mon Nov 21 01:45:50 2011 ramnes
##


if [ -d ../doc/html ]
then
    echo "Cleaning html directory"
    rm -rf ../doc/html/*
else
    echo "Creating html directory"
    mkdir ../doc/html
fi

if [ -x ./Markdown.pl ]
then
    echo "Generating html files"
    for file in `ls ../doc/md` ; do ./Markdown.pl ../doc/md/$file > ../doc/html/$file.html ; done
else
    echo "Can't use markdown (maybe chmod a+x it)"
    exit 1
fi

echo "Success :)"
exit 0