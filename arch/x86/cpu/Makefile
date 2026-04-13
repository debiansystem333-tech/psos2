INCLUDES := -I. -I../../..
CFLAGS   := -g -ffreestanding -nostdlib -fno-pic -fno-stack-protector -m32 $(INCLUDES)
ASFLAGS  := --32 -g
OBJS := gdt.o gdt_flush.o idt.o isr.o

all: $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.S
	as $(ASFLAGS) $< -o $@

clean:
	rm -f *.o

.PHONY: all clean
