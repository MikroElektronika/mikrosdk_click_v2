/*!
 * \file 
 * \brief HallCurrent2 Click example
 * 
 * # Description
 * This application very accurately measures current using Hall effect.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and reset chip
 * 
 * ## Application Task  
 * Reads current and logs on usbuart every 1 second.
 * It was tested with 1V voltage at the input and with a load of 1 - 2A.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent2.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent2_t hallcurrent2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent2_cfg_setup( &cfg );
    HALLCURRENT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent2_init( &hallcurrent2, &cfg );

    hallcurrent2_reset( &hallcurrent2 );
}

void application_task ( void )
{
    int16_t current_data;

    //  Task implementation.

    current_data = hallcurrent2_get_current( &hallcurrent2 );
    log_printf( &logger, "--- Current : %d mA\r\n", current_data );
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
