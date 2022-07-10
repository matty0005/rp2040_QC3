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


void reset_voltage();

/**
 * Set the voltage of the QC output. 
 * 
 * Parameters:
 *  voltage: int - voltage in mV.
*/
void set_voltage(uint16_t voltage);

#endif