/*!
 * \file main.c
 * \brief Fan 2 Click example
 *
 * # Description
 * This example demonstrates the use of Fan 2 Click board.
 * It demonstrates sensor measurements and fan control.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and executes a default configuration for Fan 2 click,
 * to be ready to perform a control of 3-wire fan, in our example.
 * Also initializes UART console for results logging.
 *
 * ## Application Task
 * Increments the fan speed from minimum to maximum, and on each step measures
 * the current fan speed in percents and the local temperature in Celsius
 * degrees. Fan speed will be incremented every 1500ms for 5 percents.
 * When it reaches the maximum speed (100%), it will be returned to minimum
 * speed (0%).
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fan2.h"

// ------------------------------------------------------------------ VARIABLES

static fan2_t fan2;
static log_t console;
static float fan2_speed;
static float fan2_curr_speed;
static float fan2_local_temp;

const char deg_cels[ 3 ] = { 176, 'C', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    fan2_cfg_t fan2_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    fan2_cfg_setup( &fan2_cfg );
    FAN2_MAP_MIKROBUS( fan2_cfg, MIKROBUS_1 );
    fan2_init( &fan2, &fan2_cfg );
    fan2_default_cfg( &fan2, FAN2_WIRES_3 );
    fan2_speed = FAN2_MIN_SPEED_PER;

    //  UART console initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.level = LOG_LEVEL_DEBUG;
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_printf( &console, "* * *  Fan 2 initialization done  * * *\r\n" );
    log_printf( &console, "***************************************\r\n" );
}

void application_task( void )
{
    fan2_direct_speed_control( &fan2, fan2_speed );

    if (fan2_speed < FAN2_MAX_SPEED_PER)
    {
        fan2_speed += 5;
    }
    else
    {
        fan2_speed = FAN2_MIN_SPEED_PER;
    }

    Delay_ms( 500 );

    fan2_curr_speed = fan2_read_current_speed( &fan2 );
    fan2_read_temp( &fan2, FAN2_REG_LOCAL_TEMP_READ, &fan2_local_temp );

    log_printf( &console, "* Fan 2 current speed : %.2f %%\r\n",
                fan2_curr_speed );
    log_printf( &console, "* Fan 2 local temperature : %.2f %s\r\n",
                fan2_local_temp, deg_cels );
    log_printf( &console, "***************************************\r\n" );

    Delay_ms( 1000 );
}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
