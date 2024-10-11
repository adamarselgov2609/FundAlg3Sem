TARGET = 1


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g


SRC = 1.c


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)


test: $(TARGET)
	@echo "Запуск тестов..."
	./run_tests.sh


clean:
	rm -f $(TARGET) *.o

.PHONY: test clean
