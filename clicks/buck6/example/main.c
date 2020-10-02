/*!
 * \file 
 * \brief BUCK6 Click example
 * 
 * # Description
 * BUCK 6 click is an advanced synchronous DC-DC step down (buck) converter, 
 * with a very wide input voltage range and reasonably high output current. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization Driver init and settings chip on ACTIVE mode and setting the maximum range to 5V.
 * 
 * ## Application Task  
 * Sets the different ranges of the maximum voltage.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck6.h"

// ------------------------------------------------------------------ VARIABLES

static buck6_t buck6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck6_cfg_setup( &cfg );
    BUCK6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck6_init( &buck6, &cfg );

    buck6_set_mode( &buck6, BUCK6_ACTIVE_MODE );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_5000mV );
    Delay_ms( 100 );
}

void application_task ( void )
{
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_2500mV );
    Delay_ms( 3000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_5000mV );
    Delay_ms( 3000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_7500mV );
    Delay_ms( 3000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_10000mV );
    Delay_ms( 3000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_7500mV );
    Delay_ms( 3000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_5000mV );
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
