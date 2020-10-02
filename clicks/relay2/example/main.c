/*!
 * \file 
 * \brief Relay 2 Click example
 * 
 * # Description
 * The application is composed of three sections :
 *
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Turns relays on and off.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "relay2.h"

// ------------------------------------------------------------------ VARIABLES

static relay2_t relay2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    relay2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    relay2_cfg_setup( &cfg );
    RELAY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay2_init( &relay2, &cfg );
    log_info( &logger, "---- App Init Done ----" );
}

void application_task ( void )
{
    relay2_relay2_control(&relay2, 1 );
    relay2_relay1_control(&relay2, 1 );
    
    Delay_ms( 1000 );
    
    relay2_relay2_control(&relay2, 0 );
    relay2_relay1_control(&relay2, 0 );
    
    Delay_ms( 1000 );
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
