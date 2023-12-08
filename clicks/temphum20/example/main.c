/*!
 * @file main.c
 * @brief TempHum20 Click example
 *
 * # Description
 * This example demonstrates the use of Temp & Hum 20 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration 
 * which resets the device and sets it to normal operating mode.
 *
 * ## Application Task
 * When the new data is ready, this function reads the temperature and humidity data 
 * and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum20.h"

static temphum20_t temphum20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum20_cfg_t temphum20_cfg;  /**< Click config object. */

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
    temphum20_cfg_setup( &temphum20_cfg );
    TEMPHUM20_MAP_MIKROBUS( temphum20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum20_init( &temphum20, &temphum20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM20_ERROR == temphum20_default_cfg ( &temphum20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float humidity, temperature = 0;
    
    if ( TEMPHUM20_OK == temphum20_get_measurement ( &temphum20, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.3f C\r\n", temperature );
        log_printf ( &logger, " Humidity: %.3f %%\r\n\n", humidity );
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
