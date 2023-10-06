/*!
 * @file main.c
 * @brief Hall Current 17 Click example
 *
 * # Description
 * This example demonstrates the use of Hall Current 17 Click board™ 
 * by reading and displaying the current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads the current measurements [A] and displays the results.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent17.h"

static hallcurrent17_t hallcurrent17;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent17_cfg_t hallcurrent17_cfg;  /**< Click config object. */

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
    hallcurrent17_cfg_setup( &hallcurrent17_cfg );
    HALLCURRENT17_MAP_MIKROBUS( hallcurrent17_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hallcurrent17_init( &hallcurrent17, &hallcurrent17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLCURRENT17_ERROR == hallcurrent17_default_cfg ( &hallcurrent17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static float current = 0.0;
    if ( HALLCURRENT17_OK == hallcurrent17_get_current( &hallcurrent17, &current ) )
    {
        log_printf( &logger, " Current: %.3f [A]\r\n", current );
    }
    log_printf( &logger, " --------------------\r\n" );
    Delay_ms( 1000 );
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
