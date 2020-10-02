/*!
 * \file 
 * \brief Thingstream Click example
 * 
 * # Description
 * This example reads and processes data from Thingstream clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - thingstream_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thingstream.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

char demo_cmd[ 16 ] = "+IOTCGNSINF";

#define THINGSTREAM_INFO      "AT+IOTINFO"
#define THINGSTREAM_CREATE    "AT+IOTCREATE"
#define THINGSTREAM_CONNECT   "AT+IOTCONNECT=true"
#define THINGSTREAM_GPS_PWR   "AT+IOTCGNSPWR=1"
#define THINGSTREAM_SUBSCRIBE "AT+IOTSUBSCRIBE=\"home/temperature\",1"
#define THINGSTREAM_PUBLISH   "AT+IOTPUBLISH=\"home/temperature\",0,\"23 degrees\""
#define THINGSTREAM_GPS_INFO  "AT+IOTCGNSINF"

#define THINGSTREAM_CMD_CGNSPWR "AT+CGNSPWR=1"
#define THINGSTREAM_CMD_CGNSSEQ "AT+CGNSSEQ=\"GGA\""
#define THINGSTREAM_CMD_CGNSINF "AT+CGNSINF"

// ------------------------------------------------------------------ VARIABLES

static thingstream_t thingstream;
static log_t logger;

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void thingstream_process ( void )
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
        rsp_size = thingstream_generic_read( &thingstream, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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

static void parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    
    thingstream_process( );
    
    log_printf( &logger, "\r\n_______________________________\r\n" ); 
    thingstream_generic_parser( rsp, THINGSTREAM_NEMA_CGNSINF, THINGSTREAM_CGNSINF_LATITUDE, element_buf );
    log_printf( &logger, "Latitude:  %s \r\n", element_buf );    
    thingstream_generic_parser( rsp, THINGSTREAM_NEMA_CGNSINF, THINGSTREAM_CGNSINF_LONGITUDE, element_buf );
    log_printf( &logger, "Longitude:  %s \r\n", element_buf );  
    thingstream_generic_parser( rsp, THINGSTREAM_NEMA_CGNSINF, THINGSTREAM_CGNSINF_ALTITUDE, element_buf );
    log_printf( &logger, "Alitude: %s \r\n", element_buf );  
    log_printf( &logger, "\r\n_______________________________\r\n" ); 
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thingstream_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thingstream_cfg_setup( &cfg );
    THINGSTREAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thingstream_init( &thingstream, &cfg );

    thingstream_module_power( &thingstream, true );
    Delay_ms( 3000 );

    log_printf( &logger, " --->>> INFO.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_INFO );
    Delay_ms( 5000 );
    thingstream_process( );
        
    log_printf( &logger, " --->>> CREATE.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_CREATE );
    Delay_ms( 5000 );
    thingstream_process( );

    log_printf( &logger, " --->>> CONNECT.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_CONNECT );
    Delay_ms( 5000 );
    thingstream_process( );

    log_printf( &logger, " --->>> GPS POWER.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_GPS_PWR );
    Delay_ms( 5000 );
    thingstream_process( );

    log_printf( &logger, " --->>> SUBSCRIBE.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_SUBSCRIBE );
    Delay_ms( 5000 );
    thingstream_process( );

    log_printf( &logger, " --->>> PUBLISH.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_PUBLISH );
    Delay_ms( 5000 );
    thingstream_process( );

    log_printf( &logger, " --->>> APP INIT <<<--- \r\n" );
    log_printf( &logger, " ______________________ \r\n\r\n" );
}

void application_task ( void )
{
    log_printf( &logger, " --->>> GPS INFO \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_GPS_INFO );   
    thingstream_process( );

    parser_application( current_parser_buf );
    thingstream_process( );

    Delay_ms( 5000 );
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
