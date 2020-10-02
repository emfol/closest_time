CFLAGS := -std=c89 -Wall -Wpedantic
CC := cc
SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=%.o)
BIN := closest_time.bin

.PHONY: test clean

$(BIN): $(OBJ)
	$(CC) -o $@ $^

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $<

test: $(BIN)
	./test.sh

clean:
	rm -f $(BIN) $(OBJ)
