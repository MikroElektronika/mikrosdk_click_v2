/*!
 * @file main.c
 * @brief DAC 19 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 19 Click board by changing the output voltage level.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, checks the communication by reading and verifying the device ID,
 * and enables the DAC output.
 *
 * ## Application Task
 * Changes the output voltage every 2 seconds and logs the voltage value on the USB UART.
 * It will go through the entire voltage range for the step number defined below.
 *
 * @note
 * Measure the voltage at VCC_SEL jumper and adjust the reference voltage value below for better accuracy.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac19.h"

#define REFERENCE_VOLTAGE_MV 3300 // The reference voltage defined by the VCC_SEL on-board jumper. 
#define NUMBER_OF_STEPS      20   // The number of steps by which we will divide the entire voltage range. 

static dac19_t dac19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac19_cfg_t dac19_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    dac19_cfg_setup( &dac19_cfg );
    DAC19_MAP_MIKROBUS( dac19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dac19_init( &dac19, &dac19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC19_ERROR == dac19_default_cfg ( &dac19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t step = REFERENCE_VOLTAGE_MV / NUMBER_OF_STEPS;
    uint16_t output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC19_OK == dac19_set_voltage ( &dac19, REFERENCE_VOLTAGE_MV, output_voltage ) )
        {
            log_printf( &logger, " VOUT: %u mV\r\n", output_voltage );
        }
        output_voltage += step;
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
