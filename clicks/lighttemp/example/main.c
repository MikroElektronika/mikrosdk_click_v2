/*!
 * @file 
 * @brief LightTemp Click example
 * 
 * # Description
 * This application controls light intensity of LEDs.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and pwm init for all LED's
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the Light Temp Click board.
 * This example shows the automatic control of the LED light intensity,
 * the first intensity of light is rising and then the intensity of light is falling.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * ## NOTE
 * In order to control LED2 via PWM, the PWM module should be available at CS pin. 
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lighttemp.h"

// ------------------------------------------------------------------ VARIABLES

static lighttemp_t lighttemp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lighttemp_cfg_t cfg;

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
    Delay_ms ( 100 );
    
    //  Click initialization.

    lighttemp_cfg_setup( &cfg );
    LIGHTTEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lighttemp_init( &lighttemp, &cfg );
    
    lighttemp_led1_set_duty_cycle ( &lighttemp, 0.0 );
    lighttemp_led2_set_duty_cycle ( &lighttemp, 0.0 );
    
    log_info( &logger, "---- Application Task ----" );

    Delay_ms ( 500 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    lighttemp_led1_set_duty_cycle ( &lighttemp, duty );
    lighttemp_led2_set_duty_cycle ( &lighttemp, duty );
    
    lighttemp_led1_pwm_start( &lighttemp );
    lighttemp_led2_pwm_start( &lighttemp );

    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
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
