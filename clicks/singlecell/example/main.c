/*!
 * \file 
 * \brief Single Cell Click example
 * 
 * # Description
 * Demo application is used to shows basic controls Single Cell click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO and LOG structures,
 * set CS pin as output and start write log.
 * Initialization driver enable's - GPIO, also write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Single Cell board.
 * This example shows the automatic control of the Single Cell click,
 * enable and disable power the regulator output on 10 sec. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "singlecell.h"

// ------------------------------------------------------------------ VARIABLES

static singlecell_t singlecell;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    singlecell_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    singlecell_cfg_setup( &cfg );
    SINGLECELL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlecell_init( &singlecell, &cfg );
    singlecell_default_cfg ( &singlecell );
   
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Single Cell click    \r\n");
    log_printf(&logger, "-------------------------\r\n");

    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf(&logger, "         Enable\r\n");
    singlecell_set_power_mode ( &singlecell, SINGLECELL_ENABLE );
    Delay_ms( 10000 );
    
    log_printf(&logger, "         Disable\r\n");
    singlecell_set_power_mode ( &singlecell, SINGLECELL_DISABLE );
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
