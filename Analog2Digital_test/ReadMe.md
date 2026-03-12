# AVR-ADC Exploration: Register-Level Analog Processing
**Author:** Dauda M. S.  
**GitHub:** [muazdawud](https://github.com/muazdawud)

* May include header files made by **Elliot Williams**, which I'm using his book btw.

---

This repository root contains three C programs designed for the **ATmega328P** that explore the architecture and implementation of the Analog-to-Digital Converter (ADC). The project moves from basic sampling to real-time peripheral feedback using UART and LED arrays.

---

## Technical Overview
The programs focus on direct manipulation of the following registers and bits:
- **ADMUX**: Reference selection (`REFS0`), Result Left-Adjust (`ADLAR`), and Channel selection (`MUX3:0`).
- **ADCSRA**: ADC Enable (`ADEN`), Start Conversion (`ADSC`), Auto-trigger Enable (`ADATE`) and also Prescaler selection (`ADPS2:0`).
- **ADCSRB**: Auto-trigger source control.
- **ADC (ADCH/ADCL)**: Data register management.

---

## The Programs

### 1. 2in1 Analog-to-Digital Sampling (`2_ADC_INPUT`)
Demonstrates 8-bit precision sampling of a Potentiometer and LDR Input.
- **Configuration**: `REFS0` set to use AVCC (5V) as the reference, `ADLAR` set to make use of `ADCH` for 8-bit data Input. `ADPS` Pre-scaler divisor set to 128 to achieve an update frequency of 125kHz
- **Baud Rate**: Integrated with the **Elliot Williams USART header** for 9600 baud serial communication.
- **Goal**: Read the 8-bit value ($0-255$) and stream it to a terminal emulator.

### 2. LDR Light-Level Meter (`LDR_AO_Controlled_LED`)
Maps ambient light intensity to a visual 10-bit `ASCII` representation.
- **Configuration**: A manual update/input collect using `ADSC` bit set to `ADCSRA`.
- **Output**: The 8-bit value is truncated and output to **PORTB** (Pin 0) to drive an LED intense/dim.
- **Logic**: Real-time conversion of analog environmental data into binary/`ASCII` visual states.

### 3. High-Speed Sampling & UART Test (`UART_LDR_Value`)
Explores the impact of the **ADC Prescaler** on conversion speed and accuracy.
- **Configuration**: Makes use of  `ADPS2:0` which enables 128 as the Prescaler divisor to provide the ADC running frequency of `125kHz`.
- **Outcome**: Documents the trade-off between 10-bit accuracy and high-frequency sampling for time-sensitive applications like audio processing and Serial Communication.

---

## 🎛 Register Breakdown

| Bit(s) | Functionality | Usage in this Project |
| :--- | :--- | :--- |
| **REFS0** | Voltage Reference | Set to `1 (True)` to use `VCC` as the comparison ceiling. |
| **ADLAR** | Left Adjust | Enabled for the LDR project to allow 8-bit reading from `ADCH`. |
| **ADEN** | ADC Enable | The "Power Switch" for the ADC circuitry. |
| **ADSC** | Start Conversion | Set to `1` to initiate a single sample; hardware clears it when finished. |
| **ADPS2:0** | Prescaler | Set to `111` (128) to ensure 125kHz clock at 16MHz CPU speed. |

---

## 🔌 Hardware Setup
- **Microcontroller**: ATmega328P (Arduino Uno form factor).
- **Inputs**: 
  - `10kOhms` Potentiometer on `PC3` (ADC3).
  - Photoresistor (LDR) in a voltage divider circuit on `PC0` (ADC0).
- **Outputs**: 
  - 6 LEDs with current-limiting resistors on `PB0-PB5`.
  - Serial-to-USB (via UART) to Laptop.

---

## *Developed as part of a Mechatronics Engineering exploration into bare-metal AVR development.*