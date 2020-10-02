/*!
 * \file 
 * \brief H-BRIDGE 7 Click example
 * 
 * # Description
 * H-Bridge 7 Click features flexible motor driver. This Click board integrates 
 * an N-channel H-bridge, charge pump regulator, and protection circuitry. 
 * The charge pump improves efficiency by allowing for both high-side and 
 * low-side N-channels MOSFETs and 100% duty cycle support.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and activates the motor.
 * 
 * ## Application Task  
 * Changes the direction of the motor.
 * 
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

    hbridge7_motor_state( &hbridge7, HBRIDGE7_MOTOR_ACTIVE );
}

void application_task ( void )
{
    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_FORWARD );
    Delay_ms( 3000 );

    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_BACKWARD );
    Delay_ms( 3000 );

    hbridge7_motor_control( &hbridge7, HBRIDGE7_MOTOR_STOP );
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
