/*!
 * \file 
 * \brief heater Click example
 * 
 * # Description
 *  The devices resolution depends on settings applied.
 *  User should consult the datasheet and choose resolution value 
 *  that corresponds to the settings applied.
 * 
 * ## Application Init 
 *  Initialization of PWM module and start heating up
 * 
 *  ## Application Task  
 *  Durning the task device is heating up to 50 degree C and then
 *   cooling down to 40 degree C
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heater.h"

// ------------------------------------------------------------------ VARIABLES

static heater_t heater;
static log_t logger;

static uint32_t frequency;
static float temp_read;
static uint8_t status_dev;
static float duty_cycle = 0.5;
const float HOT_TEMP = 50.0;
const float COOL_TEMP = 40.0;

char log_degree[ 5 ] = { ' ', 176, 67, 13, 10 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heater_cfg_t cfg;
    heater_config_t cfg1;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heater_cfg_setup( &cfg, &cfg1 );
    HEATER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heater_init( &heater, &cfg, &cfg1 );

    heater_pwm_start( &heater );
    
    frequency = 500;
    
    heater_set_duty_cycle( &heater, duty_cycle );
    status_dev = HEATER_HEATING;
    
    log_printf( &logger, " ***** APP INIT ***** \r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    temp_read = heater_read_temp( &heater );
    
    if ( ( temp_read > HOT_TEMP ) && ( status_dev == HEATER_WAITING ) )
    {
        status_dev = HEATER_COOLING;
    }
    else if ( ( temp_read < COOL_TEMP ) && ( status_dev == HEATER_WAITING ) )
    {
        status_dev = HEATER_HEATING;
    }

    if ( status_dev == HEATER_HEATING )
    {
        heater_pwm_start( &heater );
        heater_set_led1_status( &heater, HEATER_LED_ON );
        heater_set_led2_status( &heater, HEATER_LED_OFF );
        status_dev = HEATER_WAITING;
    }
    else if ( status_dev == HEATER_COOLING )
    {
        heater_pwm_stop( &heater );
        heater_set_led1_status( &heater, HEATER_LED_OFF );
        heater_set_led2_status( &heater, HEATER_LED_ON );
        status_dev = HEATER_WAITING;
    }

    log_printf( &logger,  " - Temperature: %.2f %s\r\n", temp_read, log_degree );
    
    log_printf( &logger, "***************\r\n" );

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
