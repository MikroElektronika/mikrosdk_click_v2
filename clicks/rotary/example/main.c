/*!
 * \file 
 * \brief Rotary Click example
 * 
 * # Description
 * The demo application controls led on click with rotory on board
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver, set initial states, 
 * set RST logic high and performs device configuration.
 *
 * ## Application Task
 * Show functionality of Rotary_R Click, rotating and turn on/off led's,
 * using the SPI interface
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rotary.h"

// ------------------------------------------------------------------ VARIABLES

static rotary_t rotary;
static log_t logger;

uint8_t start_status;
uint8_t old_state;
uint8_t new_state;
uint8_t old__rot_state;
uint8_t new_rotate_state;
uint8_t led_state;
uint16_t led_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rotary_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rotary_cfg_setup( &cfg );
    ROTARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rotary_init( &rotary, &cfg );

    led_data = 0x0001;
    old_state = 0;
    new_state = 1;
    old__rot_state = 0;
    new_rotate_state = 1;
}

void application_task ( void )
{
    rotaryr_turn_on_led_by_data( &rotary, led_data );

    // Push button
    if ( rotaryr_button_push( &rotary ) )
    {
        new_state = 1;
        if ( new_state == 1 &&  old_state == 0 )
        {
            old_state = 1;
            led_state = ( led_state + 1 ) % 5;
            if ( led_state == 4 )
            {
                for ( old_state=0; old_state < 17; old_state++ )
                {
                    rotaryr_turn_on_led_by_data( &rotary, 0xAAAA );
                    Delay_100ms();
                    rotaryr_turn_on_led_by_data( &rotary, 0x5555 );
                    Delay_100ms();
                }

                for ( old_state=0; old_state < 17; old_state++ )
                {
                    rotaryr_turn_on_led_by_position( &rotary, old_state );
                    Delay_100ms();
                }

                led_state = 0;
                led_data = rotaryr_get_led_data( led_state );
            }
            else
            {
                led_data = rotaryr_get_led_data( led_state );
            }
        }
    }
    else
    {
        old_state = 0;
    }

    // Rotate Clockwise and CounterClockwise
    if ( rotaryr_get_eca_state( &rotary ) == rotaryr_get_ecb_state( &rotary ) )
    {
        old__rot_state = 0;
        start_status = rotaryr_get_eca_state( &rotary ) && rotaryr_get_ecb_state( &rotary );
    }
    else
    {
        new_rotate_state = 1;
        if ( new_rotate_state != old__rot_state )
        {
            old__rot_state = 1;
            if ( start_status != rotaryr_get_eca_state( &rotary ) )
            {
                led_data = ( led_data << 1 ) | ( led_data >> 15 );
            }
            else
            {
                led_data = ( led_data >> 1 ) | ( led_data << 15 );
            }
        }
    }
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
