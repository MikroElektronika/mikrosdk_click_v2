/*!
 * \file 
 * \brief Motion 3 Click example
 * 
 * # Description
 * This application motion detector sensitive only to live bodies.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Maps pins and enables device.
 * 
 * ## Application Task  
 * Waiting for motion to be detected.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "motion3.h"

// ------------------------------------------------------------------ VARIABLES

static motion3_t motion3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    motion3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    motion3_cfg_setup( &cfg );
    MOTION3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion3_init( &motion3, &cfg );
}

void application_task ( void )
{
    uint8_t int_status;

    int_status = motion3_get_int( &motion3 );

    if ( int_status != MOTION3_INTERRUPT_NOT_DETECT )
    {
        log_printf( &logger, "Motion detected \r\n" );
        while ( int_status != MOTION3_INTERRUPT_NOT_DETECT )
        {
            int_status = motion3_get_int( &motion3 );
        }
        log_printf( &logger, "Motion wait \r\n" );
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
