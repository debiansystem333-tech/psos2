#include "com1.h"
#include "enter_user.h"
#include "gdt.h"
#include "idt.h"
#include "mem.h"
#include "paging.h"
#include "pic.h"
#include "pmm.h"
void kmain(void) {
  __asm__("cli");

  gdt_init();
  idt_init();
  paging_init();

  pic_remap(PIC1_OFFSET, PIC2_OFFSET);

  // mask all, then unmask only timer
  outb(PIC1_DATA, 0xFE); // IRQ0 enabled
  outb(PIC2_DATA, 0xFF);
  pic_disable();
  pic_mask_irq(IRQ_TIMER);
  enter_user_mode();
  __asm__("sti");

  // enter_user_mode();

  __asm__ volatile("int $0x30");
  puts("resumed");
  for (;;)
    __asm__ volatile("hlt");
}
// void kmain(void) {
//   __asm__("cli");
//
//   gdt_init();
//   idt_init();
//
//   // === paging should be HERE
//   paging_init();
//
//   pic_remap(PIC1_OFFSET, PIC2_OFFSET);
//
//   pic_disable();
//   pic_mask_irq(IRQ_TIMER);
//
//   __asm__("sti");
//
//   puts("halting...");
//   // pic_unmask_irq(IRQ_TIMER);
//
//   __asm__("hlt");
//
//   puts("woke up");
//
//   for (;;)
//     __asm__ volatile("hlt");
// }
