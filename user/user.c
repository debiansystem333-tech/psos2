#include <stdint.h>

uint32_t strlen(const char *string) {
  uint32_t len=0;
  while (*string != '\0'){ len++; string++;}
  return len;
}
void user_main(void) {
  volatile char *v = (volatile char *)0xB8000;


  const char *user_string = "USER MODE\0";
  uint32_t len = strlen(user_string);
  for (int i = 0; i < len; i++) {
    v[160+(i*2)] = user_string[i];
    v[160+(i*2)+1] = 0x07;
  }
  // __asm__("int $0x30");
  // __asm__("int $0x31");
  // while (1)
    // ;
 // __asm__ ("pause");
  uint32_t * addr = (uint32_t*)0x800000;
  *addr = 1;
  __asm__ ("int $0x32"); 
  for(;;);
  __builtin_unreachable();
}
