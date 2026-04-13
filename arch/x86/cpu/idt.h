#ifndef IDT_H
#define IDT_H
#include <stdint.h>

#define IDT_ENTRIES 256

struct idt_entry {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t type_attr;
  uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

void idt_init(void);
void set_idt_entry(int n, uint32_t handler, uint16_t selector, uint8_t type);

/* ISR (assembly) */
extern void isr_page_fault(void);
extern void isr_double_fault(void);
extern void isr_protection_fault(void);
extern void isr_timer(void);
extern void isr_my_interrupt(void);
extern void isr_my_interrupt2(void);
extern void isr_my_interrupt3(void);
extern void isr_invalid_opcode(void);
#endif
