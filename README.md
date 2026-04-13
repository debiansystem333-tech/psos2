# PSOS2

A bare-metal and low-level systems programming project written primarily in C with Assembly and custom linker scripts. This project demonstrates core operating system concepts and bootloader implementation.

## Overview

PSOS2 is a systems programming project that combines C for high-level logic with Assembly for performance-critical and hardware-specific operations. It includes custom linker scripts for memory management and is designed for educational purposes and embedded systems development.

## Language Composition

- **C** (71.3%) - Core system logic and algorithms
- **Assembly** (12.6%) - Low-level operations, bootloader, and hardware interaction
- **Makefile** (15%) - Build automation and compilation management
- **Linker Script** (1.1%) - Memory layout and linking configuration

## Features

- Bare-metal system programming with bootloader support
- Custom memory management via linker scripts
- Low-level hardware interaction using Assembly
- Modular C codebase for system operations
- Build automation with Make

## Prerequisites

- **Compiler**: GCC or Clang (with cross-compiler support for bare-metal)
- **Assembler**: NASM or GAS (GNU Assembler)
- **Build Tools**: Make
- **Linker**: GNU ld
- **NECESSARY**: QEMU or other emulator for testing bare-metal code

## Installation

1. Clone the repository:
```bash
git clone https://github.com/debiansystem333-tech/psos2.git
cd psos2
