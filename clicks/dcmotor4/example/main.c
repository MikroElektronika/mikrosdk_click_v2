/*!
 * \file 
 * \brief DcMotor4 Click example
 * 
 * # Description
 * This library contains API for the DC Motor 4 Click driver.
 * Application change the speed and direction.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
 * set the direction-control of the motor forward movement, PWM initialization,
 * set PWM duty cycle and PWM frequency, enable the motor, start PWM.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the DC Motor 4 Click board.
 * DC Motor 4 Click communicates with register via PWM interface.
 * It shows moving in the Clockwise direction from slow to fast speed
 * and from fast to slow speed, then rotating Counter Clockwise,
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * \author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor4.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor4_t dcmotor4;
static log_t logger;
uint8_t dcmotor_direction = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor4_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    dcmotor4_cfg_setup( &cfg );
    DCMOTOR4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms ( 100 );
    dcmotor4_init( &dcmotor4, &cfg );
    dcmotor4_pwm_start( &dcmotor4 );
}

void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor_direction == 1 )
    {
        dcmotor4_run_clockwise ( &dcmotor4 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
    }
    else
    {
        dcmotor4_run_counter_clockwise ( &dcmotor4 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
    }
    
    dcmotor4_set_duty_cycle ( &dcmotor4, duty );
    dcmotor4_enable_motor ( &dcmotor4 );
    
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        
        if ( dcmotor_direction == 1 )
        {
            dcmotor_direction = 0;
        }
        else
        {
            dcmotor_direction = 1;
        }
    }
    duty_cnt += duty_inc;

    dcmotor4_disable_motor ( &dcmotor4 );
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
