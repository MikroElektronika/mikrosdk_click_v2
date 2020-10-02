/*!
 * \file 
 * \brief DigiPot Click example
 * 
 * # Description
 * The demo application changes the resistance using DIGIPOT Click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI and LOG modules.
 *
 * ## Application Task
 * This is an example which demonstrates the use of DIGI POT Click board.
 * Increments the wiper position by 10 positions every 5 seconds.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digipot.h"

// ------------------------------------------------------------------ VARIABLES

static digipot_t digipot;
static log_t logger;

uint8_t wiper_pos;
uint16_t n_cnt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digipot_cfg_setup( &cfg );
    DIGIPOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot_init( &digipot, &cfg );

    log_printf( &logger, "     DIGI POT Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.

    for ( n_cnt = 127; n_cnt < 255; n_cnt += 10 )
    {
        wiper_pos = ( uint8_t ) n_cnt;
        digipot_set_wiper_positions( &digipot, wiper_pos );
        Delay_ms( 5000 );
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
