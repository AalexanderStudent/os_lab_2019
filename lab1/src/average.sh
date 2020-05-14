#!/bin/bash

sum=0
n=$(wc -w < $1)
echo The amount of numbers: $n

for num in $(cat $1)
do
sum=$((sum + num))
done

average=$((sum / n))
echo Average of numbers: $average