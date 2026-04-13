#include "pic.h"

void pic_remap(uint8_t offset1, uint8_t offset2) {
  uint8_t mask1 = inb(PIC1_DATA);
  uint8_t mask2 = inb(PIC2_DATA);

  outb(PIC1_CMD, PIC_ICW1_INIT | PIC_ICW1_ICW4);
  io_wait();
  outb(PIC2_CMD, PIC_ICW1_INIT | PIC_ICW1_ICW4);
  io_wait();

  outb(PIC1_DATA, offset1);
  io_wait();
  outb(PIC2_DATA, offset2);
  io_wait();

  outb(PIC1_DATA, 0x04);
  io_wait();
  outb(PIC2_DATA, 0x02);
  io_wait();

  outb(PIC1_DATA, PIC_ICW4_8086);
  io_wait();
  outb(PIC2_DATA, PIC_ICW4_8086);
  io_wait();

  outb(PIC1_DATA, mask1);
  outb(PIC2_DATA, mask2);
}

void pic_send_eoi(uint8_t irq) {
  if (irq >= 8) {
    outb(PIC2_CMD, PIC_EOI);
  }
  outb(PIC1_CMD, PIC_EOI);
}

void pic_mask_irq(uint8_t irq) {
  uint16_t port;
  uint8_t val;

  if (irq < 8) {
    port = PIC1_DATA;
  } else {
    port = PIC2_DATA;
    irq -= 8;
  }

  val = inb(port) | (1 << irq);
  outb(port, val);
}

void pic_unmask_irq(uint8_t irq) {
  uint16_t port;
  uint8_t val;

  if (irq < 8) {
    port = PIC1_DATA;
  } else {
    port = PIC2_DATA;
    irq -= 8;
  }

  val = inb(port) & ~(1 << irq);
  outb(port, val);
}

void pic_disable(void) {
  outb(PIC1_DATA, 0xFF);
  outb(PIC2_DATA, 0xFF);
}
