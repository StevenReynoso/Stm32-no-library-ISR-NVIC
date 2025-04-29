#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

struct gpio {
    volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR;
};


#define DEBOUNCE_DELAY 150

#define SYST_CSR (*(volatile uint32_t *) (0xE000E010))                       // Systick Control Status Register
#define SYST_RVR (*(volatile uint32_t *) (0xE000E014))                       // Systick Reload Value Register
#define SYST_CVR (*(volatile uint32_t *) (0xE000E018))                       // Systick Current Value Register

                                                                             // RESET CLOCK CONTROL (RCC)
#define RCC_AHB1ENR (*(volatile uint32_t *) (0x40023800 + 0x30))             // RCC AHB1 Peripheral Clock enable register
#define RCC_APB2ENR (*(volatile uint32_t *) (0x40023800 + 0x44))             // RCC APB2 ENABLE REGISTER

#define SYSCFG_EXTICR1 (*(volatile uint32_t *) (0x40013800 + 0x08))          // System Configuration Controller, External Interupt Config Register
#define SYSCFG_EXTICR3 (*(volatile uint32_t *) (0x40013800 + 0x10))

#define EXTI_IMR (*(volatile uint32_t *) (0x40013C00 + 0x00))                // EXTI - External Interupt, IMR - Interrupt Mask Register
#define EXTI_FTSR (*(volatile uint32_t *) (0x40013C00 + 0x0C))               // FTSR - Falling Trigger Selection Register
#define EXTI_PR (*(volatile uint32_t *)(0x40013C00 + 0x14))                  // PR - Pending Register

#define NVIC_ISER0 (*(volatile uint32_t *) (0xE000E100))                     // Not in memory map, but in core-side
                                                                             // NVIC - Nested Vector Interupt Controller, ISER - Interupt Set Enable Register

#define GPIO(bank) ((struct gpio *)(0x40020000 + (0x400 * ((bank) - 'A'))))  // Macro to access a gpio peripheral base address
#define PIN(bank, num) (((bank - 'A') << 8) | (num))                         // macro to encode a pin using a bank and number: Pin(A, 5) = 0x0005
#define PINNO(pin) ((pin) & 0xFF)                                            // Extract pin number 0 - 15 from encoded pin
#define PINBANK(pin) ((pin) >> 8)                                            // extract bank number 0 for A, 1 for B.. from encoded pin


typedef enum {                                                               // GPIO MODE options for MODER register
    GPIO_MODE_INPUT       = 0x00,                                
    GPIO_MODE_OUTPUT      = 0x01,
    GPIO_MODE_AF          = 0x02,
    GPIO_MODE_ANALOG      = 0x03
} gpio_mode_t;

typedef enum {                                                              // GPIO output typers for OTYPER register
    GPIO_OTYPE_PUSHPULL   = 0x00,
    GPIO_OTYPER_OPENDRAIN = 0x01
}gpio_otype_t;

typedef enum{                                                               // GPIO speed levels for OSPEEDR register
    GPIO_SPEED_LOW        = 0x00,
    GPIO_SPEED_MEDIUM     = 0x01,
    GPIO_SPEED_FAST       = 0x02,
    GPIO_SPEED_HIGH       = 0x03
}gpio_speed_t;

typedef enum{                                                               // GPIO pull up - pull down options for PUPDR register
    GPIO_NO_PULL          = 0x00,
    GPIO_PULL_UP          = 0x01,
    GPIO_PULL_DOWN        = 0x02
}gpio_pupdr_t;

typedef struct{                                                             // GPIOP configuration structure
    uint16_t     pin;                                                       // encoded pin using (x, y)
    gpio_mode_t  mode;                                                      // Pin mode: input output ...
    gpio_otype_t otype;                                                     // Output type: push pull or open
    gpio_speed_t speed;                                                     // Output speed
    gpio_pupdr_t pull;                                                      // pull up - pull down config
}gpio_config_t;
                                                                            // our function prototypes
void gpio_init_pin(gpio_config_t cfg);
void gpio_set_mode(uint16_t pin, uint8_t mode);
void rcc_gpio_enr(uint8_t bank_num);
int SysTick_Config(uint32_t ticks);
void nvic_enable_irq(void);
void exti_init(void);
#endif //GPIO_H

