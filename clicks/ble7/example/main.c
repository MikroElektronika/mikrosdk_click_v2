/*!
 * \file 
 * \brief Ble7 Click example
 * 
 * # Description
 * This example reads and processes data from BLE 7 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board.
 * 
 * ## Application Task  
 * Checks for the received data, reads it and replies with a certain message.
 * 
 * ## Additional Function
 * - ble7_process ( ) - Logs all received messages on UART, and sends the certain message back 
 * to the connected device.
 * 
 * @note
 * We have used the BLE Scanner smartphone application for the test. 
 * A smartphone and the click board must be paired in order to exchange messages with each other.
 * For more information about the BGX module commands, please refer to the following link:
 * https://docs.silabs.com/gecko-os/1/bgx/latest/commands
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ble7.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 200

// ------------------------------------------------------------------ VARIABLES

#define BLE7_ENABLE_ECHO                        "set sy c e 1"
#define BLE7_CLEAR_BONDING                      "clrb"
#define BLE7_ENABLE_BONDING                     "set bl e b 1"
#define BLE7_ENABLE_PAIRING                     "set bl e p any"
#define BLE7_SET_ADVERTISING_ON                 "adv high"
#define BLE7_SET_ADVERTISING_HIGH_DURATION      "set bl v h d 120"
#define BLE7_SET_DEVICE_NAME                    "set sy d n \"BLE7-DEVICE\""
#define BLE7_SAVE_CONFIGURATION                 "save"
#define BLE7_SWITCH_TO_STREAM_MODE              "str"

static ble7_t ble7;
static log_t logger;
static uint8_t data_mode = 0;
static uint8_t config_mode = 0;
static char current_parser_buf[ PROCESS_RX_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static int8_t ble7_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    int8_t ret_flag = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear current buffer
    memset( current_parser_buf, 0, PROCESS_RX_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = ble7_generic_read( &ble7, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            // Storages data in current buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_RX_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
            
            if ( strstr( current_parser_buf, "Command failed" ) ) 
            {
                ret_flag = 0;
                return ret_flag;
            }
            
            if ( strstr( current_parser_buf, "Success" ) ) 
            {
                ret_flag = 1;
            }
            
            if ( strstr( current_parser_buf, "STREAM_MODE" ) ) 
            {
                data_mode = 1;
                ret_flag = 1;
            }
            
            if ( strstr( current_parser_buf, "COMMAND_MODE" ) ) 
            {
                data_mode = 0;
                ret_flag = 1;
            }
            
            if ( ret_flag == 1 )
            {
                log_printf( &logger, "%s", current_parser_buf );
                return ret_flag;
            }
            
            if ( config_mode == 0 )
            {   
                log_printf( &logger, "%s", current_parser_buf );
                if ( data_mode == 0 ) 
                {
                    ble7_send_command( &ble7, "send Hello" );
                    Delay_ms( 2000 );
                    ble7_send_command( &ble7, "send MikroE" );
                }
                else
                {
                    ble7_send_command( &ble7, "Hello" );
                    Delay_ms( 2000 );
                    ble7_send_command( &ble7, "MikroE" );
                }
            }
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
    
    ret_flag = 0;
    return ret_flag;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble7_cfg_setup( &cfg );
    BLE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble7_init( &ble7, &cfg );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\r\n" );
    Delay_1sec( );
    config_mode = 1;
    
    do 
    {
        ble7_reset( &ble7 );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_CLEAR_BONDING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_ECHO );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_PAIRING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_ENABLE_BONDING );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_DEVICE_NAME );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_ADVERTISING_ON );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SET_ADVERTISING_HIGH_DURATION );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SAVE_CONFIGURATION );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    do 
    {
        ble7_send_command( &ble7, BLE7_SWITCH_TO_STREAM_MODE );
        Delay_1sec( );
    }
    while( ble7_process(  ) != 1 );
    
    config_mode = 0;
    log_printf( &logger, "The module has been configured.\r\n" );
    Delay_1sec( );
}

void application_task ( void )
{
    ble7_process(  );
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
