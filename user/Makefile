INCLUDES := -I. -I.. -I../arch/x86/cpu
CFLAGS   := -g -ffreestanding -nostdlib -fno-pic -fno-stack-protector -m32 $(INCLUDES)

all: enter_user.o user.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
