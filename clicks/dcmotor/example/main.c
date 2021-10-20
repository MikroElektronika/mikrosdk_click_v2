/*!
 * \file 
 * \brief DcMotor Click example
 * 
 * # Description
 * This application change the speed and direction of DC Motor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
 * PWM initialization, set PWM duty cycle and PWM frequency, enable the motor, start PWM and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DC Motor Click board.
 * DC Motor Click communicates with register via PWM interface.
 * It shows moving in the left direction from slow to fast speed
 * and moving in the right direction from fast to slow speed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor_t dcmotor;
static log_t logger;

static float duty_cycle = 0.5;


void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor_cfg_t cfg;

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

    dcmotor_cfg_setup( &cfg );
    DCMOTOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor_init( &dcmotor, &cfg );

    log_printf( &logger, " Initialization  PWM \r\n" );
   
    dcmotor_enable( &dcmotor );
    dcmotor_pwm_start( &dcmotor );
    Delay_ms( 1000 );
    log_printf( &logger, "---------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.
   
    log_printf( &logger, "    Left Direction   \r\n" );
    dcmotor_left_direction_slow( &dcmotor );
    dcmotor_enable( &dcmotor );
    Delay_ms( 100 );

    for ( duty_cycle = 0.1; duty_cycle < 1; duty_cycle += 0.1 )
    {
        dcmotor_set_duty_cycle( &dcmotor, duty_cycle );
        log_printf( &logger, " <\r\n" );
        Delay_ms( 1000 );
    }

    dcmotor_sleep_mode( &dcmotor );
    Delay_ms( 1000 );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Right Direction   \r\n" );

    dcmotor_right_direction_slow( &dcmotor );
    dcmotor_enable( &dcmotor );
    Delay_ms( 100 );

    for ( duty_cycle = 0.1; duty_cycle < 1; duty_cycle += 0.1)
    {
        dcmotor_set_duty_cycle( &dcmotor, duty_cycle );
        log_printf( &logger, " >\r\n" );
        Delay_ms( 1000 );
    }
  
    log_printf( &logger, "---------------------\r\n" );
    dcmotor_sleep_mode( &dcmotor );
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
