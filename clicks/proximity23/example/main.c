/*!
 * @file main.c
 * @brief Proximity 23 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 23 Click board by reading and 
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
#include "proximity23.h"

static proximity23_t proximity23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity23_cfg_t proximity23_cfg;  /**< Click config object. */

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
    proximity23_cfg_setup( &proximity23_cfg );
    PROXIMITY23_MAP_MIKROBUS( proximity23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity23_init( &proximity23, &proximity23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY23_ERROR == proximity23_default_cfg ( &proximity23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t ps_data = 0;
    if ( PROXIMITY23_OK == proximity23_read_proximity ( &proximity23, &ps_data ) )
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
