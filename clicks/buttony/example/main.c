/*!
 * @file main.c
 * @brief Button Y Click Example.
 *
 * # Description
 * This library contains API for Button Y Click driver. 
 * One library is used for every single one of them.
 * They are simple touch detectors that send a pressed/released 
 * signal and receive a PWM output which controls the backlight on the button.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * This function initializes and configures the logger and click modules. 
 *
 * ## Application Task
 * This example first increases the backlight on the button and then decreases the intensity of backlight. When the button is pressed,
 * reports the event in the console using UART communication.
 *
 * @author Nikola Peric
 *
 */

#include "board.h"
#include "log.h"
#include "buttony.h"

static buttony_t buttony;
static log_t logger;

void application_init ( void )  
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buttony_cfg_t buttony_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    buttony_cfg_setup( &buttony_cfg );
    BUTTONY_MAP_MIKROBUS( buttony_cfg, MIKROBUS_1 );
    err_t init_flag  = buttony_init( &buttony, &buttony_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 500 );
    
    buttony_set_duty_cycle ( &buttony, 0.0 );
    buttony_pwm_start( &buttony );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static float duty_cycle;
    static uint8_t button_state;
    static uint8_t button_state_old;

    button_state = buttony_get_button_state( &buttony );
    
    if ( button_state && ( button_state != button_state_old ) ) 
    {
        log_printf( &logger, " <-- Button pressed --> \r\n" );
        for ( uint8_t n_cnt = 1; n_cnt <= 100; n_cnt++  )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttony_set_duty_cycle( &buttony, duty_cycle );
            Delay_ms( 10 );
        }
        button_state_old = button_state;
    } 
    else if ( !button_state && ( button_state != button_state_old ) ) 
    {
        for ( uint8_t n_cnt = 100; n_cnt > 0; n_cnt-- )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttony_set_duty_cycle( &buttony,  duty_cycle );
            Delay_ms( 10 );
        }
        button_state_old = button_state;
    }
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
