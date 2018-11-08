#!/bin/bash  
echo "testbench started" #comment this out later
simulator=$1
for binary_file in test/mips_binary/*
do
    sim_stdout=$($simulator $binary_file)
   # printf '%d\n' "'$sim_stdout" #comment this out later
    testId=$(basename -- "${binary_file%.*}")
    instruction=${testId//[[:digit:]]/} 
    echo $testId, $instruction, pass/fail, $USER, "expected exit code:" x "actual exit code:" $?
    
done