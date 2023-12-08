/*!
 * \file 
 * \brief BtEz Click example
 * 
 * # Description
 * This example reads and processes data from BT-EZ clicks.
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
 * - btez_process ( ) - Logs all received messages on UART, and sends the certain
 * message back to the connected device.
 * 
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the click board must be paired in order to exchange messages
 * with each other.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "btez.h"
#include "string.h"

#define PROCESS_COUNTER 100
#define PROCESS_RX_BUFFER_SIZE 200

#define CMD_PING           "/PING"
#define CMD_DEVICE_NAME    "SDN,N=BT-EZ_Click"
#define CMD_SAVE           "SDA$,A=0080"
#define CMD_GDN            "GDN"
#define SEND_DATA          "MikroE // BT-EZ click\r\n"

// ------------------------------------------------------------------ VARIABLES

static btez_t btez;
static log_t logger;
static uint8_t config_mode = 0;
static char current_parser_buf[ PROCESS_RX_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void btez_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    uint8_t ret_flag = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear current buffer
    memset( current_parser_buf, 0, PROCESS_RX_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = btez_generic_read( &btez, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            if ( strchr ( uart_rx_buffer, '@' ) )
            {
                ret_flag = 1;
                process_cnt = 3;
            }
            else if ( config_mode == 0 )
            {
                btez_send_command( &btez, SEND_DATA );
                ret_flag = 2;
                process_cnt = 3;
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
    
    if ( ret_flag != 0 )
    {
        log_printf( &logger, "%s", current_parser_buf );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    btez_cfg_t cfg;

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

    btez_cfg_setup( &cfg );
    BTEZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btez_init( &btez, &cfg );
    Delay_ms( 100 );

    log_printf( &logger, "Configuring the module...\r\n" );
    config_mode = 1;
    
    btez_module_reset( &btez );
    btez_process( );
    btez_send_command( &btez, CMD_PING );
    btez_process( );
    btez_send_command( &btez, CMD_DEVICE_NAME );
    btez_process( );
    btez_send_command( &btez, CMD_SAVE );
    btez_process( );
    btez_send_command( &btez, CMD_GDN );
    btez_process( );
    
    config_mode = 0;
    log_printf( &logger, "The module has been configured.\r\n" );
    Delay_1sec( );
}

void application_task ( void )
{
    btez_process( );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
