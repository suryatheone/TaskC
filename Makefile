CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/task.c
OBJ = $(SRC:.c=.o)
TARGET = build/main

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

test:
	@echo "No test implemented yet"

clean:
	rm -rf build/*

.PHONY: all clean test
