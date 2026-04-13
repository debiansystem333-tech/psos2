CFLAGS := -g -ffreestanding -nostdlib -fno-pic -fno-stack-protector -m32 -I.

all: pmm.o mem.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
