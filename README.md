# STM32 Bare-Metal LED Control with Interrupts (NVIC & EXTI)

This project demonstrates how to control multiple LEDs on an STM32 microcontroller **without using any libraries (no HAL, no CMSIS)**. It includes **external interrupt handling (EXTI)** via **NVIC**, triggered by a push-button to cycle through LEDs.

## 🧠 What You'll Learn
- Direct register manipulation for GPIO setup
- Configuring external interrupts using **EXTI** and **NVIC**
- Writing your own startup file, linker script, and vector table
- Debugging with `gdb` and `st-util`

---

## 🚀 Features

- **Interrupt-Driven**: A button connected to `PA9` triggers an external interrupt to cycle through 5 LEDs.
- **Bare-Metal Only**: No CMSIS, no HAL, full control over registers and memory layout.
- **Custom Startup Code**: Startup file initializes `.data`/`.bss` and jumps to `main()`.
- **Clean LED Blinking**: GPIOs toggle using hardcoded config for minimal memory usage.
- **Heart-Beat Debugging**: `PC7` toggles inside main loop to show the system is alive.

---

## 🛠️ Hardware Requirements

- STM32 Nucleo Board (e.g., STM32F446RE)
- 5 LEDs + 220Ω resistors
- 1 Push Button
- Breadboard and jumper wires
- ST-Link or equivalent debugger

---

## 🧰 Setup Instructions

### 1. Wiring Guide

| Pin     | LED Color | Description     |
|---------|-----------|-----------------|
| PA5     | Red       | LED Output      |
| PA6     | Blue      | LED Output      |
| PA7     | Yellow    | LED Output      |
| PB6     | Green     | LED Output      |
| PC7     | White     | LED Output      |
| PA9     | —         | Button Input    |

🟢 **Pull-up is configured via internal register for PA9**  
🟢 LEDs should be wired with their cathodes to GND via resistors

---

### 2. Build & Flash

Ensure `arm-none-eabi-gcc`, `make`, and `st-flash` are installed.

```bash
# Build
make

# Flash binary to STM32
make flash
```

## For Debugging
- Start ST-Link server
- st-util

- In another terminal, start GDB
- gdb-multiarch build/main.elf

- Inside GDB:
- target extended-remote :4242
- monitor reset halt
- break EXTI9_5_IRQHandler
- continue


