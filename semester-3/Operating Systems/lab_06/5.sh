#!/bin/bash

usernames=$(cut -d: -f1 /etc/passwd)

shortest_username=""
shortest_length=999999  # A large initial value

for username in $usernames
do
    length=${#username}

    if [ $length -lt $shortest_length ]; then
        shortest_length=$length
        shortest_username=$username
    fi
done

echo "$shortest_username"
