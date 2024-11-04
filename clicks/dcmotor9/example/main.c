/*!
 * @file main.c
 * @brief DC Motor 9 Click Example
 *
 * # Description
 * DC Motor 9 Click is a brushed DC motor driver with the current limiting and
 * current sensing. It can be operated by two logic signals, allowing to drive
 * the connected motor in two different ways:
 * it can use fixed logic levels for the direction control,
 * or it can be controlled by a PWM signal, offering an additional speed control
 * option.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes GPIO, PWM and logger and enables the Click board.
 *
 * ## Application Task
 * This is a example which demonstrates the use of DC Motor 9 Click board.
 * DC Motor 9 Click controls DC Motor speed via PWM interface.
 * It shows moving in the both directions from slow to fast speed
 * and from fast to slow speed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor9.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor9_t dcmotor9;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor9_cfg_t dcmotor9_cfg;

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

    dcmotor9_cfg_setup( &dcmotor9_cfg );
    DCMOTOR9_MAP_MIKROBUS( dcmotor9_cfg, MIKROBUS_1 );
    if ( dcmotor9_init( &dcmotor9, &dcmotor9_cfg ) == PWM_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }

    dcmotor9_set_duty_cycle ( &dcmotor9, DCMOTOR9_PWM_DUTY_PERCENT_0 );
    
    dcmotor9_enable( &dcmotor9 );
    dcmotor9_pwm_start( &dcmotor9 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    static float duty;
    static uint8_t n_cnt;
    
    dcmotor9_clockwise ( &dcmotor9 );
    log_printf( &logger, "> CLOCKWISE <\r\n" );
    dcmotor9_enable ( &dcmotor9 );
    
    for ( n_cnt = 10; n_cnt > 0; n_cnt--  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++ )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9,  duty );
        Delay_ms ( 500 );
    }
    
    log_printf( &logger, "* Pull break *\r\n" );
    dcmotor9_short_brake( &dcmotor9 );
    Delay_ms ( 1000 );
    
    dcmotor9_counter_clockwise ( &dcmotor9 );
    log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
        
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 10; n_cnt > 0; n_cnt-- )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor9_set_duty_cycle( &dcmotor9,  duty );
        Delay_ms ( 500 );
    }
    
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
