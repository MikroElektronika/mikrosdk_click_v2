/*!
 * \file 
 * \brief C420mat Click example
 * 
 * # Description
 * This aplication changes the value of the output current.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click SPI driver.
 * 
 * ## Application Task  
 * Periodically changes Iout value.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c420mat.h"

// ------------------------------------------------------------------ VARIABLES

static c420mat_t c420mat;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c420mat_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c420mat_cfg_setup( &cfg );
    C420MAT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c420mat_init( &c420mat, &cfg );
}

void application_task ( void )
{
   c420mat_set_i_out( &c420mat, 56 );                   // sets Iout to 5.6mA
   Delay_ms( 3000 );
   c420mat_set_i_out( &c420mat, 158 );                  // sets Iout to 15.8mA
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
