/*!
 * @file main.c
 * @brief Thermo 23 Click Example.
 *
 * # Description
 * This example demonstrates the use of Thermo 23 Click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the Click default configuration which enables
 * continuous conversion and sets the conversion rate to 1 Hz.
 *
 * ## Application Task
 * Reads the temperature measurement in Celsius and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo23.h"

static thermo23_t thermo23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo23_cfg_t thermo23_cfg;  /**< Click config object. */

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
    thermo23_cfg_setup( &thermo23_cfg );
    THERMO23_MAP_MIKROBUS( thermo23_cfg, MIKROBUS_1 );
    if ( UART_ERROR == thermo23_init( &thermo23, &thermo23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO23_ERROR == thermo23_default_cfg ( &thermo23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature;
    if ( THERMO23_OK == thermo23_read_temperature ( &thermo23, &temperature ) ) 
    {
        log_printf( &logger, " Temperature : %.2f C\r\n\n", temperature );
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
