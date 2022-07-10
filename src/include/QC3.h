#ifndef QC3_H
#define QC3_h

// Macros for the 3 voltage steps
#define QC_5V 0 
#define QC_9V 1
#define QC_12V 2

/**
 * Initialises the QC protocol by handshaking.
*/
void handshake_init();

/**
 * Set the voltage of the QC output. 
 * 
 * Parameters:
 *  voltage: int - 0 = 5V, 1 = 9V, 2 = 12V.
*/
void set_voltage_qc2(uint8_t voltage);

void set_voltage(uint16_t voltage);

#endif