/*!
 * @file main.c
 * @brief USB UART 2 Click Example.
 *
 * # Description
 * This example reads and processes data from USB UART 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads data and echos it back to device and logs it to board.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "usbuart2.h"
#include "string.h"

#define PROCESS_BUFFER_SIZE 500

static usbuart2_t usbuart2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart2_cfg_t usbuart2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 100 );

    // Click initialization.

    usbuart2_cfg_setup( &usbuart2_cfg );
    USBUART2_MAP_MIKROBUS( usbuart2_cfg, MIKROBUS_1 );
    
    err_t init_flag  = usbuart2_init( &usbuart2, &usbuart2_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    
    usbuart2_pwr_ctrl( &usbuart2, USBUART2_POWER_ON );
    usbuart2_set_cts( &usbuart2, USBUART2_CTS_NO_ACTIVE );
    usbuart2_set_mode( &usbuart2, USBUART2_MODE_NORMAL );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    app_buf_len = usbuart2_generic_read( &usbuart2, app_buf, PROCESS_BUFFER_SIZE );
    
    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        memset( app_buf, 0, PROCESS_BUFFER_SIZE );
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
