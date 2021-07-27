/*!
 * \file 
 * \brief Rs485Isolator Click example
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

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

static rs485isolator_t rs485isolator;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs485isolator_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = rs485isolator_generic_read( &rs485isolator, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        log_printf( &logger, "Received data: " );
        
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ check_buf_cnt ] );
        }
    }
    Delay_ms( 100 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs485isolator_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs485isolator_cfg_setup( &cfg );
    RS485ISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485isolator_init( &rs485isolator, &cfg );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs485isolator_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator_generic_write( &rs485isolator, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#endif    
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
