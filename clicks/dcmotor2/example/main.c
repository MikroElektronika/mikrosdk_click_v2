/*!
 * \file 
 * \brief DcMotor2 Click example
 * 
 * # Description
 * This library contains API for the DC Motor 2 Click driver.
 * This example showcases how to initialize and use the DC Motor 2 click. The click contains a 
 * Driver IC for DC motors which can spin the motor clockwise, counter-clockwise, break it and
 * completely stop the motor. The example needs a DC motor and a power supply in order to work.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the DC Motor 2 Click board.
 * DC Motor 2 Click communicates with register via PWM interface.
 * It shows moving in the Clockwise direction from slow to fast speed
 * and from fast to slow speed, then rotating Counter Clockwise,
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor2.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor2_t dcmotor2;
static log_t logger;
uint8_t dcmotor_direction = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor2_cfg_t cfg;

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
    Delay_ms( 100 );

    //  Click initialization.

    dcmotor2_cfg_setup( &cfg );
    DCMOTOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms( 100 );
    dcmotor2_init( &dcmotor2, &cfg );
    dcmotor2_pwm_start( &dcmotor2 );
    Delay_ms( 1000 );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor_direction == 1 )
    {
        dcmotor2_pull_brake ( &dcmotor2 );
        dcmotor2_spin_clockwise ( &dcmotor2 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
        dcmotor2_enable_motor ( &dcmotor2 );
    }
    else
    {
        dcmotor2_pull_brake ( &dcmotor2 );
        dcmotor2_spin_counter_clockwise ( &dcmotor2 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        dcmotor2_enable_motor ( &dcmotor2 );
    }

    dcmotor2_set_duty_cycle ( &dcmotor2, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );

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
        else if ( dcmotor_direction == 0 )
        {
            dcmotor_direction = 1;
        }
    }
    duty_cnt += duty_inc;

}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
