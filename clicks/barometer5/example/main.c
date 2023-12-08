/*!
 * @file main.c
 * @brief Barometer5 Click example
 *
 * # Description
 * This library contains API for Barometer 5 Click driver.
 * The demo application reads and calculate temperature and pressure data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Barometer 5 Click board™.
 * In this example, display the Pressure ( mBar ) and Temperature ( degree Celsius ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer5.h"

static barometer5_t barometer5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer5_cfg_t barometer5_cfg;  /**< Click config object. */

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
    barometer5_cfg_setup( &barometer5_cfg );
    BAROMETER5_MAP_MIKROBUS( barometer5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer5_init( &barometer5, &barometer5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER5_ERROR == barometer5_default_cfg ( &barometer5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static float temperature;
    static float pressure;
    
    if ( barometer5_get_data( &barometer5, &temperature, &pressure ) == BAROMETER5_OK )
    {
        log_printf( &logger, " Pressure    : %.2f mbar   \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C      \r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );
    }
    
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
