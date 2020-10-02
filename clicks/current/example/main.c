/*!
 * \file 
 * \brief Current Click example
 * 
 * # Description
 * Demo app measures and displays current by using Current click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI, LOG and click drivers.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the Current click board 
 * by measuring current in miliampers. Current click board can be used to safely
 * measure current ranging from 2mA to 2048mA.
 * 
 * *note:* 
 * It is important to provide the shunt of the appropriate value.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "current.h"

// ------------------------------------------------------------------ VARIABLES

static current_t current;
static log_t logger;
static float curr;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    current_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    current_cfg_setup( &cfg );
    CURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current_init( &current, &cfg );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Current  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.
    curr = current_get_current_data( &current, CURRENT_RSHUNT_10 );
    
    if ( curr == CURRENT_OUT_OF_RANGE )
    {
        log_printf( &logger, "Out of range!\r\n" );
    }
    else
    {
       log_printf( &logger, " Current: %.2f mA\r\n", curr );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
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
