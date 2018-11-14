#author: ES5017
#expected_exit_code: 19
#extra_info: test memory mapped input without memory mapped output

#adds the ascii decimal numbers and returns the low 8 bits of the result as exit code low 8 bits of 531 is 19. ascii for 'hello', which is what is in the wibble.txt file we use for testbench input test

lui $9, 0x3000
addi $1, $0, -1
next_input:
lw $5 0($9)
nop
addu $2, $2, $5
#once we are at eof it will return -1 and equal $1 and not branch
bne $1, $5, next_input
nop
jr $0
