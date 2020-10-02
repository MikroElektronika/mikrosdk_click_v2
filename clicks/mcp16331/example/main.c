/*!
 * \file 
 * \brief Mcp16331 Click example
 * 
 * # Description
 * This application is buck-boost voltage regulator.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Sends hal pointers, and initializes click
 * 
 * ## Application Task  
 * Switches between 5 V and 12 V values
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp16331.h"

// ------------------------------------------------------------------ VARIABLES

static mcp16331_t mcp16331;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp16331_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp16331_cfg_setup( &cfg );
    MCP16331_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp16331_init( &mcp16331, &cfg );
}

void application_task ( void )
{
    mcp16331_set_vout( &mcp16331, 5000 );
    Delay_ms( 3000 );
    mcp16331_set_vout( &mcp16331, 12000 );
    Delay_ms( 3000 );
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
