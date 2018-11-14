#author: ES5017
#expected_exit_code: -10
#extra_info: does a simple test of addiu that includes overflow

lui $4, 0x7FFF
ori $5, $4, 0xFFFF

addi $2, $5, 1

jr $0