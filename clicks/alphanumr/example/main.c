/*!
 * @file main.c
 * @brief AlphaNumR Click example
 *
 * # Description
 * This example showcases the initialization and configuration of the logger and click modules
 * and shows how to display characters and numbers on both LED segments of the click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function sets the time interval at which the symbols are displayed on the LED 
 * segments and shows a few characters and numbers.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "alphanumr.h"

static alphanumr_t alphanumr;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    alphanumr_cfg_t alphanumr_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    alphanumr_cfg_setup( &alphanumr_cfg );
    ALPHANUMR_MAP_MIKROBUS( alphanumr_cfg, MIKROBUS_1 );
    err_t init_flag  = alphanumr_init( &alphanumr, &alphanumr_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    alphanumr_set_display_interval( &alphanumr, 1000 );

    alphanumr_write_character( &alphanumr, 'M', 'E' );
    alphanumr_write_character( &alphanumr, '@', '?' );

    alphanumr_write_number( &alphanumr, 0,  1 );
    alphanumr_write_number( &alphanumr, 1,  2 );
    alphanumr_write_number( &alphanumr, 2,  3 );
    alphanumr_write_number( &alphanumr, 3,  4 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
