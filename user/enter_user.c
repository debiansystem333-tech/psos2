#include <stdint.h>

extern void user_main(void);

void enter_user_mode(void) {
  uint32_t user_stack = 0x80000;

  __asm__ __volatile__("cli\n\t"

                       // load user data segments (RPL=3)
                       "mov $0x23, %%ax\n\t"
                       "mov %%ax, %%ds\n\t"
                       "mov %%ax, %%es\n\t"
                       "mov %%ax, %%fs\n\t"
                       "mov %%ax, %%gs\n\t"

                       // push user SS and ESP
                       "pushl $0x23\n\t"
                       "pushl %[stack]\n\t"

                       // EFLAGS (enable IF)
                       "pushf\n\t"
                       "pop %%eax\n\t"
                       "orl $0x3200, %%eax\n\t"
                       "push %%eax\n\t"

                       // push user CS and EIP
                       "pushl $0x1B\n\t"
                       "pushl %[entry]\n\t"

                       // go to ring 3
                       "iret\n\t"
                       :
                       : [stack] "r"(user_stack), [entry] "r"(user_main)
                       : "eax");
}
