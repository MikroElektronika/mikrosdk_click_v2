/*!
 * @file main.c
 * @brief Tilt 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Tilt 5 Click board, which detects 
 * tilt motion using a ball switch sensor. The example initializes the device 
 * and continuously monitors the tilt state, logging changes between active 
 * and idle states.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the Tilt 5 Click board.
 *
 * ## Application Task
 * Continuously reads the tilt state and logs changes. The state toggles between 
 * "ACTIVE" when a tilt is detected and "IDLE" when the sensor is in its default 
 * position.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tilt5.h"

static tilt5_t tilt5;   /**< Tilt 5 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tilt5_cfg_t tilt5_cfg;  /**< Click config object. */

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
    tilt5_cfg_setup( &tilt5_cfg );
    TILT5_MAP_MIKROBUS( tilt5_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt5_init( &tilt5, &tilt5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t old_state = TILT5_STATE_IDLE;
    uint8_t state = tilt5_get_out_pin ( &tilt5 );
    if ( state != old_state )
    {
        old_state = state;
        if ( TILT5_STATE_ACTIVE == state )
        {
            log_printf( &logger, "State: ACTIVE\r\n\n" );
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
