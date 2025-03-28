CC := gcc
CFLAGS := -Wall -Wextra -g
LDFLAGS := -lpthread
TARGET := pmutex_test
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
