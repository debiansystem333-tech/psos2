#include "pmm.h"
#include "com1.h"
// __base32 limit= 0x20000000;
__base32 base = 0x300000;

__base32 alloc_page() {
  base = ALIGN_UP(base, PS);
  
  if (base + PS > RAM_TOP) {
    puts("panic! alloc_page()");
    __asm__ volatile("hlt");
  }
  
  __base32 page = base;
  base += PS;
  return page;
}

void free_page(__base32 page) {
  // TODO
}
