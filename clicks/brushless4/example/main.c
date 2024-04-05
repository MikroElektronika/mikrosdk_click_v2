/*!
 * @file 
 * @brief Brushless 4 Click example
 * 
 * # Description
 * This click has many features for driving a wide range of small to medium BLDC motors.
 * It provides the rotor position digital output, via the FG pin, routed to the mikroBUS INT pin. 
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the GPIO driver 
 * and configures the PWM peripheral for controlling the speed of the motor.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of a Brushless 4 Click board.
 * Brushless 4 Click communicates with the register via the PWM interface.  
 * Increases and decreasing the speed of the motor demonstrate speed control.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless4.h"

// ------------------------------------------------------------------ VARIABLES

static brushless4_t brushless4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless4_cfg_t cfg;

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

    brushless4_cfg_setup( &cfg );
    BRUSHLESS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless4_init( &brushless4, &cfg );
    
    brushless4_set_duty_cycle ( &brushless4, 0.0 );
    brushless4_pwm_start( &brushless4 );  
      
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    brushless4_set_duty_cycle ( &brushless4, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
        log_printf( &logger, " Slowing down... \r\n" );
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        log_printf( &logger, " Increasing the motor speed... \r\n" );
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
