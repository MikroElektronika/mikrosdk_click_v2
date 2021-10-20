/*!
 * \file 
 * \brief Rn4871 Click example
 * 
 * # Description
 * This example reads and processes data from RN4871 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART driver. Initializes device and parser.
 * 
 * ## Application Task  
 * If 'MASTER' - connects to 'SLAVE', sends message and disconnects. If 'SLAVE' - waits for connect request 
 * and message from 'MASTER' and LOGs received message.
 * 
 * ## Additional Function
 * - rn4871_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rn4871.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

// #define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static rn4871_t rn4871;
static log_t logger;

uint8_t RN4871_ADDR_MASTER[ 13 ] = {'D', 'F', '0', '0', '0', '0', '0', '6', '8', '7', '9', '0'};
uint8_t RN4871_ADDR_SLAVE[ 13 ] = {'D', 'F', '1', '1', '1', '1', '1', '6', '8', '7', '9', '0'};
uint8_t message_payload[ 17 ] = {'M', 'i', 'k', 'r', 'o', 'E', 'l', 'e', 'k', 't', 'r', 'o', 'n', 'i', 'k', 'a'};

uint8_t dev_type;
uint8_t receive_buffer[ 255 ];
uint8_t msg_flag = 0;
char *ptr;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rn4871_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    

    rsp_size = rn4871_generic_read( &rn4871, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        // Validation of the received data
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            rn4871_receive( &rn4871, uart_rx_buffer[ check_buf_cnt ] );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4871_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rn4871_cfg_setup( &cfg );
    RN4871_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4871_init( &rn4871, &cfg );
    Delay_ms( 100 );
    
    dev_type = RN4871_DEVICETYPE_MASTER;

#ifdef DEMO_APP_TRANSMITER
    log_info( &logger, "RN4871 DEVICE TYPE MASTER" );
    rn4871_initialize( &rn4871, &RN4871_ADDR_MASTER[ 0 ] );
#endif
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "RN4871 DEVICE TYPE SLAVE" );
    rn4871_initialize( &rn4871, &RN4871_ADDR_SLAVE[ 0 ] );
    ptr = &receive_buffer[ 7 ];
#endif

    memset( &rn4871.device_buffer, 0, 255 );
    log_printf( &logger, " >>> app init done <<<  \r\n" );
}

void application_task ( void )
{
    rn4871_process(  );
#ifdef DEMO_APP_TRANSMITER
    rn4871_connect( &rn4871, &RN4871_ADDR_SLAVE[ 0 ] );
    Delay_ms( 100 );
    log_printf( &logger, ">>> sending data  <<<\r\n" );
    rn4871_send( &rn4871, RN4871_MTYPE_MSG, RN4871_DTYPE_STRING, RN4871_ID_MASTER, &message_payload[ 0 ] );
    Delay_ms( 100 );
    rn4871_disconnect( &rn4871 );
    Delay_ms( 100 );
#endif

#ifdef DEMO_APP_RECEIVER
    msg_flag = rn4871_read( &rn4871, &receive_buffer[ 0 ] );

    if ( msg_flag == 1 )
    {
        log_printf( &logger, ">>> data received <<<\r\n" );
        log_printf( &logger, ">>> data : " );
        log_printf( &logger, "%s\r\n", ptr );     
    }
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
