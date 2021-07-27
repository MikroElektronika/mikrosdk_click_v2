/*!
 * \file 
 * \brief H-BRIDGE 7 Click example
 * 
 * # Description
 * This example demonstrates the use of H-Bridge 7 click board. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and makes an initial log.
 * 
 * ## Application Task  
 * Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
 * and after that drives it in the reverse direction for 5 seconds, and finally, 
 * disconnects the motor for 2 seconds. Each step will be logged on the USB UART where
 * you can track the program flow.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hbridge7.h"

// ------------------------------------------------------------------ VARIABLES

static hbridge7_t hbridge7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge7_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    hbridge7_cfg_setup( &cfg );
    HBRIDGE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge7_init( &hbridge7, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_FORWARD );
    Delay_ms( 5000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_BRAKE );
    Delay_ms( 2000 );

    log_printf( &logger, "The motor turns in reverse! \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_REVERSE );
    Delay_ms( 5000 );

    log_printf( &logger, "The motor is disconnected (High-Z)!  \r\n" );
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_SLEEP );
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
