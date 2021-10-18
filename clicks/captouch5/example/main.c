/*!
 * \file 
 * \brief CapTouch5 Click example
 * 
 * # Description
 * This demo app demonstrates basic functionality of CapTouch 5 Click
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C module and driver, tests communication and configures device
 * 
 * ## Application Task  
 * Waiting for touch sensor to detect something and then logs what is touched
 * 
 * *note:* 
 * Click will go to sleep if doesn't get any command in 340ms
 * When you start device try restarting your board few times to start device
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "captouch5.h"

// ------------------------------------------------------------------ VARIABLES

static captouch5_t captouch5;
static log_t logger;

static T_CAPTOUCH5_BUTTONS buttons;
static T_CAPTOUCH5_DEVICE_CONFIG device_cfg;
static uint8_t state_check;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void captouch5_read_buttons(  )
{
    uint8_t press = 0;

    if ( buttons.button1 == CAPTOUCH5_BUTTON_PRESSED )
    {
        log_info( &logger, "Button 1 : pressed" );
        press = 1;
    }

    if ( buttons.button2 == CAPTOUCH5_BUTTON_PRESSED )
    {
        log_info( &logger, "Button 2 : pressed" );
        press = 1;
    }

    if ( buttons.button3 == CAPTOUCH5_BUTTON_PRESSED )
    {
        log_info( &logger, "Button 3 : pressed" );
        press = 1;
    }

    if (buttons.button4 == CAPTOUCH5_BUTTON_PRESSED)
    {
        log_info( &logger, "Button 4 : pressed" );
        press = 1;
    }

    if (press)
    {
        log_printf( &logger, "\r\n" );
        state_check = 1;
        press = 0;
    }
}


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch5_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    captouch5_cfg_setup( &cfg );
    CAPTOUCH5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch5_init( &captouch5, &cfg );
    captouch5_default_cfg ( &captouch5, &device_cfg );
    
//     uint8_t fam_id = captouch5_get_family_id( &captouch5 );
//     if ( CAPTOUCH5_FAMILY_ID != fam_id )
//     {
//         log_info( &logger, "---- ID ERROR ----" );
//         for ( ; ; );
//     }
}

void application_task ( void )
{
    uint16_t temp_byte;
    uint16_t last_temp;
    uint8_t error_data;
    uint8_t temp_slider;

    state_check = 0;

    error_data = captouch5_process( &captouch5 );

    if ( error_data == CAPTOUCH5_ERROR )
    {
        log_printf( &logger, "***** ERROR *****" );
        state_check = 1;
        return;
    }

    temp_byte = captouch5_read_slider_position( &captouch5 );
    captouch5_read_button_status( &captouch5, &buttons );

    if ( temp_byte != last_temp )
    {
        log_printf( &logger, "Slider position value: %u \r\n", temp_byte );
        last_temp = temp_byte;
        state_check = 1;
    }

    captouch5_read_buttons(  );

    Delay_ms ( 100 );

    if ( state_check == 1 )
    {
        log_info( &logger, "--- Waiting for command ---\r\n" );
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
