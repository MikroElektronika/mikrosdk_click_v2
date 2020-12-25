/*!
 * \file 
 * \brief MBusRf4 Click example
 * 
 * # Description
 * This example reads and processes data from M-BUS RF 4 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, reads basic information and checks communication
 * 
 * ## Application Task  
 *  In the RX mode it is waiting to receive data from another module...
 *  In the TX mode sends the data packet....
 * 
 * ## Additional Function
 * - mbusrf4_process ( ) - The general process of collecting data and adding it to application buffer;
 * 
 * - mbrusrf4_clear_buff ( void ) - Clear application buffer data;
 * 
 * - mbusrf4_parser_tx ( void ) - Transmit data status parser;
 * 
 * - mbusrf4_parser_rx ( uint8_t logg_type ) - Receiver data parser;
 * 
 * - mbusrf4_log_data ( uint8_t log_type, uint8_t *log_buf, int32_t log_len ) - Log application buffer;
 * 
 * ## Note: You can't send less then 10 data byte!
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mbusrf4.h"
#include "string.h"
#include "generic_pointer.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 256
#define PROCESS_PARSER_BUFFER_SIZE 256

#define LOG_HEX 0 
#define LOG_STR 1
#define LOG_DEC 2

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITER

static mbusrf4_t mbusrf4;
static log_t logger;

static char parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static int32_t parser_cnt = 0;

static uint8_t * __generic parser_ptr;

uint8_t msg[ ] = "MikroE -  FW team";

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


static void mbrusrf4_clear_buff ( void );

static void mbusrf4_parser_tx ( void );

static void mbusrf4_parser_rx ( uint8_t logg_type );

static void mbusrf4_process ( void );

static void mbusrf4_log_data ( uint8_t log_type, uint8_t *log_buf, int32_t log_len );


static void mbusrf4_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt; 
    uint8_t process_cnt = PROCESS_COUNTER;
    
    
    rsp_size = mbusrf4_generic_read( &mbusrf4, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        if ( parser_cnt + rsp_size >= PROCESS_PARSER_BUFFER_SIZE )
        {
            log_info( &logger, "Buffer Overflow!" );
            mbrusrf4_clear_buff(  );
        }
        else
        {
            for( int32_t rsp_cnt = 0; rsp_cnt < rsp_size; rsp_cnt++ )
            {
                parser_buf[ parser_cnt ] = uart_rx_buffer[ rsp_cnt ];
                parser_cnt++;
                if ( parser_cnt >= parser_cnt + rsp_size )
                    break;
            }
        }
    } 
}

static void mbusrf4_parser_rx ( uint8_t logg_type )
{
    const int32_t RSP_LEN = 2;
    const int32_t TIMEOUT_EXIT = 10000;
    uint8_t * __generic rsp_start;
    uint8_t full_rsp = 0;
    int32_t timeout_cnt = 0;
    int32_t rsp_len = 0;
    int32_t rsp_start_index = 0;
    
    for ( ; ; )
    {
        rsp_start = strchr( parser_ptr, MBUSRF4_HEADER );
        if (rsp_start != 0)
            break;
        else 
            mbusrf4_process();
        
        timeout_cnt++;
        Delay_ms( 1 );
        if ( timeout_cnt >= TIMEOUT_EXIT )
        {
            log_error( &logger, "TIMEOUT!( Header not found )" );
            mbrusrf4_clear_buff();
            return;
        }
    }
    
    timeout_cnt = 0;
    
    for ( ; ; )
    {
        for ( int32_t cnt = 0; cnt < parser_cnt; cnt++ )
        {
            if ( rsp_start == ( parser_ptr + cnt ) )
            {
                if ( cnt + RSP_LEN <= parser_cnt )
                {
                    rsp_start_index = cnt;
                    full_rsp = 1;
                }
                else
                    full_rsp = 0;
            }
        }  
        
        if ( full_rsp == 1 )
            break;
        else
            mbusrf4_process();
        
        timeout_cnt++;
        Delay_ms( 1 );
        if ( timeout_cnt >= TIMEOUT_EXIT )
        {
            log_error( &logger, "TIMEOUT! ( Response length not found )" );
            return;
        }
    }
    
    timeout_cnt = 0;
    
    rsp_len = ( int32_t )parser_buf[ rsp_start_index + 2 ];
    
    if ( rsp_len <= 0 )
    {
        mbrusrf4_clear_buff();
        return;
    }
    
    for ( ; ; )
    {
        if ( ( rsp_start_index + RSP_LEN + rsp_len + 1 ) <= parser_cnt )
            full_rsp = 1;
        else
            full_rsp = 0;
        
        if ( full_rsp == 1 )
            break;
        else
            mbusrf4_process();
        
        timeout_cnt++;
        Delay_ms( 1 );
        if ( timeout_cnt >= TIMEOUT_EXIT )
        {
            log_error( &logger, "TIMEOUT! ( Response not found )" );
            return;
        }
    }
    
    rsp_start_index += 3;
    mbusrf4_log_data( logg_type, &parser_buf[ rsp_start_index ], rsp_len );
    mbrusrf4_clear_buff();
}

static void mbusrf4_parser_tx ( void )
{
    const int32_t RSP_LEN = 4;
    const int32_t STATUS_DIFF = 3;
    const int32_t TIMEOUT_EXIT = 5000;
    
    uint8_t * __generic rsp_start;
    uint8_t full_rsp = 0;
    int32_t timeout_cnt = 0;
    
    for ( ; ; )
    {
        rsp_start = strchr( parser_ptr, MBUSRF4_HEADER );
        if ( rsp_start != 0 )
            break;
        else 
            mbusrf4_process();
        
        timeout_cnt++;
        Delay_ms( 1 );
        if ( timeout_cnt >= TIMEOUT_EXIT )
        {
            log_error( &logger, "TIMEOUT!( Header not found )" );
            return;
        }
    }
    
    timeout_cnt = 0;
    
    for ( ; ; )
    {
        for ( int32_t cnt = 0; cnt < parser_cnt; cnt++ )
        {
            if ( rsp_start == ( parser_ptr + cnt ) )
            {
                if ( cnt + RSP_LEN <= parser_cnt )
                {
                    full_rsp = 1;
                }
                else
                {
                    full_rsp = 0;
                }
            }
        }  
        
        if ( full_rsp == 1 )
            break;
        else
            mbusrf4_process();
        
        timeout_cnt++;
        Delay_ms( 1 );
        if ( timeout_cnt >= TIMEOUT_EXIT )
        {
            log_error( &logger, "TIMEOUT! ( Response not found )" );
            return;
        }
    }
    
    rsp_start += STATUS_DIFF;
    
    if ( *rsp_start == 0x00 )
        log_info( &logger, "TX OK" );
    else if ( *rsp_start == 0xFF )
        log_info( &logger, "TX ERROR" );
    else
        log_error( &logger, "TX PARSER ERROR" );
}

static void mbrusrf4_clear_buff ( void )
{
    memset( parser_buf, 0, parser_cnt );
    parser_cnt = 0;
}

static void mbusrf4_log_data ( uint8_t log_type, uint8_t *log_buf, int32_t log_len )
{
    if ( LOG_HEX == log_type )
    { 
        for ( int32_t data_cnt = 0; data_cnt < log_len; data_cnt++ )
        {
            log_printf( &logger, "[ 0x%.02X ]", ( int32_t )( *( log_buf + data_cnt ) ) );
        }   
    }
    else if( LOG_STR == log_type )
    {
        for ( int32_t data_cnt = 0; data_cnt < log_len; data_cnt++ )
        {
            log_printf( &logger, "%c", *( log_buf + data_cnt ) );
        } 
    }
    else if( LOG_DEC == log_type )
    {
        for ( int32_t data_cnt = 0; data_cnt < log_len; data_cnt++ )
        {
            log_printf( &logger, "%d", ( int32_t )( *( log_buf + data_cnt ) ) );
        }  
    }
    else
    {
        log_error( &logger, "Log type error!" );
    }
    log_printf( &logger, "\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusrf4_cfg_t cfg;

    uint8_t payload_buff[ 20 ] = { 0 };

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "Application Init" );

    //  Click initialization.

    mbusrf4_cfg_setup( &cfg );
    MBUSRF4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusrf4_init( &mbusrf4, &cfg );
    
    parser_cnt = 0;
    parser_ptr = &parser_buf[ 0 ];
    mbusrf4_process( );
    mbrusrf4_clear_buff();

    //Command SET mode
    payload_buff[ 0 ] = MBUSRF4_SET_VALUE_IN_EEPROM_MEMORY;
    payload_buff[ 1 ] = MBUSRF4_EEPARAM_WMBUS_MODE_S2_SHORT_PREAMBLE;

    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_SET_MODE, 2, &payload_buff[ 0 ] );
    Delay_ms( 500 );
    mbusrf4_process( );
    mbusrf4_parser_tx();
    mbrusrf4_clear_buff();
    
    // Reads FW version
    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_GET_FW_VERSION, 0, &payload_buff[ 0 ] );
    Delay_ms( 500 );
    mbusrf4_process( );
    log_info( &logger, "FW version:" );
    mbusrf4_parser_rx( LOG_HEX );
    log_printf( &logger, "-----------------------------------------------------------\r\n" );
    mbusrf4_process( );

    Delay_ms( 1000 );
    log_info( &logger, "Application Task" );
}

void application_task ( void )
{
    // RX App mode
    #ifdef DEMO_APP_RECEIVER

    if ( mbusrf4_get_state_ind( &mbusrf4 ) == 0 )
    {     
        Delay_ms( 100 );
        mbusrf4_process( );
        
        mbusrf4_parser_rx( LOG_STR );
    }
    
    #endif
    
    // TX App Mode
    #ifdef DEMO_APP_TRANSMITER
    
    mbusrf4_transmit_data( &mbusrf4, msg, 17 );
    Delay_ms( 100 );
    mbrusrf4_clear_buff();
    mbusrf4_parser_tx();
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
