#! /bin/bash
CC=gcc

# Compiler flags
CFLAGS = -Wall

# Libraries to link against
LIBS = -lrt

# Name of output executable
TARGET = timer

# Source and Object Files
SRC = timerlib.c timerlib_test.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET)
