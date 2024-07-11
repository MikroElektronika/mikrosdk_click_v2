/*!
 * @file main.c
 * @brief Proximity 19 Click example
 *
 * # Description
 * This example demonstrates the use of the Proximity 19 click board 
 * by measuring and displaying the distance data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * The demo app measures the distance between the sensor and the object in millimeters 
 * and displays the result approximately every 100 milliseconds.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity19.h"

static proximity19_t proximity19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity19_cfg_t proximity19_cfg;  /**< Click config object. */

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
    proximity19_cfg_setup( &proximity19_cfg );
    PROXIMITY19_MAP_MIKROBUS( proximity19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity19_init( &proximity19, &proximity19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY19_ERROR == proximity19_default_cfg ( &proximity19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float distance = 0;
    if ( PROXIMITY19_OK == proximity19_get_distance( &proximity19, &distance ) )
    {
        log_printf( &logger, " Distance: %.2f [mm] \r\n\n", distance );
    }
    Delay_ms ( 100 );
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
