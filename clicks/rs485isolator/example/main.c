/*!
 * \file 
 * \brief RS485 Isolator Click example
 * 
 * # Description
 * This example reads and processes data from RS485 Isolator clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - rs485isolator_process ( ) - The general process of collecting the received data.
 * 
 * @note
 * Wire connection guide : Driver(Master)       Slave
 *                                     Y   ->   A
 *                                     Z   ->   B
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs485isolator.h"
#include "string.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

#define TEXT_TO_SEND "MIKROE - RS485 Isolator click\r\n"

#define PROCESS_RX_BUFFER_SIZE 100

// ------------------------------------------------------------------ VARIABLES

static rs485isolator_t rs485isolator;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs485isolator_process ( void )
{
    uint8_t uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    
    int32_t rsp_size = rs485isolator_generic_read( &rs485isolator, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        log_printf( &logger, "Received data: " );
        
        for ( uint8_t check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ check_buf_cnt ] );
        }
        Delay_ms ( 100 );
        rsp_size = rs485isolator_generic_read( &rs485isolator, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
        if ( rsp_size > 0 )
        { 
            for ( uint8_t check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                log_printf( &logger, "%c", uart_rx_buffer[ check_buf_cnt ] );
            }
        }
    }
    Delay_ms ( 100 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs485isolator_cfg_t cfg;

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
    rs485isolator_cfg_setup( &cfg );
    RS485ISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485isolator_init( &rs485isolator, &cfg );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator_generic_write( &rs485isolator, TEXT_TO_SEND, strlen ( TEXT_TO_SEND ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    rs485isolator_process( );
#endif    
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
