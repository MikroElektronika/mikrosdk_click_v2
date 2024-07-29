/*!
 * @file main.c
 * @brief Proximity 20 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 20 click board by reading and 
 * displaying the proximity data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the click default configuration.
 *
 * ## Application Task
 * Reads the proximity data from 2 sensors and displays the results on the USB UART every 200ms.
 * The higher the proximity value, the closer the detected object.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity20.h"

static proximity20_t proximity20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity20_cfg_t proximity20_cfg;  /**< Click config object. */

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
    proximity20_cfg_setup( &proximity20_cfg );
    PROXIMITY20_MAP_MIKROBUS( proximity20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity20_init( &proximity20, &proximity20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY20_ERROR == proximity20_default_cfg ( &proximity20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t ps_data_u2 = 0;
    uint16_t ps_data_u3 = 0;
    if ( PROXIMITY20_OK == proximity20_read_proximity ( &proximity20, &ps_data_u2, &ps_data_u3 ) )
    {
        log_printf ( &logger, " PS data [U2]: %u\r\n", ps_data_u2 );
        log_printf ( &logger, " PS data [U3]: %u\r\n\n", ps_data_u3 );
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
