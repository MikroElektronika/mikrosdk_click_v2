/*!
 * \file 
 * \brief BATT-MAN Click example
 * 
 * # Description
 * BATT-MAN click is a very versatile battery operated power manager. When powered via mikroBUS,
 * it will charge the connected Li-Ion/Li-Po 3.7V battery, while providing the output voltage 
 * on all its outputs at the same time.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes pin direction and logger utility and click driver.
 * 
 * ## Application Task  
 * Alternates between enabled and disabled state.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "battman.h"

// ------------------------------------------------------------------ VARIABLES

static battman_t battman;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    battman_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    battman_cfg_setup( &cfg );
    BATTMAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    battman_init( &battman, &cfg );
}

void application_task ( void )
{
    battman_set_enable( &battman, 1 );
    log_printf( &logger, "Click enabled.\r\n" );
    Delay_ms( 10000 );
    log_printf( &logger, "Click disabled.\r\n" );
    battman_set_enable( &battman, 0 );
    Delay_ms( 10000 );
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
