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
 * and from fast to slow speed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor_t dcmotor;
static log_t logger;
uint8_t dcmotor_direction = 1;

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
    
    dcmotor_set_duty_cycle ( &dcmotor, 0.0 );
    dcmotor_pwm_start( &dcmotor );
    log_printf( &logger, "---------------------\r\n" );
}

void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor_direction == 1 )
    {
        dcmotor_sleep_mode ( &dcmotor );
        dcmotor_right_direction_slow ( &dcmotor );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
        dcmotor_enable ( &dcmotor );
    }
    else
    {
        dcmotor_sleep_mode ( &dcmotor );
        dcmotor_left_direction_slow ( &dcmotor );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        dcmotor_enable ( &dcmotor );
    }

    dcmotor_set_duty_cycle ( &dcmotor, duty );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
        
        if ( dcmotor_direction == 1 )
        {
            dcmotor_direction = 0;
        }
        else if ( dcmotor_direction == 0 )
        {
            dcmotor_direction = 1;
        }
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;

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
