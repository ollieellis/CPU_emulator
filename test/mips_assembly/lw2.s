#author: ES5017
#expected_exit_code: -11
#extra_info: test memory mapped input 

#testing quickly:
#expected_output: 69

#expected_output_0: 104
#expected_output_1: 101
#expected_output_2: 108
#expected_output_3: 108
#expected_output_4: 111

#the above expected outputs are ascii for 'hello', which is what is in the wibble.txt file we use for testbench input test
#cat test/wibble.txt | bin/mips_simulator test/mips_binary/lw2.bin

lui $9, 0x3000
addi $1, $0, -1
next_input:
lw $5 0($9)
nop
#write the input back to output so we can check it correctly read the input
sw $5 4($9)
#once we are at eof it will return -1 and equal $1 and not branch
bne $1, $5, next_input
nop
jr $0
