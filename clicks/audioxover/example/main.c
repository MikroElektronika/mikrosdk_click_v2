/*!
 * \file 
 * \brief Audio Xover Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Audio Xover click module. The
 * click splits an incoming audio signal into two channels. It has one output pin which serves as
 * a switch. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules.
 * 
 * ## Application Task  
 * This function enables and disables the switch with a 3 second delay between and after the 
 * function calls. Status feedback is printed in the UART console.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioxover.h"

// ------------------------------------------------------------------ VARIABLES

static audioxover_t audioxover;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioxover_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audioxover_cfg_setup( &cfg );
    AUDIOXOVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioxover_init( &audioxover, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, " * Switch: ON *\r\n" );
    digital_out_write( &audioxover.sdn, AUDIOXOVER_ENABLE );
    Delay_ms( 3000 );

    log_printf( &logger, " * Switch: OFF *\r\n" );
    digital_out_write( &audioxover.sdn, AUDIOXOVER_DISABLE );
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
