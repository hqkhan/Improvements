#!/bin/bash

# Filename: ex20.sh
#
# Problem: Remove the html tags from ex20.input.
cat ex20.input | awk '{
	#anything that starts with < and ignore anything in the middle and make sure it ends with >
        gsub("<[^>]*>", "",$0)	
	print $0	
    }'
