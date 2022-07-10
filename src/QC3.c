#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "QC3.h"

// Set pins that will be used to control the D+ and D- pins
#define DATA_PLUS 2
#define DATA_MINUS 3

// 12V in mV
#define MAX_VOLTAGE 12000
#define MIN_VOLTAGE 3600

// Current voltage of the output
static uint16_t currentVoltage = 5000;

// variable to hold the state of the handshake
static bool handshakeComplete = false;
static bool continousMode = false;

/**
 * Initialises the QC protocol by handshaking.
*/
void handshake_init() {

    gpio_init(DATA_PLUS);
    gpio_init(DATA_MINUS);

    // Set high impeadance to reach 0.325v-2v crietia
    gpio_set_dir(DATA_PLUS, GPIO_IN);
    gpio_set_dir(DATA_PLUS, GPIO_IN);
    sleep_ms(1500);

    // Discharge D1
    gpio_set_dir(DATA_MINUS, GPIO_OUT);
    gpio_put(DATA_MINUS, 0);
    sleep_ms(5);

    handshakeComplete = true;
    continousMode = false;
}

/**
 * Set the voltage of the QC output. 
 * 
 * Parameters:
 *  voltage: int - 0 = 5V, 1 = 9V, 2 = 12V.
*/
void set_voltage_qc2(uint8_t voltage) {

    // Make sure the handshake has occured to be in QC mode.
    if (!handshakeComplete) {
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

uint16_t get_voltage_mv() {

    return currentVoltage;
}

void set_continous_mode() {

    // If already in continous mode, we don't need to set again
    if (continousMode) {

        return;
    }

    gpio_set_dir(DATA_PLUS, GPIO_IN);

    gpio_set_dir(DATA_MINUS, GPIO_OUT);
    gpio_put(DATA_MINUS, 1);

    continousMode = true;
}

void increment_voltage() {

    if (!handshakeComplete) {
        handshake_init();
    }

    // Make sure we don't increase over the max voltage
    if (currentVoltage >= MAX_VOLTAGE) {

        return;
    }

    set_continous_mode();

    gpio_set_dir(DATA_PLUS, GPIO_OUT);
    gpio_put(DATA_PLUS, 1);
    sleep_ms(2);   

    gpio_set_dir(DATA_PLUS, GPIO_IN);
    sleep_ms(2);

    currentVoltage += 200;
}

void decrement_voltage() {

    if (!handshakeComplete) {
        handshake_init();
    }

    // Make sure we don't increase over the max voltage
    if (currentVoltage >= MAX_VOLTAGE) {

        return;
    }

    set_continous_mode();

    gpio_set_dir(DATA_MINUS, GPIO_IN);
    sleep_ms(2);

    gpio_set_dir(DATA_MINUS, GPIO_OUT);
    gpio_put(DATA_PLUS, 1);
    sleep_ms(2);   
    

    currentVoltage -= 200;

}


/**
 * Set the voltage of the QC output in 200mV steps. 
 * 
 * Parameters:
 *  voltage: int - voltage in mV.
*/
void set_voltage(uint16_t voltage) {

    // Verify that voltage step is in 200mV steps.
    if (voltage % 200 != 0) {

        return;
    }

    // Make sure the handshake has occured to be in QC mode.
    if (!handshakeComplete) {
        handshake_init();
    }

    if (voltage == currentVoltage) {

        return;
    }

    if (voltage > currentVoltage) {

        while (currentVoltage < voltage) {

            increment_voltage();
        }
    } else {

        while (currentVoltage > voltage) {

            decrement_voltage();
        }
    }



}