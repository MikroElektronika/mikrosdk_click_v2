/*!
 * \file 
 * \brief Brushless2 Click example
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
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless2.h"

// ------------------------------------------------------------------ VARIABLES

static brushless2_t brushless2;
static log_t logger;

static float duty_cycle = 0.5;
static uint8_t flag = 0;

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
}

void application_task ( void )
{    
    brushless2_invert_direction( &brushless2 );
    Delay_ms( 6000 );
    
    brushless2_pwm_start( &brushless2 );
    Delay_ms( 100 );
    
    log_printf( &logger, "    acceleration      \r\n" );
    
    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        brushless2_set_duty_cycle ( &brushless2, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 500 );
    }

    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
    log_printf( &logger, "    slowing down     \r\n" );
    
    for ( duty_cycle = 1.0; duty_cycle > 0.09; duty_cycle -= 0.1 )
    {
        brushless2_set_duty_cycle ( &brushless2, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 500 );
    }
    
    brushless2_pwm_stop( &brushless2 );
    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
    Delay_ms( 100 );
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
