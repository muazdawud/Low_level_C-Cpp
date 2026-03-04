# Low_level_C-Cpp
> **Direct Register AVR Development | ATmega328P**

A high-performance repository for bare-metal C/C++ experiments on the AVR architecture. This project bypasses the Arduino abstraction layer to interface directly with silicon via memory-mapped I/O.

---

## 🏗️ General Architecture Summary
The system follows a modular, low-level design pattern optimized for 8-bit RISC microcontrollers.

### 1. Hardware Abstraction Layer (HAL)
* **Direct Register Access:** Interfaces with silicon via Special Function Registers (SFRs) using bitwise masks and shifts.
* **Peripheral Drivers:** Decoupled USART, SPI, and I2C drivers designed for low-latency, blocking, or interrupt-driven I/O.
* **Pin Mapping:** Centralized configuration via `pinDefines.h` to ensure code portability across different PCB layouts.

### 2. Execution & Timing
* **Deterministic Logic:** Avoids dynamic memory allocation (`malloc`/`free`) to prevent heap fragmentation.
* **Cycle-Accurate Math:** Utilizes `F_CPU` defined constants and integer-only arithmetic to maintain precise timing for serial and PWM protocols.
* **Polling vs Interrupts:** Implements both "Busy-Wait" polling for simple tasks and "Interrupt Service Routines" (ISRs) for high-frequency background operations.

### 3. Build & Toolchain
* **Compiler:** `avr-gcc` with `-Os` (Optimization for Size) to fit complex logic within limited Flash memory.
* **Linking:** Multi-root linking allows the inclusion of external driver libraries (e.g., `AVR-Programming-Library`) without code duplication.
* **Verification:** Generates `.lst` and `.map` files for manual inspection of the generated assembly and memory usage.
---

## 🛠️ Compilation & Linking
To use headers from the external `AVR-Programming-Library` root without moving files:

```bash
# Compile with Include Path (-I)
avr-gcc -Wall -Os -I../AVR-Programming-Library -mmcu=atmega328p -c main.c
# Link objects
avr-gcc -mmcu=atmega328p main.o USART.o -o main.elf
# Generate Hex
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
```

## 📜 Attribution & License
External Drivers: Based on Elliot Williams' AVR-Programming-Library.

Logic: Custom firmware by muazdawud.

License: MIT Permissive.

