#!/bin/bash

read expression

# Extract the individual parts of the expression
symbol=$(echo "$expression" | cut -c2)
operand1=$(echo "$expression" | cut -c1)
operand2=$(echo "$expression" | cut -c3)

# Perform the operation based on the symbol
if [ "$symbol" = "+" ]; then
    result=$((operand1 + operand2))
    echo "$result"
elif [ "$symbol" = "-" ]; then
    result=$((operand1 - operand2))
    echo "$result"
elif [ "$symbol" = "*" ]; then
    result=$((operand1 * operand2))
    echo "$result"
elif [ "$symbol" = "/" ]; then
    if [ "$operand2" -eq 0 ]; then
        echo "Error: Division by zero"
    else
        result=$((operand1 / operand2))
        echo "$result"
    fi
else
    echo "Invalid operator entered: $symbol"
fi
