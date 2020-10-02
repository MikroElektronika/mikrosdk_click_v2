/*!
 * \file 
 * \brief Servo Click example
 * 
 * # Description
 * This app sets servo motor at three different positions 0, 90, 180.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * The servo motor is set at three different positions 0, 90, 180 - every two second,
 * and reads current value witch motor spends in the moment when it runs to new position.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "servo.h"

// ------------------------------------------------------------------ VARIABLES

static servo_t servo;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    servo_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    servo_cfg_setup( &cfg );
    SERVO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    servo_init( &servo, &cfg );
    
    servo_default_cfg( &servo );
}

void application_task ( void )
{
    uint16_t current;

    servo_set_position( &servo, SERVO_MOTOR_1, 0 );
    Delay_ms( 2000 );
    servo_set_position( &servo, SERVO_MOTOR_1, 90 );
    Delay_ms( 1000 );
    servo_set_position( &servo, SERVO_MOTOR_1, 180 );
    Delay_ms( 2000 );
    servo_set_position( &servo, SERVO_MOTOR_1, 90 );

    current = setvo_get_current( &servo, SERVO_POSITIVE_CH0 );
    log_printf( &logger, "Current - %u  mA \r\n", current );

    Delay_ms( 1000 );
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
