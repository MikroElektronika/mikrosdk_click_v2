/*!
 * @file main.c
 * @brief Proximity17 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 17 click board by reading and 
 * displaying the proximity data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the click default configuration.
 *
 * ## Application Task
 * Reads the proximity data and displays it on the USB UART approximately once per second.
 * The higher the proximity value, the closer the detected object is.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity17.h"

static proximity17_t proximity17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity17_cfg_t proximity17_cfg;  /**< Click config object. */

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
    proximity17_cfg_setup( &proximity17_cfg );
    PROXIMITY17_MAP_MIKROBUS( proximity17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity17_init( &proximity17, &proximity17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY17_ERROR == proximity17_default_cfg ( &proximity17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t proximity;
    if ( PROXIMITY17_OK == proximity17_read_proximity ( &proximity17, &proximity ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n\n", proximity );
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
