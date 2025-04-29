
#include "gpio.h"

volatile uint32_t last_button_press_time = 0;
volatile uint32_t current_time = 0;
volatile uint8_t button_pressed = 0;


/* === gpio_set_mode ===
 * Sets the mode of a GPIO pin (input, output, alternate function, analog).
 * - Extracts GPIO bank and pin number from encoded `pin`.
 * - Updates only the relevant bits in MODER.
 */
inline void gpio_set_mode(uint16_t pin, uint8_t mode) {
    struct gpio *gpio = GPIO(PINBANK(pin));                   // Get pointer to GPIO port struct
    uint8_t gpio_pin = PINNO(pin);                            // Extract pin number (0–15)

    gpio->MODER &= ~(0x3U << (gpio_pin * 2));                 // Clear the 2 bits for this pin
    gpio->MODER |= ((mode & 0x3U) << (gpio_pin * 2));         // Set new mode
}


/* === rcc_gpio_enr ===
 * Enables the clock for the specified GPIO bank via RCC_AHB1ENR.
 * - `bank_num` is 0 for A, 1 for B, etc.
 */
void rcc_gpio_enr(uint8_t bank_num) {
    RCC_AHB1ENR |= (1 << bank_num);                           // Enable clock for corresponding GPIO port
}

void nvic_enable_irq(void){
    NVIC_ISER0 |= (1 << 23);
}

void exti_init(void){
    RCC_APB2ENR |= (1 << 14);

    SYSCFG_EXTICR3 &= ~(0xF << 4);
    SYSCFG_EXTICR3 |= (0X0 << 4);

    EXTI_IMR  |= (1 << 9);                                    // IMR = 0 (line X is masked), IMR = 1, (line X is not masked)
    EXTI_FTSR |= (1 << 9);                                    // Falling trigger 0 = Disabled, Falling Trigger 1 = Enabled.
}

int SysTick_Config(uint32_t ticks){
    if(ticks > 0xFFFFFF){
        return 1;
    }

    SYST_RVR = ticks - 1;                                     // setting the reload register
    SYST_CVR = 0;                                             // clear current value register
    SYST_CSR = 0x07;                                          // enabling clock source, tickint, enable systick timer

    return 0; 

}


void SysTick_Handler(void){
    current_time++;
}


volatile int step = 0;
void EXTI9_5_IRQHandler(void) {
    if(EXTI_PR & (1 << 9)){
        uint32_t time_now = current_time;

        if((time_now - last_button_press_time) > DEBOUNCE_DELAY){
               // Reset all LEDs
            GPIO('A')->ODR &= ~((1 << 5) | (1 << 6) | (1 << 7));
            GPIO('B')->ODR &= ~(1 << 6);
            GPIO('C')->ODR &= ~(1 << 7);

            // Toggle current LED
            switch (step) {
                case 0: GPIO('A')->ODR |= (1 << 5); break;
                case 1: GPIO('A')->ODR |= (1 << 6); break;
                case 2: GPIO('A')->ODR |= (1 << 7); break;
                case 3: GPIO('B')->ODR |= (1 << 6); break;
                case 4: GPIO('C')->ODR |= (1 << 7); break;
            }

            step = (step + 1) % 5;

            last_button_press_time = time_now;
        }

        EXTI_PR |= (1 << 9);  // Clear pending
    }

}





/* === gpio_init_pin ===
 * Configures a GPIO pin based on the given configuration struct:
 * - Enables peripheral clock
 * - Sets mode, output type, speed, and pull-up/down configuration
 */
void gpio_init_pin(gpio_config_t cfg) {
    struct gpio *gpio = GPIO(PINBANK(cfg.pin) + 'A');        // Get GPIO port base address
    uint8_t gpio_pin = PINNO(cfg.pin);                       // Extract pin number (0–15)

    rcc_gpio_enr(PINBANK(cfg.pin));                          // Enable clock for this GPIO bank

    /* Set pin mode (MODER) */
    gpio->MODER &= ~(0x03 << (gpio_pin * 2));                // Clear mode bits
    gpio->MODER |= ((cfg.mode & 0x03) << (gpio_pin * 2));    // Set mode bits

    /* Set output type (OTYPER) */
    gpio->OTYPER &= ~(1 << gpio_pin);                        // Clear output type
    gpio->OTYPER |=  ((cfg.otype & 0x01) << gpio_pin);       // Set output type

    /* Set output speed (OSPEEDR) */
    gpio->OSPEEDR &= ~(0x03 << (gpio_pin * 2));              // Clear speed bits
    gpio->OSPEEDR |= ((cfg.speed & 0x03) << (gpio_pin * 2)); // Set speed bits

    /* Set pull-up/pull-down (PUPDR) */
    gpio->PUPDR &= ~(0x03 << (gpio_pin * 2));                // Clear pull config
    gpio->PUPDR |= ((cfg.pull & 0x03) << (gpio_pin * 2));    // Set pull config
}
