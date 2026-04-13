

# .include "arch/x86/boot/kernel_sectors.inc"
.code16
.text
.set SECTORS, 9
.globl _start

_start:
  cli
  movw $0x00, %ax
  movw %ax, %ss
  movw %ax, %es
  movw %ax, %ds
  movw $0x7c00, %sp


  mov $0x02, %ah
  mov $SECTORS, %al
  mov $0x00, %ch
  mov $0x02, %cl
  mov $0x00, %dh
  mov $0x7e00, %bx
  int $0x13
  jc disk_err
  lgdt gdt
  movl %cr0, %eax
  orl $1, %eax
  movl %eax, %cr0

  ljmp $0x08, $pmode

.code32
.extern kmain
pmode:
  movw $0x10, %ax
  movw %ax, %ss
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movl $0x90000, %esp
  call kmain
  movl $0xb8000, %edi
  movb $0x49, %al
  movb %al, (%edi)
  movb $0x17, 0x1(%edi)

hang:
  hlt
  jmp hang
disk_err:
  mov $0x45, %al
  mov $0x0e, %ah
  int $0x10
  jmp hang
.align 8
gdt_start:
	.quad 0x0000000000000000
	.quad 0x00CF9A000000FFFF
	.quad 0x00CF92000000FFFF
	.quad 0x00CFFA000000FFFF
	.quad 0x00CFF2000000FFFF
gdt_end:
gdt:
  .word gdt_end - gdt_start - 1
  .long gdt_start

# dap:
# 	.byte 0x10
# 	.byte 0x00
# 	.word SECTORS
# 	.word 0x7e00
# 	.word 0x0000
# 	.quad 1
.org 510
.byte 0x55, 0xaa
