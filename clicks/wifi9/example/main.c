/*!
 * \file 
 * \brief Wifi9 Click example
 * 
 * # Description
 * This example reads and processes data from Wifi 9 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data
 * 
 * ## Additional Function
 * - wifi9_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifi9.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static wifi9_t wifi9;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void wifi9_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = wifi9_generic_read( &wifi9, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            log_printf( &logger, "%s", uart_rx_buffer );
            
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
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi9_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi9_cfg_setup( &cfg );
    WIFI9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi9_init( &wifi9, &cfg );

    wifi9_module_power( &wifi9 );
    wifi9_select_uart( &wifi9, WIFI9_SELECT_CMD_UART );

    Delay_ms( 4000 );

    wifi9_process(  );

    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "---- System Info ----\r\n" );
    log_printf( &logger, "---------------------\r\n" );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_FIRMWARE );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_MAC_ADDR );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_SERIAL_NUM );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_RADIO_VER );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_BOOTL_VER );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_HW_REV );
    
    Delay_ms( 5000 );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "---- Start NETCAT app ----\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "> Reads the current Station status\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_WLAN_STATE_STA );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Set Station to ON status\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_WLAN_STATE_STA_ON );
    Delay_ms( 2000 );

    log_printf( &logger, "> Sets Station SSID and PASSWORD\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_WLAN_CFG_STA );
    Delay_ms( 4000 );
    
    log_printf( &logger, "> Turn OFF - Netcat module\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_STATE_OFF );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Turn ON - Netcat module\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_STATE_ON );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Sets the Netcat module as a server with port 1234\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_CFG_SERVER );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Excludes Netcat authentication\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_AUTH_OFF );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Gets the current received IP address\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_NET_CFG_STA );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> At the moment, a netcat server at port 1234 has been built\r\n" );
    log_printf( &logger, "> The module is transferred to BIN-UART - for data collection\r\n" );

    wifi9_select_uart( &wifi9, WIFI9_SELECT_BIN_UART );
    log_printf( &logger, "test" );
    Delay_ms( 5000 );
}

void application_task ( void )
{
    wifi9_process(  );
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
