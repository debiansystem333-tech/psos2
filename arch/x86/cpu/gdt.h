#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct __attribute__((packed)) gdt_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access;
  uint8_t gran;
  uint8_t base_high;
};

struct __attribute__((packed)) gdt_ptr {
  uint16_t limit;
  uint32_t base;
};

struct __attribute__((packed)) tss_entry {
  uint32_t prev_tss;
  uint32_t esp0;
  uint32_t ss0;
  uint32_t unused[23];
};

void gdt_init(void);
void gdt_set_gate(int i, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran);

void write_tss(int i, uint16_t ss0, uint32_t esp0);

extern void gdt_flush(uint32_t);
extern void tss_flush(void);

#endif
