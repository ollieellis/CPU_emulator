#author: ES5017
#expected_exit_code: -10
#expected_output: 0
#extra_info: tests that add correctly traps overflow

lui $6, 0x7FFF
lui $4, 0x6FFF

add $5, $4, $6

#this is how to get output - it should not trigger so it should be 0, if non 0 then exception did not occur
lui $9, 0x3000
sw $5, 4($9)
jr $0