#!/bin/bash  
#cd test/mips-parser
#make parser

rm -rf test/mips_binary #refresh the binaries and remove the old ones
mkdir -p test/mips_binary
for assembly_file in test/mips_assembly/*
do
    
   test/mips-parser/bin/parser $assembly_file test/mips_binary/#
done