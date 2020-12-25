/*!
 * \file 
 * \brief LightTemp Click example
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
 * Increases/decreases light intensity.
 * 
 * ## NOTE
 * In order to control LED2 via PWM, the PWM module should be available at CS pin. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lighttemp.h"

// ------------------------------------------------------------------ VARIABLES

static lighttemp_t lighttemp;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lighttemp_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );
    
    //  Click initialization.

    lighttemp_cfg_setup( &cfg );
    LIGHTTEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lighttemp_init( &lighttemp, &cfg );

    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, ">>> Increasing LEDs light intensity \r\n" );
    
    lighttemp_led1_pwm_start( &lighttemp );
    lighttemp_led2_pwm_start( &lighttemp );
    
    for ( duty_cycle = 0.1; duty_cycle <= 0.5; duty_cycle += 0.1 )
    {
        lighttemp_led1_set_duty_cycle ( &lighttemp, duty_cycle );
        lighttemp_led2_set_duty_cycle ( &lighttemp, duty_cycle );
        Delay_ms( 500 );
    }
    Delay_ms( 1000 );
    
    
    log_printf( &logger, ">>> Decreasing LEDs light intensity \r\n" );
    for ( duty_cycle = 0.5; duty_cycle > 0; duty_cycle -= 0.1 )
    {
        lighttemp_led1_set_duty_cycle ( &lighttemp, duty_cycle );
        lighttemp_led2_set_duty_cycle ( &lighttemp, duty_cycle );
        Delay_ms( 500 );
    }
    lighttemp_led1_pwm_stop( &lighttemp );
    lighttemp_led2_pwm_stop( &lighttemp );
    Delay_ms( 1000 );
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
