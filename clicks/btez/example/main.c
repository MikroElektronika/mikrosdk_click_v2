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
 * Initializes driver and reset module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - btez_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "btez.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define CMD_PING           "/PING"
#define CMD_DEVICE_NAME    "SDN,N=BTEZ-MikroE"
#define CMD_SAVE           "SDA$,A=0080"
#define CMD_GDN            "GDN"
#define SEND_DATA          "MikroE // BT-EZ click\r\n"

// ------------------------------------------------------------------ VARIABLES

static btez_t btez;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void btez_process ( void )
{
    int16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = btez_generic_read( &btez, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
        log_printf( &logger, "%s \r\n", uart_rx_buffer );

        // Clear RX buffer
        memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    } 
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    btez_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    btez_cfg_setup( &cfg );
    BTEZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btez_init( &btez, &cfg );

    log_printf( &logger, ">> Initializes module << \r\n" );
    log_printf( &logger, ">> [ HARDWARE RESET ] << \r\n" );
    btez_module_reset( &btez );
    Delay_ms( 2000 );
    
    btez_send_command( &btez, CMD_PING );
    btez_process( );
    Delay_ms( 5000 );
    btez_send_command( &btez, CMD_DEVICE_NAME );
    btez_process( );
    Delay_ms( 5000 );
    btez_send_command( &btez, CMD_SAVE );
    btez_process( );
    Delay_ms( 5000 );
    btez_send_command( &btez, CMD_GDN );
    btez_process( );
    Delay_ms( 5000 );
}

void application_task ( void )
{
    btez_send_command( &btez, SEND_DATA );
    btez_process( );
    Delay_ms( 10000 );
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
