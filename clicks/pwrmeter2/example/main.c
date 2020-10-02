/*!
 * \file 
 * \brief PwrMeter2 Click example
 * 
 * # Description
 * This app measuring and monitoring voltage up to 24V and current up to 5A.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Gets calculated voltage, current and power data every 500 miliseconds
 * and shows results on UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pwrmeter2.h"

// ------------------------------------------------------------------ VARIABLES

static pwrmeter2_t pwrmeter2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwrmeter2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pwrmeter2_cfg_setup( &cfg );
    PWRMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwrmeter2_init( &pwrmeter2, &cfg );

    pwrmeter2_default_cfg( &pwrmeter2 );
    log_printf( &logger, "PWR Meter 2 is initialized \r\n" );
    Delay_ms( 200 );
}

void application_task ( void )
{
    int32_t voltage_res;
    int32_t current_res;
    uint32_t power_res;

    pwrmeter2_get_data( &pwrmeter2, &voltage_res, &current_res, &power_res );

    log_printf( &logger, "U = %d mV \r\n", voltage_res );
    log_printf( &logger, "I = %d mV \r\n", current_res );
    log_printf( &logger, "P = %u mV \r\n", power_res );

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
