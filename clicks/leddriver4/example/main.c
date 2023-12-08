/*!
 * @file 
 * @brief LedDriver4 Click example
 * 
 * # Description
 * This click has the ability to dim the connected LED array, without producing any noise on the output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the GPIO driver and
 * configures the PWM peripheral for controlling the LED array intensity.
 * 
 * ## Application Task  
 * Increases and decreases LED array intensity
 * ( first increases light intensity to the maximum and then decreases to the minimum ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver4.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver4_t leddriver4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver4_cfg_t cfg;

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

    leddriver4_cfg_setup( &cfg );
    LEDDRIVER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver4_init( &leddriver4, &cfg );
    
    leddriver4_set_duty_cycle ( &leddriver4, 0.0 );
    leddriver4_pwm_start( &leddriver4 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    leddriver4_set_duty_cycle ( &leddriver4, duty );
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
