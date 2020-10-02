/*!
 * \file main.c
 * \brief OLED BW Click example
 *
 * # Description
 * This example demonstrates the use (control) of the OLED B/W display.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configures the microcontroller for communication and initializes the click
 * board to default state.
 *
 * ## Application Task
 * This section contains the main program that is executed showing a practical
 * example on how to use the implemented functions.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oledbw.h"
#include "resources.h"

// ------------------------------------------------------------------ VARIABLES

static oledbw_t oledbw;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    log_cfg_t log_cfg;
    oledbw_cfg_t oledbw_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    oledbw_cfg_setup( &oledbw_cfg );
    OLEDBW_MAP_MIKROBUS( oledbw_cfg, MIKROBUS_1 );
    oledbw_init( &oledbw, &oledbw_cfg );

    oledbw_default_cfg( &oledbw );
}

void application_task( void )
{
    uint8_t i;

    oledbw_display_picture( &oledbw, oledbw_img );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_INVERTDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_NORMALDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_INVERTDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 500 );
    oledbw_send( &oledbw, OLEDBW_NORMALDISPLAY, OLEDBW_COMMAND );
    Delay_ms( 300 );

    for (i = 0xAF; i > 0x00; i--)
    {
        oledbw_set_contrast( &oledbw, i );
        Delay_ms( 5 );
    }

    for (i = 0x00; i < 0xAF; i++)
    {
        oledbw_set_contrast( &oledbw, i );
        Delay_ms( 5 );
    }

    oledbw_scroll_right( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
    oledbw_display_picture( &oledbw, oledbw_img );

    oledbw_scroll_left( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
    oledbw_display_picture( &oledbw, oledbw_img );

    oledbw_scroll_diag_right( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
    oledbw_display_picture( &oledbw, oledbw_img );

    oledbw_scroll_diag_left( &oledbw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledbw_stop_scroll( &oledbw );
}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
