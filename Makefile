CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lpthread
TARGET = pmutex_test
SRC_DIR = src
SRC = $(SRC_DIR)/pmutex.c $(SRC_DIR)/main.c

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
    rm -f $(TARGET)

.PHONY: all clean
