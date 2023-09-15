/*!
 * @file main.c
 * @brief XSENS MTi-3 Click Example.
 *
 * # Description
 * This example reads and processes data from XSENS MTi-3 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wake-up module.
 *
 * ## Application Task
 * Reads the received data and parses it. Shows Roll, Pitch and Yaw data.
 *
 * ## Additional Function
 * - void xsensmti3_process ( void ) - The general process of collecting data the module sends.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "xsensmti3.h"

#define PROCESS_RX_BUFFER_SIZE 200
#define PROCESS_PARSER_BUFFER_SIZE 1000

static xsensmti3_t xsensmti3;
static log_t logger;

static uint8_t current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t parser_buf_cnt;
static uint8_t active_flag;
static uint8_t start_rsp;
static uint16_t rsp_cnt;

static xsensmti3_parse_t parse_data_obj;
static xsensmti3_data_t data_obj;

/**
 * @brief XSENS MTi-3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return Nothing.
 * @note None.
 */
static void xsensmti3_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xsensmti3_cfg_t xsensmti3_cfg;  /**< Click config object. */

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
    xsensmti3_cfg_setup( &xsensmti3_cfg );
    XSENSMTI3_MAP_MIKROBUS( xsensmti3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xsensmti3_init( &xsensmti3, &xsensmti3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t check_data = 0;
    uint8_t cnt = 0;

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

    if ( ( parser_buf_cnt > 100 ) && ( active_flag == XSENSMTI3_START_PROCESS ) )
    {
       active_flag = XSENSMTI3_DATA_PROCESSING;
    }

    if ( active_flag == XSENSMTI3_DATA_PROCESSING )
    {
        check_data = xsensmti3_check_package( &current_parser_buf[ 0 ], &start_rsp );
        if ( check_data == XSENSMTI3_OK )
        {
            active_flag = XSENSMTI3_PARSER_DATA;
        }
        else
        {
            active_flag = XSENSMTI3_WAIT_FOR_START;
        }
    }

    if ( active_flag == XSENSMTI3_PARSER_DATA )
    {
       xsensmti3_parser( &current_parser_buf[ 0 ], start_rsp, &parse_data_obj );

       log_printf( &logger, ">> Quaternion data <<\r\n" );

       for ( cnt = 0; cnt < 4; cnt++ )
       {
           log_printf( &logger, ">> Q: %f\r\n", parse_data_obj.quat_obj.quat_data[ cnt ] );
       }

       log_printf( &logger, "--------------\r\n" );

       xsensmti3_get_data( &parse_data_obj.quat_obj, &data_obj );

       log_printf( &logger, ">> ROLL:  %.4f \r\n", data_obj.roll );
       log_printf( &logger, ">> PITCH: %.4f \r\n", data_obj.pitch );
       log_printf( &logger, ">> YAW:   %.4f \r\n", data_obj.yaw );

       active_flag = XSENSMTI3_WAIT_FOR_START;

       log_printf( &logger, "--------------\r\n" );
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

static void xsensmti3_process ( void ) 
{
    int32_t rsp_size;
    
    uint8_t uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    
    rsp_size = xsensmti3_generic_read( &xsensmti3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
    
    if ( rsp_size > 0 )
    {  
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
        
        memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    } 
    else 
    {
        Delay_ms( 100 );
    }
}

// ------------------------------------------------------------------------ END
