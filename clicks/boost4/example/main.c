/*!
 * \file 
 * \brief Boost4 Click example
 * 
 * # Description
 * This example uses of Boost 4 Click board to set the desired output voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * initializes devices driver and starts write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Boost 4 Click board.
 * Boost 4 Click communicates with register via SPI by write value to the 
 * TPS61230A chip. This example shows how to set the desired output voltage, 
 * by cycling through a couple of predefined voltage values. All data logs 
 * write on usb uart for aproximetly every 3 sec.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost4.h"

// ------------------------------------------------------------------ VARIABLES

static boost4_t boost4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boost4_cfg_setup( &cfg );
    BOOST4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost4_init( &boost4, &cfg );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "        Boost 4 Click        \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    boost4_enable( &boost4, BOOST4_ENABLE );
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, " Set the max Vout  ~ 5.25 V \r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MAX );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );

    log_printf( &logger, " Set the min Vout  ~ 3.05 V \r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MIN );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
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
