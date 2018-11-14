#author: ES5017
#expected_exit_code: 1
#extra_info: tests simple case for sltu

addi $1, $0, 15
addi $2, $0, 18

sltu $2, $1, $2

jr $0
