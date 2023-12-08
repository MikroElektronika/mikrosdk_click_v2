/*!
 * @file 
 * @brief Leddriver6 Click example
 *
 * # Description
 * This application designed to be used in tunable Smart Connected Lighting applications.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and PWM driver for the LED driver 6 control.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the LED Driver 6 Click board.
 * This example shows the automatic control LED light intensity,
 * the first intensity of light is rising and then the intensity of light is falling.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nikola Peric
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver6.h"

static leddriver6_t leddriver6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    leddriver6_cfg_t leddriver6_cfg;

    //  Click initialization.

    leddriver6_cfg_setup( &leddriver6_cfg );
    LEDDRIVER6_MAP_MIKROBUS( leddriver6_cfg, MIKROBUS_1 );

    if ( leddriver6_init( &leddriver6, &leddriver6_cfg ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );
    
    leddriver6_set_duty_cycle ( &leddriver6, 0.0 );
    if ( leddriver6_pwm_start( &leddriver6 ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- PWM can't be started. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- PWM is started. ----" );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    leddriver6_set_duty_cycle ( &leddriver6, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
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
