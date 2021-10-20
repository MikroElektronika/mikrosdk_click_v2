/*!
 * @file main.c
 * @brief CurrentLimit Click example
 *
 * # Description
 * This example shows capabilities of Current Limit Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes SPI driver and enables the device.
 *
 * ## Application Task
 * Reading users input from USART terminal and using it as an index for
 * an array of pre-calculated values that define current limit level.
 *
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "currentlimit.h"

static currentlimit_t currentlimit;
static log_t logger;

const uint8_t lim_val[ 8 ] = { 223, 241, 247, 250, 252, 253, 254, 255 };
uint16_t lim_data[8] = { 100, 200, 300, 400, 500, 600, 700, 867 };

void display_settings ( void ) {
    log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
    log_printf( &logger, " To select current limit \r\n" );
    log_printf( &logger, " Send one of the numbers \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
    log_printf( &logger, " 1 - Limited to 100 mA \r\n" );
    log_printf( &logger, " 2 - Limited to 200 mA \r\n" );
    log_printf( &logger, " 3 - Limited to 300 mA \r\n" );
    log_printf( &logger, " 4 - Limited to 400 mA \r\n" );
    log_printf( &logger, " 5 - Limited to 500 mA \r\n" );
    log_printf( &logger, " 6 - Limited to 600 mA \r\n" );
    log_printf( &logger, " 7 - Limited to 700 mA \r\n" );
    log_printf( &logger, " 8 - Limited to 867 mA \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
}

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit_cfg_t currentlimit_cfg;  /**< Click config object. */

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

    currentlimit_cfg_setup( &currentlimit_cfg );
    CURRENTLIMIT_MAP_MIKROBUS( currentlimit_cfg, MIKROBUS_1 );
    err_t init_flag  = currentlimit_init( &currentlimit, &currentlimit_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    currentlimit_dev_enable( &currentlimit, CURRENTLIMIT_ENABLE );
    log_printf( &logger, "    Click  Enabled!    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    display_settings( );
}

void application_task ( void ) {
    char inx;
    if ( log_read( &logger, &inx, 1 ) != CURRENTLIMIT_ERROR ) {
        if ( inx >= '1' && inx <= '8' ) {
            currentlimit_set_limit( &currentlimit, lim_val[ inx - 1 ] );
            log_printf( &logger, " Selected mode %d, \r\n Current limit is %d mA \r\n", ( uint16_t ) inx - 48, lim_data[ inx - 49 ] );
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
        } else { 
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
            log_printf( &logger, " Data not in range! \r\n" );
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
            display_settings( );
        }
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
