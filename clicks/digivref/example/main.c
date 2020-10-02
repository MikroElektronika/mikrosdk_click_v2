/*!
 * \file 
 * \brief DigiVref Click example
 * 
 * # Description
 * This app changes the reference output voltage. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * Changes the reference output voltage every 3 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digivref.h"

// ------------------------------------------------------------------ VARIABLES

static digivref_t digivref;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    digivref_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digivref_cfg_setup( &cfg );
    DIGIVREF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digivref_init( &digivref, &cfg );
}

void application_task ( void )
{
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_4096mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage(  &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_1024mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
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
