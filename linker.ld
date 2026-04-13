ENTRY(_start)
PHDRS {
  text PT_LOAD FLAGS(5);
  data PT_LOAD FLAGS(6);
}
SECTIONS {
  . = 0x7c00;
  .text : {*(.text)} :text
  . = ALIGN(4);
  .data : {*(.data)} :data
  . = ALIGN(4);
  .bss : {*(.bss)} :data
  }
