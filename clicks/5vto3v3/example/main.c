/*!
 * @file main.c
 * @brief 5V to 3V3 Click Example.
 *
 * # Description
 * This example demonstrates the use of the 5V to 3V3 Click board to control and
 * toggle all mikroBUS pins. The application alternates between two toggle modes:
 * toggling all pins simultaneously a fixed number of times with a defined delay,
 * and toggling pins sequentially with a separate delay between each pin change.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the 5V to 3V3 Click driver. After driver setup and
 * mikroBUS mapping, the digital output pins are initialized and the example is
 * ready to run.
 *
 * ## Application Task
 * Executes two toggle demonstrations in a loop:
 * - Toggles all output pins together 5 times with a 500 ms delay.
 * - Toggles all output pins sequentially with a 300 ms delay.
 *
 * @note
 * Use a Tester 2 Click board for real-time visual monitoring of mikroBUS pin logic levels.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c5vto3v3.h"

#ifndef MIKROBUS_POSITION_5VTO3V3
    #define MIKROBUS_POSITION_5VTO3V3 MIKROBUS_1
#endif

static c5vto3v3_t c5vto3v3;   /**< 5V to 3V3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c5vto3v3_cfg_t c5vto3v3_cfg;  /**< Click config object. */

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
    c5vto3v3_cfg_setup( &c5vto3v3_cfg );
    C5VTO3V3_MAP_MIKROBUS( c5vto3v3_cfg, MIKROBUS_POSITION_5VTO3V3 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == c5vto3v3_init( &c5vto3v3, &c5vto3v3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Toggling all pins together 5 times with 500ms delay\r\n\n" );
    c5vto3v3_toggle_all ( &c5vto3v3, 5, 500 );

    log_printf( &logger, " Toggling all pins sequentially with 300ms delay\r\n\n" );
    c5vto3v3_toggle_seq ( &c5vto3v3, 300 );
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
