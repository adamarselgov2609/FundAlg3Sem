CС=gcc
CFLAGS= -Wall -Werror -Wextra

SOURCES=1.c
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




test_command_args1_1:
	@$(FAILED_CMD) "./1.a" 1 "Error: Invalid arguments."
	@echo "TASK 1: TEST WITH NO ARGUMENTS PASSED"

test_command_args2_1:
	@$(FAILED_CMD) "./1.a -q wwfr" 3 "Error: Invalid flag provided."
	@echo "TASK 1: TEST WITH WRONG AMOUNT OF ARGUMENTS PASSED"

test_command_args3_1:
	@$(FAILED_CMD) "./1.a eg" 1 "Error: Invalid arguments."
	@echo "TASK 1: TEST WITH WRONG ARGUMENTS PASSED"

test_command_args4_1:
	@$(FAILED_CMD) "./1.a -c wrt yr hty" 4 "Error: Invalid seed value."
	@echo "TASK 1: TEST WITH WRONG ARGUMENTS PASSED"

test_success1_1:
	@$(SUCCESS_CMD) "./1.a -l qaz" "Length of the string: 3"
	@echo "TASK 1: TEST -l ARGUMENT SUCCESS"

test_success2_1:
	@$(SUCCESS_CMD) "./1.a -r qaz" "Reversed string: zaq"
	@echo "TASK 1: TEST -r ARGUMENT SUCCESS"

test_success3_1:
	@$(SUCCESS_CMD) "./1.a -u werwfj" "String with uppercase odd positions: wErWfJ"
	@echo "TASK 1: TEST -u ARGUMENT SUCCESS"

test_success4_1:
	@$(SUCCESS_CMD) "./1.a -n wt65erwf8j30" "Sorted string: 65830wterwfj"
	@echo "TASK 1: TEST -n ARGUMENT SUCCESS"

test_success5_1:
	@$(SUCCESS_CMD) "./1.a -c 1234 tyr iyu kuy4" "Concatenated string: tyrkuy4tyr"
	@echo "TASK 1: TEST -c ARGUMENT SUCCESS"

test: test_command_args1_1 test_command_args2_1 test_command_args3_1 test_command_args4_1 test_success1_1 test_success2_1 test_success3_1 test_success4_1 test_success5_1