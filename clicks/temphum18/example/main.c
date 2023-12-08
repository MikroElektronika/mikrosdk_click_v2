/*!
 * @file main.c
 * @brief TempHum18 Click example
 *
 * # Description
 * This library contains API for the Temp&Hum 18 Click driver.
 * This demo application shows an example of 
 * relative humidity and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization and default settings, 
 * the app display retrieves the sensor parameters 
 * such as temperature and relative humidity.
 *
 * ## Application Task
 * This is an example that shows the use of a Temp&Hum 18 Click board™.
 * Logs the temperature [ degree Celsius ] and relative humidity [ % ] data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum18.h"

static temphum18_t temphum18;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum18_cfg_t temphum18_cfg;  /**< Click config object. */

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
    temphum18_cfg_setup( &temphum18_cfg );
    TEMPHUM18_MAP_MIKROBUS( temphum18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum18_init( &temphum18, &temphum18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM18_ERROR == temphum18_default_cfg ( &temphum18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static float temperature;
    static float humidity;
    
    if ( temphum18_get_temp_hum( &temphum18, TEMPHUM18_RESOLUTION_14_BITS, &temperature, &humidity ) == TEMPHUM18_STATUS_VALID_DATA ) 
    {
        log_printf( &logger, "  Temperature : %.02f C\r\n  Humidity    : %.02f %%\r\n", temperature, humidity );
    } 
    else 
    {
        log_printf( &logger, "     Measurement Error\r\n\tStale Data\r\n" );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
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
