#author: ES5017
#expected_exit_code: -10
#extra_info: tests that add correctly traps overflow

lui $6, 0x7FFF
lui $4, 0x6FFF

sub $5, $4, $6
jr $0