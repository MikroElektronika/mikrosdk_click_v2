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
 * v2hz_setOutputFrequency - Sets the PWM duty cycle to required value, changing
   the output frequency.
 * 
 * ## Application Task  
 * Alternates between different output frequencies.
 * 
 * Note: Output frequency may vary, depending on the offset and gain potentiometers 
   on board the click.
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

static void set_output_frequency ( float frequency )
{
    float duty_cycle;

    duty_cycle *= frequency;
    duty_cycle /= 10000;
    vtohz_set_duty_cycle( &vtohz, duty_cycle );
    vtohz_pwm_start( &vtohz );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vtohz_cfg_setup( &cfg );
    VTOHZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz_init( &vtohz, &cfg );

    vtohz_pwm_start( &vtohz );
}

void application_task ( void )
{
    set_output_frequency( 1000 );        //1000 Hz output
    Delay_ms( 3000 );
    set_output_frequency( 2000 );        //2000 Hz output
    Delay_ms( 3000 );
    set_output_frequency( 5000 );        //5000 Hz output
    Delay_ms( 3000 );
    set_output_frequency( 10000 );       //10000 Hz output
    Delay_ms( 3000 );
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
