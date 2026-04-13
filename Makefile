NAME := Malinga RK
RED   := \033[1;31m
RESET := \033[0m
GREEN := \033[1;32m
ARCH := x86

OBJS := \
    arch/x86/boot/boot.o \
    arch/x86/cpu/gdt.o \
    arch/x86/cpu/gdt_flush.o \
    arch/x86/cpu/idt.o \
    arch/x86/cpu/isr.o \
    arch/x86/mm/paging.o \
    drivers/pic/pic.o \
    drivers/serial/com1.o \
    mm/pmm.o \
    mm/mem.o \
    user/enter_user.o \
    user/user.o \
    kernel.o \
    fault.o

INCLUDES := -I. -Iarch/x86/cpu -Iarch/x86/mm -Idrivers/pic \
            -Idrivers/serial -Imm -Iuser

CFLAGS  := -g -ffreestanding -nostdlib -fno-pic -fno-stack-protector -m32 $(INCLUDES)
ASFLAGS := --32 -g

all: boot.bin boot.elf
		 @echo "[build] author: $(NAME)"

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.S
	as $(ASFLAGS) $< -o $@

boot.bin: $(OBJS)
	ld -m elf_i386 -T linker.ld --oformat binary $(OBJS) -o boot.bin
	@SIZE=$$(wc -c < boot.bin); \
		 SECTORS=$$(( ($$SIZE + 511) / 512 - 1)); \
		 echo "[build] binary: $$SIZE bytes ($(GREEN)$$SECTORS sectors$(RESET))"; \
		 if [ $$SECTORS -gt 9 ]; then \
		     echo "$(RED)[WARN] approaching 8-sector limit, increase boot.S sector count$(RESET)"; \
		 fi
boot.elf: $(OBJS)
	ld -m elf_i386 -T linker.ld $(OBJS) -o boot.elf

run:
	qemu-system-i386 -smp 2 -drive format=raw,file=boot.bin \
	    -m 128M -no-reboot -d int
run2:
	qemu-system-i386 -smp 2 -drive format=raw,file=boot.bin \
	    -m 128M

run-nox:
	qemu-system-i386 -smp 2 -drive format=raw,file=boot.bin \
	    -m 128M -no-reboot -d int -nographic
run-gdb:
	qemu-system-i386 -smp 2 -drive format=raw,file=boot.bin \
	    -m 128M -no-reboot -d int -nographic -s -S
clean:
	find . -name "*.o" -delete
	rm -f boot.bin boot.elf

.PHONY: all run run-nox clean
