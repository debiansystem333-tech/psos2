#pragma once

#include <stdint.h>

void page_fault_handler_c(uint32_t error_code);
void protection_fault_handler_c(uint32_t error_code);
void double_fault_handler_c(uint32_t error_code);
