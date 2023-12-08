/*!
 * @file main.c
 * @brief Barometer 10 Click example
 *
 * # Description
 * This example demonstrates the use of the Barometer 10 Click board™.
 * The demo application reads and calculates pressure and temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example displays the Pressure [mBar] and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer10.h"

static barometer10_t barometer10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer10_cfg_t barometer10_cfg;  /**< Click config object. */

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
    barometer10_cfg_setup( &barometer10_cfg );
    BAROMETER10_MAP_MIKROBUS( barometer10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer10_init( &barometer10, &barometer10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER10_ERROR == barometer10_default_cfg ( &barometer10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void ) 
{
    static float pressure, temperature;
    if ( BAROMETER10_OK == barometer10_get_pressure( &barometer10, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.2f [mbar] \r\n", pressure );
    }
    
    if ( BAROMETER10_OK == barometer10_get_temperature( &barometer10, &temperature ) )
    {
        log_printf( &logger, " Temperature : %.2f [deg c] \r\n", temperature );
    }
    log_printf( &logger, "------------------------\r\n" );
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
