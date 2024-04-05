/*!
 * @file main.c
 * @brief Binho Nova Click Example.
 *
 * # Description
 * This example demonstrates the use of Binho Nova click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * All data received from the USB UART will be forwarded to mikroBUS UART, and vice versa.
 *
 * @note
 * The example code is performed via UART communication and consists of a few simple steps:
 * 1. Place "Binho Nova Click" into the mikroBUS socket 1.
 * 2. Insert the "Binho USB Host Adapter" connector into the "Binho Nova Click" I2C/UART slot.
 * 3. Start the "Mission Control Software" application.
 * 4. Connect "Binho USB Host Adapter".
 * 5. Activate UART Bridge with a baud rate of 115200bps.
 * 6. All data sent via the "Mission Control Software" application will be displayed on
 * the USB UART logger, and vice versa.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "binhonova.h"

#define PROCESS_BUFFER_SIZE 200

static binhonova_t binhonova;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    binhonova_cfg_t binhonova_cfg;  /**< Click config object. */

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
    binhonova_cfg_setup( &binhonova_cfg );
    BINHONOVA_MAP_MIKROBUS( binhonova_cfg, MIKROBUS_1 );
    if ( UART_ERROR == binhonova_init( &binhonova, &binhonova_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    
    uart_set_blocking( &logger.uart, false );
}

void application_task ( void ) 
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &binhonova.uart, app_buf, app_buf_len );
        memset( app_buf, 0, app_buf_len );
        app_buf_len = 0;
    }
    app_buf_len = uart_read( &binhonova.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        memset( app_buf, 0, app_buf_len );
        app_buf_len = 0;
    }
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
