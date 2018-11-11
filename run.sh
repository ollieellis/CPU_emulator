#!/bin/bash
echo "running programme \n" #comment this out later
make simulator
#sh test/convert_mips.sh #done in testbench
make testbench
bin/mips_testbench bin/mips_simulator