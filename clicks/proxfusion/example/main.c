/*!
 * \file 
 * \brief ProxFusion Click example
 * 
 * # Description
 * This demo-app reads and displays touch events using ProxFusion click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Checks if a new touch event occurred and prints(logs) event message on usbuart.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proxfusion.h"

// ------------------------------------------------------------------ VARIABLES

static proxfusion_t proxfusion;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proxfusion_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proxfusion_cfg_setup( &cfg );
    PROXFUSION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proxfusion_init( &proxfusion, &cfg );

    proxfusion_default_cfg( &proxfusion );
    Delay_ms( 1500 );
    log_info( &logger, "- It waits for a new touch press event. " );
}

void application_task ( void )
{
    uint8_t touch;

    //  Task implementation.

    touch = proxfusion_get_touch( &proxfusion );

    if (  touch == 1  )
    {
        log_printf( &logger, "** Touch 1 is pressed..\r\n" );
    }
    else if ( touch == 2 )
    {
        log_printf( &logger, "** Touch 2 is pressed..\r\n" );
    }
    else if ( touch == 3 )
    {
        log_printf( &logger, "** All the touch is pressed..\r\n" );
    }

    Delay_100ms();
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
