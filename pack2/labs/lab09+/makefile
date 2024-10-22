CС=gcc
CFLAGS= -Wall -Werror -Wextra

SOURCES=9.c
TEST_TEMPLATES_DIR=./test_templates
EXECUTABLES=$(SOURCES:.c=.a)
BASH=bash
SUCCESS_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_cmd
SUCCESS_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ofile
FAILED_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/failed_cmd
FAILED_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ofile
SUCCESS_RFILE_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_cmd
SUCCESS_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_ofile


.PHONY: all test clean

all: $(EXECUTABLES) 

%.a : %.c
	$(CC) $(CFLAGS) $< -o $@ -lm

clean:
	rm -r -f *.a


test_command_args1_9:
	@$(FAILED_CMD) "./9.a" 1 "Usage: ./9.a <base> <decimal1> <decimal2> ..."
	@echo "TASK 9: TEST WITH NO ARGUMENTS PASSED"

test_command_args2_9:
	@$(FAILED_CMD) "./9.a re 0.11" 1 "An error occurred during calculation: 1"
	@echo "TASK 9: TEST WITH WRONG AMOUNT OF ARGUMENTS PASSED"

test_command_args3_9:
	@$(FAILED_CMD) "./9.a 10 2.11" 4 "An error occurred during calculation: 4"
	@echo "TASK 9: TEST WITH WRONG ARGUMENTS PASSED"

test_command_args4_9:
	@$(FAILED_CMD) "./9.a 2 grt" 4 "An error occurred during calculation: 4"
	@echo "TASK 9: TEST WITH WRONG ARGUMENTS PASSED"

test_success1_9:
	@$(SUCCESS_CMD) "./9.a 10 0.11 0.22222222222 0.31 0.99" "Number 0.110000 has a finite representation in base 10.Number 0.222222 does not have a finite representation in base 10.Number 0.310000 has a finite representation in base 10.Number 0.990000 has a finite representation in base 10."
	@echo "TASK 9: TEST CORRECT ARGUMENT SUCCESS"

test_success2_9:
	@$(SUCCESS_CMD) "./9.a 2 0.10101111 0.11011001 0.000011" "Number 0.101011 does not have a finite representation in base 2.Number 0.110110 does not have a finite representation in base 2.Number 0.000011 does not have a finite representation in base 2."
	@echo "TASK 9: TEST CORRECT ARGUMENT SUCCESS"


test: test_command_args1_9 test_command_args2_9 test_command_args3_9 test_command_args4_9 test_success1_9 test_success2_9