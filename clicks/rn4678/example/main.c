/*!
 * \file 
 * \brief Rn4678 Click example
 * 
 * # Description
 * This example reads and processes data from RN4678 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 *  Initialization driver enables - UART, also write log..
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of RN4870 Click board.
 * If 'MASTER' - connects to 'SLAVE', sends message and disconnects.
 * If 'SLAVE' - waits for connect request and message from 'MASTER' and LOGs received message.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * ## Additional Function
 * - rn4678_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rn4678.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static rn4678_t rn4678;
static log_t logger;

uint8_t MESSAGE_DATA[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
uint8_t RN4678_ADDR_MASTER[ 13 ] = {'D', 'F', '0', '0', '0', '0', '0', '6', '8', '7', '9', '0'};
uint8_t RN4678_ADDR_SLAVE1[ 13 ] = {'D', 'F', '1', '1', '1', '1', '1', '6', '8', '7', '9', '0'};
uint8_t RN4678_ADDR_SLAVE2[ 13 ] = {'D', 'F', '2', '2', '2', '2', '2', '6', '8', '7', '9', '0'};
uint8_t dev_type;
uint8_t receive_buffer[ 255 ];
uint8_t msg_flag = 0;
char *log_text;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rn4678_process ( void )
{
    uint16_t rsp_size;

    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = uart_read( &rn4678.uart, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size != 0 )
    {  
        // Validation of the received data
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            rn4678_receive( &rn4678, uart_rx_buffer[ check_buf_cnt ] );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4678_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rn4678_cfg_setup( &cfg );
    RN4678_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4678_init( &rn4678, &cfg );

    dev_type = RN4678_DEVICE_TYPE_MASTER;

    if ( dev_type == RN4678_DEVICE_TYPE_MASTER )
    {
        rn4678_initialize( &rn4678, &RN4678_ADDR_MASTER[ 0 ] );
    }
    else if ( dev_type == RN4678_DEVICE_TYPE_SLAVE )
    {
        rn4678_initialize( &rn4678, &RN4678_ADDR_SLAVE1[ 0 ] );
        log_text = &receive_buffer[ 7 ];
    }

    memset( &rn4678.device_buffer, 0, 255 );

    log_printf( &logger, " Clearing Msg Data  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 100 );

}

void application_task ( void )
{
    rn4678_process( );
    
    if ( dev_type == RN4678_DEVICE_TYPE_MASTER )
    {
        rn4678_connect( &rn4678, &RN4678_ADDR_SLAVE1[ 0 ] );
        rn4678_send( &rn4678, RN4678_MTYPE_MSG, RN4678_DTYPE_STRING, RN4678_ID_SLAVE, &MESSAGE_DATA[ 0 ] );
        log_printf( &logger, "    Message Send    \r\n" );
        rn4678_disconnect( &rn4678 );
    }
    else if ( dev_type == RN4678_DEVICE_TYPE_SLAVE )
    {
        msg_flag = rn4678_read( &rn4678, receive_buffer );

        if ( msg_flag == 1 )
        {
            log_printf( &logger, " %s \r\n", receive_buffer );
        }
    }
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
