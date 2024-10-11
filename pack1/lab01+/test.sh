#!/bin/bash

run_test() {
    echo "Тестирование с аргументами: $@"
    output=$(./1 "$@" 2>&1) 
    echo "$output"
    echo "---------------------------------"
}


check_output() {
    local expected="$1"
    local output="$2"
    
    if [[ "$output" == *"$expected"* ]]; then
        echo "Тест пройден: Ожидалось \"$expected\""
    else
        echo "Тест не пройден: Ожидалось \"$expected\", но получено \"$output\""
    fi
}

run_test 5 -h  
output=$(./1 5 -h)
check_output "Числа, кратные 5" "$output"

run_test 7 -p 
output=$(./1 7 -p)
check_output "7 является простым числом" "$output"

run_test 10 -s 
output=$(./1 10 -s)
check_output "Цифры в 16-ричной системе:" "$output"

run_test 3 -e 
output=$(./1 3 -e)
check_output "Основание" "$output"

run_test 15 -a  
output=$(./1 15 -a)
check_output "Сумма чисел от 1 до 15" "$output"

run_test 5 -f 
output=$(./1 5 -f)
check_output "Факториал 5:" "$output"


echo "Тестирование некорректных аргументов:"
run_test  #
output=$(./1)
check_output "Ошибка: Неверные аргументы." "$output"

run_test 123 "invalid_flag"  
output=$(./1 123 "invalid_flag")
check_output "Ошибка: Неизвестный флаг" "$output"

run_test -1 -h  
output=$(./1 -1 -h)
check_output "Ошибка: Неверные аргументы." "$output"

run_test "123asdadqwe" -h 
output=$(./1 "123asdadqwe" -h)
check_output "Ошибка: Неверные аргументы." "$output"

run_test 3 
output=$(./1 3)
check_output "Ошибка: Неверные аргументы." "$output"


run_test -5 -p 
output=$(./1 -5 -p)
check_output "Ошибка: Неверные аргументы." "$output"
