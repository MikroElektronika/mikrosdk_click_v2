/*!
 * \file 
 * \brief ButtonLibrary Click example
 * 
 * # Description
 * This example showcases how to initialize and use the whole family of Button clicks. One library
 * is used for every single one of them. They are simple touch detectors which send a pressed/
 * released signal and receive a PWM output which controls the backlight on the button.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules. 
 * 
 * ## Application Task  
 * This function first turns the backlight on the button ON/OFF and then checks if the button
 * has been pressed and reports the event in the console using UART communication.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buttonlibrary.h"

// ------------------------------------------------------------------ VARIABLES

static buttonlibrary_t buttonlibrary;
static log_t logger;

static float duty_cycle;
static uint8_t button_state;
static uint8_t button_state_old;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void backlight_on ( ) 
{
    float cnt;

    for ( cnt = 0; cnt < 1; cnt += 0.1 )
    {
        buttonlibrary_set_duty_cycle( &buttonlibrary, cnt );
        Delay_ms( 10 );
    }
}

static void backligh_off ( )
{
    float cnt;

    for ( cnt = 0; cnt < 1; cnt += 0.1 )
    {
        buttonlibrary_set_duty_cycle( &buttonlibrary, 1 - cnt );
        Delay_ms( 10 );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    buttonlibrary_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    buttonlibrary_cfg_setup( &cfg );
    BUTTONLIBRARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_ms( 100 );
    buttonlibrary_init( &buttonlibrary, &cfg );
    buttonlibrary_pwm_start( &buttonlibrary );
    Delay_ms( 100 );
    
    backlight_on( );
    Delay_ms( 500 );
    backligh_off( );
    Delay_ms( 500 );
    backlight_on( );
    button_state = buttonlibrary_get_button_state( &buttonlibrary );
    button_state_old = button_state;
}

void application_task ( )
{    
    button_state = buttonlibrary_get_button_state( &buttonlibrary );
    if ( button_state && ( button_state != button_state_old ) )
    {
        backligh_off( );
        button_state_old = button_state;
    }
    else if ( !button_state && ( button_state != button_state_old ) )
    {
        backlight_on( );
        button_state_old = button_state;
    }
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
