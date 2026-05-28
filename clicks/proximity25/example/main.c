/*!
 * @file main.c
 * @brief Proximity 25 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 25 Click board by reading and 
 * displaying the proximity data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the proximity data and displays the results on the USB UART every 200ms.
 * The higher the proximity value, the closer the detected object.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity25.h"

#ifndef MIKROBUS_POSITION_PROXIMITY25
    #define MIKROBUS_POSITION_PROXIMITY25 MIKROBUS_1
#endif

static proximity25_t proximity25;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity25_cfg_t proximity25_cfg;  /**< Click config object. */

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
    proximity25_cfg_setup( &proximity25_cfg );
    PROXIMITY25_MAP_MIKROBUS( proximity25_cfg, MIKROBUS_POSITION_PROXIMITY25 );
    if ( I2C_MASTER_ERROR == proximity25_init( &proximity25, &proximity25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY25_ERROR == proximity25_default_cfg ( &proximity25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t ps_data = 0;
    if ( PROXIMITY25_OK == proximity25_read_proximity ( &proximity25, &ps_data ) )
    {
        log_printf ( &logger, " PS data: %u\r\n\n", ps_data );
        Delay_ms ( 200 );
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
