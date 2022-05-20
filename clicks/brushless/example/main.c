/*!
 * \file 
 * \brief Brushless Click example
 * 
 * # Description
 * This example showcases how to initialize and use the Brushless click. 
 * The click has a brushless motor driver which controls the work 
 * of the motor through the BLDC terminal. 
 * In order for this example to work a motor and a power supply are needed. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of a Brushless Click board.
 * Brushless Click communicates with the register via the PWM interface.
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
#include "brushless.h"

// ------------------------------------------------------------------ VARIABLES

static brushless_t brushless;
static log_t logger;
uint8_t brushless_direction = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    brushless_cfg_t cfg;

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
    brushless_cfg_setup( &cfg );
    BRUSHLESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms( 100 );
    
    brushless_init( &brushless, &cfg );
    brushless_pwm_start( &brushless );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 1000 );
}

void application_task ( )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( brushless_direction == 1 )
    {
        brushless_spin_clockwise ( &brushless );
        log_printf( &logger, "<<<< " );
    }
    else
    {
        brushless_spin_counter_clockwise ( &brushless );
        log_printf( &logger, ">>>> " );
    }

    brushless_set_duty_cycle ( &brushless, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
                
        if ( brushless_direction == 1 )
        {
            brushless_direction = 0;
        }
        else if ( brushless_direction == 0 )
        {
            brushless_direction = 1;
        }
    }
    duty_cnt += duty_inc;
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
