#include "paging.h"
#include "mem.h"
#include <stdint.h>

page_dir_entry_t page_dir[1024] __attribute__((aligned(4096)));
static page_table_entry_t page_table_0[1024] __attribute__((aligned(4096)));
static page_table_entry_t page_table_1[1024] __attribute__((aligned(4096)));

static void enable_paging(uint32_t pd_phys_addr) {
  __asm__ volatile("mov %0, %%cr3\n\t"
                   "mov %%cr0, %%eax\n\t"
                   "or $0x80000000, %%eax\n\t"
                   "mov %%eax, %%cr0"
                   :
                   : "r"(pd_phys_addr)
                   : "eax");
}

void paging_init() {
  memset32(page_dir, 0, 1024);
  memset32(page_table_0, 0, 1024);
  memset32(page_table_1, 0, 1024);
  for (int i = 0; i < 1024; i++) {
    page_table_0[i] = (i * 0x1000) | PAGE_PRESENT | PAGE_RW;
  }
  page_dir[0] = ((uint32_t)page_table_0) | PAGE_PRESENT | PAGE_RW;
  enable_paging((uint32_t)page_dir);
}
void map_page1() {}
