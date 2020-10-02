/*!
 * \file 
 * \brief GainAmp2 Click example
 * 
 * # Description
 * This application is programmable gain amplifier
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes CS pin as output and SPI module
 * 
 * ## Application Task  
 * Setup GainAMP 2 click channel 4 to amplify the signal 4 times
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gainamp2.h"

// ------------------------------------------------------------------ VARIABLES

static gainamp2_t gainamp2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gainamp2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gainamp2_cfg_setup( &cfg );
    GAINAMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gainamp2_init( &gainamp2, &cfg );

    gainamp2_default_cfg( &gainamp2 );

    log_printf( &logger,"Channel 4 - aplified 4x \r\n " );
}

void application_task( void )
{
    // Nothing to do here
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
