/*!
 * @file 
 * @brief Stspin250 Click example
 * 
 * # Description
 * This application enables usage of brushed DC motor driver with
 * the current limiting and current sensing.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, PWM init and enable device
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Stspin250 Click board.
 * Stspin250 Click communicates with register via PWM interface.
 * It shows moving in the left direction from slow to fast speed
 * and from fast to slow speed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stspin250.h"

// ------------------------------------------------------------------ VARIABLES

static stspin250_t stspin250;
static log_t logger;
uint8_t motor_direction = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin250_cfg_t cfg;

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

    stspin250_cfg_setup( &cfg );
    STSPIN250_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin250_init( &stspin250, &cfg );

    stspin250_enable( &stspin250, STSPIN250_DEVICE_ENABLE );
    stspin250_set_duty_cycle ( &stspin250, 0.0 );

    stspin250_pwm_start( &stspin250 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( motor_direction == 1 )
    {
        stspin250_set_ph( &stspin250, 1 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
    }
    else
    {
        stspin250_set_ph( &stspin250, 0 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
    }

    stspin250_set_duty_cycle ( &stspin250, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        if ( motor_direction == 1 )
        {
            motor_direction = 0;
        }
        else if ( motor_direction == 0 )
        {
            motor_direction = 1;
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
