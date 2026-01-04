# STM32F103C8T6_Project

STM32 Bare-Metal ADC Data Acquisition System
This repository contains the bare-metal implementation of a timer-triggered ADC with DMA and UART on STM32F103C8T6 (Black Pill board), submitted to Unmanned Dynamics India Private Limited.
​

The system achieves precise 100 Hz sampling using hardware timer, DMA for efficient data transfer, and UART for PC visualization via PuTTY.
​

Features
Timer-Triggered Sampling: 100 Hz precise intervals using STM32 hardware timer (PSC and ARR for 72 MHz clock division).
​

ADC Conversion: 12-bit ADC captures variable analog input from 10k potentiometer (0-3.3V).
​

DMA Transfer: Automatic DMA moves ADC results to RAM without CPU intervention.
​

UART Output: Data transmitted at 9600 baud to serial terminal for real-time monitoring.
​

Pure Bare-Metal: No HAL, LL, Arduino, or OS layers—direct register access in Embedded C.
​

Hardware Setup
Microcontroller: STM32F103C8T6 (ARM Cortex-M3, 72 MHz).
​

Programmer: ST-Link V2 (SWD interface).
​

UART Bridge: CP2102 USB-to-TTL (COM port, 9600 bps, 8N1).
​

Input: 10k Potentiometer to ADC pin.
​

Connect as per standard Black Pill pinout: Timer to ADC trigger, ADC to pot, UART to CP2102.
​

Software Requirements
IDE: Keil uVision (Embedded C development).
​

Programmer: STM32CubeProgrammer (HEX flashing).
​

Terminal: PuTTY (for UART data view).
​

Installation & Build
Clone this repository.

Open project in Keil uVision.

Build to generate HEX file.

Flash using STM32CubeProgrammer via ST-Link.
​

Usage
Power the Black Pill (3.3V).

Connect potentiometer and adjust for varying ADC input.

Open PuTTY: Select COM port, 9600 baud, view real-time ADC values (100 Hz updates).
​

Rotate pot to see voltage changes reflected in digital output.
​

Example PuTTY output shows raw ADC values streamed continuously.
​

System Flow
text
Timer (100 Hz) → Triggers ADC → DMA to RAM → UART Tx → PuTTY Terminal
Project Report
Detailed report available: Report_Unmanned-Dynamics-India-Private-Limited.pdf.
​

Author
