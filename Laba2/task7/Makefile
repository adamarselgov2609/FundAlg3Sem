CС=gcc
CFLAGS= -Wall -Werror -Wextra
CLIBS= -lm

SOURCES=task2_7.c# Тут вы перечислятете файлы с вашими лабами по 1 файлу на задание
TEST_TEMPLATES_DIR=../test_templates# Это директория с шаблонами тестов (если вы их разместите в той же директории что и лабы пишите ./)
EXECUTABLES=$(SOURCES:.c=.a)
BASH=bash


SUCCESS_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_cmd
FAILED_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/failed_cmd

SUCCESS_RFILE_CMD=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_cmd

SUCCESS_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ofile
FAILED_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ofile

SUCCESS_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_rfile_ofile

SUCCESS_IFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ifile_ofile
SUCCESS_IFILE_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/success_ifile_rfile_ofile
FAILED_IFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ifile_ofile
FAILED_IFILE_RFILE_OFILE=$(BASH) $(TEST_TEMPLATES_DIR)/failed_ifile_rfile_ofile


.PHONY: all test clean

all: $(EXECUTABLES) # Чтобы собрать все лабы надо ввести команду make

%.a : %.c
	$(CC) $(CFLAGS) $< $(CLIBS) -o $@

clean: # Чтобы удалить все исполняемые файлы надо ввести команду make clean
	rm -r -f *.a


# Принцип формирования названия выполняемого теста:
#
# (SUCESS|FAILED)[_IFILE][_RFILE](CMD|OFILE)
#		 1			2		3		 4
#
# 1){ОБЯЗАТЕЛЬНЫЙ} В зависимости от предполагаемого окончания теста мы выбираем либо успешный вариант - SUCCESS, либо провальный - FAILED 
# 2){ОПЦИОНАЛЬНЫЙ} При необходимости ввода в консоль программы (использвуя scanf или аналоги) добавляется суффикс _IFILE
# 3){ОПЦИОНАЛЬНЫЙ} Если программа предполагает наличие выходного файла с данными добавляется суффикс _RFILE
# 4){ОБЯЗАТЕЛЬНЫЙ} В зависимости от того однострочный или многострочный вывод в консоль ожидается у программы выбираем окончание CMD - для однострочного вывода и OFILE для многострочного
#


# Все тесты разделены на категории по результату работы программы и формату ввода:
#
# В случае если ввод в программу только с помощью аругментов командной строки:
# 	В случае если вывод в консоль у программы однострочный:
# 		1) Успешный с выводом в консоль (вывод сравнивается со строкой) - $(SUCCESS_CMD)
# 		2) Провальный с выводом в консоль (вывод сравнивается со строкой) - $(FAILED_CMD)
# 		3) Успешный с выводом в консоль и в файл (вывод сравнивается со строкой, а выходной файл с подготовленным файлом) - $(SUCCESS_RFILE_CMD)
#	
# 	В случае если вывод в консоль у программы многострочный:
# 		1) Успешный с выводом в консоль (вывод сравнивается со строками из файла) - $(SUCCESS_OFILE)
# 		2) Провальный с выводом в консоль (вывод сравнивается со строками из файла) - $(FAILED_OFILE)
# 		3) Успешный с выводом в консоль и в выходной файл (вывод сравнивается со строками из файла, а выходной файл с подготовленным файлом) - $(SUCCESS_RFILE_OFILE)
#
# В случае если ввод в консоль программы осуществляется из подготовленного файла а вывод у программы многострочный:  
# 	1) Успешный с вводом из файла, выводом в консоль (вывод сравнивается со строками из файла) - $(SUCCESS_IFILE_OFILE)
# 	2) Успешный с водом из файла, выводом в консоль и выходной файл (вывод сравнивается со строками из файла, а выходной файл с подготовленным файлом) - $(SUCCESS_IFILE_RFILE_OFILE)
# 	3) Провальный с вводом из файла, выводом в консоль (вывод сравнивается со строками из файла) - $(FAILED_IFILE_OFILE)
#


# Использование тестов:
#
# 1) $(SUCCESS_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый в консоль вывод>"
# 2) $(FAILED_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<ожидаемый в консоль вывод>"
# 3) $(SUCCESS_RFILE_CMD) "<вызов исполняемого файла с его аргументами>" "<ожидаемый в консоль вывод>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
#
# 1) $(SUCCESS_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл с ожидаемым в консоль выводом>"
# 2) $(FAIED_OFILE) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<файл с ожидаемым в консоль выводом>"
# 3) $(SUCCESS_RFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл с ожидаемым в консоль выводом>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
# 
# 1) $(SUCCESS_IFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>" 
# 2) $(SUCCESS_IFILE_RFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>" "<выходной файл>" "<файл с которым должен совпадать выходной файл>"
# 3) $(FAILED_IFILE_OFILE) "<вызов исполняемого файла с его аргументами>" "<ожидаемый код возврата отличный от 0>" "<файл данными которые вводятся в консоль через stdin>" "<файл с ожидаемым в консоль выводом>"



#
# Ниже приведены примеры тестов. В выводе после теста должна быть краткая информация о том что это был за тест. "TEST N PASSED" это не информативно и принято не будет.
# Символ @ необходимо писать для подавления лишнего вывода в консоль при выполнении make файла.
#  


test_failed_1:
	@$(FAILED_IFILE_OFILE) "task2_7.a" 1 "7i_2.txt" "7_2.txt"
	@echo "TEST 1: PASS WITH WRONG LOWER BOUND SUCCESS"

test_failed_2:
	@$(FAILED_IFILE_OFILE) "task2_7.a" 1 "7i_3.txt" "7_3.txt"
	@echo "TEST 1: PASS WITH WRONG EPSILON SUCCESS"


test_success: test_success_1 test_success_2 test_success_3 test_success_4 test_success_5 test_success_6

test_success_1:
	@$(SUCCESS_IFILE_OFILE) "task2_7.a" "7i.txt" "7.txt"
	@echo "TEST 1: PASS WITH RIGHT ARGUMENTS FOR FUNC1 SUCCESS"

test_success_2:
	@$(SUCCESS_IFILE_OFILE) "task2_7.a" "7i_5.txt" "7_5.txt"
	@echo "TEST 1: PASS WITH RIGHT ARGUMENTS FOR FUNC2 SUCCESS"

test_success_3:
	@$(SUCCESS_IFILE_OFILE) "task2_7.a" "7i_6.txt" "7_6.txt"
	@echo "TEST 1: PASS WITH RIGHT ARGUMENTS FOR FUNC3 SUCCESS"

test_success_4:
	@$(SUCCESS_IFILE_OFILE) "task2_7.a" "7i_7.txt" "7_7.txt"
	@echo "TEST 1: PASS WITH RIGHT ARGUMENTS FOR FUNC4 SUCCESS"

test_success_5:
	@$(SUCCESS_IFILE_OFILE) "task2_7.a" "7i_8.txt" "7_8.txt"
	@echo "TEST 1: PASS WITH RIGHT ARGUMENTS FOR FUNC5 SUCCESS"

test_success_6:
	@$(SUCCESS_IFILE_OFILE) "task2_7.a" "7i_9.txt" "7_9.txt"
	@echo "TEST 1: PASS WITH RIGHT ARGUMENTS FOR FUNC6 SUCCESS"



test:  test_failed_1 test_failed_2 test_success



# test_task_2: test_command_args_2 test_success_task_2


# test_command_args_2:
# 	@$(FAILED_CMD) "task_2.a" 2 "Incorrect args count"
# 	@echo "TEST 4 PASSED"

# test_success_task_2:
# 	@$(SUCCESS_RFILE_CMD) "task_2.a ./input_file_for_task_2.txt ./output_file_for_task_2.txt" "" "./output_file_for_task_2.txt" "expected_data_for_task_2.txt"
# 	@echo "TEST 5 PASSED"

# test_task_3: test_command_args_3 test_success_task_3


# test_command_args_3:
# 	@$(FAILED_CMD) "task_3.a" -1 "Incorrect args count"
# 	@echo "TEST 6 PASSED"


# test_success_task_3:
# 	@$(SUCCESS_CMD) "task_3.a 1 2" "argv_1+argv_2=3"
# 	@echo "TEST 7 PASSED"

# test: test_task_1 test_task_2 test_task_3 # Здесь перечисляются все написанные вами тесты. Запуск тестов производится по команде make test
	