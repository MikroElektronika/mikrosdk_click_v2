/*!
 * @file main.c
 * @brief IPD 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of IPD 2 Click by toggling the output state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Toggles OUT1 and OUT2 state every 3 seconds and displays both outputs state and
 * status diagnostics pin state. If the status pin is HIGH it indicates that the fault
 * condition on this output has occurred and the output is disabled.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ipd2.h"

static ipd2_t ipd2;     /**< IPD 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipd2_cfg_t ipd2_cfg;  /**< Click config object. */

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
    ipd2_cfg_setup( &ipd2_cfg );
    IPD2_MAP_MIKROBUS( ipd2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ipd2_init( &ipd2, &ipd2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    ipd2_enable_out1 ( &ipd2 );
    ipd2_disable_out2 ( &ipd2 );
    Delay_ms ( 100 );
    log_printf( &logger, " OUT1: enabled\r\n" );
    log_printf( &logger, " OUT2: disabled\r\n" );
    log_printf( &logger, " ST1: %s\r\n", ( char * ) ( ipd2_get_st1_pin ( &ipd2 ) ? "high" : "low" ) );
    log_printf( &logger, " ST2: %s\r\n\n", ( char * ) ( ipd2_get_st2_pin ( &ipd2 ) ? "high" : "low" ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    ipd2_disable_out1 ( &ipd2 );
    ipd2_enable_out2 ( &ipd2 );
    Delay_ms ( 100 );
    log_printf( &logger, " OUT1: disabled\r\n" );
    log_printf( &logger, " OUT2: enabled\r\n" );
    log_printf( &logger, " ST1: %s\r\n", ( char * ) ( ipd2_get_st1_pin ( &ipd2 ) ? "high" : "low" ) );
    log_printf( &logger, " ST2: %s\r\n\n", ( char * ) ( ipd2_get_st2_pin ( &ipd2 ) ? "high" : "low" ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
