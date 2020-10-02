/*!
 * \file 
 * \brief Alcohol3 Click example
 * 
 * # Description
 * Code of this sensor reacts to the presence of deoxidizing and reducing gases,
 * such as ethanol (also known as alcohol).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * Reads percentage of alcohol in the blood (BAC) 
 * and this data logs to USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "alcohol3.h"

// ------------------------------------------------------------------ VARIABLES

static alcohol3_t alcohol3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    alcohol3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms ( 100 );

    //  Click initialization.

    alcohol3_cfg_setup( &cfg );
    ALCOHOL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alcohol3_init( &alcohol3, &cfg );

    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ---- Alcohol 3 Click ----\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );

    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    uint16_t co_ppm;
    uint16_t p_bac;

    //  Task implementation.

    log_printf( &logger, " --- Alcohol diagnostics ---- \r\n" );

    co_ppm = alcohol3_get_co_in_ppm ( &alcohol3 );
    log_printf( &logger, " co in ppm  %d    | \r\n", co_ppm );

    p_bac = alcohol3_get_percentage_bac( &alcohol3 ) * 1000;

    if ( 10 > p_bac && p_bac < 100 )
    {
        log_printf( &logger, " BAC    %d  | 0.00\r\n", p_bac );
    }
    else if ( 100 <= p_bac && 1000 > p_bac )
    {
        log_printf( &logger, " BAC    %d  | 0.00\r\n", p_bac );
    }
    else if ( p_bac >= 1000 )
    {
        log_printf( &logger, " BAC    %d  | 0.\r\n", p_bac );
    }
    else
    {
        log_printf( &logger, " BAC  | 0.0000\r\n" );
    }
    log_printf( &logger, " ---------------------------- \r\n" );

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
