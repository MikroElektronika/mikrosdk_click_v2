/*!
 * \file 
 * \brief AnyNet2g Click example
 * 
 * # Description
 * This example reads and processes data from AnyNet 2G clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - anynet2g_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "anynet2g.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

#define AT                    "AT" 
#define AT_AWSVER             "AT+AWSVER"
#define AT_QCCID              "AT+QCCID"
#define AT_AWSSTATE_TEST      "AT+AWSSTATE=?"
#define AT_AWSSTATE_GET       "AT+AWSSTATE?"
#define AT_AWSPUBOPEN_TEST    "AT+AWSPUBOPEN=?"
#define AT_AWSPUBOPEN_GET     "AT+AWSPUBOPEN?" 
#define AT_AWSPUBOPEN_SET     "AT+AWSPUBOPEN=0,\"MyTopic\"" 
#define MY_TOPIC              "MY_TOPIC" 
#define AT_AWSPUBLISH_SET     "AT+AWSPUBLISH=0,6,MikroE"

// ------------------------------------------------------------------ VARIABLES

static anynet2g_t anynet2g;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void anynet2g_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = anynet2g_generic_read( &anynet2g, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }

            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
    log_printf( &logger, "%s\r\n", current_parser_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    anynet2g_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    anynet2g_cfg_setup( &cfg );
    ANYNET2G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    anynet2g_init( &anynet2g, &cfg );

    anynet2g_send_command( &anynet2g, AT );
    anynet2g_process( );
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_AWSVER );
    anynet2g_process( );
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_QCCID );
    anynet2g_process( );
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_AWSSTATE_GET );  
    anynet2g_process( );                     
    Delay_ms( 3000 );
    anynet2g_send_command( &anynet2g, AT_AWSPUBOPEN_SET );
    anynet2g_process( );
    Delay_ms( 3000 );
}

void application_task ( void )
{
    anynet2g_send_command( &anynet2g, AT_AWSPUBLISH_SET );
    anynet2g_process( );
    Delay_ms( 3000 );
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
