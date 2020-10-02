/*!
 * \file 
 * \brief WifiEsp Click example
 * 
 * # Description
 * This example reads and processes data from Wifi ESP clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - wifiesp_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifiesp.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static wifiesp_t wifiesp;
static log_t logger;

#define SSID       "\"MikroE Public\","
#define PASSWORD   "\"mikroe.guest\""

char txt_state_A0[ 9 ] = "OFF</p>";

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void wifiesp_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = wifiesp_generic_read( &wifiesp, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            log_printf( &logger, "%s", uart_rx_buffer );

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
            Delay_100ms( );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifiesp_cfg_t cfg;

    char temp[ PROCESS_RX_BUFFER_SIZE ] = { 0 } ;
    char ip_address[ 17 ];
    uint8_t length;
    char *txt_val;
    char *data_buff;
    uint8_t i;
    uint8_t flag;
    uint8_t cnt;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifiesp_cfg_setup( &cfg );
    WIFIESP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifiesp_init( &wifiesp, &cfg );

    wifiesp_reset( &wifiesp );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_RST );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );
    
    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_SET_AT_CWMODE_1 );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    strcat( temp, "AT+CWJAP=" );
    strcat( temp, SSID );
    strcat( temp, PASSWORD );
 
    wifiesp_send_command ( &wifiesp, temp );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );
    
    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_CIPSTATUS );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    flag = 0;

    for ( ; ; )
    {
        wifiesp_process(  );
        
        for ( i = 0; i < strlen( current_parser_buf ); i++ )
        {
              if ( current_parser_buf[ i ] == 'K' )
            {
                flag = 1;
              break;
            }
        }
        
        if( flag == 1 )
        {
            break;
        }
        
    }
    
    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_SET_AT_CIPMUX_1 );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_SET_AT_CIPSERVER_1_80 );

    wifiesp_process(  );
    
    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_GET_AT_CIPSTO );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    //returns ip address and mac address

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_CIFSR ); 

    wifiesp_process(  ); 

    flag = 0;
    cnt = 0;

    memset( ip_address, 0, 17 );
    
    for ( i = 0; i < strlen( current_parser_buf); i++ )
    {

        if ( ( current_parser_buf[ i ] == 34 ) && ( flag == 0 ) ) 
        {
            flag = 1;
           
        }
        else if ( ( current_parser_buf[ i ] == 13 ) && ( flag == 1 ) )
        {
            memset( &ip_address[ cnt - 2 ], 0, 2 );
            flag = 0;
            break;
        }
        
        if ( flag == 1 )
        {
            ip_address[ cnt++ ] = current_parser_buf[ i + 1 ];

        }
    }
  
    log_printf( &logger, " \r\n--------------------------- \r\n" );
        
    log_printf( &logger, "%s", ip_address );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    wifiesp_send_command ( &wifiesp, WIFIESP_SINGLE_CMD_AT_CIPSTATUS );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    strcat( temp, "AT+CIPSTART=4,\"TCP\",\"" );
    strcat( temp, ip_address );
    strcat( temp, "\",80" );

    wifiesp_send_command ( &wifiesp, temp );

    wifiesp_process(  );

    log_printf( &logger, " \r\n--------------------------- \r\n" );

    Delay_ms( 2000 );
}

void application_task ( void )
{
    wifiesp_process(  );
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
