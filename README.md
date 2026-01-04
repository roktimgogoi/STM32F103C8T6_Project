# STM32F103C8T6_Project

Submitted by: **Roktim Probal Gogoi**  
B.Tech in Power Electronics and Instrumentation  
Email: `rpgogoi2019@gmail.com`
Submitted to: **Unmanned Dynamics India Private Limited**  
Date: **4 Jan 2026**


## 1. Introduction

This project is implemented using bare-metal programming, which allows direct access to hardware resources such as timer registers, USART registers, ADC registers, and GPIO registers. It is completely free from any Arduino framework, HAL/LL libraries, or operating system abstraction layer.
In modern embedded systems, low latency, precise timing, and efficient CPU utilization are essential requirements. To meet these demands, hardware peripherals such as timers, ADCs, DMA controllers, and Universal Synchronous/Asynchronous Receiver-Transmitters (USARTs) are used in an interrupt-driven and hardware-triggered manner.
This project demonstrates a bare-metal implementation on an STM32 ARM Core Board (STM32F103C8T6) microcontroller, where, A hardware timer generates a 100 Hz trigger to generate precise sampling intervals. The trigger initiates an ADC conversion, that aquitsion system collect the raw analog value and convert to digital and ADC results are transferred to memory using DMA. Upon DMA completion, data is sent via UART to transmit data into PC. The results are displayed on a PC using a serial terminal (PuTTY). The use of bare-metal programming ensures complete control over the hardware and eliminates unnecessary abstraction layers.
This report explains the hardware setup, peripheral configuration, system architecture, and verification process in detail that highlighting the advantages of bare-metal embedded system design.

## 3. Methodology

In this project, the timer on the STM32 microcontroller is configured to operate at 100 Hz. Given that the STM32 system clock runs at 72 MHz, the system can count up to 72,000,000 cycles per second. This frequency is too high for most timing applications, so two hardware dividers are used to slow it down:
1.	PSC (Prescaler), and
2.	ARR (Auto-Reload Register).
These two registers make the timer fully hardware-controlled, ensuring precise and stable timing operation.
For analog-to-digital conversion (ADC) testing, a 10 kΩ potentiometer is used to provide a variable analog voltage input. The resulting digital data is transferred to the STM32’s internal RAM using Direct Memory Access (DMA). Since the microcontroller cannot retain data permanently unless it is stored in non-volatile memory such as EEPROM, Flash, or an SD card, the data remains temporarily in RAM. Finally, the collected data is transmitted via the UART interface and displayed on a terminal program such as PuTTY.

### 3.2 Hardware Components Used

The componets are use: 

-**STM32F103C8T6 Microcontroller**
-**ST-Link V2 Programmer**
-**CP2102 USB-to-TTL UART Converter**

