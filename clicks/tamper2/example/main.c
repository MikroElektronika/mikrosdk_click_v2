/*!
 * \file 
 * \brief Tamper 2 Click example
 * 
 * # Description
 * This application sets switch on ON or OFF.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Sends HAL pointers
 * 
 * ## Application Task  
 * Detects whether the state of switch on Tamper 2 click is ON or OFF.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tamper2.h"

// ------------------------------------------------------------------ VARIABLES

static tamper2_t tamper2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    tamper2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    tamper2_cfg_setup( &cfg );
    TAMPER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tamper2_init( &tamper2, &cfg );
}

void application_task ( )
{
    uint8_t on_state;
    uint8_t off_state;

    on_state = tamper2_get_on_state( &tamper2 );
    off_state = tamper2_get_off_state( &tamper2 );

    if ( on_state == 1 )
    {
        log_printf( &logger, "Tamper 2 click is in ON state.\r\n" );
		
    }

    if ( off_state == 1 )
    {
       log_printf( &logger, "Tamper 2 click is in OFF state.\r\n" );
		
    }

    Delay_ms( 200 );
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
