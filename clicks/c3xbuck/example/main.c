/*!
 * \file 
 * \brief 3xBuck Click example
 * 
 * # Description
 * This example sets voltages on the 3xBuck Click Board
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C module and set INT pin, PWM pin and AN pin as OUTPUT
 * 
 * ## Application Task  
 * Initializes the driver init, enable and configuration Buck 1, Buck 2 and Buck 3.
 * 
 * *note:* 
 *  Default output voltage on Buck 1 is 1800mV, Buck 2 is 3300mV and Buck 3 is 5000mV
 *  Variable output voltage on all Bucks from 680mV to 1950mV
 * 
 * \author Petar Suknjaja
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

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3xbuck_cfg_setup( &cfg );
    C3XBUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3xbuck_init( &c3xbuck, &cfg );
    c3xbuck_default_cfg ( &c3xbuck );
    log_info( &logger, "---- System Init ----" );
}

void application_task ( void )
{
    //  Task implementation.
    log_printf( &logger, "Setting predefined values : \r\n" );
    log_printf( &logger, "Buck 1 : 1000 mV\r\n");
    log_printf( &logger, "Buck 2 : 1250 mV\r\n");
    log_printf( &logger, "Buck 3 : 1500 mV\r\n");
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1,  C3XBUCK_OUTPUT_VOLTAGE_1000mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2,  C3XBUCK_OUTPUT_VOLTAGE_1250mV );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3,  C3XBUCK_OUTPUT_VOLTAGE_1500mV );
    
    Delay_ms( 5000 );
    
    log_printf( &logger, "Setting default values: \r\n");
    log_printf( &logger, "Buck 1 : 1800 mV\r\n");
    log_printf( &logger, "Buck 2 : 3300 mV\r\n");
    log_printf( &logger, "Buck 3 : 5000 mV\r\n");
    
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_1,  C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_2,  C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    c3xbuck_set_voltage( &c3xbuck, C3XBUCK_SELECT_BUCK_3,  C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE );
    
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
