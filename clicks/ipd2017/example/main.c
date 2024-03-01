/*!
 * @file main.c
 * @brief IPD 2017 Click Example.
 *
 * # Description
 * This example demonstrates the use of IPD 2017 click board by toggling the output state.
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
#include "ipd2017.h"

static ipd2017_t ipd2017;   /**< IPD 2017 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipd2017_cfg_t ipd2017_cfg;  /**< Click config object. */

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
    ipd2017_cfg_setup( &ipd2017_cfg );
    IPD2017_MAP_MIKROBUS( ipd2017_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ipd2017_init( &ipd2017, &ipd2017_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Turning OUT 1 to OUT 4 HIGH \r\n" );
    ipd2017_all_pins_set( &ipd2017 );
    Delay_ms( 2000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 LOW \r\n" );
    ipd2017_all_pins_clear( &ipd2017 );
    Delay_ms( 2000 );

    log_printf( &logger, " Turning OUT 1 to OUT 4 one by one \r\n" );
    uint8_t out_sel = IPD2017_OUT1_PIN_MASK;
    do
    {
        ipd2017_set_out_level( &ipd2017, out_sel, IPD2017_PIN_STATE_HIGH );
        Delay_ms( 2000 );
        ipd2017_set_out_level( &ipd2017, out_sel, IPD2017_PIN_STATE_LOW );
        out_sel <<=  1;
    }
    while ( out_sel <= IPD2017_OUT4_PIN_MASK );
    
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
