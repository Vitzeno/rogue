CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -lncurses

SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c

all : rogue
rogue:
	$(CC) $(SOURCES) $(CFLAGS) -o $@
run:
	./rogue