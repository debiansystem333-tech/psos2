.globl isr_invalid_opcode
.globl isr_page_fault
.globl isr_double_fault
.globl isr_protection_fault
.globl isr_my_interrupt
.globl isr_my_interrupt2
.globl isr_my_interrupt3
.globl isr_timer

isr_page_fault:
  cli
  pusha
  mov 0x20(%esp), %eax
  push %eax
  call page_fault_handler_c
  add $4, %esp
  popa
  add $4, %esp
  iret

isr_double_fault:
  cli
  pusha
  mov 0x20(%esp), %eax
  push %eax
  call double_fault_handler_c
  add $4, %esp
  popa
  add $4, %esp
.Lhalt:
  hlt
  jmp .Lhalt

isr_protection_fault:
  cli
  pusha
  mov 0x20(%esp), %eax
  push %eax
  call protection_fault_handler_c   # fixed: was double_fault_handler_c
  add $4, %esp
  popa
  add $4, %esp
  iret
isr_invalid_opcode:
	pusha
	call invalid_opcode_handler_c
	popa
	iret
isr_timer:
  cli
  pusha
  call timer_handler_c
  movb $0x20, %al
  outb %al, $0x20                   # EOI only here
  popa
  iret                              # iret restores IF from stack, no sti needed

isr_my_interrupt:
  cli
  pusha
  call custom_0x30_handler
  popa
  iret

isr_my_interrupt2:
	pusha
	call custom_0x31_handler
	popa
	iret
isr_my_interrupt3:
	pusha
	call custom_0x32_handler
	popa
	iret
