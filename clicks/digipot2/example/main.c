
/*!
 * @file main.c
 * @brief DigiPot2 Click example
 *
 * # Description
 * The demo application changes the resistance using DIGI POT 2 Click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI and LOG modules.
 *
 * ## Application Task
 * This is an example which demonstrates the use of DIGI POT 2 Click board.
 * Increments the wiper position by 10 positions every 5 seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot2.h"

static digipot2_t digipot2;
static log_t logger;

uint8_t wiper_pos;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot2_cfg_t digipot2_cfg;  /**< Click config object. */

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

    digipot2_cfg_setup( &digipot2_cfg );
    DIGIPOT2_MAP_MIKROBUS( digipot2_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot2_init( &digipot2, &digipot2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "----------------\r\n" );
    log_printf( &logger, " DIGI POT 2 Click\r\n" );
    log_printf( &logger, "----------------\r\n" );
}

void application_task ( void ) {
    for ( uint16_t n_cnt = 127; n_cnt < 255; n_cnt += 10 ) {
        wiper_pos = ( uint8_t ) n_cnt;
        digipot2_set_wiper_positions( &digipot2, wiper_pos );
        Delay_ms( 5000 );
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
