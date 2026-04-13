#include "gdt.h"

struct gdt_entry gdt[6];
struct gdt_ptr gp;
struct tss_entry tss;

void gdt_set_gate(int i, uint32_t base, uint32_t limit, uint8_t access,
                  uint8_t gran) {
  gdt[i].base_low = base & 0xFFFF;
  gdt[i].base_mid = (base >> 16) & 0xFF;
  gdt[i].base_high = (base >> 24) & 0xFF;

  gdt[i].limit_low = limit & 0xFFFF;
  gdt[i].gran = (limit >> 16) & 0x0F;

  gdt[i].gran |= gran & 0xF0;
  gdt[i].access = access;
}

void write_tss(int i, uint16_t ss0, uint32_t esp0) {
  uint32_t base = (uint32_t)&tss;
  uint32_t limit = sizeof(struct tss_entry);

  gdt_set_gate(i, base, limit, 0x89, 0x40);

  // zero TSS
  for (int j = 0; j < sizeof(struct tss_entry) / 4; j++)
    ((uint32_t *)&tss)[j] = 0;

  tss.ss0 = ss0;
  tss.esp0 = esp0;
}

void gdt_init(void) {
  gp.limit = sizeof(gdt) - 1;
  gp.base = (uint32_t)&gdt;

  // null
  gdt_set_gate(0, 0, 0, 0, 0);

  // kernel
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data

  // user (DPL=3)
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // code
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // data

  // TSS (index 5)
  write_tss(5, 0x10, 0x90000);

  gdt_flush((uint32_t)&gp);
  tss_flush();
}
