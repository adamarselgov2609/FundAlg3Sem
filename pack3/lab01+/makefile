CС=gcc
CFLAGS= -Wall -Wextra

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
	@$(FAILED_CMD) "./1.a" 1 "Ошибка: необходимо ввести одно число."
	@echo "TASK 1: TEST WITH NO ARGUMENTS PASSED"

test_command_args2_1:
	@$(FAILED_CMD) "./1.a er" 1 "Ошибка: недопустимое число. Введите положительное целое число." 
	@echo "TASK 1: TEST WITH WRONG AMOUNT OF ARGUMENTS PASSED"

test_command_args3_1:
	@$(FAILED_CMD) "./1.a 5 ggfd" 1 "Ошибка: необходимо ввести одно число."
	@echo "TASK 1: TEST WITH WRONG ARGUMENTS PASSED"

test_success1_1:
	@$(SUCCESS_CMD) "./1.a 6" "Число 6 в системе счисления с основанием 2:  00000000000000000000000000000110Число 6 в системе счисления с основанием 4:  00000000000000000000000000000012Число 6 в системе счисления с основанием 8:  00000000000000000000000000000006Число 6 в системе счисления с основанием 16: 00000000000000000000000000000006Число 6 в системе счисления с основанием 32: 00000000000000000000000000000006"
	@echo "TASK 1: TEST PASSED SUCCESS"



test: test_command_args1_1 test_command_args2_1 test_command_args3_1 test_success1_1