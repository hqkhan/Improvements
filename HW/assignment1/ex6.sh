#!/bin/bash

# Filename: ex6.sh
#
# Problem: Modify the case statement so it uses a regular expression 
# (also known as Regexp) so that any response starting with y or n, both
# capital or lower case works.

read -p "Do you wish to open the pod bay doors?" inputVar

case $inputVar in
	y*|Y*) echo "I'm sorry, Dave. I'm afraid I can't do that.";;
	n*|N*) echo "That is good. I wouldn't open them anyway.";;
	*) echo "Please answer yes or no.";;
esac


