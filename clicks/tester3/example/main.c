/*!
 * @file main.c
 * @brief Tester 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of Tester 3 Click board by controlling all
 * LEDs on the Click board together and in sequential pin toggling with different delays.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Toggles all pins together 5 times with a 500ms delay between each toggle, then toggles
 * each pin sequentially with a 300ms delay between toggling each pin.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tester3.h"

#ifndef MIKROBUS_POSITION_TESTER3
    #define MIKROBUS_POSITION_TESTER3 MIKROBUS_1
#endif

static tester3_t tester3;   /**< Tester 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tester3_cfg_t tester3_cfg;  /**< Click config object. */

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
    tester3_cfg_setup( &tester3_cfg );
    TESTER3_MAP_MIKROBUS( tester3_cfg, MIKROBUS_POSITION_TESTER3 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tester3_init( &tester3, &tester3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Toggling all pins together 5 times with 500ms delay\r\n\n" );
    tester3_toggle_all ( &tester3, 5, 500 );

    log_printf( &logger, " Toggling all pins sequentially with 300ms delay\r\n\n" );
    tester3_toggle_seq ( &tester3, 300 );
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
