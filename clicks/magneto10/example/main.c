/*!
 * @file main.c
 * @brief Magneto10 Click example
 *
 * # Description
 * This example demonstrates the use of Magneto 10 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the magnetic flux as well as the internal temperature data every 100ms 
 * and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneto10.h"

static magneto10_t magneto10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    magneto10_cfg_t magneto10_cfg;  /**< Click config object. */

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
    magneto10_cfg_setup( &magneto10_cfg );
    MAGNETO10_MAP_MIKROBUS( magneto10_cfg, MIKROBUS_1 );
    
    if ( I2C_MASTER_ERROR == magneto10_init( &magneto10, &magneto10_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( MAGNETO10_ERROR == magneto10_default_cfg( &magneto10 ) ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float x_axis, y_axis, z_axis, temperature;
    if ( MAGNETO10_OK == magneto10_get_magnetic_flux ( &magneto10, &x_axis, &y_axis, &z_axis ) )
    {
        log_printf( &logger, " X-axis: %.2f uT\r\n Y-axis: %.2f uT\r\n Z-axis: %.2f uT\r\n", 
                    x_axis, y_axis, z_axis );
    }
    if ( MAGNETO10_OK == magneto10_get_temperature ( &magneto10, &temperature ) )
    {
        log_printf( &logger, " Internal temperature: %.2f C\r\n\n", temperature );
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
