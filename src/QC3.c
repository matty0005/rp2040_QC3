#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "QC3.h"

// Set pins that will be used to control the D+ and D- pins
#define DATA_PLUS 2
#define DATA_MINUS 3

// variable to hold the state of the handshake
static bool handshake_complete = false;

/**
 * Initialises the QC protocol by handshaking.
*/
void handshake_init() {

    gpio_init(DATA_PLUS);
    gpio_init(DATA_MINUS);

    // Set high impeadance to reach 0.325v-2v crietia
    gpio_set_dir(DATA_PLUS, GPIO_IN);
    sleep_ms(1500);

    // Discharge D1
    gpio_set_dir(DATA_MINUS, GPIO_OUT);
    gpio_put(DATA_MINUS, 0);
    sleep_ms(2);

    handshake_complete = true;
}

/**
 * Set the voltage of the QC output. 
 * 
 * Parameters:
 *  voltage: int - 0 = 5V, 1 = 9V, 2 = 12V.
*/
void set_voltage(uint8_t voltage) {

    // Make sure the handshake has occured to be in QC mode.
    if (!handshake_complete) {
        handshake_init();
    }

    // Change based on voltage.
    switch (voltage) {
        
        case QC_5V:

            // Set to high impeadance to reset the voltage
            gpio_set_dir(DATA_PLUS, GPIO_IN);
            gpio_set_dir(DATA_MINUS, GPIO_IN);
            break;

        case QC_9V:

            gpio_set_dir(DATA_PLUS, GPIO_OUT);
            gpio_put(DATA_PLUS, 1);

            gpio_set_dir(DATA_MINUS, GPIO_OUT);
            gpio_put(DATA_MINUS, 1);
            break;

        case QC_12V:

            // Disconnect (make high impeadance)
            gpio_set_dir(DATA_PLUS, GPIO_IN);

            gpio_set_dir(DATA_MINUS, GPIO_OUT);
            gpio_put(DATA_MINUS, 1);
            break;
    }
}