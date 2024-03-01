/*!
 * @file main.c
 * @brief IPD 2015 Click Example.
 *
 * # Description
 * This example demonstrates the use of IPD 2015 click board by toggling the output state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Switches on all output pins state for 2 seconds, then switches them off, and turns them on one by one.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ipd2015.h"

static ipd2015_t ipd2015;   /**< IPD 2015 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipd2015_cfg_t ipd2015_cfg;  /**< Click config object. */

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
    ipd2015_cfg_setup( &ipd2015_cfg );
    IPD2015_MAP_MIKROBUS( ipd2015_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ipd2015_init( &ipd2015, &ipd2015_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Turning OUT 1 to OUT 4 HIGH \r\n" );
    ipd2015_all_pins_set( &ipd2015 );
    Delay_ms( 2000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 LOW \r\n" );
    ipd2015_all_pins_clear( &ipd2015 );
    Delay_ms( 2000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 one by one \r\n" );
    uint8_t out_sel = IPD2015_OUT1_PIN_MASK;
    do
    {
        ipd2015_set_out_level( &ipd2015, out_sel, IPD2015_PIN_STATE_HIGH );
        Delay_ms( 2000 );
        ipd2015_set_out_level( &ipd2015, out_sel, IPD2015_PIN_STATE_LOW );
        out_sel <<=  1;
    }
    while ( out_sel <= IPD2015_OUT4_PIN_MASK );
    
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
