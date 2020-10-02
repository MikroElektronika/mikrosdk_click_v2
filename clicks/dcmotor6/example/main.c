/*!
 * \file 
 * \brief DC MOTOR 6 Click example
 * 
 * # Description
 * This IC includes one channel of motor output block, using a wide range of supply voltages,
 * while delivering reasonably high current to the connected DC motors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes application init.
 * 
 * ## Application Task  
 * Set the motor direction in clockwise and Counte clockwise direction.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor6.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor6_t dcmotor6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    dcmotor6_cfg_setup( &cfg );
    DCMOTOR6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor6_init( &dcmotor6, &cfg );
}

void application_task ( void )
{
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_DIR_CCW );
    Delay_ms( 2000 );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_STOP );
    Delay_ms( 2000 );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_DIR_CW );
    Delay_ms( 2000 );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_STOP );
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
