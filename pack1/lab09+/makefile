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




test_command_args_9:
	@$(FAILED_CMD) "./9.a" 1 "Error: invalid arguments. Usage: 9.a <a> <b>"
	@echo "TASK 9: TEST WITH NO ARGUMENTS PASSED"


test_failed1_9:
	@$(FAILED_CMD) "./9.a -10 100 qwerty" 1 "Error: invalid arguments. Usage: 9.a <a> <b>"
	@echo "TASK 9: TEST WITH WRONG AMOUNT OF ARGUMENTS PASSED"

test_failed2_9:
	@$(FAILED_CMD) "./9.a -10 100 20" 1 "Error: invalid arguments. Usage: 9.a <a> <b>"
	@echo "TASK 9: TEST WITH WRONG ARGUMENTS PASSED"


test: test_command_args_9  test_failed1_9 test_failed2_9