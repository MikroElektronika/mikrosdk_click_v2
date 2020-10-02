/*!
 * \file 
 * \brief MatrixRG Click example
 * 
 * # Description
 * This example showcases how to prepare the logger and click modules for use and how to display
 * ASCII characters on both of the LED segments of the click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules. After the initialization
 * of the logger module, communication, mikrobus and pin setup, some of the registers are configured
 * in order for the click module to work properly.
 * 
 * ## Application Task  
 * This function displays two strings on each of the LED segments, showing one character every
 * second. It should display " Mikroelektronika" on the left one and "Mikroelektronika " on the 
 * right.
 * 
 * *note:* 
 * The click has two chips, each controlling one of the LED segments, on and requires you to write
 * data to both at the same time. Writing to one specific chip will not work. If you wish to display
 * characters on a single segment, you have to send ' ' characters to the other segment.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "matrixrg.h"

// ------------------------------------------------------------------ VARIABLES

static matrixrg_t matrixrg;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    matrixrg_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    matrixrg_cfg_setup( &cfg );
    MATRIXRG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixrg_init( &matrixrg, &cfg );
    Delay_ms( 100 );
    matrixrg_default_cfg( &matrixrg );
    Delay_ms( 100 );
}

void application_task ( )
{
    matrixrg_display_characters( &matrixrg, ' ', 'M' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'M', 'i' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'i', 'k' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'k', 'r' );
    Delay_ms( 1000);
    matrixrg_display_characters( &matrixrg, 'r', 'o' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'o', 'E' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'E', 'l' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'l', 'e' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'e', 'k' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'k', 't' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 't', 'r' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'r', 'o' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'o', 'n' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'n', 'i' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'i', 'k' );
    Delay_ms( 1000 );
    matrixrg_display_characters( &matrixrg, 'k', 'a' );
    Delay_ms( 100 );
    matrixrg_display_characters( &matrixrg, 'a', ' ' );
    Delay_ms( 100 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
