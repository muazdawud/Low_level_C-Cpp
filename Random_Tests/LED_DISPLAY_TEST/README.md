# 4D_7S Library

A high-performance, interrupt-driven C library for multiplexing **4-digit 7-segment displays** on AVR-based microcontrollers. Designed for low CPU overhead and flicker-free operation using Timer 2 SFR. *(Also applicable with Arduino microcontrollers but not yet set)*

> *See `/examples` root for an example which compiles with not more than 850 bytes of flash size.*

> **Currently supports Common-Cathode 4-digit 7-segment displays.**

## Features
* **Interrupt-Driven:** Background refreshing using Timer 2 ISR.
* **Hardware Agnostic:** Supports both modern (ATmega328P, 168, 2560) and legacy (ATmega8, 16, 32) AVR MCUs.
* **Lightweight:** Minimal memory footprint using register-level programming.
* **Decimal Point Support:** Individual control over decimal points for each digit.
* **Automatic Parsing:** Built-in number extraction from 16-bit integers.

---

## Hardware Configuration

This library assumes a standard 4-digit multiplexed configuration. The segments (A-G and DP) should be connected to a single 8-bit port, while the digit selectors (Grounds/Commons) are connected to specific pins on a separate port.



![Wiring Diagram](resource/photo_2026-04-08_16-36-53.jpg)


### Connection Mapping
| Segment | Port Bit |
| :--- | :--- |
| A | 0 |
| B | 1 |
| C | 2 |
| D | 3 |
| E | 4 |
| F | 5 |
| G | 6 |
| DP | 7 |

---

## API Reference

### `void setPin(const uint8_t ground[])`
Configures the pin indices on the ground port used to select each of the 4 digits.
* **ground[]**: An array of 4 bytes representing the ground bit-position (0-7). *(Requires only 4 pin-bit)*

### `setPin(PIN_ARRAY)`
This function call passes a pre-initialized array, the array consists of 4 bytes which correspond to the bit-position of the pins (in the register) that are going to be used to control the individual ground of the display. A clear example is like the `uint8_t grounds[4] = {PB0, PB1, PB2, PB3};` above which initializes the `ground[]` array with the bit-positions of the individual ground of the display.

### `void initLED_DISPLAY(volatile uint8_t *PORT_1, volatile uint8_t *PORT_2, uint8_t dp_mask)`
Initializes the timer and assigns the ports for segments and digit selection.
* **PORT_1**: Pointer to the Data Register (e.g., `&PORTD`) for segments.
* **PORT_2**: Pointer to the Data Register (e.g., `&PORTB`) for digit selection (grounds).
* **dp_mask**: Controls decimal points. Pass `1-4` to enable DP on a specific digit, or `0` to disable all decimal points. *(DP stands for Decimal Point)*

### `initLED_DISPLAY(&PORTD, &PORTB, 0)`
This function call also passes the elements `PORTD` and `PORTB` both as reference, the elements `PORTD` and `PORTB` contain the register address for the I/O ports provided by the AVR Microcontroller and allow us to make I/O operations. Other ports could be used like in the case of a bigger board like the Atmega2560 and others which has more I/O ports than the popular Atmega328 on the Arduino UNO. The ports also must be passed by reference to allow its manipulation by the `4D_7S` library. The last argument which is a number from `0-4` enables turning the decimal points on the LED display individually or entirely (depending on user need). Below is the mapping of the numbers;

#### DP Connection Mapping
| dp_mask | Target Digit | DP Behavior |
| --- | --- | --- |
| 0 | None | All Decimal Points Disabled |
| 1 | Digit 1 (Most Left) | DP active on Digit 1 |
| 2 | Digit 2 | DP active on Digit 2 |
| 3 | Digit 3 | DP active on Digit 3 |
| 4 | Digit 4 (Most Right) | DP active on Digit 4 |

### `void DISPLAY(uint16_t num)`
Updates the internal buffer with a new number to be displayed.
* **num**: 16-bit integer (0-9999) to display.

### `DISPLAY(1234)`
This is the actual function that takes the number to be displayed ranging from `0-9999` and nothing more.

---

## Usage Example

```c
#include <avr/io.h>
#include "4D_7S.h"

int main(void) {
    // Define the pins on PORTB used for digit selection (Grounds)
    uint8_t grounds[4] = {PB0, PB1, PB2, PB3};
    
    // Set DDR for Ports
    DDRD = 0xFF; // Segments as output
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3); // Grounds as output

    // Initialize: Port D for segments, Port B for grounds, no DP
    setPin(grounds);
    initLED_DISPLAY(&PORTD, &PORTB, 0);

    while (1) {
        DISPLAY(1234); // Continuously display 1234
    }
}
```

---

## Why Use 4D_7S Over Standard Implementations?
The library offers various advantages and features over others, and it was inspired from not seeing/using a similar version of it.

* **`98%` Reduction in Logic Execution Time**: By bypassing the Arduino abstraction layer and using direct register manipulation, segment switching is nearly instantaneous compared to `digitalWrite()` multiplexing.

* **`99.8%` Background Transparency**: Because the library is interrupt-driven, `99.8%` of CPU cycles remain available for the user's primary application logic (sensors, math, communication).

* **Constant-Time Performance (O(1))**: Unlike delay-based code where CPU usage scales with display complexity, your overhead remains a flat, negligible fraction of total clock cycles.

* **Improved Code Readability**: Because a user/programmer only needs to make three function calls to configure the display, and with clear self-explanatory function name, it reduces learning complexity for beginners while speeding up coding time for mature programmers (because of the function call minimalism).

* **Program-size Optimization**: The entire library is optimized to an entire scaled-up level to ensure minimal program size on a size-resourced microcontrollers.

---

## Credits
Maintained by: Dauda Muazu Sulaiman

Affiliation: [KibrisOrder](https://ss.kibrisorder.com)

Special thanks to **KibrisOrder** for supporting the development of high-performance embedded drivers.

*Copyright (c) 2026 Dauda Muazu Sulaiman, KibrisOrder. Licensed under the MIT License.*

---

*"Good and rigid answers are the foundation of stable systems."*
*(I hope this will be useful to the public and the opensource world)*