/*!
 * @file main.c
 * @brief Button G Click Example.
 *
 * # Description
 * This example showcases how to initialize and use the whole family of Button clicks. 
 * One library is used for every single one of them. They are simple touch detectors which 
 * send a pressed/released signal and receive a PWM output which controls the backlight on the button.
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
 * @author Jelena Milosavljevic
 *
 */
#include "board.h"
#include "log.h"
#include "buttong.h"


static buttong_t buttong;
static log_t logger;
static float duty_cycle;
static uint8_t button_state;
static uint8_t button_state_old;

static void backlight_on ( void ) {
    for ( float cnt = 0; cnt < 1; cnt += 0.1 ) {
        buttong_set_duty_cycle( &buttong, cnt );
        Delay_ms( 10 );
    }
}

static void backligh_off ( void ) {
    for ( float cnt = 0; cnt < 1; cnt += 0.1 ) {
        buttong_set_duty_cycle( &buttong, 1 - cnt );
        Delay_ms( 10 );
    }
}

void application_init ( void )  {
    log_cfg_t log_cfg;          /**< Logger config object. */
    buttong_cfg_t buttong_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    buttong_cfg_setup( &buttong_cfg );
    BUTTONG_MAP_MIKROBUS( buttong_cfg, MIKROBUS_1 );
    err_t init_flag  = buttong_init( &buttong, &buttong_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 500 );
    
    buttong_set_duty_cycle ( &buttong, 0.0 );
    buttong_pwm_start( &buttong );
    
    backlight_on( );
    Delay_ms( 500 );
    
    backligh_off( );
    Delay_ms( 500 );
    
    backlight_on( );
    button_state = buttong_get_button_state( &buttong );
    button_state_old = button_state;
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    button_state = buttong_get_button_state( &buttong );
    if ( button_state && ( button_state != button_state_old ) ) {
        backligh_off( );
        button_state_old = button_state;
        Delay_ms( 500 );
    } else if ( !button_state && ( button_state != button_state_old ) ) {
        backlight_on( );
        button_state_old = button_state;
        Delay_ms( 500 );
    }
}

void main ( void )  {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
