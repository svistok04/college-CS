#!/bin/bash
read input
lines=$(echo "$input" | fold -w1)
reversed_lines=$(echo "$lines" | tac)
reversed_string=$(echo "$reversed_lines" | tr -d '\n')
echo "$reversed_string"
