#!/bin/bash

# Filename: ex12.sh
#
# Problem: Make the code into a function and call function using cat, dog 
# and frog as an argument.

function homework {
echo The $1 chased it tail.
echo Then the $1 sat on a $2.
}

homework cat mat
homework dog kennel
homework frog lily  

