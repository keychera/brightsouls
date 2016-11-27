CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-g -lm

SOURCES=$(wildcard ./*.c)
OBJECTS=$(SOURCES:.c=.o)
MAIN=./brightsoul.c
EXECUTABLE=./brightsouls

.PHONY: all bin test clean


all: bin

bin: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(OBJECTS)
	-rm $(EXECUTABLE)
