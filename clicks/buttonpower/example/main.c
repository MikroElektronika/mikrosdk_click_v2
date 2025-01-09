/*!
 * @file main.c
 * @brief Button Power Click Example.
 *
 * # Description
 * This example showcases how to initialize and use the whole family of Button Clicks. 
 * One library is used for every single one of them. They are simple touch detectors which send
 * a pressed/released signal and receive a PWM output which controls the backlight on the button.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * This function initializes and configures the logger and Click modules.
 *
 * ## Application Task
 * This example first increases the backlight on the button and then decreases the intensity of the backlight. When the button is touched,
 * reports the event in the console using UART communication.
 * 
 *
 * @author Nikola Peric
 *
 */

#include "board.h"
#include "log.h"
#include "buttonpower.h"

static buttonpower_t buttonpower;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                   /**< Logger config object. */
    buttonpower_cfg_t buttonpower_cfg;   /**< Click config object. */

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

    buttonpower_cfg_setup( &buttonpower_cfg );
    BUTTONPOWER_MAP_MIKROBUS( buttonpower_cfg, MIKROBUS_1 );
    err_t init_flag  = buttonpower_init( &buttonpower, &buttonpower_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 500 );
    
    buttonpower_pwm_start( &buttonpower );
    buttonpower_set_duty_cycle ( &buttonpower, 0.1 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static float duty_cycle;
    static uint8_t button_state;
    static uint8_t button_state_old;

    button_state = buttonpower_get_button_state( &buttonpower );
    
    if ( button_state && ( button_state != button_state_old ) ) 
    {
        log_printf( &logger, " <-- Button pressed --> \r\n" );
        for ( uint8_t n_cnt = 1; n_cnt <= 100; n_cnt++ )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttonpower_set_duty_cycle( &buttonpower, duty_cycle );
            Delay_ms ( 10 );
        }
        button_state_old = button_state;
    } 
    else if ( !button_state && ( button_state != button_state_old ) ) 
    {
        for ( uint8_t n_cnt = 100; n_cnt > 0; n_cnt-- )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttonpower_set_duty_cycle( &buttonpower, duty_cycle );
            Delay_ms ( 10 );
        }
        button_state_old = button_state;
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
