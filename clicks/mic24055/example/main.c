/*!
 * \file 
 * \brief Mic24055 Click example
 * 
 * # Description
 * This application is the buck regulato.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver.
 * 
 * ## Application Task  
 * Slowly alternates the click output between two values.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic24055.h"

// ------------------------------------------------------------------ VARIABLES

static mic24055_t mic24055;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24055_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mic24055_cfg_setup( &cfg );
    MIC24055_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24055_init( &mic24055, &cfg );
}

void application_task ( void )
{
    mic24055_set_vout( &mic24055, 500 );
    log_printf( &logger, "Setting Vout to 500mV \r\n" );
    Delay_ms( 3000 );
    mic24055_set_vout( &mic24055, 2300 );
    log_printf( &logger, "Setting Vout to 2300mV \r\n" );
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
