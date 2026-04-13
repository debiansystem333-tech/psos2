INCLUDES := -I. -I../../.. -I../cpu
CFLAGS   := -g -ffreestanding -nostdlib -fno-pic -fno-stack-protector -m32 $(INCLUDES)

all: paging.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
