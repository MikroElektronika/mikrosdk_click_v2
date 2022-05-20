/*!
 * @file 
 * @brief DcMotor3 Click example
 * 
 * # Description
 * This click has four operating modes: clockwise, counter-clockwise, short brake and stop. 
 * The operating mode is configured through IN1 and IN2 pins.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
 * PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DC Motor 3 Click board.
 * DC Motor 3 Click communicates with register via PWM interface.
 * It shows moving in the left direction from slow to fast speed
 * and from fast to slow speed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor3.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor3_t dcmotor3;
static log_t logger;
uint8_t dcmotor3_direction = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor3_cfg_t cfg;

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

    dcmotor3_cfg_setup( &cfg );
    DCMOTOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor3_init( &dcmotor3, &cfg );

    dcmotor3_set_duty_cycle ( &dcmotor3, 0.0 );
    dcmotor3_pwm_start( &dcmotor3 );
    Delay_ms( 1000 );
    dcmotor3_enable( &dcmotor3 );
    Delay_ms( 1000 );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( dcmotor3_direction == 1 )
    {
        dcmotor3_clockwise( &dcmotor3 );
        log_printf( &logger, ">>>> CLOCKWISE " );
        dcmotor3_enable ( &dcmotor3 );
    }
    else
    {
        dcmotor3_counter_clockwise( &dcmotor3 );
        log_printf( &logger, "<<<< COUNTER CLOCKWISE " );
        dcmotor3_enable ( &dcmotor3 );
    }

    dcmotor3_set_duty_cycle ( &dcmotor3, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
                
        if ( dcmotor3_direction == 1 )
        {
            dcmotor3_direction = 0;
        }
        else if ( dcmotor3_direction == 0 )
        {
            dcmotor3_direction = 1;
        }
    }
    duty_cnt += duty_inc;
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
