/*!
 * \file 
 * \brief T420ma Click example
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
#include "t420ma.h"

// ------------------------------------------------------------------ VARIABLES

static t420ma_t t420ma;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    t420ma_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    t420ma_cfg_setup( &cfg );
    T420MA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    t420ma_init( &t420ma, &cfg );
}

void application_task ( void )
{
   t420ma_set_i_out( &t420ma, 56 );                   // sets Iout to 5.6mA
   Delay_ms( 3000 );
   t420ma_set_i_out( &t420ma, 158 );                  // sets Iout to 15.8mA
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
