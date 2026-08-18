/*!
 * @file main.c
 * @brief 3D Hall 17 Click example
 *
 * # Description
 * This example demonstrates the use of the 3D Hall 17 Click board by reading
 * and displaying the magnetic flux density on all three axes (X, Y, Z) in
 * Gauss, and the sensor die temperature in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads data from the sensor and displays them on the USB UART every 200ms.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "c3dhall17.h"

#ifndef MIKROBUS_POSITION_3DHALL17
    #define MIKROBUS_POSITION_3DHALL17 MIKROBUS_1
#endif

static c3dhall17_t c3dhall17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall17_cfg_t c3dhall17_cfg;  /**< Click config object. */

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
    c3dhall17_cfg_setup( &c3dhall17_cfg );
    C3DHALL17_MAP_MIKROBUS( c3dhall17_cfg, MIKROBUS_POSITION_3DHALL17 );
    if ( I2C_MASTER_ERROR == c3dhall17_init( &c3dhall17, &c3dhall17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL17_ERROR == c3dhall17_default_cfg ( &c3dhall17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    c3dhall17_data_t meas_data;

    if ( C3DHALL17_OK == c3dhall17_get_data( &c3dhall17, &meas_data ) )
    {
        log_printf( &logger, " Bx: %.1f Gauss\r\n", meas_data.x_val );
        log_printf( &logger, " By: %.1f Gauss\r\n", meas_data.y_val );
        log_printf( &logger, " Bz: %.1f Gauss\r\n", meas_data.z_val );
        log_printf( &logger, " Temperature: %.1f degC\r\n", meas_data.temp_val );
        log_printf( &logger, " ---------------------------\r\n" );
        Delay_ms( 200 );
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
