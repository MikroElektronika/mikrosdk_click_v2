/*!
 * \file 
 * \brief CapSense Click example
 * 
 * # Description
 * This demo example shows level of the slider on the terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Waits user to press top and bottom button to turn click's LEDs ON or OFF.
 * User can swipe slider to send log to the UART where one can track their changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "capsense.h"

// ------------------------------------------------------------------ VARIABLES

static capsense_t capsense;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void bits_to_str( uint8_t num, uint8_t *s )
{
    uint8_t mask = 0x80;
    while ( mask )
    {
        if ( num & mask )
        {
            *s++ = '1';
        }
        else
        {
            *s++ = '0';
        }
        mask >>= 1;
    }
    *s = '\0';
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    capsense_cfg_t cfg;

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
    capsense_cfg_setup( &cfg );
    CAPSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capsense_init( &capsense, &cfg );
    
    if ( CAPSENSE_ERROR == capsense_default_cfg ( &capsense ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t current_led_state = 0;
    uint8_t output_lvl[ 10 ] = { 0 };
    uint8_t button_select = 0;
    uint8_t slider_lvl = 0;
    capsense_read_data( &capsense, CAPSENSE_CS_READ_STATUS0, &button_select );
    capsense_get_slider_lvl( &capsense, &slider_lvl );
    capsense_write_data( &capsense, CAPSENSE_OUTPUT_PORT0, current_led_state );
    Delay_ms( 100 );

    if ( 8 == button_select )
    {
        current_led_state ^= 0x01;
        log_printf( &logger, "Toggle LED1\r\n");
        Delay_ms( 100 );
    }
    if ( 16 == button_select )
    {
        current_led_state ^= 0x02;
        log_printf( &logger, "Toggle LED2\r\n");
        Delay_ms( 100 );
    }
    if ( 24 == button_select )
    {
        current_led_state = ~current_led_state;
        log_printf( &logger, "Toggle both LEDs\r\n");
        Delay_ms( 100 );
    }

    if ( slider_lvl )
    {
        bits_to_str( slider_lvl, output_lvl );
        log_printf( &logger, "Slider level - channels [5-1]:\t%s \r\n", &output_lvl[ 3 ] );
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
