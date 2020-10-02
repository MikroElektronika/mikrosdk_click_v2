/*!
 * \file 
 * \brief 3xbuck Click example
 * 
 * # Description
 * This specific selection of output voltages makes this Click board™ a perfect choice for an embedded application power supply,
 * as these voltages are the most commonly used values.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver init, enable and configuration Buck 1, Buck 2 and Buck 3.
 * 
 * ## Application Task  
 * Sets variable output voltage and default output voltage.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3xbuck.h"

// ------------------------------------------------------------------ VARIABLES

static c3xbuck_t c3xbuck;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3xbuck_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3xbuck_cfg_setup( &cfg );
    c3xbuck_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3xbuck_init( &c3xbuck, &cfg );
    c3xbuck_default_cfg ( &c3xbuck );
}

void application_task ( void )
{
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_OUTPUT_VOLTAGE_1000mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_OUTPUT_VOLTAGE_1250mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_OUTPUT_VOLTAGE_1500mV );
    Delay_ms( 5000 );
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3, C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    Delay_ms( 5000 );
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
