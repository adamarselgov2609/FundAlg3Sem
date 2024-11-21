CС=gcc
CFLAGS= -Wall -Werror -Wextra

SOURCES=task2_8.c
TEST_TEMPLATES_DIR=../test_templates
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


test_command_args1_8:
	@$(FAILED_CMD) "./task2_8.a" 1 "Usage:  <base> <number1> <number2> ... <numberN>"
	@echo "TASK 9: TEST WITH NO ARGUMENTS PASSED"

test_command_args2_8:
	@$(FAILED_CMD) "./task2_8.a tr 65" 1 "Usage:  <base> <number1> <number2> ... <numberN>"
	@echo "TASK 9: TEST WITH WRONG AMOUNT OF ARGUMENTS PASSED"

test_command_args3_8:
	@$(FAILED_CMD) "./task2_8.a tr tryrfg yh" 2 "Error: Base must be between 2 and 36"
	@echo "TASK 9: TEST WITH WRONG ARGUMENTS PASSED"

test_success1_8:
	@$(SUCCESS_CMD) "./task2_8.a 10 21 43 67" "Sum in base 10: 131"
	@echo "TASK 9: TEST CORRECT ARGUMENT SUCCESS"

test_success2_8:
	@$(SUCCESS_CMD) "./task2_8.a 2 100111 10 00101" "Sum in base 2: 101110"
	@echo "TASK 9: TEST CORRECT ARGUMENT SUCCESS"


test: test_command_args1_8 test_command_args2_8 test_command_args3_8 test_success1_8 test_success2_8