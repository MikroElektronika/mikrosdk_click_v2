/*!
 * @file 
 * @brief HBridge3 Click example
 * 
 * # Description
 * H-bridge in general, allows the current to flow in one or another direction.
 * This click is used for driving a H-Bridge motor by changing output states. 
 * The outputs can be pulse width modulated at frequencies up to 20kHz by means of PWM/DIR control. 
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI and LOG modules, AN, RST, CS and PWM pins
 * 
 * ## Application Task  
 * This example demonstrates the use of H-Bridge 3 Click board, 
 * by running dc motor in both directions - increasing and decreasing PWM duty cycle.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hbridge3.h"

// ------------------------------------------------------------------ VARIABLES

static hbridge3_t hbridge3;
static log_t logger;
uint8_t motor_direction = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge3_cfg_t cfg;

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

    hbridge3_cfg_setup( &cfg );
    HBRIDGE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge3_init( &hbridge3, &cfg );
    Delay_ms ( 500 );
    
    hbridge3_pwm_start( &hbridge3 );
    log_info( &logger, "---- Application Task ----" );
    log_printf( &logger, "> CLOCKWISE <\r\n" );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;


    hbridge3_set_duty_cycle ( &hbridge3, duty );
    log_printf( &logger, " Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        
        if ( motor_direction == 1 )
        {
            log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
            motor_direction = 0;
             hbridge3_dir_set ( &hbridge3 , 0 );
        }
        else if ( motor_direction == 0 )
        {
            log_printf( &logger, "> CLOCKWISE <\r\n" );
            motor_direction = 1;
            hbridge3_dir_set ( &hbridge3 , 1 );
        }
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
