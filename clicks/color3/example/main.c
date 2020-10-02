/*!
 * \file 
 * \brief Color3 Click example
 * 
 * # Description
 * This application return the color of object.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies default settings and makes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Color 3 Click board. It reads 
 * reflected color values and displays the results on USART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color3.h"

// ------------------------------------------------------------------ VARIABLES

static color3_t color3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    color3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    color3_cfg_setup( &cfg );
    COLOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color3_init( &color3, &cfg );
    Delay_ms( 100 );

    color3_set_default_settings( &color3 );
    Delay_ms( 1000 );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Color 3  Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );
}

void application_task ( void )
{
    uint16_t red_data;
    uint16_t green_data;
    uint16_t blue_data;
    uint16_t clear_data;

    clear_data = color3_read_clear_data( &color3 );
    log_printf( &logger, " Clear: %f\r\n", clear_data );

    red_data = color3_read_red_data( &color3 );
    log_printf( &logger, " Red: %d\r\n", red_data);

    green_data = color3_read_green_data( &color3 );
    log_printf( &logger, " Green: %d\r\n", green_data );

    blue_data = color3_read_blue_data( &color3 );
    log_printf( &logger, " Blue: %d\r\n", blue_data );

    log_printf( &logger, "-----------------\r\n" );
    Delay_ms( 500 );
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
