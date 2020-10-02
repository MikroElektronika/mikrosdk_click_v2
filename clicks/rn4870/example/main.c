/*!
 * \file 
 * \brief Rn4870 Click example
 * 
 * # Description
 * This example reads and processes data from RN4870 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - UART, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of RN4870 Click board.
 * If 'MASTER' - connects to 'SLAVE', sends message and disconnects.
 * If 'SLAVE' - waits for connect request and message from 'MASTER' and LOGs received message.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * ## Additional Function
 * - rn4870_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rn4870.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static rn4870_t rn4870;
static log_t logger;

static uint8_t send_data_cnt = 0; 
uint8_t dev_type;
uint8_t receive_buffer[ 255 ];
uint8_t msg_flag = 0;
char *log_text;

uint8_t MESSAGE_DATA[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
uint8_t RECIVE_DATA[ 50 ];
uint8_t RN4870_ADDR_MASTER[ 13 ] = {'D', 'F', '0', '0', '0', '0', '0', '6', '8', '7', '9', '0'};
uint8_t RN4870_ADDR_SLAVE1[ 13 ] = {'D', 'F', '1', '1', '1', '1', '1', '6', '8', '7', '9', '0'};
uint8_t RN4870_ADDR_SLAVE2[ 13 ] = {'D', 'F', '2', '2', '2', '2', '2', '6', '8', '7', '9', '0'};

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rn4870_process ( void )
{
    int16_t rsp_size;
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = 10;
    
    while( process_cnt != 0 )
    {
        rsp_size = rn4870_generic_read( &rn4870, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                rn4870_receive( &rn4870, uart_rx_buffer[ check_buf_cnt ] );
            }
        }
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4870_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rn4870_cfg_setup( &cfg );
    RN4870_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4870_init( &rn4870, &cfg );

    dev_type = RN4870_DEVICETYPE_MASTER;

    if ( dev_type == RN4870_DEVICETYPE_MASTER )
    {
        rn4870_initialize( &rn4870, &RN4870_ADDR_MASTER[ 0 ] );
    }
    else if ( dev_type == RN4870_DEVICETYPE_SLAVE )
    {
        rn4870_initialize( &rn4870, &RN4870_ADDR_SLAVE1[ 0 ] );
        log_text = &receive_buffer[ 7 ];
    }

    memset( &rn4870.device_buffer, 0, 255 );
    log_printf( &logger, " Clearing Msg Data  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
}

void application_task ( void )
{
    rn4870_process(  );

    if ( dev_type == RN4870_DEVICETYPE_MASTER )
    {
        rn4870_connect( &rn4870, &RN4870_ADDR_SLAVE1[ 0 ] );
        rn4870_send( &rn4870, RN4870_MTYPE_MSG, RN4870_DTYPE_STRING, RN4870_ID_SLAVE, &MESSAGE_DATA[ 0 ] );
        log_printf( &logger, "    Message Send    \r\n" );
        rn4870_disconnect( &rn4870 );
    }
    else if ( dev_type == RN4870_DEVICETYPE_SLAVE )
    {
        msg_flag = rn4870_read( &rn4870, &RECIVE_DATA[ 0 ] );

        if ( msg_flag == 1 )
        {
            log_printf( &logger, "%s\r\n", RECIVE_DATA );
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
