/*!
 * @file main.c
 * @brief UART MUX 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of UART MUX 4 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the UART driver and additional pins.
 *
 * ## Application Task
 * Writes demo message, echos it back, processes all incoming data 
 * and displays them on the USB UART.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "uartmux4.h"

#define PROCESS_BUFFER_SIZE 200
#define DEMO_MESSAGE "\r\nMikroE\r\n"

static uartmux4_t uartmux4;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uartmux4_cfg_t uartmux4_cfg;  /**< Click config object. */

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
    uartmux4_cfg_setup( &uartmux4_cfg );
    UARTMUX4_MAP_MIKROBUS( uartmux4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == uartmux4_init( &uartmux4, &uartmux4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    log_printf( &logger, " ---------------- \r\n" );
    log_printf( &logger, " UART 1 demo message:\r\n" );
    uartmux4_enable_uart1( &uartmux4 );
    Delay_ms ( 100 );
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( uartmux4_generic_write ( &uartmux4, DEMO_MESSAGE, sizeof( DEMO_MESSAGE ) ) )
        {
            if ( uartmux4_generic_read( &uartmux4, app_buf, sizeof( DEMO_MESSAGE ) ) )
            {
                log_printf( &logger, "%s", app_buf );
            }
        }
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " ---------------- \r\n" );
    log_printf( &logger, " UART 2 demo message:\r\n" );
    uartmux4_enable_uart2( &uartmux4 );
    Delay_ms ( 100 );
    for ( uint8_t n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        if ( uartmux4_generic_write ( &uartmux4, DEMO_MESSAGE, sizeof( DEMO_MESSAGE ) ) )
        {
            if ( uartmux4_generic_read( &uartmux4, app_buf, sizeof( DEMO_MESSAGE ) ) )
            {
                log_printf( &logger, "%s", app_buf );
            }
        }
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
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
