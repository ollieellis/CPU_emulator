#author: ES5017
#expected_exit_code: -10
#expected_output: 0
#extra_info: tests that add correctly traps overflow

lui $6, 0x7FFF
lui $4, 0x6FFF

add $5, $4, $6

#if the exception was thrown, this should not trigger an output ie its = 0
sw $5, 12($0)

jr $0