/*!
 * \file 
 * \brief Button G  Click example
 * 
 * # Description
 * <DEMOAPP_DESCRIPTION>
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Button G Click board.
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
#include "buttong.h"

// ------------------------------------------------------------------ VARIABLES

static buttong_t         buttong;
static log_t              logger;
static uint8_t     buttong_state;
static uint8_t buttong_state_old;
static uint8_t         led_state;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buttong_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    buttong_cfg_setup( &cfg );
    BUTTONG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buttong_init( &buttong, &cfg );
}

void application_task ( void )
{
    buttong_state = buttong_press_button( &buttong );

    if ( buttong_state == 1 && buttong_state_old == 0 )
    {
        buttong_state_old = 1;
        log_printf( &logger, "CLICK \n");
        
        if ( led_state == 0 )
        {
            led_state = 1;
            buttong_turn_on_led( &buttong );
            log_printf( &logger, "ON\r\n");
        }
        else
        {
            led_state = 0;
            buttong_turn_off_led( &buttong );
            log_printf( &logger, "OFF\r\n");
        }
        
        Delay_ms( 100 );
    }

    if ( buttong_state == 0 && buttong_state_old == 1 )
    {
        buttong_state_old = 0;
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
