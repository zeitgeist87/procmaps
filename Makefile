TARGET := test/procmaps_test

CC := c99
LINKER := c99
CFLAGS := -std=c99 -pedantic -Wall -Wextra -g -O1 -I.

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
