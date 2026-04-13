#pragma once

typedef unsigned int __base32;
#define PS        4096
#define RAM_TOP   0x20000000

#define ALIGN_UP(addr, size) (((addr) + (size) - 1) & ~((size) - 1))
extern __base32 base;
__base32 alloc_page();
void free_page(__base32 page);
