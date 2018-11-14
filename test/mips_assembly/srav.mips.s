#author: ES5017
#expected_output: -2
#extra_info: tests simple case for srav

lui $1, 0x8069
addi $3, $0, 30

srav $2, $1, $3

lui $9, 0x3000
sw $2 4($9)

jr $0
