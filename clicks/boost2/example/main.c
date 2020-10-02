/*!
 * \file 
 * \brief Boost 2 Click example
 * 
 * # Description
 * This application features very high efficiency, low noise and anti-ringing voltage output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver.
 * 
 * ## Application Task  
 * Demonstrates the use of the click drivers function. It
shows how to enable or disable click operation, and how to check if supplied
voltage is good.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost2.h"

// ------------------------------------------------------------------ VARIABLES

static boost2_t boost2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    boost2_cfg_setup( &cfg );
    BOOST2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost2_init( &boost2, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "Enabling click operation... \r\n" );
    boost2_set_en_pin( &boost2, 1 );
    Delay_ms(3000);
    
    log_printf( &logger, "Checking output voltage... \r\n" );
    Delay_ms(500);
    if ( boost2_get_pg_pin( &boost2 ))
    {
        log_printf( &logger, "Output voltage good. \r\n" );
    }
    else
    {
        log_printf( &logger, "Output voltage incorrect. \r\n" );
    }
    Delay_ms(3000);
    
    log_printf( &logger, "Disabling click operation... \r\n" );
    boost2_set_en_pin( &boost2, 0 );
    Delay_ms(5000);
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
