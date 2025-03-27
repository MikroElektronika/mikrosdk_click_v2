/*!
 * @file main.c
 * @brief Tilt 6 Click Example.
 *
 * # Description
 * This example demonstrates the functionality of the Tilt 6 Click board, which detects 
 * tilt motion in multiple directions. The example continuously monitors tilt movements,
 * logging when the sensor detects a left tilt, right tilt, or remains idle.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the Tilt 6 Click board.
 *
 * ## Application Task
 * Continuously reads the tilt state and logs changes. The sensor can detect three states: 
 * "RIGHT TILT", "LEFT TILT", and "IDLE" indicating no tilt.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tilt6.h"

static tilt6_t tilt6;   /**< Tilt 6 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tilt6_cfg_t tilt6_cfg;  /**< Click config object. */

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
    tilt6_cfg_setup( &tilt6_cfg );
    TILT6_MAP_MIKROBUS( tilt6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt6_init( &tilt6, &tilt6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t old_state = TILT6_STATE_IDLE;
    uint8_t state = tilt6_get_tilt_state ( &tilt6 );
    if ( state != old_state )
    {
        old_state = state;
        if ( TILT6_STATE_RIGHT_TILT == state )
        {
            log_printf( &logger, "State: RIGHT TILT\r\n\n" );
        }
        else if ( TILT6_STATE_LEFT_TILT == state )
        {
            log_printf( &logger, "State: LEFT TILT\r\n\n" );
        }
        else
        {
            log_printf( &logger, "State: IDLE\r\n\n" );
        }
        Delay_ms ( 100 );
    }
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
