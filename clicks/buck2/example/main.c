/*!
 * \file 
 * \brief Buck 2 Click example
 * 
 * # Description
 * The demo application displays output voltage change.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Sets a different range of input voltages 
 * every 3 sec and checks if it has reached the set output voltage.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck2.h"

// ------------------------------------------------------------------ VARIABLES

static buck2_t buck2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck2_cfg_setup( &cfg );
    BUCK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck2_init( &buck2, &cfg );

    buck2_default_cfg( &buck2 );
}

void application_task ( void )
{
    uint8_t pg_state;

    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state != 0 )
    {
        log_info( &logger, "---- Power good output voltage ----" );
    }

    log_info( &logger, "---- Output voltage is 3300 mV ----" );
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_3300mV );
    Delay_ms( 3000 );
    log_info( &logger, "---- Output voltage is 2500 mV ----" );
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_2500mV );
    Delay_ms( 3000 );
    log_info( &logger, "---- Output voltage is 1800 mV ----" );
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1800mV );
    Delay_ms( 3000 );
    log_info( &logger, "---- Output voltage is 1500 mV ----" );
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1500mV );
    Delay_ms( 3000 );
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
