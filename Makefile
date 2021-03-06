TARGET := test/procmaps_test

CC := gcc
LINKER := gcc
CFLAGS := -std=c99 -ansi -pedantic -Wall -Wextra -g -O1 -I.

SRCFILES := $(wildcard *.c test/*.c)
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(LINKER) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

check: $(TARGET)
	./test/procmaps_test

clean:
	rm -f $(OBJFILES) $(TARGET)
