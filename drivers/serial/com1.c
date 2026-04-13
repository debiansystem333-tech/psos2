#include "com1.h"
static inline void outb(u16 port, u8 val) {
  __asm__ volatile("outb %0, %1" ::"r"(val), "Nd"(port));
}
void puts(const char *str) {
  while (*str) {
    outb(COM1, *str);
    str++;
  }
}