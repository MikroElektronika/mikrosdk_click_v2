/*!
 * @file main.c
 * @brief UVB Click example
 *
 * # Description
 * This Click is ultraviolet sensing board, capable of measuring UV index between 0 to 16. 
 * UVB Click supports integrated functions of ultraviolet light sensors.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver init, check communication and configuration module for measurement.
 *
 * ## Application Task
 * Reads UVB data and logs to the USBUART every 1500ms.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "uvb.h"

static uvb_t uvb;
static log_t logger;

static uint16_t uvb_data;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uvb_cfg_t uvb_cfg;  /**< Click config object. */

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
    uvb_cfg_setup( &uvb_cfg );
    UVB_MAP_MIKROBUS( uvb_cfg, MIKROBUS_1 );
    err_t init_flag = uvb_init( &uvb, &uvb_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uvb_default_cfg ( &uvb );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
}

void application_task ( void ) 
{
    uvb_data = uvb_get_uv_data( &uvb );

    log_printf( &logger, ">> UVB data: %d\r\n", uvb_data );

    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
