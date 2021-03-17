/*!
 * \file 
 * \brief Buck 3 Click example
 * 
 * # Description
 * This example demonstrates the use of Buck 3 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board.
 * 
 * ## Application Task  
 * Checks the PGD pin state which signalize the undervoltage or overvoltage fault or
 * the thermal shutdown condition. 
 * If there's any of the above faults detected it logs a desired message on USB UART.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck3.h"

// ------------------------------------------------------------------ VARIABLES

static buck3_t buck3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck3_cfg_setup( &cfg );
    BUCK3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck3_init( &buck3, &cfg );

    buck3_default_cfg( &buck3 );
    log_info( &logger, "---- Buck 3 is activated ----" );
	Delay_1sec( );
}

void application_task ( void )
{
    uint8_t pg_state;

    //  Task implementation.
    
    pg_state = buck3_get_power_good( &buck3 );
	
    if ( pg_state == 0 )
    {
        log_info
        ( 
            &logger, 
            "---- Overvoltage or thermal shutdown detected ----" 
        );
    }
	Delay_1sec( );
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
