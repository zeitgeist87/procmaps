TARGET := procmaps

CC := gcc
LINKER := gcc
INCDIRS := -I.
CFLAGS := -std=c99 -ansi -pedantic -Wall -Wextra -g -O1

SRCFILES := $(wildcard *.c)
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(LINKER) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@


clean:
	rm -f $(OBJFILES) $(TARGET)