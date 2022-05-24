#!/bin/bash

if [ "$#" -lt 2 ];
then
    echo "Usage: difftool [OPTION]... FILES"
    exit 1
fi

counter=0
IFS=$'\n' diff_brief=$(diff -q $@)
for elem in $diff_brief; do
    # echo "=== $elem"
    IFS=' '
    read -r -a arrelem <<< $elem
    if [ ${arrelem[0]} = "Files" ];
    then
        ((counter+=1))
        file1=${arrelem[1]}
        file2=${arrelem[3]}
        # echo "$counter: differing files $file1 and $file2"
        # test invocation with meld
        difftool="meld"
        # prompt
        printf "\nViewing #%s: '%s'\n" $counter $(basename $file1)
        printf "Launch '%s' [Y/n]? " $difftool
        read ans || return
        if test "$ans" = n
        then
            continue
        fi
        # $($difftool $file1 $file2)
        eval $difftool $file1 $file2
    fi
done
