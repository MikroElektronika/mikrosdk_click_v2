/*!
 * @file main.c
 * @brief AMR Angle 2 Click example
 *
 * # Description
 * This example demonstrates the use of AMR Angle 2 click board by reading and displaying
 * the magnet's angular position in Degrees and a system temperature in Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees and a system temperature in Celsius 
 * and displays the results on the USB UART approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "amrangle2.h"

static amrangle2_t amrangle2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    amrangle2_cfg_t amrangle2_cfg;  /**< Click config object. */

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
    amrangle2_cfg_setup( &amrangle2_cfg );
    AMRANGLE2_MAP_MIKROBUS( amrangle2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == amrangle2_init( &amrangle2, &amrangle2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMRANGLE2_ERROR == amrangle2_default_cfg ( &amrangle2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle, temperature;
    if ( AMRANGLE2_OK == amrangle2_read_angle ( &amrangle2, &angle ) ) 
    {
        log_printf( &logger, " Angle: %.2f Degrees\r\n", angle );
    }
    if ( AMRANGLE2_OK == amrangle2_read_temperature ( &amrangle2, &temperature ) ) 
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
