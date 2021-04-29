/*!
 * \file 
 * \brief ClockGen3 Click example
 * 
 * # Description
 * This example demonstrates the use of Clock Gen 3 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board.
 * 
 * ## Application Task  
 * Sets different frequencies every 3 seconds and displays the set frequency 
 * on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "clockgen3.h"

// ------------------------------------------------------------------ VARIABLES

static clockgen3_t clockgen3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    clockgen3_cfg_setup( &cfg );
    CLOCKGEN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen3_init( &clockgen3, &cfg );

    clockgen3_config( &clockgen3, CLOCKGEN3_CFG_ON_CLK_180 );
    Delay_ms( 500 );
}

void application_task ( void )
{
    log_printf( &logger, ">> Set Freq = 12.000 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 12000.0 );
    Delay_ms( 3000 );
    log_printf( &logger, ">> Set Freq = 8.000 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 8000.0 );
    Delay_ms( 3000 );
    log_printf( &logger, ">> Set Freq = 5.500 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 5500.0 );
    Delay_ms( 3000 );
    log_printf( &logger, ">> Set Freq = 2.700 MHz \r\n" );
    clockgen3_set_freq( &clockgen3, 2700.0 );
    Delay_ms( 3000 );
    log_printf( &logger, ">> Set Freq = 800 KHz \r\n" );
    clockgen3_set_freq( &clockgen3, 800.0 );
    Delay_ms( 3000 );
    log_printf( &logger, ">> Set Freq = 200 KHz \r\n" );
    clockgen3_set_freq( &clockgen3, 200.0 );
    Delay_ms( 3000 );
    log_printf( &logger, "---------------------------- \r\n" );
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
