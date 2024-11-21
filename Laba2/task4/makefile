CС=gcc
CFLAGS= -Wall -Werror -Wextra

SOURCES=task2_4_1.c
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




test_command_args1_1:
	@$(FAILED_CMD) "./task2_4_1.a" -3 "Usage: <function_number> arguments"
	@echo "TASK 1: TEST WITH NO ARGUMENTS PASSED"

test_command_args2_1:
	@$(FAILED_CMD) "./task2_4_1.a 1" -3 "Usage: 1 <number_of_vertices> <x1 y1> <x2 y2> ..."
	@echo "TASK 1: TEST WITH WRONG AMOUNT OF ARGUMENTS PASSED"

test_command_args4_1:
	@$(FAILED_CMD) "./task2_4_1.a 1 2" -1 "The number of vertices must be more than 2."
	@echo "TASK 1: TEST WITH WRONG ARGUMENTS PASSED"


test_success2_1:
	@$(SUCCESS_CMD) "./task2_4_1.a 1 4 0 0 1 0 1 1 0 1" "The polygon is convex."
	@echo "TASK 1: TEST POLYGON IS CONVEX ARGUMENT SUCCESS"

test_success3_1:
	@$(SUCCESS_CMD) "./task2_4_1.a 2 2 2.0 1.0 2.0 3.0" "Polynomial value at x = 3.00: 23.00"
	@echo "TASK 1: TEST Polynomial ARGUMENT SUCCESS"

test_success4_1:
	@$(SUCCESS_CMD) "./task2_4_1.a 3 10 1 9" "Kaprekar numbers in base 10:9 is a Kaprekar number in base 10"
	@echo "TASK 1: TEST KAPREKAR ARGUMENT SUCCESS"


test: test_command_args1_1 test_command_args2_1 test_command_args4_1  test_success2_1 test_success3_1 test_success4_1