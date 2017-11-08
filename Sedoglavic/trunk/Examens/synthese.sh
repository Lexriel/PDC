#!/bin/bash


for i in `ls TeX/*.tex` 
do
    LINE=" "
    for j in `ls *.tex`
    do
	if grep "\\input{${i%%.*}}" $j > /dev/null
	then 
	    LINE=$LINE:"X"
	else 
	    LINE=$LINE:" "
	fi ;
    done ;
    LINE=$LINE::$i
    echo $LINE
done ;