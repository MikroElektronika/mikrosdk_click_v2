/*!
 * \file 
 * \brief MCP73871 Click example
 * 
 * # Description
 * This application is battery charger.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click driver, and enables the click board.
 * 
 * ## Application Task  
 * This is the example of MCP73871 click functions usage.
 * It enables this click, sets input current to 100mA, 
 * and enables safety timer.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp73871.h"

// ------------------------------------------------------------------ VARIABLES

static mcp73871_t mcp73871;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp73871_cfg_t cfg;

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

    mcp73871_cfg_setup( &cfg );
    MCP73871_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp73871_init( &mcp73871, &cfg );
}

void application_task ( void )
{
    mcp73871_enable_pin_control( &mcp73871, 1 );
    mcp73871_prog_pin_control( &mcp73871, 0 );
    mcp73871_timer_pin_control( &mcp73871, 0 );
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
