# Memory Management
This project demonstrates common memory-related errors in C/C++:

* Stack Overflow
* Memory Leak
* Out of Memory

It is intended for learning and experimenting with how these issues behave at runtime.

## Requirements
* Linux environment (recommended).
* GCC compiler.

Install GCC on Ubuntu:
```bash
sudo apt update
sudo apt install gcc
```

## Build
Inside the memory_management folder, compile the program:
```bash
gcc memory_lab.c -o memory_lab.out
```

# Usage
Run the program with one of the available commands:
```bash
./memory_lab.out <command>
```
Available commands:

* memory_leak → simulate memory leak
* stack_overflow → trigger stack overflow
* out_of_memory → exhaust heap memory

# Examples
Run the program with each mode:
```bash
# Memory leak example
./memory_lab.out memory_leak

# Stack overflow example
./memory_lab.out stack_overflow

# Out of memory example
./memory_lab.out out_of_memory
```

# Notes
⚠️ Warning: These programs are designed to intentionally cause memory errors.
* Running stack_overflow will crash the program.
* memory_leak and out_of_memory may consume large amounts of memory and slow down your system.

