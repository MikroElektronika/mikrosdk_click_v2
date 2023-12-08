/*!
 * @file main.c
 * @brief TempHum 24 Click example
 *
 * # Description
 * This example demonstrates the use of Temp & Hum 24 click board by reading
 * the temperature and humidity data.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which
 * resets the device and starts the auto measurement mode with data rate of 1 Hz.
 *
 * ## Application Task
 * Reads the temperature (degrees C) and the relative humidity (%RH) data and 
 * displays the results on the USB UART approximately once per second. It also
 * reads and displays the minimum and maximum values measured since the beginning
 * of measurements.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum24.h"

static temphum24_t temphum24;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum24_cfg_t temphum24_cfg;  /**< Click config object. */

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
    temphum24_cfg_setup( &temphum24_cfg );
    TEMPHUM24_MAP_MIKROBUS( temphum24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum24_init( &temphum24, &temphum24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM24_ERROR == temphum24_default_cfg ( &temphum24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temp = 0, hum = 0;
    if ( TEMPHUM24_OK == temphum24_read_temp_and_rh ( &temphum24, &temp, &hum ) )
    {
        float min_temp = 0, max_temp = 0;
        float min_rh = 0, max_rh = 0;
        log_printf ( &logger, " Temperature: %.2f C\r\n", temp );
        if ( TEMPHUM24_OK == temphum24_read_temp_history ( &temphum24, &min_temp, &max_temp ) )
        {
            log_printf ( &logger, " MIN: %.2f C\r\n MAX: %.2f C\r\n", min_temp, max_temp );
        }
        log_printf ( &logger, "\r\n Humidity: %.1f %%RH\r\n", hum );
        if ( TEMPHUM24_OK == temphum24_read_rh_history ( &temphum24, &min_rh, &max_rh ) )
        {
            log_printf ( &logger, " MIN: %.1f %%RH\r\n MAX: %.1f %%RH\r\n", min_rh, max_rh );
        }
        log_printf ( &logger, "----------------------\r\n" );
        Delay_ms ( 1000 );
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
