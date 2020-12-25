/*!
 * \file 
 * \brief LteIot Click example
 * 
 * # Description
 * This example reads and processes data from LTE IoT clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - lteiot_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lteiot.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_CURRENT_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static lteiot_t lteiot;
static log_t logger;

#define LTEIOT_AT        "AT"
#define LTEIOT_ATE1      "ATE1"
#define LTEIOT_AT_CMEE   "AT+CMEE=2"
#define LTEIOT_AT_CGATT  "AT+CGATT?"
#define LTEIOT_AT_CEREG  "AT+CEREG?"
#define LTEIOT_AT_COPS   "AT+COPS=0"
#define LTEIOT_AT_COPS_1 "AT+COPS?"
#define LTEIOT_AT_USOCR  "AT+USOCR=17"
#define LTEIOT_AT_USOST  "AT+USOST=0,\"195.34.89.241\",7,13,\"TestNumberOne\""
#define LTEIOT_AT_USORF  "AT+USORF=0,13"
#define LTEIOT_AT_USOCL  "AT+USOCL=0"

static char current_rx_buf[ PROCESS_CURRENT_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lteiot_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear current buffer
    memset( current_rx_buf, 0 , PROCESS_CURRENT_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = lteiot_generic_read( &lteiot, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            //log_printf( &logger, "%s", uart_rx_buffer );

            // Storages data in current buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_CURRENT_BUFFER_SIZE )
            {
                strncat( current_rx_buf, uart_rx_buffer, rsp_size );
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
    log_printf( &logger, "%s", current_rx_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lteiot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lteiot_cfg_setup( &cfg );
    LTEIOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lteiot_init( &lteiot, &cfg );

    lteiot_module_power( &lteiot, LTEIOT_MODULE_POWER_ON );

    // MODULE INIT
    
    lteiot_send_command( &lteiot, LTEIOT_AT );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_ATE1 );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_CMEE );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_CGATT );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_CEREG );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_COPS );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_COPS_1 );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USOCR );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USOST );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USORF );
    lteiot_process( );
    Delay_1sec( );
    lteiot_send_command( &lteiot, LTEIOT_AT_USOCL );
    lteiot_process( );
    Delay_1sec( );
}

void application_task ( void )
{
    lteiot_process( );
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
