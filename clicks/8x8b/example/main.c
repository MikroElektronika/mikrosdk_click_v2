/*!
 * @file main.c
 * @brief 8x8 B Click example
 *
 * # Description
 * This demo example shows a drawing of Image, new create string and character on the screen.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Shows one byte, then scrolls the string and image, every 1 sec.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "c8x8b.h"

static c8x8b_t c8x8b;
static log_t logger;

uint8_t demo_string[ 11 ] = { ' ', '-', 'M', 'i', 'k', 'r', 'o', 'E', '-', ' ', 0 };
uint8_t demo_img_on[ 8 ] = { 0x08, 0x1c, 0x36, 0x22, 0x08, 0x1c, 0x36, 0x22 };
uint8_t demo_img_off[ 8 ] = { 0xf7, 0xe3, 0xc9, 0xdd, 0xf7, 0xe3, 0xc9, 0xdd };
char demo_char = 'A';

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    c8x8b_cfg_t c8x8b_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    c8x8b_cfg_setup( &c8x8b_cfg );
    C8X8B_MAP_MIKROBUS( c8x8b_cfg, MIKROBUS_1 );
    err_t init_flag  = c8x8b_init( &c8x8b, &c8x8b_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_info( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c8x8b_default_cfg ( &c8x8b );
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
}

void application_task ( void ) {    
    c8x8b_display_byte( &c8x8b, demo_char );
    Delay_ms( 1000 );
    
    c8x8b_display_string( &c8x8b, &demo_string[ 0 ] );
    Delay_ms( 1000 );

    c8x8b_display_image( &c8x8b, &demo_img_on[ 0 ] );
    Delay_ms( 1000 );

    c8x8b_display_image( &c8x8b, &demo_img_off[ 0 ] );
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
