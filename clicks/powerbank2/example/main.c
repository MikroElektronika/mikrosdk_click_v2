/*!
 * \file 
 * \brief Powerbank2 Click example
 * 
 * # Description
 * This single chip includes a linear charger, a synchronous Boost with dual output load 
 * management and a torch function support. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the Power Bank 2 click
 * by measuring voltage of the connected battery. In order to get correct calculations 
 * the user should change "v_ref" value to his own power supply voltage.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "powerbank2.h"

// ------------------------------------------------------------------ VARIABLES

static powerbank2_t powerbank2;
static log_t logger;

static uint16_t voltage;
static uint16_t v_ref = 5000; // milivolts

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    powerbank2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    powerbank2_cfg_setup( &cfg );
    POWERBANK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerbank2_init( &powerbank2, &cfg );
}

void application_task ( void )
{
    voltage = powerbank2_read_voltage( &powerbank2, v_ref );

    log_printf( &logger, "Battery voltage: %u mV\r\n", voltage );

    Delay_ms( 2000 );
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
