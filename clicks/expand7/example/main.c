/*!
 * \file 
 * \brief Expand7 Click example
 * 
 * # Description
 * This example demonstrates the use of the EXPAND 7 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the EXPAND 7 click by toggling 
 * each of the 40 available pins.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "expand7.h"

// ------------------------------------------------------------------ VARIABLES

static expand7_t expand7;
static log_t logger;

uint8_t pin_num;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand7_cfg_setup( &cfg );
    EXPAND7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand7_init( &expand7, &cfg );
    Delay_ms( 100 );
    
    expand7_reset( &expand7 );
    Delay_ms( 1000 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 7 click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}

void application_task ( void )
{
    expand7_write_all ( &expand7, 0xFF );
    log_printf( &logger, "All pins set to HIGH logic level!\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 2000 );
    
    for ( pin_num = 0; pin_num < 40; pin_num++ )
    {
        expand7_write_pin( &expand7, pin_num, EXPAND7_LOW );
        log_printf( &logger, "Pin %u is set to LOW logic level!\r\n", ( uint16_t) pin_num );
        Delay_ms( 300 );
    }
    log_printf( &logger, "---------------------------------\r\n" );
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
