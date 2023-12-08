/*!
 * \file 
 * \brief PWM Click example
 * 
 * # Description
 * This is an example that shows the capability of PWM click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, enables output, configures device, sets prescaling,
 * configures output and makes an initial log.
 * 
 * ## Application Task  
 * Changes the duty cycle of all channels every 10 seconds.
 * All data are being logged on USB UART where you can track their changes.
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
static uint8_t config0[ 6 ] = { 1, 0, 0, 0, 1, 0 };
static uint8_t config1[ 6 ] = { 1, 0, 0, 0, 0, 1 };
static uint8_t config2[ 4 ] = { 0, 1, 0, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwm_cfg_t cfg;

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

    pwm_cfg_setup( &cfg );
    PWM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm_init( &pwm, &cfg );
    Delay_ms( 100 );
    
    pwm_set_output( &pwm, PWM_ENABLE );
    pwm_dev_config( &pwm, &config0 );
    pwm_set_pre_scale( &pwm, 0x04 );
    pwm_dev_config( &pwm, &config1 );
    pwm_output_config( &pwm,  &config2 );
    Delay_ms( 100 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " PWM  Click \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
}

void application_task ( void )
{
    uint8_t chann_id;
    
    pwm_set_all_raw( &pwm, PWM_MAX_RESOLUTION / 2 );
    log_printf( &logger, "All Channels set to 50%% duty cycle \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 10000 );
    
    for ( chann_id = 0; chann_id < 8; chann_id++ )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, PWM_MAX_RESOLUTION / 4 );
    }
    log_printf( &logger, "Channels 0-7 set to 25%% duty cycle \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 10000 );
    
    for ( chann_id = 0; chann_id < 8; chann_id++ )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, ( PWM_MAX_RESOLUTION / 4 ) * 3 );
    }
    log_printf( &logger, "Channels 0-7 set to 75%% duty cycle \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 10000 );
    
    pwm_all_chann_state( &pwm, 0 );
    log_printf( &logger, "All Channels disabled \r\n " );
    log_printf( &logger, "--------------------------\r\n" );
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
