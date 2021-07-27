/*!
 * @file main.c
 * @brief OLEDB Click example
 *
 # Description
 * This example demonstrates the use (control) of the OLED B display.
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
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "oledb.h"
#include "resources.h"

static oledb_t oledb;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    oledb_cfg_t oledb_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    oledb_cfg_setup( &oledb_cfg );
    OLEDB_MAP_MIKROBUS( oledb_cfg, MIKROBUS_1 );
    err_t init_flag  = oledb_init( &oledb, &oledb_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    oledb_default_cfg ( &oledb );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint8_t i;

    oledb_display_picture( &oledb, oledb_img );
    Delay_ms( 500 );
    oledb_send( &oledb, OLEDB_INVERTDISPLAY, OLEDB_COMMAND );
    Delay_ms( 500 );
    oledb_send( &oledb, OLEDB_NORMALDISPLAY, OLEDB_COMMAND );
    Delay_ms( 500 );
    oledb_send( &oledb, OLEDB_INVERTDISPLAY, OLEDB_COMMAND );
    Delay_ms( 500 );
    oledb_send( &oledb, OLEDB_NORMALDISPLAY, OLEDB_COMMAND );
    Delay_ms( 300 );

    for (i = 0xAF; i > 0x00; i--) {
        oledb_set_contrast( &oledb, i );
        Delay_ms( 5 );
    }

    for (i = 0x00; i < 0xAF; i++) {
        oledb_set_contrast( &oledb, i );
        Delay_ms( 5 );
    }

    oledb_scroll_right( &oledb, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledb_stop_scroll( &oledb );
    oledb_display_picture( &oledb, oledb_img );

    oledb_scroll_left( &oledb, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledb_stop_scroll( &oledb );
    oledb_display_picture( &oledb, oledb_img );

    oledb_scroll_diag_right( &oledb, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledb_stop_scroll( &oledb );
    oledb_display_picture( &oledb, oledb_img );

    oledb_scroll_diag_left( &oledb, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledb_stop_scroll( &oledb );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
