/*!
 * \file 
 * \brief DcMotor7 Click example
 * 
 * # Description
 * This application is a dual brushed DC motor driving.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, enabled all output port, sets H-Bridge operation mode and Motor Digital tblk
 * 
 * ## Application Task  
 * Set the motor A and the motor B to rotate clockwise and in the Counte clockwise direction, 
 * and between the change of direction, the motor stops the motor.
 * 
 * *note:* 
 * VM input - 10 V (min) to 47 V (max)
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "dcmotor7.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor7_t dcmotor7;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    dcmotor7_cfg_t cfg;

    //  Click initialization.

    dcmotor7_cfg_setup( &cfg );
    DCMOTOR7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor7_init( &dcmotor7, &cfg );

    dcmotor7_default_cfg( &dcmotor7 );
}

void application_task ( void )
{
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_A, 0, 1 );
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_B, 0, 1 );
    Delay_ms ( 500 );
    
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_A );
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_B );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_A, 1, 0 );
    dcmotor7_set_motor( &dcmotor7, DCMOTOR7_MOTOR_B, 1, 0 );
    Delay_ms ( 500 );
    
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_A );
    dcmotor7_motor_stop( &dcmotor7, DCMOTOR7_MOTOR_B );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
