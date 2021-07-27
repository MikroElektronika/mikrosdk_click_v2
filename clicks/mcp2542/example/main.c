/*!
 * \file 
 * \brief Mcp2542 Click example
 * 
 * # Description
 * This application use for comunication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver intialization.
 * 
 * ## Application Task  
 * Checks if new data byte have received in rx buffer (ready for reading),
 * and if ready than reads one byte from rx buffer. In second case aplication task writes
 * message data via UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp2542.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static mcp2542_t mcp2542;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };


void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp2542_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp2542_cfg_setup( &cfg );
    MCP2542_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp2542_init( &mcp2542, &cfg );

     mcp2542_default_cfg( &mcp2542 );
}

void application_task ( void )
{
    char tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp = mcp2542_generic_single_read( &mcp2542 );
       log_printf( &logger, "%c\r\n", tmp );
#endif
#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       mcp2542_generic_multi_write( &mcp2542, demo_message, 9 );
       Delay_ms( 2000 );
#endif

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
