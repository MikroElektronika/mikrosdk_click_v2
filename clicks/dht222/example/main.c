/*!
 * \file 
 * \brief DHT22 2 Click example
 * 
 * # Description
 * This example demonstrates the use of DHT22 2 click board by reading
 * the temperature and humidity data.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the temperature (degrees C) and the relative humidity (%RH) data and 
 * displays the results on the USB UART approximately once per second.
 * 
 * \author MikroE Team
 *
 */
#include "board.h"
#include "log.h"
#include "dht222.h"

static dht222_t dht222;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    dht222_cfg_t cfg;

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

    //  Click initialization.
    dht222_cfg_setup( &cfg );
    DHT222_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dht222_init( &dht222, &cfg );
    Delay_ms( 500 );
}

void application_task ( void )
{
    uint16_t temperature = 0;
    uint16_t humidity = 0;
    if ( DHT222_OK == dht222_get_temp_hum ( &dht222, &temperature, &humidity ) )
    {
        log_printf( &logger, " Humidity   : %.1f %%\r\n", ( float ) humidity / 10 );
        log_printf( &logger, " Temperature: %.1f C \r\n", ( float ) temperature / 10 );
        log_printf( &logger, "---------------------\r\n" );
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
