#author: ES5017
#expected_output: 205 103
#extra_info: tests lwl aligned

lui $1, 0x2000

lui $3, 0x6789
ori $3, $3, 0xABCD
#we have in $3 0x6789ABCD

sw $3, 0($1)

addi $2, $0, 0x1234
lwl $2, 0($1)
#in $2 we have 0x89ABCD34


lui $9, 0x3000
sw $2 4($9)

srl $2, $2, 24
sw $2 4($9)

addi $2, $0, 0

jr $0

