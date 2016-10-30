#!/bin/bash
function checkCPP {
  corename=${1%.*}
  file=test/$corename

  if [ ! -f "$file.in" ]; then
	echo There is no testcase for the program $1.
  elif [ -f $1 ]; then
	if ! diff $file.out $file.sol >& /dev/null; then
		if [ -f $file ]; then
	        rm $file
	    fi
		g++ -o $file `ls $corename[-\.]*cpp`
	fi

	if [ ! -f $file ]; then
        echo -en '\e[1;31m'"[Compile Failure!]"'\e[0;39m' for $1
		echo
		exit 
	fi
	if [ -f $file.arg ]; then
		$file `cat $file.arg` < "$file.in" > $file.out
	else
		$file < "$file.in" > $file.out
	fi

	if diff $file.out $file.sol >/dev/null; then
		echo -en '\e[1;32m'"[Success!]"'\e[0;39m' for $1
		echo
	else
		echo -en '\e[1;31m'"[Fail!]"'\e[0;39m' for $1
		echo
		echo -en '\e[1;31m'YOUR OUTPUT:'\e[0;39m'
		echo
		cat $file.out | head -15
		echo -en '\e[1;31m'"EXPECTED OUTPUT:"'\e[0;39m'
		echo
		cat $file.sol | head -15
		exit
	fi

  else
	echo File "'"$1"'" does not exist!
  fi
}

function deleteTest {
  corename=${1%.*}
  file=test/$corename
  
  if [ -f $file ]; then
	rm $file
  fi

  if [ -f $file.out ]; then
    rm $file.out
  fi
}

if [ -z $1 ]; then
	echo Please type \"./check "<filename>"\".
	echo Other options are \"./check clean\" and \"./check all\".
elif [ $1 = "all" ]; then
	files=`ls *[0-9].cpp`
	sorted=`echo $files | awk '{for (ii=NF; ii>=1; ii--) {if (match($ii,"[0-9]+")) 
		{printf substr($ii,RSTART,RLENGTH)" "};print $ii}}' | sort -n | awk '{print $NF}'`
	for xx in $sorted
	do
		checkCPP $xx
	done
elif [ $1 = "clean" ]; then
    files=`ls *[0-9].cpp`
    sorted=`echo $files | awk '{for (ii=NF; ii>=1; ii--) {if (match($ii,"[0-9]+"))
        {printf substr($ii,RSTART,RLENGTH)" "};print $ii}}' | sort -n | awk '{print $NF}'`
    for xx in $sorted
    do
		deleteTest $xx
    done
else
	checkCPP $1
fi
