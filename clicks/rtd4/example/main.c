/*!
 * @file main.c
 * @brief RTD 4 Click Example.
 *
 * # Description
 * This example initializes RTD 4 Click and configures the ADS122U04 for a
 * 3-wire PT100 RTD measurement. The application reads the conversion result,
 * calculates RTD resistance and displays an approximate temperature value.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, click driver and default ADS122U04 configuration for
 * the RTD 4 Click 3-wire measurement circuit.
 *
 * ## Application Task
 * Reads the ADC result, converts it to RTD resistance and prints the calculated
 * resistance and approximate PT100 temperature once per second.
 *
 * @note
 * Connect a 3-wire PT100 RTD sensor to the terminal block pins R+, R- and F
 * before running the example.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtd4.h"

#ifndef MIKROBUS_POSITION_RTD4
    #define MIKROBUS_POSITION_RTD4 MIKROBUS_1
#endif

static rtd4_t rtd4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtd4_cfg_t rtd4_cfg;  /**< Click config object. */

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
    rtd4_cfg_setup( &rtd4_cfg );
    RTD4_MAP_MIKROBUS( rtd4_cfg, MIKROBUS_POSITION_RTD4 );
    if ( UART_ERROR == rtd4_init( &rtd4, &rtd4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTD4_ERROR == rtd4_default_cfg ( &rtd4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float resistance = 0.0f;
    float temperature = 0.0f;

    if ( RTD4_OK == rtd4_read_temp( &rtd4, &temperature, &resistance ) )
    {
        log_printf( &logger, "RTD resistance: %.2f Ohm\r\n", resistance );
        log_printf( &logger, "Temperature: %.2f degC\r\n\n", temperature );
    }

    Delay_ms( 1000 );
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
