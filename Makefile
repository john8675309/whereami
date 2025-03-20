# Makefile for whereami

CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = whereami
SOURCE = whereami.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin

clean:
	rm -f $(TARGET)
