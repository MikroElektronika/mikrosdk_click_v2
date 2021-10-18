/*!
 * @file main.c
 * @brief OLEDW Click example
 *
 # Description
 * This example demonstrates the use (control) of the OLED W display.
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
#include "oledw.h"
#include "resources.h"

static oledw_t oledw;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    oledw_cfg_t oledw_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    oledw_cfg_setup( &oledw_cfg );
    OLEDW_MAP_MIKROBUS( oledw_cfg, MIKROBUS_1 );
    err_t init_flag  = oledw_init( &oledw, &oledw_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    oledw_default_cfg ( &oledw );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint8_t i;

    oledw_display_picture( &oledw, oledw_img );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_INVERTDISPLAY, OLEDW_COMMAND );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_NORMALDISPLAY, OLEDW_COMMAND );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_INVERTDISPLAY, OLEDW_COMMAND );
    Delay_ms( 500 );
    oledw_send( &oledw, OLEDW_NORMALDISPLAY, OLEDW_COMMAND );
    Delay_ms( 300 );

    for (i = 0xAF; i > 0x00; i--) {
        oledw_set_contrast( &oledw, i );
        Delay_ms( 5 );
    }

    for (i = 0x00; i < 0xAF; i++) {
        oledw_set_contrast( &oledw, i );
        Delay_ms( 5 );
    }

    oledw_scroll_right( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_left( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_diag_right( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_diag_left( &oledw, 0x00, 0x05 );
    Delay_ms( 1000 );
    oledw_stop_scroll( &oledw );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
