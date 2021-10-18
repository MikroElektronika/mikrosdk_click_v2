/*!
 * @file main.c
 * @brief UT-S7-SEGR Click example
 *
 * # Description
 * The demo application shows basic usage of the UT 7 SEG display.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 *
 * ## Application Task
 * Draws numbers from 0 to 99 on the screen.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "uts7segr.h"

static uts7segr_t uts7segr;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    uts7segr_cfg_t uts7segr_cfg;  /**< Click config object. */

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

    uts7segr_cfg_setup( &uts7segr_cfg );
    UTS7SEGR_MAP_MIKROBUS( uts7segr_cfg, MIKROBUS_1 );
    err_t init_flag  = uts7segr_init( &uts7segr, &uts7segr_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uts7segr_default_cfg ( &uts7segr );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) { 
    log_info( &logger, "---- Number counter ----" );

    for ( uint8_t cnt = 0; cnt < 100; cnt++ ) {
        uts7segr_display_number( &uts7segr, cnt, UTS7SEGR_DOT_LEFT );
        Delay_ms( 500 );
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
