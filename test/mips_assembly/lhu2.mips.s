#author: ES5017
#expected_exit_code: 0
#extra_info: test memory mapped input with lh assuming memory mapped output works

#expected_output: 104 101 108 108 111 -1


#the above expected outputs are ascii for 'hello', which is what is in the wibble.txt file we use for testbench input test
#cat test/wibble.txt | bin/mips_simulator test/mips_binary/lw2.bin

lui $9, 0x3000
ori $9, $9, 0x0002
addi $1, $0, -1


next_input:
lhu $5 0($9)
nop
#write the input back to output so we can check it correctly read the input
sh $5 4($9)
#once we are at eof it will return -1 and equal $1 and not branch
bne $1, $5, next_input
nop
jr $0
