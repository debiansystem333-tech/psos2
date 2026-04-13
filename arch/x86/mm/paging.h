
#pragma once

#include <stdint.h>

#define PAGE_PRESENT (1 << 0)
#define PAGE_RW (1 << 1)
#define PAGE_USER (1 << 2)
#define PAGE_4MB_SIZE (1 << 7)

typedef uint32_t page_dir_entry_t;
typedef uint32_t page_table_entry_t;

extern uint32_t page_dir[1024];
void paging_init(void);
