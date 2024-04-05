/*!
 * @file 
 * @brief Brushless2 Click example
 * 
 * # Description
 * This application controlled speed motor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO, PWM initialization
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Brushless 2 Click board.
 * Brushless 2 Click communicates with register via PWM interface.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless2.h"

// ------------------------------------------------------------------ VARIABLES

static brushless2_t brushless2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless2_cfg_t cfg;

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

    brushless2_cfg_setup( &cfg );
    BRUSHLESS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless2_init( &brushless2, &cfg );
    
    log_printf( &logger, "---------------------- \r\n" );
    
    brushless2_set_duty_cycle ( &brushless2, 0.0 );
    brushless2_pwm_start ( &brushless2 );
    Delay_ms ( 500 );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless2_set_duty_cycle ( &brushless2, duty );
    brushless2_clockwise ( &brushless2 );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
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
