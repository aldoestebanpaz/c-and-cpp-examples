TARGET = no-libc-example

CSOURCES = $(wildcard *.c)
SSOURCES = $(wildcard *.S)

OBJECTS = $(CSOURCES:.c=_c.o)
OBJECTS += $(SSOURCES:.S=_s.o)

CC = gcc
LD = ld
LDFLAGS = -nostdlib
CFLAGS = -nostdlib -Wall -g -ffreestanding
# -no-pie

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%_c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%_s.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o $(TARGET)
