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
 * On first LED is a pwm module, which increases/decreases light intensity, 
 * and on second LED turn ON/OFF light. 
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

    //  Click initialization.

    lighttemp_cfg_setup( &cfg );
    LIGHTTEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lighttemp_init( &lighttemp, &cfg );

    lighttemp_pwm_start( &lighttemp );
    lighttemp_cs_set_state( &lighttemp, 0 );
}

void application_task ( void )
{
    uint16_t pg_volt;
    uint8_t i;  
    
    pg_volt = lighttemp_get_pg_voltage( &lighttemp );
    log_printf( &logger, ">>> PG Voltage: %ld mV \r\n", pg_volt );

    log_printf( &logger, ">>> LED 1 Increase \r\n" );
    
    for ( i = 0; i < 72; i++ )
    {
        if ( duty_cycle > 1 )
        {
            duty_cycle = 0.1;
        }

        lighttemp_set_duty_cycle( &lighttemp, duty_cycle );
        duty_cycle += 0.1;
        Delay_ms( 100 );
    }
    
    Delay_ms( 1000 );
    
    log_printf( &logger, ">>> LED 1 Decrease \r\n" );
    
    
    for ( i = 0; i < 72; i++ )
    {
        if ( duty_cycle < 0 )
        {
            duty_cycle = 1;
        }

        lighttemp_set_duty_cycle( &lighttemp, duty_cycle );
        duty_cycle -= 0.1;
        Delay_ms( 100 ); 
    }
    
    Delay_ms( 1000 );
     
    log_printf( &logger, ">>> LED 2 -> ON \r\n" );
    lighttemp_cs_set_state( &lighttemp, 1 );
    Delay_ms( 1000 );
    log_printf( &logger, ">>> LED 2 -> OFF \r\n" );
    lighttemp_cs_set_state( &lighttemp, 0 );
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
