

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
- Custom memory management
- Low-level hardware interaction using Assembly
- Modular C codebase for system operations
- Build automation with Make

## Prerequisites

- **Compiler**: GCC or Clang (with cross-compiler support for bare-metal)
- **Assembler**: NASM or GAS (GNU Assembler)
- **Build Tools**: Make
- **Linker**: GNU ld
- **Optional**: QEMU or other emulator for testing bare-metal code

## Installation

1. Clone the repository:
```bash
git clone https://github.com/debiansystem333-tech/psos2.git
cd psos2
```

2. Build the project:
```bash
make
```

3. Clean build artifacts:
```bash
make clean
```

## Project Structure

```
psos2/
├── arch/                # main bootloader and related files
├── drivers/             # drivers
├── include/             # Header files
├── linker.ld/           #
├── Makefile             # Build configuration
├── mm/                  # Bootloader code
├── user/                # User code
└── README.md            # This file
```

## Building & Compilation

The project uses a Makefile for build automation. Key targets:

```bash
make              # Build the complete project
make clean        # Remove build artifacts
make run          #
make run-gdb      # 
make run-nox      # 
```

## Usage

## Technical Details

### Bootloader
- Custom assembly bootloader for system initialization
- Memory setup and CPU initialization
- Transition from real mode (if applicable)

### Memory Layout
- Defined via custom linker scripts
- Bare-metal memory segments management
- Stack and heap configuration

### Hardware Abstraction
- Low-level I/O operations in Assembly
- Hardware register access and control
- Interrupt and exception handling (if applicable)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License



## Author

**debiansystem333-tech**

---

Last Updated: April 13, 2026
