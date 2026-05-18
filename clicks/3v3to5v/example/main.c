/*!
 * @file main.c
 * @brief 3V3 to 5V Click Example.
 *
 * # Description
 * This example demonstrates the use of the 3V3 to 5V Click board to control and
 * toggle all mikroBUS pins. The application alternates between two toggle modes:
 * toggling all pins simultaneously a fixed number of times with a defined delay,
 * and toggling pins sequentially with a separate delay between each pin change.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the 3V3 to 5V Click driver. After driver setup and
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
#include "c3v3to5v.h"

#ifndef MIKROBUS_POSITION_3V3TO5V
    #define MIKROBUS_POSITION_3V3TO5V MIKROBUS_1
#endif

static c3v3to5v_t c3v3to5v;   /**< 3V3 to 5V Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3v3to5v_cfg_t c3v3to5v_cfg;  /**< Click config object. */

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
    c3v3to5v_cfg_setup( &c3v3to5v_cfg );
    C3V3TO5V_MAP_MIKROBUS( c3v3to5v_cfg, MIKROBUS_POSITION_3V3TO5V );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == c3v3to5v_init( &c3v3to5v, &c3v3to5v_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Toggling all pins together 5 times with 500ms delay\r\n\n" );
    c3v3to5v_toggle_all ( &c3v3to5v, 5, 500 );

    log_printf( &logger, " Toggling all pins sequentially with 300ms delay\r\n\n" );
    c3v3to5v_toggle_seq ( &c3v3to5v, 300 );
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
