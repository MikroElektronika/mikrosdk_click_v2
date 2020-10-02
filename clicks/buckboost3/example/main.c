/*!
 * \file 
 * \brief Buck-Boost 3 Click example
 * 
 * # Description
 * This application sets buck-boost voltages.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and enable device
 * 
 * ## Application Task  
 * It checks if the input voltage is below the operating voltage.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buckboost3.h"

// ------------------------------------------------------------------ VARIABLES

static buckboost3_t buckboost3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buckboost3_cfg_setup( &cfg );
    BUCKBOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost3_init( &buckboost3, &cfg );
}

void application_task ( void )
{
     uint8_t interrupt_state;

    //  Task implementation.

    interrupt_state = buckboost3_get_interrupt_state( &buckboost3 );
    
    if ( interrupt_state == 0 )
    {
        log_printf( &logger, " Low input voltage !!!\r\n" );
    }

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
