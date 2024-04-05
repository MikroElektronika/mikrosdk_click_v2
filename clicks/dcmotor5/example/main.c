/*!
 * @file main.c
 * @brief DCMotor5 Click example
 *
 * # Description
 * This library contains API for the DC Motor 5 Click driver.
 * This application enables usage of brushed DC motor 5 gate driver.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes GPIO, PWM and logger and enables the click board.
 *
 * ## Application Task
 * This is a example which demonstrates the use of DC Motor 5 Click board.
 * DC Motor 5 Click controls DC Motor speed via PWM interface.
 * It shows moving in the both directions from slow to fast speed
 * and from fast to slow speed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nikola Peric
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor5.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor5_t dcmotor5;
static log_t logger;
uint8_t dcmotor_direction = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor5_cfg_t cfg;

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

    dcmotor5_cfg_setup( &cfg );
    DCMOTOR5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor5_init( &dcmotor5, &cfg );
    
    log_printf( &logger, " Initialization  PWM \r\n" );

    dcmotor5_pwm_start( &dcmotor5 );
    dcmotor5_enable ( &dcmotor5 );
    Delay_ms ( 500 );
    log_printf( &logger, "---------------------\r\n" );
    log_info( &logger, "---- Application Task ----" );
}


void application_task ( )
{    
    static float duty;
    static uint8_t n_cnt;
    
    
    dcmotor5_clockwise ( &dcmotor5 );
    log_printf( &logger, "\r\n> CLOCKWISE <\r\n" );
    dcmotor5_enable ( &dcmotor5 );
    
    for ( n_cnt = 10; n_cnt > 0; n_cnt--  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        log_printf( &logger, " >" );
        dcmotor5_set_duty_cycle( &dcmotor5, duty );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++ )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        log_printf( &logger, " <" );
        dcmotor5_set_duty_cycle( &dcmotor5,  duty );
        Delay_ms ( 500 );
    }
    
    log_printf( &logger, "\r\n * Pull break *\r\n" );
    dcmotor5_short_brake( &dcmotor5 );
    Delay_ms ( 1000 );
    
    dcmotor5_counter_clockwise ( &dcmotor5 );
    log_printf( &logger, "\r\n> COUNTER CLOCKWISE <\r\n" );
        
    for ( n_cnt = 1; n_cnt <= 10; n_cnt++  )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor5_set_duty_cycle( &dcmotor5, duty );
        log_printf( &logger, " >" );
        Delay_ms ( 500 );
    }
    for ( n_cnt = 10; n_cnt > 0; n_cnt-- )
    {
        duty = ( float ) n_cnt ;
        duty /= 10;
        dcmotor5_set_duty_cycle( &dcmotor5,  duty );
        log_printf( &logger, " <" );
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
