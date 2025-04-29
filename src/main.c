



#include <stdint.h> 
#include "gpio.h"

uint32_t SystemCoreClock = 16000000;

int main(void){                                     
    //red
    gpio_config_t led_cfg0 = {                      // creates gpio config for PA5 to control LED
        .pin = PIN('A', 5),                         // tell config which port and pin number to deal with
        .mode = GPIO_MODE_OUTPUT,                   // set mode to Output
        .otype = GPIO_OTYPE_PUSHPULL,               // set OTYPE to push-pull output 
        .speed = GPIO_SPEED_HIGH,                   // set Speed as high for output driver
        .pull = GPIO_NO_PULL                        // not using a pull up or pull down resistor
    };
    // Blue
    gpio_config_t led_cfg1 = {                      // creates gpio config for PA6 to control LED
        .pin = PIN('A', 6),                         // tell config which port and pin number to deal with
        .mode = GPIO_MODE_OUTPUT,                   // set mode to Output
        .otype = GPIO_OTYPE_PUSHPULL,               // set OTYPE to push-pull output 
        .speed = GPIO_SPEED_HIGH,                   // set Speed as high for output driver
        .pull = GPIO_NO_PULL                        // not using a pull up or pull down resistor
    };
    // Yellow
    gpio_config_t led_cfg2 = {                      // creates gpio config for PA7 to control LED
        .pin = PIN('A', 7),                         // tell config which port and pin number to deal with
        .mode = GPIO_MODE_OUTPUT,                   // set mode to Output
        .otype = GPIO_OTYPE_PUSHPULL,               // set OTYPE to push-pull output 
        .speed = GPIO_SPEED_MEDIUM,                 // set Speed as high for output driver
        .pull = GPIO_NO_PULL                        // not using a pull up or pull down resistor
    };
    // Green
    gpio_config_t led_cfg3 = {                      // creates gpio config for PB6 to control LED
        .pin = PIN('B', 6),                         // tell config which port and pin number to deal with
        .mode = GPIO_MODE_OUTPUT,                   // set mode to Output
        .otype = GPIO_OTYPE_PUSHPULL,               // set OTYPE to push-pull output 
        .speed = GPIO_SPEED_FAST,                   // set Speed as high for output driver
        .pull = GPIO_NO_PULL                        // not using a pull up or pull down resistor
    };
    // White
    gpio_config_t led_cfg4 = {                      // creates gpio config for PC7 to control LED
        .pin = PIN('C', 7),                         // tell config which port and pin number to deal with
        .mode = GPIO_MODE_OUTPUT,                   // set mode to Output
        .otype = GPIO_OTYPE_PUSHPULL,               // set OTYPE to push-pull output 
        .speed = GPIO_SPEED_HIGH,                   // set Speed as high for output driver
        .pull = GPIO_NO_PULL                        // not using a pull up or pull down resistor
    };

    gpio_config_t push_button = {                   // creates gpio config for PA9 Push-Button
        .pin = PIN('A', 9),                         // tell config which port and pin number to deal with
        .mode = GPIO_MODE_INPUT,                    // set mode to Input
        .otype = GPIO_OTYPE_PUSHPULL,               // ignored for Input Mode
        .speed = GPIO_SPEED_HIGH,                   // ignored for Input Mode
        .pull = GPIO_PULL_UP                       // not using a pull up or pull down resistor
    };


    SysTick_Config(SystemCoreClock / 1000); // 1ms tick
    gpio_init_pin(led_cfg0);                         // initializing pin with our config file
    gpio_init_pin(led_cfg1);
    gpio_init_pin(led_cfg2);
    gpio_init_pin(led_cfg3);
    gpio_init_pin(led_cfg4);
    gpio_init_pin(push_button);


    exti_init();
    nvic_enable_irq();
  
    while (1)
    {   
    }
    

}
