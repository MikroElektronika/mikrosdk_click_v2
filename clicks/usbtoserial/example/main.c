/*!
 * @file main.c
 * @brief USB to Serial Click Example.
 *
 * # Description
 * This example demonstrates the USB to Serial Click board's ability to act as a USB-to-UART bridge.
 * It enables bidirectional communication between a USB host and a UART device by forwarding 
 * received data between the USB and UART interfaces.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board and enables the device.
 *
 * ## Application Task
 * Continuously reads the data from one UART interface and forwards it to the other,
 * enabling seamless USB to UART data transfer and vice versa.
 *
 * @note
 * Make sure the USB to Serial Click is properly connected to a USB host and the 
 * mikroBUS socket, and that both UART interfaces are configured for the same baud rate.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "usbtoserial.h"

#ifndef MIKROBUS_POSITION_USBTOSERIAL
    #define MIKROBUS_POSITION_USBTOSERIAL MIKROBUS_1
#endif

#define PROCESS_BUFFER_SIZE 200

static usbtoserial_t usbtoserial;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbtoserial_cfg_t usbtoserial_cfg;  /**< Click config object. */

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
    usbtoserial_cfg_setup( &usbtoserial_cfg );
    USBTOSERIAL_MAP_MIKROBUS( usbtoserial_cfg, MIKROBUS_POSITION_USBTOSERIAL );
    if ( UART_ERROR == usbtoserial_init( &usbtoserial, &usbtoserial_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbtoserial_reset_device ( &usbtoserial );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );

    uart_set_blocking( &logger.uart, false );

    // Dummy read to enable RX interrupts
    uart_read( &usbtoserial.uart, app_buf, 1 );
    uart_read( &logger.uart, app_buf, 1 );
}

void application_task ( void ) 
{
    if ( uart_bytes_available ( &logger.uart ) ) 
    {
        app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
        if ( app_buf_len > 0 )
        {
            uart_write ( &usbtoserial.uart, app_buf, app_buf_len );
            memset( app_buf, 0, app_buf_len );
            app_buf_len = 0;
        }
    }
    if ( uart_bytes_available ( &usbtoserial.uart ) ) 
    {
        app_buf_len = uart_read( &usbtoserial.uart, app_buf, PROCESS_BUFFER_SIZE );
        if ( app_buf_len > 0 )
        {
            uart_write ( &logger.uart, app_buf, app_buf_len );
            memset( app_buf, 0, app_buf_len );
            app_buf_len = 0;
        }
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
