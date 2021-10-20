/*!
 * @file main.c
 * @brief MatrixG Click example
 *
 * # Description
 * This example showcases how to prepare the logger and click modules for use and 
 * how to display ASCII characters on both of the LED segments of the click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * This function initializes and configures the logger and click modules. After the initialization of the logger module, 
 * communication, mikrobus and pin setup, some of the registers are configured in order for the click module to work properly.
 *
 * ## Application Task
 * This function displays two strings on each of the LED segments, showing one character every second. 
 * It should display " Mikroelektronika" on the left one and "Mikroelektronika " on the right.
 *
 * @note
 * The click has two chips, each controlling one of the LED segments, on and requires you to write data to both at the same time. 
 * Writing to one specific chip will not work. If you wish to display characters on a single segment, you have to send ' ' characters to the other segment.
 *
 * @author Jelena Milosavljevic
 *
 */

// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "matrixg.h"

// ------------------------------------------------------------------ VARIABLES

static matrixg_t matrixg;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( ) {
   
    log_cfg_t log_cfg;
    matrixg_cfg_t cfg;

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

    matrixg_cfg_setup( &cfg );
    MATRIXG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixg_init( &matrixg, &cfg );
    Delay_ms( 100 );
    matrixg_default_cfg( &matrixg );
    Delay_ms( 100 );
}

void application_task ( ) {
   
    matrixg_display_characters( &matrixg, ' ', 'M' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'M', 'i' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'i', 'k' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'k', 'r' );
    Delay_ms( 1000);
    matrixg_display_characters( &matrixg, 'r', 'o' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'o', 'E' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'E', 'l' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'l', 'e' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'e', 'k' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'k', 't' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 't', 'r' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'r', 'o' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'o', 'n' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'n', 'i' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'i', 'k' );
    Delay_ms( 1000 );
    matrixg_display_characters( &matrixg, 'k', 'a' );
    Delay_ms( 100 );
    matrixg_display_characters( &matrixg, 'a', ' ' );
    Delay_ms( 100 );
}

void main ( ) {
    
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
