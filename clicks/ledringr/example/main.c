/*!
 * \file 
 * \brief LedringR Click example
 * 
 * # Description
 * LED ring  R click is a mikroBUS™ add-on board with a ring of 32 red LEDs driven.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI driver and performs device configuration.
 * 
 * ## Application Task  
 * Show functionality of Led_Ring_R Click, rotating and turn on/off led's, using the SPI interface.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ledringr.h"

// ------------------------------------------------------------------ VARIABLES

static ledringr_t ledringr;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ledringr_cfg_t cfg;

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

    ledringr_cfg_setup( &cfg );
    LEDRINGR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledringr_init( &ledringr, &cfg );
}

void application_task ( void )
{
    uint32_t ring_led_on = 0x00000001;
    uint8_t ring_led_counter;
    uint8_t number_led;

    ledringr_led_ring_set( &ledringr );

    for ( ring_led_counter = 32; ring_led_counter > 0; ring_led_counter--)
    {
        ledringr_turn_on_led( &ledringr, ring_led_counter );
        Delay_100ms( );
    }

    Delay_100ms( );

    while ( ring_led_on < 0xFFFFFFFF )
    {
        ledringr_write_data( &ledringr, ring_led_on );
        ring_led_on = ring_led_on | (ring_led_on << 1);
        Delay_100ms( );
    }
    ledringr_write_data( &ledringr, ring_led_on );

    while ( ring_led_on > 0x00000001 )
    {
        ledringr_write_data( &ledringr, ring_led_on );
        ring_led_on = ring_led_on >> 1;
        Delay_100ms( );
    }
    ledringr_write_data( &ledringr, ring_led_on );

    Delay_100ms( );

    ring_led_on = 0x11111111;
    for ( ring_led_counter = 0; ring_led_counter < 32; ring_led_counter++ )
    {
        ledringr_write_data( &ledringr, ring_led_on );

        ring_led_on *= 2;

        if ( ring_led_on == 0x88888888 )
        {
            ring_led_on = 0x11111111;
        }
            
        Delay_100ms( );
    }
    
    for ( ring_led_counter = 0; ring_led_counter < 16; ring_led_counter++ )
    {
        ledringr_write_data( &ledringr, 0xAAAAAAAA );
        Delay_100ms( );
        
        ledringr_write_data( &ledringr, 0x55555555 );
        Delay_100ms( );
    }

    ledringr_led_ring_reset( &ledringr );

    Delay_1sec( );
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
