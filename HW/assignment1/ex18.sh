#!/bin/bash

# Filename: ex18.sh
#
# Problem: Find the highest number for each line and print it. 
cat ex18.input | awk '{max=$1;
		       check=0;
		       if($2>max){
			     max=$2}
		       if($3>max){
		             max=$3}
		       if($4>max){
			     max=$4}
		       if($5>max){
			     max=$5}
		       if($6>max){
			     max=$6}
			
			printf "%d\n", max
	}'
