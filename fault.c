#include "fault.h"
#include "com1.h"
#include "idt.h"
#include "mem.h"
#include "paging.h"
#include "pic.h"
#include "pmm.h"
// static inline void outb(uint16_t port, uint8_t val) {
//   __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
// }
void page_fault_handler_c(uint32_t error_code) {
  uint32_t faddr;
  __asm__ volatile("mov %%cr2, %0" : "=r"(faddr));
  page_dir_entry_t pd_index = (faddr >> 22);
  page_table_entry_t pt_index = (faddr >> 12) & 0x3FF;
  int user = (error_code >> 2) & 1;
  int present = error_code & 1;
  uint32_t *page_table;
  if (user) {
    if (!(page_dir[pd_index] & PAGE_PRESENT)) {
      uint32_t *new_page = (uint32_t *)alloc_page();
      memset32(new_page, 0, 1024);
      page_dir[pd_index] =
          ((uint32_t)new_page) | PAGE_PRESENT | PAGE_RW | PAGE_USER;
    }
    page_table = (uint32_t *)(page_dir[pd_index] & 0xFFFFF000);
    page_dir[pd_index] |= PAGE_USER;
    if (present) {
      page_table[pt_index] |= PAGE_USER;
    } else {
      uint32_t *frame = (uint32_t *)alloc_page();
      page_table[pt_index] =
          ((uint32_t)frame) | PAGE_PRESENT | PAGE_RW | PAGE_USER;
    }
    __asm__ volatile("invlpg (%0)" ::"r"(faddr));
    puts("user fault handled");
    return;
  }

  // === KERNEL FAULT ===

  if (!(page_dir[pd_index] & PAGE_PRESENT)) {
    uint32_t *new_page = (uint32_t *)alloc_page();
    memset32(new_page, 0, 1024);
    page_dir[pd_index] =
        ((uint32_t)new_page) | PAGE_PRESENT | PAGE_RW | PAGE_USER;
  }
  page_table = (uint32_t *)(page_dir[pd_index] & 0xFFFFF000);
  if (!present) {
    uint32_t *newframe = (uint32_t *)alloc_page();
    page_table[pt_index] =
        ((uint32_t)newframe) | PAGE_PRESENT | PAGE_RW | PAGE_USER;
    __asm__ volatile("invlpg (%0)" ::"r"(faddr));
  } else {
    puts("kernel protection fault");
    for (;;)
      ;
  }
  puts("kernel fault handled");
}

void double_fault_handler_c(uint32_t error_code) {
  (void)error_code;
  puts("DF");
  __asm__ volatile("hlt");
}
void protection_fault_handler_c(uint32_t error_code) {
  (void)error_code;
  puts("PFA");
  __asm__ volatile("hlt");
}

// static uint32_t ticks = 0;
void timer_handler_c(void) {
  // ticks++;
  pic_send_eoi(IRQ_TIMER);
}

void custom_0x30_handler(void) { puts("mi"); }
void custom_0x31_handler(void) { puts("mi2"); }
void custom_0x32_handler(void) {
  puts("mi2");
  __asm__("hlt");
}
void invalid_opcode_handler_c(void) {
  puts("iv");
  __asm__("hlt");
}
