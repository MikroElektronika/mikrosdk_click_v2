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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    capsense_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    capsense_cfg_setup( &cfg );
    CAPSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capsense_init( &capsense, &cfg );
    capsense_default_cfg( &capsense );

}

void application_task ( void )
{

    uint8_t current_led_state;
    uint8_t button_select;
    uint8_t slider_value;
    uint16_t slider_lvl;
    
    button_select = capsense_read_data( &capsense, CAPSENSE_CS_READ_STATUS0 );
    slider_value = capsense_read_data_bytes( &capsense, CAPSENSE_CS_READ_RAW );
    capsense_write_data( &capsense, CAPSENSE_OUTPUT_PORT0, current_led_state );
    
    Delay_ms( 100 );

    if ( button_select == 8 )
    {
        current_led_state ^= 0x01;
        Delay_ms( 100 );
    }
    if ( button_select == 16 )
    {
        current_led_state ^= 0x02;
        Delay_ms( 100 );
    }
    if ( button_select == 24 )
    {
        current_led_state = ~current_led_state;
        Delay_ms( 100 );
    }

    slider_lvl = capsense_get_slider_lvl( &capsense );

    if ( slider_value != 0 )
    {
        log_printf( &logger, "Slider lvl. %u \r\n", slider_lvl );
        log_printf( &logger, "Slider value: %u \r\n", slider_value );
        
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
