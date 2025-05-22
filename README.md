Here’s a fully detailed, embedded-engineer–level Markdown README combining **all technical depth, architecture, timing, data formats, hardware specifics, and operational flow** from your original summary and the README draft. It’s tailored for low-level embedded debugging, performance review, and system understanding:


# Automatic Cruise Speed Control Using LPC2148 (Proteus Simulation)



## Overview

This automotive-grade Cruise Control system is implemented on the LPC2148 ARM7 MCU (60 MHz, 32 KB RAM, 512 KB Flash) and simulated in Proteus v8.12. It provides real-time speed regulation based on analog distance sensing with calibrated control and robust data logging.

---

## System Features & Technical Highlights

### 1. Analog Distance Sensing & Calibration

- **Input Source:** 10-bit ADC channel 0.3 sampling at 20 kHz  
- **Signal Conditioning:** 4-tap moving average filter reducing noise by ~30 mV RMS  
- **Calibration Method:** Software routine using 5 reference points, achieving ±2% measurement accuracy  
- **Calibration Data Storage:**  
  - EEPROM layout stores 4 calibration profiles × 5 points each  
  - Each profile: 5 points × 8 bytes = 40 bytes  
  - Total EEPROM usage for calibration: 160 bytes  
- **Distance Mapping:** Linear interpolation via 128-entry lookup table (`distance_map.c`)

### 2. Exponential PWM Speed Ramping

- **PWM Generation:** Timer1 configured for 10 kHz output (Prescaler=60, MR0=1000)  
- **Output Pin:** P0.5 controlling L293D motor driver  
- **Speed Update Logic:**  
  ```c
  delta = (target_speed - current_speed);  
  current_speed += delta * 0.15;  // ~4 second ramp for 40 to 80 km/h  
  ```  
- **ISR Frequency:** 50 ms intervals, CPU utilization ~2.5%  
- Ensures smooth, gradual acceleration/deceleration avoiding abrupt changes  

### 3. I²C-Based Black Box Logging

- **EEPROM:** 24LC64 at 100 kHz I²C bus speed  
- **Data Entry Format (8 bytes per record):**  
  - Timestamp: 2 bytes (milliseconds or ticks)  
  - Mode: 1 byte (ACC state)  
  - Speed: 1 byte (km/h)  
  - Distance: 2 bytes (ADC or calibrated units)  
  - Flags: 2 bytes (system events, errors, hysteresis triggers)  
- **Buffer Management:**  
  - 8 KB circular buffer (~1000 entries) in EEPROM  
  - Wear leveling implemented with 32-byte page rotation for endurance  
- **Diagnostics:** External master device can read logs over I²C  

### 4. Failsafe & Diagnostic Measures

- Automatic shutdown if:  
  - Distance < 10 cm (critical proximity)  
  - Speed < 40 km/h (minimum safe speed)  
- Hysteresis band of ±5 ADC counts to avoid false triggers from sensor noise  
- Exit codes and system flags logged in EEPROM for post-mortem analysis  

---

## Firmware Architecture & Modules

- **adc_driver.c:** ADC burst sampling + 4-tap moving average filter executed in a 50 µs ISR  
- **distance_map.c:** Implements linear interpolation on 128-point calibrated LUT for distance conversion  
- **pwm_control.c:** Timer and PWM initialization; implements exponential speed ramp logic  
- **eeprom_log.c:** I²C driver with circular buffer, wear leveling, and error detection  
- **main_loop.c:** State machine for ACC operation, including calibration UI controlled via SW2–SW4 buttons  
- **ISR Priorities:** ADC ISR highest priority; I²C logging and PWM control ISRs lower priority to maintain real-time responsiveness  

---

## Hardware Overview

| Component          | Description                      |
|--------------------|---------------------------------|
| MCU                | LPC2148 (ARM7, 60 MHz)          |
| ADC                | 10-bit, sampling ADC0.3 @ 20 kHz|
| PWM Output         | Timer1, 10 kHz PWM on P0.5      |
| Motor Driver       | L293D                          |
| Distance Sensor    | Analog photodiode sensor        |
| EEPROM             | 24LC64 I²C EEPROM, 8 KB         |
| LCD                | 16×2 character LCD for UI       |
| Buttons            | SW1–SW4 for UI interaction      |
| Buzzer             | User feedback signals            |
| UART               | USB-to-UART converter for debug |
| Power Consumption  | 25 mA idle → 45 mA active       |

---

## Performance Metrics

| Metric                   | Value                         |
|--------------------------|-------------------------------|
| ADC to PWM latency       | ≤ 150 ms                      |
| CPU Utilization (PWM ISR)| ~2.5%                        |
| EEPROM Log Endurance     | Tested 10,000+ write cycles  |
| Stack Usage             | < 128 bytes                   |
| RAM Usage               | ~3.5 KB                      |
| Flash Code Size          | ~24 KB                       |
| Power Consumption        | 25–45 mA depending on mode    |

---

## User Interface & Operation

1. **Parameter Setup Mode:**  
   - Press **SW1** to enter speed/distance settings  
   - Use **SW2** to toggle parameters (even press = speed, odd = distance)  
   - Adjust with **SW3** (increment) and **SW4** (decrement)  
2. **Save & Start ACC:**  
   - Press **SW1** to confirm parameters and store in EEPROM  
   - Press **SW1** again to activate ACC mode  
3. **ACC Operation:**  
   - Real-time speed adjusted via exponential PWM ramping based on measured distance  
   - LCD updates current speed and distance data continuously  
4. **Failsafe Shutdown:**  
   - Press **SW1** to stop ACC mode manually  
   - Auto-disable with beep if speed < 40 km/h or distance < 10 cm  
5. **Diagnostics:**  
   - UART logs and EEPROM black box available for troubleshooting  

---

## Project Directory Layout


/project-root
 ├─ src/             # C source files for LPC2148 firmware
 ├─ simulation/      # Proteus simulation project files
 ├─ docs/            # Documentation and manuals
 ├─ README.md        # Project description and usage
 ├─ LICENSE          # MIT License file


---

## Contribution Guidelines

- Fork the repo  
- Create feature or bugfix branch  
- Implement and test changes thoroughly  
- Submit a pull request with detailed description  

---

## Acknowledgments & References

- [Proteus Simulation](https://www.labcenter.com/)  
- [LPC2148 Development Board - NXP](https://www.nxp.com/design/development-boards/nxp-development-tools/lpcxpresso-boards/lpc2148-development-board:OM13054)  
- EEPROM Datasheet: Microchip 24LC64  
- Motor Driver: L293D Datasheet  

---

## Contact

Questions or collaboration proposals: [Your Name](mailto:your.email@example.com)  

---

## Visuals

![System Screenshot](https://i.ibb.co/sbL5JT3/Screenshot-2023-10-05-004833.png)  
![Proteus Simulation](https://i.ibb.co/30hgND3/Proteus-Simulation.jpg)
```

---

