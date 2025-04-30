# STM32F4 Bare-Metal Interrupt-Driven LED Controller

This project demonstrates a fully bare-metal implementation of GPIO control, external interrupts (EXTI), and system timer configuration (SysTick) on the STM32F4 series microcontroller (STM32F446RE). It does not rely on STM32 HAL, CMSIS drivers, or external libraries. All peripheral configurations are handled through direct register access.

## Project Overview

A push-button is connected to GPIOA pin 9. When pressed, it triggers an interrupt using EXTI line 9. To avoid false triggers due to mechanical bouncing, the project implements software-based debouncing using the Cortex-M4 SysTick timer. Each valid press cycles through five LEDs connected to various GPIO pins (PA5–PA7, PB6, and PC7).

## Features

- Manual GPIO pin initialization using RCC and GPIOx registers
- External interrupt configuration using EXTI and SYSCFG
- NVIC interrupt enabling for EXTI9_5
- Software debounce using SysTick timer (1 ms tick)
- LED cycling with each debounced button press
- No external libraries or runtime dependencies

## Hardware Connections

- **Button**: GPIOA pin 9 (configured with internal pull-up)
- **LEDs**:
  - PA5 (Red)
  - PA6 (Blue)
  - PA7 (Yellow)
  - PB6 (Green)
  - PC7 (White)

## File Structure

- `main.c` - Sets up GPIOs, button, EXTI, and SysTick. Contains main loop.
- `gpio.c/.h` - Low-level GPIO, RCC, NVIC, EXTI, and SysTick configuration functions.
- `startup.s` - Cortex-M4 startup assembly with interrupt vector table.
- `linker.ld` - Custom linker script defining memory layout.
- `Makefile` - Builds the binary, creates `.elf` and `.bin`, and supports flashing.

## Build and Flash

1. Ensure `arm-none-eabi-gcc` and `st-flash` are installed.
2. Run the following commands:

```bash
make            # Build the project
make flash      # Flash the binary to the STM32 board
```
## Key Concepts Demonstrated

    Bare-metal system initialization without HAL or CMSIS

    Direct register manipulation for GPIO and peripheral control

    Efficient interrupt-driven design with minimal CPU load

    Real-time debounce using a hardware timer (SysTick)

    Clean separation of startup code, application logic, and hardware control

## Target MCU

- STM32F446RE (Cortex-M4 core)

- This code can be adapted to other STM32F4 series chips with minor modifications to GPIO port and clock configuration

