#!/bin/bash
read input
lines=$(echo "$input" | fold -w1)
reversed_lines=$(echo "$lines" | sort -r)
sorted_string=$(echo "$reversed_lines" | tr -d '\n')
echo "$sorted_string"
