#include "idt.h"
#include "com1.h"
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

void set_idt_entry(int vector, uint32_t handler, uint16_t selector,
                   uint8_t type) {
  idt[vector].offset_low = handler & 0xFFFF;
  idt[vector].selector = selector; // code segment
  idt[vector].zero = 0x0;
  idt[vector].type_attr = type;
  idt[vector].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init(void) {
  idtp.limit = sizeof(idt) - 1;
  idtp.base = (uint32_t)&idt;
  for (uint32_t i = 0; i < IDT_ENTRIES; i++) {
    idt[i].offset_low = 0;
    idt[i].selector = 0;
    idt[i].zero = 0;
    idt[i].type_attr = 0;
    idt[i].offset_high = 0;
  }

  set_idt_entry(0x06, (uint32_t)isr_invalid_opcode, 0x08, 0x8E);
  set_idt_entry(0x08, (uint32_t)isr_double_fault, 0x08, 0x8E);
  set_idt_entry(0x0D, (uint32_t)isr_protection_fault, 0x08, 0x8E);
  set_idt_entry(0x0E, (uint32_t)isr_page_fault, 0x08, 0x8E);
  set_idt_entry(0x20, (uint32_t)isr_timer, 0x08, 0x8E);
  set_idt_entry(0x30, (uint32_t)isr_my_interrupt, 0x08, 0xEE);
  set_idt_entry(0x31, (uint32_t)isr_my_interrupt2, 0x08, 0xEE);
  set_idt_entry(0x32, (uint32_t)isr_my_interrupt3, 0x08, 0xEE);
  __asm__ volatile("lidt %0" ::"m"(idtp));
}
