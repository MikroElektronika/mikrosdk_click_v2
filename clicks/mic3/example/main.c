/*!
 * \file 
 * \brief MIC 3 Click example
 * 
 * # Description
 * The MIC 3 Click is a very easy solution to work with it. It can be used for desktop, 
 * portable or palmtop computers, telephone conferencing, communication headsets, two-way 
 * communication, surveillance system where the microphone is needed, stethoscope, karaoke 
 * and DJ mixers.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Maps GPIO for Mikrobus1.
 * 
 * ## Application Task  
 * This example show use of MIC 3 click. It sets SHD pin to HIGH state, 
 * so the Microphone is ready to use.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic3.h"

// ------------------------------------------------------------------ VARIABLES

static mic3_t mic3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mic3_cfg_setup( &cfg );
    MIC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic3_init( &mic3, &cfg );
}

void application_task ( void )
{
    mic3_set_shd_pin( &mic3, MIC3_PIN_STATE_HIGH );
    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    log_printf( &logger, " - Microphone is turned on - \r\n" );
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
