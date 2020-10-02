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

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void backlight_on ( ) 
{
    uint8_t cnt;

    for ( cnt = 0; cnt < 200; cnt++ )
    {
        if ( !button_state )
        {
            button_state = buttonlibrary_get_button_state( &buttonlibrary );
            buttonlibrary_set_duty_cycle( &buttonlibrary, buttonlibrary.pwm_period );
            Delay_1ms();
        }
    }
}

static void backligh_off ( )
{
    uint8_t cnt;

    for ( cnt = 0; cnt < 200; cnt++ )
    {
        if ( !button_state )
        {
            button_state = buttonlibrary_get_button_state( &buttonlibrary );
            buttonlibrary_set_duty_cycle( &buttonlibrary, 0 );
            Delay_1ms();
        }
    }
}

static void button_pressed ( )
{
    if ( button_state )
    {
        log_printf( &logger, " * The button is pressed. *\r\n" );

        while ( duty_cycle < buttonlibrary.pwm_period )
        {
            duty_cycle += 200;
            buttonlibrary_set_duty_cycle( &buttonlibrary, duty_cycle );
            Delay_10ms();
        }

        duty_cycle = 0;
        log_printf( &logger, "------------------------------------------\r\n" );
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
    Delay_100ms( );

    //  Click initialization.

    buttonlibrary_cfg_setup( &cfg );
    BUTTONLIBRARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms( );
    buttonlibrary_init( &buttonlibrary, &cfg );
    buttonlibrary_pwm_start( &buttonlibrary );
    Delay_100ms( );
}

void application_task ( )
{    
    if ( duty_cycle > buttonlibrary.pwm_period )
    {
        duty_cycle = 0;
    }

    button_state = buttonlibrary_get_button_state( &buttonlibrary );

    backlight_on( );
    backligh_off( );
    button_pressed( );
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
