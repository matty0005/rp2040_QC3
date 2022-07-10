#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "QC2.h"

int main() {

    // Set the voltage of the output
    set_voltage(QC_9V);
}