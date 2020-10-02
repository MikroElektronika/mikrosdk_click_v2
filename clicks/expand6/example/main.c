/*!
 * \file 
 * \brief Expand6 Click example
 * 
 * # Description
 * This demo app shows the capabilities of the EXPAND 6.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the
 * EXPAND 6 click by toggling each of 20 available pins.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "expand6.h"

// ------------------------------------------------------------------ VARIABLES

static expand6_t expand6;
static log_t logger;

uint8_t pin_num;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand6_cfg_setup( &cfg );
    EXPAND6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand6_init( &expand6, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 6 click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}

void application_task ( void )
{
    log_printf( &logger, " PORT 0 \r\n" );
    for ( pin_num = 0; pin_num < 8; pin_num++ )
    {
        expand6_write_port( &expand6, EXPAND6_PORT_0, 0xFF );
        expand6_write_pin( &expand6, pin_num, EXPAND6_LOW );
        log_printf( &logger, "Pin %d is low! \r\n", pin_num );
        Delay_ms( 500 );
        expand6_write_port( &expand6, EXPAND6_PORT_0, 0xFF );
    }

    Delay_ms( 1000 );

    log_printf( &logger, " PORT 1 \r\n" );
    for ( pin_num = 8; pin_num < 16; pin_num++ )
    {
        expand6_write_port( &expand6, EXPAND6_PORT_1, 0xFF );
        expand6_write_pin( &expand6, pin_num, EXPAND6_LOW );
        log_printf( &logger, "Pin %d is low!\r\n", pin_num );

        Delay_ms( 500 );
        expand6_write_port( &expand6, EXPAND6_PORT_1, 0xFF );
    }

    Delay_ms( 1000 );

    log_printf( &logger, " PORT 2 \r\n" );
    for ( pin_num = 16; pin_num < 20; pin_num++ )
    {
        expand6_write_port( &expand6, EXPAND6_PORT_2, 0xFF );
        expand6_write_pin( &expand6, pin_num, EXPAND6_LOW );
        log_printf( &logger, "Pin %d is low!\r\n", pin_num );

        Delay_ms( 500 );
        expand6_write_port( &expand6, EXPAND6_PORT_2, 0xFF );
    }
    log_printf( &logger, "-------------------\r\n" );
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
