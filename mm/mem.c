#include "mem.h"
#include <stdint.h>
inline void memset32(void *addr, uint32_t val, uint32_t count) {
  __asm__ volatile("rep stosl" : "+D"(addr), "+c"(count) : "a"(val) : "memory");
}
