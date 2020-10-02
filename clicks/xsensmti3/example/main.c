/*!
 * \file 
 * \brief XsensMti3 Click example
 * 
 * # Description
 * This example reads and processes data from XSENS MTi 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize driver init and uart interrupt.
 * 
 * ## Application Task  
 * Reads the received data and parses it. Shows Roll, Pitch and Yaw data.
 * 
 * ## Additional Function
 * - xsensmti3_process ( ) - The general process of collecting presponce that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "xsensmti3.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

static xsensmti3_t xsensmti3;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t parser_buf_cnt;
static uint8_t active_flag;
static uint8_t start_rsp;
static uint16_t rsp_cnt;

static xsensmti3_parse_t parse_data_obj;
static xsensmti3_data_t data_obj;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void xsensmti3_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    
    // Clear parser buffer
//     memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    rsp_size = xsensmti3_generic_read( &xsensmti3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
    
    if ( rsp_size != -1 )
    {  
        // Storages data in parser buffer
//         rsp_cnt += rsp_size;
        parser_buf_cnt += rsp_size;
        if ( rsp_cnt + rsp_size < PROCESS_PARSER_BUFFER_SIZE )
        {
            strncat( &current_parser_buf[ rsp_cnt ], uart_rx_buffer, rsp_size );
            rsp_cnt += rsp_size;
        }
        else
        {
            memset( &current_parser_buf[ 0 ], 0 , PROCESS_PARSER_BUFFER_SIZE );
            parser_buf_cnt = 0;
            active_flag = 0;
            start_rsp = 0;
            rsp_cnt = 0;
        }
        
        // Clear RX buffer
        memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    } 
    else 
    {
        // Process delay 
        Delay_100ms( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    xsensmti3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    xsensmti3_cfg_setup( &cfg );
    XSENSMTI3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    xsensmti3_init( &xsensmti3, &cfg );

    parser_buf_cnt = 0;
    active_flag = 0;
    start_rsp = 0;
    rsp_cnt = 0;
}

void application_task ( void )
{
    uint8_t check_data = 0;
    uint8_t cnt = 0;

//     Delay_ms( 500 );
    xsensmti3_process( );

    // STARTS COLLECTING DATA
    if ( active_flag == XSENSMTI3_WAIT_FOR_START )
    {
        memset( &current_parser_buf[ 0 ], 0 , PROCESS_PARSER_BUFFER_SIZE );
        parser_buf_cnt = 0;
        active_flag = 0;
        start_rsp = 0;
        rsp_cnt = 0;
        active_flag = XSENSMTI3_START_PROCESS;
    }

    // CHECKS RECEIVED DATA
    if ( ( parser_buf_cnt > 100 ) && ( active_flag == XSENSMTI3_START_PROCESS ) )
    {
       active_flag = XSENSMTI3_DATA_PROCESSING;
    }

    // CHECKS IF THE VALID PACKAGE IS RECEIVED
    if ( active_flag == XSENSMTI3_DATA_PROCESSING )
    {
        check_data = xsensmti3_check_package( &current_parser_buf[ 0 ], &start_rsp );
        if ( check_data == 1 )
        {
            active_flag = XSENSMTI3_PARSER_DATA;
        }
        else
        {
            active_flag = XSENSMTI3_WAIT_FOR_START;
        }
    }

    // PARSING DATA AND DISPLAY
    if ( active_flag == XSENSMTI3_PARSER_DATA )
    {
       xsensmti3_parser( &current_parser_buf[ 0 ], start_rsp, &parse_data_obj );

       log_printf( &logger, ">> Quaternion data <<\r\n" );

       for ( cnt = 0; cnt < 4; cnt++ )
       {
           log_printf( &logger, ">> Q: %e\r\n", parse_data_obj.quat_obj.quat_data[ cnt ] );
       }

       log_printf( &logger, "--------------\r\n" );

       xsensmti3_get_data( &parse_data_obj.quat_obj, &data_obj );

       log_printf( &logger, ">> ROLL: %.4f\r\n", data_obj.roll );

       log_printf( &logger, ">> PITCH: %.4f\r\n", data_obj.pitch );

       log_printf( &logger, ">> YAW: %.4f\r\n", data_obj.yaw );

       active_flag = XSENSMTI3_WAIT_FOR_START;

       log_printf( &logger, " \r\n--------------\r\n" );
//        Delay_ms( 300 );
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
