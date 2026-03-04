# Low_level_C-Cpp
> **Direct Register AVR Development**

A high-performance repository for bare-metal C/C++ experiments on the AVR architecture. This project bypasses the Arduino abstraction layer to interface directly with silicon via memory-mapped I/O.

---

## 🏗️ Architecture Summary
This project implements and test many kinds of AVR special functions.

* **Baud Rate:** 9600 Baud (Calculated: $UBRR=207$ with $U2X0$ enabled).
* **Clock Speed:** 16 MHz ($16,000,000UL$).
* **I/O Logic:** Maps the high 5 bits of incoming Serial Data to `PORTB` pins.

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