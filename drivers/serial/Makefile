CFLAGS := -ffreestanding -nostdlib -fno-pic -fno-stack-protector -m32 -I.

all: com1.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
