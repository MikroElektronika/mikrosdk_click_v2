/*!
 * \file 
 * \brief WiFi 9 Click example
 * 
 * # Description
 * This application showcases capability of the WiFi 9 Click board. 
 * It initializes device, connects to local WiFi. Creates TCP server, waits for connection, 
 * and logs every message it receives from clients and returns back those messages as an echo response.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wifi communication, then connects to the desired WiFi network
 * and creates TCP server on the IP address assigned to the click board.
 * 
 * ## Application Task  
 * All data received from the TCP clients will be logger to USB UART and echoed back to the clients.
 * 
 * ## Additional Function
 * - static void wifi9_clear_app_buf ( void )
 * - static err_t wifi9_process ( void )
 * - static void wifi9_log_app_buf ( void )
 * - static err_t wifi9_rsp_check ( uint8_t *rsp )
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wifi9.h"
#include "string.h"

// Example parameters
#define EXAMPLE_SSID                        "MikroE Public"
#define EXAMPLE_PASSWORD                    "mikroe.guest"
#define EXAMPLE_SERVER_PORT                 "1234"

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256
// ------------------------------------------------------------------ VARIABLES

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static wifi9_t wifi9;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application
 * buffer and reset its length.
 */
static void wifi9_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and
 * appends it to the application buffer.
 * @return @li @c  0 - Some data is read.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 */
static err_t wifi9_process ( void );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void wifi9_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Unknown error.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 */
static err_t wifi9_rsp_check ( uint8_t *rsp );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi9_cfg_t cfg;

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
    wifi9_cfg_setup( &cfg );
    WIFI9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi9_init( &wifi9, &cfg );

    wifi9_reset_device( &wifi9 );
    wifi9_select_uart( &wifi9, WIFI9_SELECT_CMD_UART );
    Delay_ms( 4000 );

    wifi9_process( );
    wifi9_clear_app_buf( );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "---- System Info ----\r\n" );
    log_printf( &logger, "---------------------\r\n" );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_FIRMWARE );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_FIRMWARE );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_MAC_ADDR );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_MAC_ADDR );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_SERIAL_NUM );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_SERIAL_NUM );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_RADIO_VER );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_RADIO_VER );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_BOOTL_VER );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_BOOTL_VER );
    wifi9_log_app_buf( );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_HW_REV );
    wifi9_rsp_check( WIFI9_CMD_GET_SYSTEM_HW_REV );
    wifi9_log_app_buf( );
    Delay_ms( 3000 );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "---- Start NETCAT app ----\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "\r\nSet Station to ON status: " );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_WLAN_STATE_STA_ON );
    wifi9_rsp_check( WIFI9_CMD_SET_WLAN_STATE );
    wifi9_log_app_buf( );
    Delay_ms( 3000 );

    log_printf( &logger, "\r\nSet Station SSID and PASSWORD: " );
    strcpy( app_buf, WIFI9_CMD_SET_WLAN_CFG_STA );
    strcat( app_buf, " \"" );
    strcat( app_buf, EXAMPLE_SSID );
    strcat( app_buf, "\" \"" );
    strcat( app_buf, EXAMPLE_PASSWORD );
    strcat( app_buf, "\" 4" );
    wifi9_send_command( &wifi9, app_buf );
    wifi9_rsp_check( WIFI9_CMD_SET_WLAN_CFG );
    wifi9_log_app_buf( );
    Delay_ms( 500 );
    
    log_printf( &logger, "\r\nTurn ON - Netcat module: " );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_STATE_ON );
    wifi9_rsp_check( WIFI9_CMD_SET_NETCAT_STATE );
    wifi9_log_app_buf( );
    Delay_ms( 500 );
    
    log_printf( &logger, "\r\nExclude Netcat authentication: " );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_AUTH_OFF );
    wifi9_rsp_check( WIFI9_CMD_SET_NETCAT_AUTH );
    wifi9_log_app_buf( );
    Delay_ms( 500 );
    
    log_printf( &logger, "\r\nSet the Netcat module server port: " );
    strcpy( app_buf, WIFI9_CMD_SET_NETCAT_CFG_SERVER );
    strcat( app_buf, " " );
    strcat( app_buf, EXAMPLE_SERVER_PORT );
    wifi9_send_command( &wifi9, app_buf );
    wifi9_rsp_check( WIFI9_CMD_SET_NETCAT_CFG );
    wifi9_log_app_buf( );
    Delay_ms( 3000 );
    
    log_printf( &logger, "\r\nWaiting for an IP address assignment from DHCP server...\r\n" );
    for ( ; ; )
    {
        log_printf( &logger, "\r\nGet IP address: " );
        wifi9_send_command( &wifi9, WIFI9_CMD_GET_NET_CFG_STA );
        wifi9_rsp_check( WIFI9_CMD_GET_NET_CFG );
        wifi9_log_app_buf( );
        if ( !strstr ( app_buf, "0.0.0.0" ) )
        {
            break;
        }
        Delay_ms( 5000 );
    }
    wifi9_clear_app_buf( );
    Delay_ms( 1000 );
    
    log_printf( &logger, "\r\nNow you can connect to the TCP server listed above via a TCP client app\r\n" );  
    log_printf( &logger, "The module is transferred to BIN-UART - for data collection\r\n" );

    wifi9_select_uart( &wifi9, WIFI9_SELECT_BIN_UART );
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    wifi9_process( );
    if ( app_buf_len )
    {
        wifi9_log_app_buf( );
        wifi9_generic_write( &wifi9, app_buf, app_buf_len );
        wifi9_clear_app_buf( );
        Delay_ms ( 100 );
    }
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

static void wifi9_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t wifi9_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = wifi9_generic_read( &wifi9, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = APP_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - APP_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ APP_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < APP_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return WIFI9_OK;
    }
    return WIFI9_ERROR;
}

static void wifi9_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t wifi9_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 60000;
    wifi9_clear_app_buf( );
    wifi9_process( );
    while ( 0 == strstr( app_buf, rsp ) )
    {
        wifi9_process( );
        if ( timeout_cnt++ > timeout )
        {
            wifi9_clear_app_buf( );
            return WIFI9_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 100 );
    wifi9_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return WIFI9_OK;
    }
    return WIFI9_ERROR;
}

// ------------------------------------------------------------------------ END
