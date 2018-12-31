CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -lncurses -I$(IDIR)

SRCDIR = ./src/
IDIR = ./include/
SOURCES = $(SRCDIR)*.c

all : rogue run clean
rogue:
	$(CC) $(SOURCES) $(CFLAGS) -o $@
run:
	./rogue
clean:
	rm -f rogue