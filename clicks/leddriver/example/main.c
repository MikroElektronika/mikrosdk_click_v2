/*!
 * \file 
 * \brief LedDriver Click example
 * 
 * # Description
 * This application controls the brightness.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * PWM initialization set PWM duty cycle and PWM frequency and start PWM.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of LED Driver Click board.
 * LED Driver Click communicates with register via PWM interface.
 * This example shows the automatic control halogen bulb light intensity,
 * the first intensity of light is rising and then the intensity of light is falling.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver_t leddriver;
static log_t logger;

static float duty_ratio;


void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
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

    duty_ratio = 0;

    log_info( &logger, "---- Init Done ----\r\n" );
    leddriver_set_duty_cycle( &leddriver, duty_ratio );
    leddriver_pwm_start( &leddriver );
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, " Light Intensity Rising\r\n" );

    for ( duty_ratio = 0.1; duty_ratio < 1; duty_ratio += 0.1 )
    {
        leddriver_set_duty_cycle(  &leddriver, duty_ratio );
        Delay_ms( 1000 );
    }

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, " Light Intensity Falling\r\n" );

    for ( duty_ratio = 1; duty_ratio >= 0; duty_ratio -= 0.1 )
    {
        leddriver_set_duty_cycle(  &leddriver, duty_ratio );
        Delay_ms( 1000 );
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
