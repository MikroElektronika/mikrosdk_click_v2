/*!
 * @file main.c
 * @brief AlphaNumG Click example
 *
 * # Description
 * This example showcases the initialization and configuration of the logger and Click modules
 * and shows how to display characters and numbers on both LED segments of the Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and Click modules.
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
#include "alphanumg.h"

static alphanumg_t alphanumg;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    alphanumg_cfg_t alphanumg_cfg;  /**< Click config object. */

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

    alphanumg_cfg_setup( &alphanumg_cfg );
    ALPHANUMG_MAP_MIKROBUS( alphanumg_cfg, MIKROBUS_1 );
    err_t init_flag  = alphanumg_init( &alphanumg, &alphanumg_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    alphanumg_set_display_interval( &alphanumg, 1000 );

    alphanumg_write_character( &alphanumg, 'M', 'E' );
    alphanumg_write_character( &alphanumg, '@', '?' );

    alphanumg_write_number( &alphanumg, 0,  1 );
    alphanumg_write_number( &alphanumg, 1,  2 );
    alphanumg_write_number( &alphanumg, 2,  3 );
    alphanumg_write_number( &alphanumg, 3,  4 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
