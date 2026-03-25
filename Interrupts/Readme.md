# AVR Embedded Systems: Interrupt Visualizer with LED Pattern Sequencer

This repository contains multiple distinct firmware implementations for the **ATmega328P** (Arduino Uno/Nano compatible) written in AVR C. These projects demonstrate low-level hardware control using **AVR Digital Input**, **Interrupt Service Routines (ISRs)**, **Analog-to-Digital Conversion (ADC)**, and **USART Serial Debugging**.

---

## Hardware Mapping

The following pinout is used across both firmware versions:

| Peripheral | Port Pin | Function |
| :--- | :--- | :--- |
| **LED Array (6)** | `PB0` – `PB5` | Active-High Visual Output |
| **Push Button** | `PD2` (INT0) | External Interrupt (Active-Low) |
| **Potentiometer** | `PC3` (ADC3) | Analog Input |
| **USART TX** | `PD1` | Serial Communication (9600-115200 Baud) |

---

## 2_ISRs: ADC-Controlled LED Bar Graph with multiple ISRs

This program transforms a potentiometer input into a 6-stage LED "thermometer" display. 

### Core Logic
* **On/Off Toggle:** The `INT0` interrupt toggles the `check` flag. When `check` is `0`, all LEDs are disabled.
* **ADC Configuration:**
  - **Left Adjust (`ADLAR`):** Allows reading 8-bit resolution directly from the `ADCH` register.
  - **Auto-Triggering:** Continuously samples the input voltage without manual re-triggering.
* **The Scaling Formula:**
  The 8-bit value from `ADCH` ($0$ to $255$) is mapped to the 6-LED array using:
  $$\text{ADC\_Input} = \left\lfloor \frac{\text{input} \times 6}{256} \right\rfloor + 1$$

### LED Output States
| Scaled Value | PORTB Output (Hex) | LEDs ON |
| :--- | :--- | :--- |
| 1 | `0x01` | PB0 |
| 2 | `0x03` | PB0–PB1 |
| 3 | `0x07` | PB0–PB2 |
| 4 | `0x0f` | PB0–PB3 |
| 5 | `0x1f` | PB0–PB4 |
| 6 | `0x3F` | PB0–PB5 |

---

## ISR_INT0: Dual-Mode Pattern Sequencer

This program alternates between two distinct animation sequences on the LED array, toggled by the hardware button.

### Animation Modes
1. **Mode A (`moveA`):** - **Fill:** LEDs 0 to 5 turn on sequentially.
   - **Drain:** LEDs 5 down to 0 turn off sequentially. *Note: Uses an unsigned underflow trick (`while(i < 255)`) to terminate the loop.*
2. **Mode B (`moveB`):** - **Fill:** LEDs 0 to 5 turn on sequentially.
   - **Clear:** LEDs 0 to 5 turn off in the **same** order (FIFO style).

### Interrupt Behavior
The `check` flag is toggled inside the ISR. The `main` loop evaluates this flag at the start of every cycle, ensuring a smooth transition between `moveA` and `moveB` only after a pattern completes.

---

## 🧠 Technical Implementation Notes

### Software Debouncing
Mechanical buttons produce electrical noise ("bouncing"). Both programs filter this inside the ISR to prevent false triggers:
```c
_delay_ms(DEBOUNCE);           // Ignore initial noise
if(bit_is_clear(PIND, PD2)){   // Verify button is still held low
    check ^= 1;                // Toggle logic flag
}
```

---

## The `volatile` Keyword
Variables such as `check`, `input`, and `ADC_Input` are declared as `volatile`. This informs the compiler that these values can change unexpectedly via hardware `interrupts`, preventing the optimizer from caching them in registers and causing logic errors.

---

## Compilation & Deployment

### Prerequisites:
1. `avr-gcc` toolchain
2. `avrdude` (for flashing)
3. Custom `USART.h` and `pinDefines.h` headers

### Build Instructions:
1. Compile:
````bash
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o firmware.elf main.c USART.c
````
2. Generate Hex:
````bash
avr-objcopy -O ihex firmware.elf firmware.hex
````
3. Flash:
````bash
avrdude -c arduino -p m328p -P [COM_PORT] -b 115200 -U flash:w:firmware.hex:i
````

4. Or simply open a bash terminal in the root folder of your file and type `make flash`.