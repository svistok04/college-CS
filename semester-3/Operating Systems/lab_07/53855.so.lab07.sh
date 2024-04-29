#! /bin/bash
# SO IS1 223A LAB07
# Vladyslav Zosimchuk
# zv53855@zut.edu.pl

if [ -z "$1" ] || [ -n "$2" ]; then
    echo "Too much or none options were used!"
    exit
fi

if [ "$1" != "-l" ] && [ "$1" != "-b" ]; then
    echo "A wrong option was used!"
    exit
fi

if [ "$1" == "-l" ]; then
    for module in /sys/module/*/; do
        name=$(basename "$module")
        if [ -f "$module/refcnt" ]; then
            refcnt=$(cat "$module/refcnt")
            if [ -d "$module/holders" ]; then
                holders=$(ls -m "$module/holders")
            fi
            echo "$name $refcnt $holders"
        fi
    done
    elif [ "$1" == "-b" ]; then
    for module in /sys/module/*/; do
        if [ ! -f "$module/refcnt" ]; then
            name=$(basename "$module")
            if [ -d "$module/parameters" ]; then
                parameters=$(ls -m "$module/parameters")
            fi
            echo "$name $parameters"
        fi
    done
fi
