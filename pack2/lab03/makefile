CС=gcc
CFLAGS= -Wall -Werror -Wextra

SOURCES=3.c
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



test_command_args1_3:
	@$(FAILED_CMD) "./3.a" 1 "Usage: /home/user/FundAlg3Sem/pack2/lab03/./3.a <substring> <file1> <file2> ..."
	@echo "TASK 3: TEST WITH NO ARGUMENTS PASSED"

test_command_args2_3:
	@$(FAILED_CMD) "./3.a 123" 1 "Usage: /home/user/FundAlg3Sem/pack2/lab03/./3.a <substring> <file1> <file2> ..."
	@echo "TASK 3: TEST WITH WRONG AMOUNT OF ARGUMENTS PASSED"

test_command_args3_3:
	@$(FAILED_CMD) "./3.a 123 teg.txt ryy.txt" 2 "Ошибка при работе с файлом teg.txt"
	@echo "TASK 3: TEST WITH WRONG ARGUMENTS PASSED"

test_success1_3:
	@$(SUCCESS_CMD) "./3.a egt f1.txt f2.txt f3.txt" ""
	@echo "TASK 3: TEST PASSED SUCCESS WITH INCORRECT"

test_success2_3:
	@$(SUCCESS_CMD) "./3.a money f1.txt f2.txt f3.txt" "Файл: f1.txt, строка: 4, позиция: 1"
	@echo "TASK 3: TEST PASSED SUCCESS WITH CORRECT ARGUMENTS"

test: test_command_args1_3 test_command_args2_3 test_command_args3_3 test_success1_3 test_success2_3