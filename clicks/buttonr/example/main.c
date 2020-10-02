/*!
 * \file 
 * \brief ButtonR Click example
 * 
 * # Description
 * This example turns on/off the LED on the Button R Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - Start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Button R Click board.
 * In this example light on the button switch is controlled by PWM by turning LED ON and OFF
 * When button is pressed, it sends an signal to the target board microcontroller,
 * LED change states ( turn ON or OFF ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 * Data logs on usb uart when the sensor is triggered.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buttonr.h"

// ------------------------------------------------------------------ VARIABLES

static buttonr_t buttonr;
static log_t logger;

uint8_t buttonr_state;
uint8_t buttonr_state_old;
uint8_t buttonr_led_state ;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buttonr_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    buttonr_cfg_setup( &cfg );
    BUTTONR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buttonr_init( &buttonr, &cfg );
    
}

void application_task ( void )
{
    //  Task implementation.

    buttonr_state = buttonr_press_button( &buttonr );

    if ( buttonr_state == 1 && buttonr_state_old == 0 )
    {
        buttonr_state_old = 1;
        log_printf(&logger, "CLICK\n");

        if ( buttonr_led_state == 0 )
        {
            buttonr_led_state = 1;
            buttonr_turn_on_led( &buttonr );
            log_printf(&logger, "ON\r\n");
        }
        else
        {
            buttonr_led_state = 0;
            buttonr_turn_off_led( &buttonr );
            log_printf(&logger, "OFF\r\n");
        }

        Delay_ms( 100 );
    }

    if ( buttonr_state == 0 && buttonr_state_old == 1 )
    {
        buttonr_state_old = 0;
        Delay_ms( 100 );
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
