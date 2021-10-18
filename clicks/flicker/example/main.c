/*!
 * \file 
 * \brief Flicker Click example
 * 
 * # Description
 * This application simple solution if you need to turn a device on and off at specific time intervals.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO and also starts write log.
 * 
 * ## Application Task  
 * This example demonstrates capabilities of Flicker Click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flicker.h"

// ------------------------------------------------------------------ VARIABLES

static flicker_t flicker;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flicker_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    flicker_cfg_setup( &cfg );
    FLICKER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flicker_init( &flicker, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    log_printf( &logger, " *Flicker on!* \r\n" );
    Delay_ms( 500 );
    flicker_engage( &flicker );
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
