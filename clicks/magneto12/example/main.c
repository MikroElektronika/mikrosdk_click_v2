/*!
 * @file main.c
 * @brief Magneto 12 Click Example.
 *
 * # Description
 * This example demonstrates the use of Magneto 12 click board by reading and displaying
 * the magnet's angular position in degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees every 100ms and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneto12.h"

static magneto12_t magneto12;   /**< Magneto 12 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto12_cfg_t magneto12_cfg;  /**< Click config object. */

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
    magneto12_cfg_setup( &magneto12_cfg );
    MAGNETO12_MAP_MIKROBUS( magneto12_cfg, MIKROBUS_1 );
    err_t init_flag = magneto12_init( &magneto12, &magneto12_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float angle = 0;
    if ( MAGNETO12_OK == magneto12_read_angle ( &magneto12, &angle ) )
    {
        log_printf( &logger, " Angle: %.2f degrees\r\n\n", angle );
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
