
#pragma once

#define VGA_BASE 0xB8000
#define WIDTH 80
#define HEIGHT 25

static unsigned short row = 0;
static unsigned short col = 0;

static unsigned char *vga;
void vga_init() { vga = (unsigned char *)VGA_BASE; }
static void __putc(char c, char color_code) {
  vga[row * WIDTH + col] = c;
  vga[row * WIDTH + col + 1] = color_code;
  col++;
  if (col > WIDTH) {
    row++;
  }
}
