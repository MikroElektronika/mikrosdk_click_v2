/*!
 * \file 
 * \brief ADC7 Click example
 * 
 * # Description
 * This application collects data from the analog signal, calculates and logs the
 * converted voltage value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and performs configuration for conversion cycles.
 * 
 * ## Application Task  
 * Performs the determined number of conversion cycles which are necessary for averaging. 
 * When all conversion cycles are done, it reads the converted voltage value.
 * Results will be logged on UART terminal every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc7.h"

// ------------------------------------------------------------------ VARIABLES

static adc7_t adc7;
static log_t logger;

static float voltage_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc7_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    adc7_cfg_setup( &cfg );
    ADC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc7_init( &adc7, &cfg );
    
    adc7_default_cfg( &adc7 );
}

void application_task ( void )
{
    adc7_start_conv_cycle( &adc7 );
    adc7_read_results( &adc7, &voltage_data );
    log_printf( &logger, "Voltage: %.2f mV\r\n", voltage_data );

    Delay_ms( 1000 );
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
