/*!
 * \file 
 * \brief VtoHz Click example
 * 
 * # Description
 * This application converts an analog voltage input signal into a pulse wave signal of a certain frequency.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init
 * Initializes driver and enables the click board. 
 * 
 * ## Application Task  
 * Alternates between different output frequencies.
 * 
 * ## Additional functions
 *  - set_output_frequency - Changing the output frequency by setting the PWM duty cycle to desired value. 
 * 
 * @note Output frequency may vary depending on the offset and gain potentiometers on board the click.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vtohz.h"

// ------------------------------------------------------------------ VARIABLES

static vtohz_t vtohz;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

uint16_t pwm_period;

static uint8_t set_output_frequency ( float frequency )
{
    float duty_cycle;

    if ( frequency > 10000 )
    {
        return -1;
    }
    
    duty_cycle = frequency;
    duty_cycle /= 10000;
    vtohz_set_duty_cycle( &vtohz, duty_cycle );
    vtohz_pwm_start( &vtohz );
    
    return 0;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz_cfg_t cfg;

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

    vtohz_cfg_setup( &cfg );
    VTOHZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz_init( &vtohz, &cfg );
    
    vtohz_enable ( &vtohz );
}

void application_task ( void )
{
    set_output_frequency( 1000 );        //1000 Hz output
    log_printf( &logger, "Output frequency: \t 1000 Hz\r\n" );
    Delay_ms( 5000 );
    set_output_frequency( 2000 );        //2000 Hz output
    log_printf( &logger, "Output frequency: \t 2000 Hz\r\n" );
    Delay_ms( 5000 );
    set_output_frequency( 5000 );        //5000 Hz output
    log_printf( &logger, "Output frequency: \t 5000 Hz\r\n" );
    Delay_ms( 5000 );
    set_output_frequency( 10000 );       //10000 Hz output
    log_printf( &logger, "Output frequency: \t 10000 Hz\r\n" );
    Delay_ms( 5000 );
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
