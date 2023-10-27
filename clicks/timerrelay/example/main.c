/*!
 * @file main.c
 * @brief Timer Relay Click example
 *
 * # Description
 * This example demonstrates the use of the Timer Relay Click board by
 * setting the relay timer to 2 seconds ON time, then holding it OFF for 2 more seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration,
 * then setting the ON time to 2 seconds.
 *
 * ## Application Task
 * This example is activating the trigger every 4 seconds activating the relay timer.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "timerrelay.h"

static timerrelay_t timerrelay;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    timerrelay_cfg_t timerrelay_cfg;  /**< Click config object. */

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
    timerrelay_cfg_setup( &timerrelay_cfg );
    TIMERRELAY_MAP_MIKROBUS( timerrelay_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == timerrelay_init( &timerrelay, &timerrelay_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TIMERRELAY_ERROR == timerrelay_default_cfg ( &timerrelay ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( TIMERRELAY_ERROR == timerrelay_set_delay( &timerrelay, 2 ) )
    {
        log_error( &logger, " Value configuration." );
        for ( ; ; );
    }
    
    timerrelay_activate_reset( &timerrelay );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    timerrelay_activate_trigger( &timerrelay );
    log_printf( &logger, " Trigger activated. \r\n" );
    Delay_ms( 4000 );
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
