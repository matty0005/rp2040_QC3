#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "QC3.h"

int main() {

    // Set the voltage of the output
    set_voltage(7200);
    sleep_ms(5000);
    
    set_voltage(8400);
    sleep_ms(5000);

    reset_voltage();
    sleep_ms(5000);

    set_voltage(8000);

}