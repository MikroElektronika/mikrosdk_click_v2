/*!
 * \file 
 * \brief Current Click example
 * 
 * # Description
 * This is an example that shows the capabilities of the Current click board 
 * by measuring current in miliampers. Current click board can be used to safely
 * measure DC current in the range of 2-2048mA depending on shunt resistor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI, LOG and click drivers.
 * 
 * ## Application Task  
 * Measures DC current and displays the results on USB UART each second.
 * 
 * @note
 * Shunt resistor used in the example covers 4 default values (0.05 Ohm, 0.2 Ohm, 1 Ohm, 10 Ohm).
 * To operate in linear range of INA196 check table bellow for shunt selection.
 * |------------------------------------|
 * | Rshunt  | Imin [mA]  | Imax  [mA]  |
 * |------------------------------------|
 * |   0.05  |    400     |   2048      |
 * |   0.2   |    100     |    512      |
 * |   1     |     20     |    102      |
 * |  10     |      2     |     10      |
 * --------------------------------------
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "current.h"

// ------------------------------------------------------------------ VARIABLES

static current_t current;
static log_t logger;
static float curr;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    current_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    current_cfg_setup( &cfg );
    CURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current_init( &current, &cfg );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Current  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void )
{
    curr = current_get_current_data( &current, CURRENT_RSHUNT_0_05 );
    
    if ( curr == CURRENT_OUT_OF_RANGE )
    {
        log_printf( &logger, "Out of range!\r\n" );
    }
    else
    {
       log_printf( &logger, " Current: %.2f mA\r\n", curr );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
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
