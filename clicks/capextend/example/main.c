/*!
 * \file 
 * \brief CapExtend Click example
 * 
 * # Description
 * This example showcases the initialization and configuration of the logger and click modules
 * and later on shows how to read and display the 16-bit button map ( LSB + MSB ).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules.
 * 
 * ## Application Task  
 * This function collects map data and displays the 16-bit button map, where each bit that has
 * the value 1 represents a button that has been pressed.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "capextend.h"

// ------------------------------------------------------------------ VARIABLES

static capextend_t capextend;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    capextend_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    capextend_cfg_setup( &cfg );
    CAPEXTEND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capextend_init( &capextend, &cfg );
    capextend_reset( &capextend );
}

void application_task ( )
{
    uint8_t msb;
    uint8_t lsb;

    msb = capextend_read_msb_buttons( &capextend );
    lsb = capextend_read_lsb_buttons( &capextend );

    // LSB

    log_printf( &logger, " * ---------LSB--------- * \r\n" );
    log_printf( &logger, " * | %d", ( lsb & 0x80 ) >> 7 );
    log_printf( &logger, " %d", ( lsb & 0x40 ) >> 6 );
    log_printf( &logger, " %d", ( lsb & 0x20 ) >> 5 );
    log_printf( &logger, " %d |",( lsb & 0x10 ) >> 4 );
    log_printf( &logger, " %d", ( lsb & 0x08 ) >> 3 );
    log_printf( &logger, " %d", ( lsb & 0x04 ) >> 2 );
    log_printf( &logger, " %d", ( lsb & 0x02 ) >> 1 );
    log_printf( &logger, " %d | * \r\n", lsb & 0x01 );

    // MSB

    log_printf( &logger, " * ---------MSB--------- * \r\n" );
    log_printf( &logger, " * | %d", ( msb & 0x80 ) >> 7 );
    log_printf( &logger, " %d", ( msb & 0x40 ) >> 6 );
    log_printf( &logger, " %d", ( msb & 0x20 ) >> 5 );
    log_printf( &logger, " %d |",( msb & 0x10 ) >> 4 );
    log_printf( &logger, " %d", ( msb & 0x08 ) >> 3 );
    log_printf( &logger, " %d", ( msb & 0x04 ) >> 2 );
    log_printf( &logger, " %d", ( msb & 0x02 ) >> 1 );
    log_printf( &logger, " %d | * \r\n", msb & 0x01 );

    log_printf( &logger, " * ----------------------- * \r\n\r\n" );
    Delay_ms( 500 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
