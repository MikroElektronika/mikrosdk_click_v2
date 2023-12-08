/*!
 * \file 
 * \brief LedDriver Click example
 * 
 * # Description
 * This library contains API for the LED Driver Click driver.
 * This application controls the brightness.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * PWM initialization set PWM duty cycle and PWM frequency and start PWM.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the LED Driver Click board.
 * LED Driver Click communicates with register via PWM interface.
 * This example shows the automatic control halogen bulb light intensity,
 * the first intensity of light is rising and then the intensity of light is falling.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver_t leddriver;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver_cfg_t cfg;

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

    leddriver_cfg_setup( &cfg );
    LEDDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    if ( LEDDRIVER_OK != leddriver_init( &leddriver, &cfg ) )
    {
        log_info( &logger, "---- Init Error ----" );
        log_info( &logger, "---- Run program again ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Init Done ----\r\n" );
    leddriver_set_duty_cycle ( &leddriver, 0.0 );
    leddriver_pwm_start( &leddriver );
    Delay_ms( 100 );
    log_info( &logger, "---- Application Task ----\r\n" );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver_set_duty_cycle ( &leddriver, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 500 );
    
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
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
