TARGET = 1

CC = gcc
CFLAGS = -Wall -Wextra -g


all: $(TARGET)

$(TARGET): 1.c
	$(CC) $(CFLAGS) 1.c -o $(TARGET)


clean:
	rm -f $(TARGET)


test: $(TARGET)
	./test.sh

.PHONY: all clean test
