/*!
 * @file main.c
 * @brief Compass 8 Click example
 *
 * # Description
 * This library contains API for the Compass 8 Click driver.
 * The library initializes and defines the I2C drivers to 
 * write and read data from registers, as well as the default 
 * configuration for reading measurement data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Compass 8 Click board.
 * Measures and displays magnetic flux density in microtesla (uT) for X-axis, Y-axis, and Z-axis.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "compass8.h"

static compass8_t compass8;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass8_cfg_t compass8_cfg;  /**< Click config object. */

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
    compass8_cfg_setup( &compass8_cfg );
    COMPASS8_MAP_MIKROBUS( compass8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == compass8_init( &compass8, &compass8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS8_ERROR == compass8_default_cfg ( &compass8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    compass8_axes_t axis; 
    if ( COMPASS8_OK == compass8_get_magnetic_data( &compass8, &axis ) ) 
    {
        log_printf( &logger, " X-axis: %.2f uT\r\n", axis.x );
        log_printf( &logger, " Y-axis: %.2f uT\r\n", axis.y );
        log_printf( &logger, " Z-axis: %.2f uT\r\n", axis.z );
        log_printf( &logger,  "--------------------\r\n" );
        Delay_ms ( 100 );
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
