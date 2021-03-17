/*!
 * \file 
 * \brief Buck 8 Click example
 * 
 * # Description
 * Demo application shows basic usage of BUCK 8 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configures the driver and enables the click board.
 * 
 * ## Application Task  
 * Reads the VOUT state and parses it on USB UART.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck8.h"

// ------------------------------------------------------------------ VARIABLES

static buck8_t buck8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck8_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck8_cfg_setup( &cfg );
    BUCK8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck8_init( &buck8, &cfg );

    buck8_default_cfg( &buck8 );
}

void application_task ( void )
{
    uint8_t pg_state;
    
    pg_state = buck8_get_state( &buck8 );
    
    if ( pg_state == 1 )
    {
        log_info( &logger, "VOUT is below 92.2%% of VIN" );
    }
    else
    {
        log_info( &logger, "VOUT is above 92.2%% of VIN" );
    }
    
    Delay_1sec();
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
