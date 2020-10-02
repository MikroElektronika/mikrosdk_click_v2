/*!
 * \file 
 * \brief Nano Power 2 Click example
 * 
 * # Description
 * This application logs the comparators output value on USBUART.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver.
 * 
 * ## Application Task  
 * Checks the comparator's output and logs output value on USBUART.
 * 
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nanopower2.h"

// ------------------------------------------------------------------ VARIABLES

static nanopower2_t nanopower2;
static log_t logger;

NANOPOWER2_RETVAL out_check;
NANOPOWER2_RETVAL out_check_prev;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanopower2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nanopower2_cfg_setup( &cfg );
    NANOPOWER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower2_init( &nanopower2, &cfg );

	log_printf( &logger, "NANO POWER 2 is initialized\r\n" );
	out_check_prev = 2;
}

void application_task ( void )
{
	out_check = nanopower2_check_output( &nanopower2 );
	if ( out_check != out_check_prev )
	{
		log_printf( &logger, "OUT is: %d\r\n", out_check );

		out_check_prev = out_check;
	}
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
