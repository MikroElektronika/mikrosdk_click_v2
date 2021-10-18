/*!
 * \file 
 * \brief UvcLight Click example
 * 
 * # Description
 * This click has ultraviolet LEDs with 275nm wavelength. UVC radiation refers to wavelengths 
 * shorter than 280 nm. Because of the spectral sensitivity of DNA, only the UVC region 
 * demonstrates significant germicidal properties.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver.
 * 
 * ## Application Task  
 * Increases and decreases the pwm duty cycle.
 * 
 * CAUTION! High intensity UV Light - avoid eye and skin exposure. Avoid looking direclty at light!
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uvclight.h"

// ------------------------------------------------------------------ VARIABLES

static uvclight_t uvclight;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uvclight_cfg_t cfg;

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

    uvclight_cfg_setup( &cfg );
    UVCLIGHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvclight_init( &uvclight, &cfg );

    uvclight_pwm_start( &uvclight );
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, "Increasing PWM duty cycle...\r\n" );
    
    for ( duty_cycle = 0; duty_cycle < 1.0; duty_cycle += 0.1 )
    {
        uvclight_set_duty_cycle ( &uvclight, duty_cycle );
        Delay_ms( 100 );
    }

    Delay_ms( 500 );
    
    log_printf( &logger, "Decreasing PWM duty cycle...\r\n" );
    for ( duty_cycle = 1.0; duty_cycle >= 0; duty_cycle-= 0.1 )
    {
        uvclight_set_duty_cycle ( &uvclight, duty_cycle );
        Delay_ms( 100 );
    }
    log_printf( &logger, "-------------------------------\r\n" );

    Delay_ms( 500 );
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
