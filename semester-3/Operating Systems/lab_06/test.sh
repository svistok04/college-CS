#!/bin/bash
read -r numbers
even_numbers=""

for number in $numbers
do
    if ((num % 2 == 0))
    then
        even_numbers=$((even_numbers + num + " "))
    fi
done

lines=$(echo "$even_numbers" | fold -w1)
sorted=$(echo "$lines" | sort)
echo "$sorted"


#!/bin/bash
read numbers
sorted=$(for num in $numbers; do
    if ((num % 2 == 0)); then
        echo "$num"
    fi
done | sort)
echo "$sorted"
