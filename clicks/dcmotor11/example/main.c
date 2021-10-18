/*!
 * \file 
 * \brief DcMotor11 Click example
 * 
 * # Description
 * This application is motor driver with the current limiting and current sensing.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and sets first motor settings.
 * 
 * ## Application Task  
 * Waits for valid user input and executes functions based on set of valid commands.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor11.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor11_t dcmotor11;
static log_t logger;

uint8_t motor_speed;
uint8_t motor_dir;
uint8_t f_motor_state = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor11_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor11_cfg_setup( &cfg );
    DCMOTOR11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor11_init( &dcmotor11, &cfg );

    dcmotor11_get_fault( &dcmotor11 );
    
    // Start settings 
    motor_dir = DCMOTOR11_DIRECTION_FORWARD;
    motor_speed = DCMOTOR11_VSET_480mV;
    dcmotor11_control( &dcmotor11, DCMOTOR11_DIRECTION_FORWARD, motor_speed );
}

void application_task ( void )
{
    // Speed increase 
    motor_speed += 4;
    if ( motor_speed >= DCMOTOR11_VSET_4820mV )
    {
        log_printf( &logger, "---- MAX SPEED ---- \r\n" );
        motor_speed = DCMOTOR11_VSET_4820mV;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
    else
    {
        log_printf( &logger, "---- Speed increase ---- \r\n" );
        log_printf( &logger, " MOTOR SPEED: %d \r\n", motor_speed );
        
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms( 2000 );

    // Speed decrease 
    motor_speed -= 4;
    if ( motor_speed < DCMOTOR11_VSET_480mV )
    {
        log_printf( &logger, "---- MIN SPEED ---- \r\n" );
        motor_speed = DCMOTOR11_VSET_480mV;
    }
    else
    {
        log_printf( &logger, "---- Speed decrease ---- \r\n");
        log_printf( &logger, " MOTOR SPEED: %d \r\n", motor_speed );
        
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms( 2000 );

    // Stop / Start
    if( f_motor_state == 1 )
    {
        log_printf( &logger,"---- Stop Motor!!! ---- \r\n" );
        f_motor_state = 0;
        dcmotor11_stop( &dcmotor11 );
    }
    else
    {
        log_printf( &logger,"---- Start Motor ---- \r\n" );
        f_motor_state = 1;
        motor_speed = DCMOTOR11_VSET_480mV;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }

    Delay_ms ( 2000 );

    // Direction - Forward / Backword 
    if ( motor_dir == 2 )
    {
        log_printf( &logger,"---- Direction - [FORWARD] ---- \r\n" );
        motor_dir = 1;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
    else
    {
        log_printf( &logger,"---- Direction - [BACKWARD] ---- \r\n" );
        motor_dir = 2;
        dcmotor11_control( &dcmotor11, motor_dir, motor_speed );
    }
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
