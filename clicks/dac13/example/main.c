/*!
 * @file main.c
 * @brief DAC 13 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 13 click board by changing 
 * the outputs voltage level every 2 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the output voltage every 2 seconds and logs the voltage value on the USB UART.
 * It will go through the entire voltage range taking into account the number of steps
 * which is defined below.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac13.h"

#define NUMBER_OF_STEPS 20  // A number of steps by which the entire voltage range will be divided, must be >= 1. 

static dac13_t dac13;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac13_cfg_t dac13_cfg;  /**< Click config object. */

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
    dac13_cfg_setup( &dac13_cfg );
    DAC13_MAP_MIKROBUS( dac13_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac13_init( &dac13, &dac13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC13_ERROR == dac13_default_cfg ( &dac13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float step = ( dac13.v_full_scale - dac13.v_zero_scale ) / ( NUMBER_OF_STEPS - 1 );
    float out_voltage = dac13.v_zero_scale;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC13_OK == dac13_set_output_voltage ( &dac13, out_voltage ) )
        {
            log_printf ( &logger, " Output voltage : %.2f V\r\n\n", out_voltage );
            out_voltage += step;
            Delay_ms ( 2000 );
        }
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
