/*!
 * @file main.c
 * @brief ReRAM2 Click example
 *
 * # Description
 * This library contains API for ReRAM 2 Click driver.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver and log UART.
 * After driver initialization the app set default settings, 
 * performs device wake-up, check Device ID,
 * set Write Enable Latch command and write demo_data string ( mikroE ), 
 * starting from the selected memory_addr ( 1234 ).
 *
 * ## Application Task
 * This is an example that demonstrates the use of the ReRAM 2 Click board™.
 * In this example, we read and display a data string, which we have previously written to memory, 
 * starting from the selected memory_addr ( 1234 ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "reram2.h"

static reram2_t reram2;
static log_t logger;
static char demo_data[ 9 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static uint32_t memory_addr;

void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    reram2_cfg_t reram2_cfg;  /**< Click config object. */

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
    reram2_cfg_setup( &reram2_cfg );
    RERAM2_MAP_MIKROBUS( reram2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == reram2_init( &reram2, &reram2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RERAM2_ERROR == reram2_default_cfg ( &reram2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    reram2_wake_up( &reram2 );
    Delay_ms( 100 );
    
    if ( RERAM2_ERROR == reram2_check_device_id( &reram2 ) )
    {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );
        for( ; ; );
    }

    reram2_send_command( &reram2, RERAM2_CMD_WREN );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    
    memory_addr = 1234;   
    log_printf( &logger, "\r\n  Write data : %s", demo_data );
    reram2_write_memory( &reram2, memory_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    static char rx_data[ 9 ] = { 0 };
    
    reram2_read_memory( &reram2, memory_addr, &rx_data[ 0 ], 9 );
    log_printf( &logger, "  Read data  : %s", rx_data ); 
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 2000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
