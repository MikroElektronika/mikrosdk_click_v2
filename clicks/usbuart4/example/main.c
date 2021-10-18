/*!
 * @file main.c
 * @brief USB UART 4 Click Example.
 *
 *# Description
 * This example reads and processes data from USB UART 4 clicks.
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
#include "usbuart4.h"
#include "string.h"

#define PROCESS_BUFFER_SIZE 500

static usbuart4_t usbuart4;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart4_cfg_t usbuart4_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );

    // Click initialization.

    usbuart4_cfg_setup( &usbuart4_cfg );
    USBUART4_MAP_MIKROBUS( usbuart4_cfg, MIKROBUS_1 );
    
    err_t init_flag  = usbuart4_init( &usbuart4, &usbuart4_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    
    usbuart4_pwr_ctrl( &usbuart4, USBUART4_POWER_ON );
    usbuart4_set_cts( &usbuart4, USBUART4_CTS_NO_ACTIVE );
    usbuart4_set_mode( &usbuart4, USBUART4_MODE_NORMAL );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    app_buf_len = usbuart4_generic_read( &usbuart4, app_buf, PROCESS_BUFFER_SIZE );
    
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
