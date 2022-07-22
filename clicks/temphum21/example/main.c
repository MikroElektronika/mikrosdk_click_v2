/*!
 * @file main.c
 * @brief TempHum21 Click example
 *
 * # Description
 * This example demonstrates the use of Temp & Hum 21 click board by reading
 * the temperature and humidity data.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the temperature (Celsius) and humidity (Percents) data and displays the
 * results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum21.h"

static temphum21_t temphum21;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum21_cfg_t temphum21_cfg;  /**< Click config object. */

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
    temphum21_cfg_setup( &temphum21_cfg );
    TEMPHUM21_MAP_MIKROBUS( temphum21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum21_init( &temphum21, &temphum21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature, humidity;
    if ( TEMPHUM21_STATUS_NORMAL_OP == temphum21_read_measurement ( &temphum21, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f C\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%\r\n\n", humidity );
        Delay_ms ( 1000 );
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
