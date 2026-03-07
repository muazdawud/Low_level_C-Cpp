# Serial Organ Control System
**Author:** Dauda M. S.  
**GitHub:** [muazdawud](https://github.com/muazdawud)

* May include header files made by **Elliot Williams**, which I'm using his book btw.

---

## Description
This is a custom-built **Serial Organ** implemented in bare-metal C for AVR microcontrollers. The system turns your PC keyboard into a musical piano by intercepting keystrokes via UART and translating them into precise frequencies. 

The project features a dedicated `scaleGenerator.cpp` utility that calculates the necessary timer constants to ensure musical accuracy across multiple octaves.

---

## Features
* **Low Latency:** Direct register access for near-instantaneous sound generation.
* **Three Octave Range:** Supports a wide array of notes from **D5** to **D8**.
* **Dynamic Duration:** Real-time switching between "Long" and "Short" notes using dedicated toggle keys.
* **Visual Debugging:** Returns serial feedback (`_` for long, `-` for short) to the terminal to confirm mode changes.
* **Custom Scale Engine:** Includes pre-calculated values for sharps and standard notes.

---

## Hardware Configuration


| Component | Connection |
| :--- | :--- |
| **MCU** | ATmega328P (or compatible AVR) |
| **Output** | Piezo Buzzer / Speaker on `SPEAKER` pin / `PD6`|
| **Input** | USB-to-UART (FTDI / CH340) |
| **Baud Rate** | Set in `USART.h` (Standard 9600) |

---

## Controls & Mapping
Open your serial terminal (TeraTerm, PuTTY, or Screen) and use the following keys:

### Musical Notes
The notes are mapped across the QWERTY layout for ergonomic playability:
* **Top Row (`q` to `p`):** Lower Octave (D5 - Dx6)
* **Middle Row (`a` to `'`):** Middle Octave (D6 - Dx7)
* **Bottom Row (`z` to `.`):** Upper Octave (F7 - Dx8)

### System Commands
| Key | Function | Feedback |
| :--- | :--- | :--- |
| `[` | **Set Long Duration** | `_` |
| `]` | **Set Short Duration** | `-` |
| *Other* | **System Sleep** | N/A |

---

## Project Structure
* `main.c` - Primary application logic and UART polling.
* `scale.h` - Generated frequency definitions (Timer counts).
* `scaleGenerator.cpp` - Independent tool for calculating frequency-to-timer constants.
* `player.h/c` - Hardware abstraction layer for the piezo driver.
* `USART.h/c` - Bare-metal UART communication library.
* `pinDefines.h` - Hardware-specific pin mappings.

---

## Build & Flash Instructions
Ensure you have the `avr-gcc` toolchain installed.

1. **Compile the source:**
   ```bash
   avr-gcc -mmcu=atmega328p -Wall -Os -o organ.elf main.c USART.c player.c
   ````
2. **Generate Intel HEX file:**
   ````bash
   avr-objcopy -j .text -j .data -O ihex organ.elf organ.hex
   ````
3. **Upload to hardware:**
   ````bash
   avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:organ.hex
   ````

---

## **Developed as part of a Mechatronics Engineering exploration into embedded audio systems.