CFLAGS := -ffreestanding -nostdlib -fno-pic -fno-stack-protector -m32 -I.

all: pic.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
