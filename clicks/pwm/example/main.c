/*!
 * \file 
 * \brief PWM Click example
 * 
 * # Description
 * This is an example that shows some of the functions that PWM click has.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, enables output, configures device, sets prescaling,
 * configures output and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows some of the functions that PWM click has.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pwm.h"

// ------------------------------------------------------------------ VARIABLES

static pwm_t pwm;
static log_t logger;
static uint8_t config[ 6 ] = { 1, 0, 0, 0, 1, 0 };
static uint8_t config1[ 4 ] = { 0x00, 1, 0, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwm_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pwm_cfg_setup( &cfg );
    PWM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm_init( &pwm, &cfg );
    Delay_ms( 100 );
    
    pwm_set_output( &pwm, PWM_DISABLE  );
    pwm_dev_config( &pwm, &config );
    pwm_set_pre_scale( &pwm, 0x04 );
    pwm_dev_config( &pwm, &config  );
    pwm_output_config( &pwm,  &config1 );
    Delay_ms( 100 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " PWM  Click \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
}

void application_task ( void )
{
    uint16_t raw_dc;
    uint8_t chann_id;
    uint8_t duty_cycle;
    chann_id = 0;
    
    log_printf( &logger, "Channel 0 false state \r\n " );
    pwm_channel_state( &pwm, chann_id, 0 );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
    
    log_printf( &logger, "Channel 0 set raw  \r\n" );
    for ( raw_dc = 0; raw_dc < PWM_MAX_RESOLUTION; raw_dc += 256 )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, raw_dc );
        log_printf( &logger, " >\r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "Channel 0 set  \r\n" );
    for ( duty_cycle = 0; duty_cycle < 100; duty_cycle += 10 )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, duty_cycle );
        log_printf( &logger, " > \r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "All Channels raw set  \r\n" );
    for ( raw_dc = 0; raw_dc < PWM_MAX_RESOLUTION; raw_dc += 256 )
    {
        pwm_set_all_raw( &pwm, raw_dc );
        log_printf( &logger, " >\r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "All Channels set  \r\n" );
    for ( duty_cycle = 0; duty_cycle < 100; duty_cycle += 10 )
    {
        pwm_set_all( &pwm, duty_cycle );
        log_printf( &logger, " >\r\n" );
        Delay_ms( 500 );
    }
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "All Channels false state \r\n " );
    pwm_all_chann_state( &pwm, 0 );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
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
