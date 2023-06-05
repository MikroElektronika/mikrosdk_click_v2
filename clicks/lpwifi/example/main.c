/*!
 * @file main.c
 * @brief LP WiFi Click Example.
 *
 * # Description
 * This example reads and processes data from LP WiFi clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and powers up the module, then connects to the desired AP
 * and creates TCP and UDP servers on the desired local port.
 *
 * ## Application Task
 * Logs all the data received from TCP/UDP clients on the USB UART.
 *
 * ## Additional Function
 * - static void lpwifi_clear_app_buf ( void )
 * - static err_t lpwifi_process ( void )
 * - static void lpwifi_error_check( err_t error_flag )
 * - static void lpwifi_log_app_buf ( void )
 * - static err_t lpwifi_rsp_check ( void )
 * - static void lpwifi_check_connection( void )
 *
 * @note
 * In order for the example to work, user needs to set the AP SSID, password, and Local port
 * on which the TCP server and UDP socket will be created.
 * Enter valid data for the following macros: AP_SSID, AP_PASSWORD and LOCAL_PORT.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lpwifi.h"
#include "string.h"
#include "generic_pointer.h"

// Set AP SSID
#define AP_SSID                     ""

// Set AP password - if the AP is OPEN remain this NULL
#define AP_PASSWORD                 ""

// Set Local port on which the TCP server and UDP socket will be created.
#define LOCAL_PORT                  1

#define APP_OK                      0
#define APP_ERROR_DRIVER            -1
#define APP_ERROR_OVERFLOW          -2
#define APP_ERROR_TIMEOUT           -3

#define RSP_OK                      "OK"
#define RSP_ERROR                   "ERROR"

#define PROCESS_BUFFER_SIZE         400

#define WAIT_FOR_CONNECTION         0
#define CONNECTED_TO_AP             1
#define NOT_CONNECTED_TO_AP         2

static lpwifi_t lpwifi;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len                 = 0;
static int32_t app_buf_cnt                 = 0;

static char assigned_ip_address[ 25 ]      = { 0 };
static uint8_t app_connection_status       = WAIT_FOR_CONNECTION;

static err_t app_error_flag;

/**
 * @brief LP WiFi clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void lpwifi_clear_app_buf ( void );

/**
 * @brief LP WiFi data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lpwifi_process ( void );

/**
 * @brief LP WiFi check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void lpwifi_error_check( err_t error_flag );

/**
 * @brief LP WiFi logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void lpwifi_log_app_buf ( void );

/**
 * @brief LP WiFi response check.
 * @details This function checks for response and returns the status of response.
 *
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lpwifi_rsp_check ( void );

/**
 * @brief LP WiFi check connection.
 * @details This function checks connection to the AP, and fills the assigned_ip_address buffer and
 *          logs the response on the USB UART if it is connected successfully.
 *
 * @note None.
 */
static void lpwifi_check_connection( void );

/**
 * @brief LP WiFi str cut chr function.
 * @details This function removes all selected characters from string str,
 * and returns it to the same str without those characters.
 * @param str Address of string.
 * @param chr Character to cut.
 */
static void lpwifi_str_cut_chr ( uint8_t *str, uint8_t chr );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lpwifi_cfg_t lpwifi_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );

    // Click initialization.

    lpwifi_cfg_setup( &lpwifi_cfg );
    LPWIFI_MAP_MIKROBUS( lpwifi_cfg, MIKROBUS_1 );
    err_t init_flag = lpwifi_init( &lpwifi, &lpwifi_cfg );
    if ( UART_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    lpwifi_default_cfg( &lpwifi );
    Delay_ms( 500 );

    // Initiate the communication
    lpwifi_send_cmd( &lpwifi, LPWIFI_CMD_AT );
    Delay_ms( 1000 );

    // Dummy read
    lpwifi_process( );
    lpwifi_clear_app_buf( );

    log_printf( &logger, "\r\n --- Factory reset --- \r\n" );
    lpwifi_factory_reset_device ( &lpwifi );
    Delay_ms( 500 );
    // Enable Echo
    lpwifi_send_cmd( &lpwifi, LPWIFI_CMD_ATE );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    Delay_ms( 500 );
    log_printf( &logger, " ----------------------------------------------- \r\n" );

    log_printf( &logger, "\r\n --- Connecting to the access point --- \r\n" );
    // Connect to AP
    lpwifi_connect_to_ap( &lpwifi, AP_SSID, AP_PASSWORD );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    lpwifi_check_connection();
    while ( CONNECTED_TO_AP != app_connection_status )
    {
        lpwifi_check_connection();
        if ( NOT_CONNECTED_TO_AP == app_connection_status )
        {
            Delay_ms( 500 );
            app_connection_status = WAIT_FOR_CONNECTION;

            // Connect to AP
            lpwifi_connect_to_ap( &lpwifi, AP_SSID, AP_PASSWORD );
            app_error_flag = lpwifi_rsp_check( );
            lpwifi_error_check( app_error_flag );
        }
    }
    log_printf( &logger, " ----------------------------------------------- \r\n" );
    log_printf( &logger, "\r\n --- Creating a TCP server --- \r\n" );
    // Create TCP Server
    lpwifi_create_tcp_server( &lpwifi, LOCAL_PORT );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    Delay_ms( 500 );

    log_printf( &logger, " ----------------------------------------------- \r\n" );
    log_printf( &logger, "\r\n --- Creating a UDP socket --- \r\n" );
    // Create UDP socket
    lpwifi_create_udp_socket( &lpwifi, LOCAL_PORT );
    app_error_flag = lpwifi_rsp_check( );
    lpwifi_error_check( app_error_flag );
    Delay_ms( 500 );

    log_printf( &logger, " ----------------------------------------------- \r\n" );
    log_printf( &logger, " TCP server and UDP socket are available at: \r\n" );
    log_printf( &logger, "    SSID: \"%s\"\r\n    IP: %s\r\n    Port: %u", ( char * ) AP_SSID,
                                                                           ( char * ) assigned_ip_address,
                                                                         ( uint16_t ) LOCAL_PORT );
    log_printf( &logger, "\r\n ----------------------------------------------- \r\n" );
    log_printf( &logger, " You can connect to it via a TCP/UDP client." );
    log_printf( &logger, "\r\n ----------------------------------------------- \r\n" );
}

void application_task ( void )
{
    lpwifi_process( );
    lpwifi_log_app_buf( );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void lpwifi_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t lpwifi_process ( void )
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = lpwifi_generic_read( &lpwifi, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            lpwifi_clear_app_buf(  );
            return LPWIFI_ERROR;
        }
        else
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ )
        {
            if ( rx_buff[ rx_cnt ] != 0 )
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }

        }
        return LPWIFI_OK;
    }
    return LPWIFI_ERROR;
}

static err_t lpwifi_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;

    err_t error_flag = lpwifi_process(  );

    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }

    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = lpwifi_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }

        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            // Initialize AT command
            while ( ( 0 == strstr( app_buf, RSP_OK ) ) && ( 0 == strstr( app_buf, RSP_ERROR ) ) )
            {
                lpwifi_send_cmd( &lpwifi, LPWIFI_CMD_ATZ );
                lpwifi_process(  );
                Delay_ms( 100 );
            }
            lpwifi_clear_app_buf(  );
            // Enable Echo
            while ( ( 0 == strstr( app_buf, RSP_OK ) ) && ( 0 == strstr( app_buf, RSP_ERROR ) ) )
            {
                lpwifi_send_cmd( &lpwifi, LPWIFI_CMD_ATE );
                lpwifi_process(  );
                Delay_ms( 100 );
            }
            lpwifi_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }

        Delay_ms( 1 );
    }

    lpwifi_log_app_buf();

    return APP_OK;
}

static void lpwifi_error_check( err_t error_flag )
{
    if ( ( error_flag != APP_OK ) && ( error_flag != APP_ERROR_DRIVER ) )
    {
        switch ( error_flag )
        {
            case APP_ERROR_OVERFLOW:
                log_error( &logger, " Overflow!" );
                break;
            case APP_ERROR_TIMEOUT:
                log_error( &logger, " Timeout!" );
                break;
            default:
                break;
        }
    }
}

static void lpwifi_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }

    lpwifi_clear_app_buf(  );
}

static void lpwifi_check_connection( void )
{
    #define CONNECTED     "+WFJAP:1"
    #define NOT_CONNECTED "+WFJAP:0"

    lpwifi_process( );
    if ( 0 != strstr( app_buf, CONNECTED ) )
    {
        #define IP_DELIMITER "',"
        char * __generic_ptr app_buf_ptr;
        Delay_ms( 200 );
        lpwifi_process( );
        app_buf_ptr = strstr( app_buf, IP_DELIMITER );
        strcpy( assigned_ip_address, app_buf_ptr );
        lpwifi_str_cut_chr( assigned_ip_address, '\'' );
        lpwifi_str_cut_chr( assigned_ip_address, ',' );
        lpwifi_str_cut_chr( assigned_ip_address, '\r' );
        lpwifi_str_cut_chr( assigned_ip_address, '\n' );
        lpwifi_log_app_buf( );
        app_connection_status = CONNECTED_TO_AP;
    }
    else if ( 0 != strstr( app_buf, NOT_CONNECTED ) )
    {
        app_connection_status = NOT_CONNECTED_TO_AP;
    }
}

static void lpwifi_str_cut_chr ( uint8_t *str, uint8_t chr )
{
    uint16_t cnt_0, cnt_1;
    for ( cnt_0 = 0; cnt_0 < strlen( str ); cnt_0++ )
    {
        if ( str[ cnt_0 ] == chr )
        {
            for ( cnt_1 = cnt_0; cnt_1 < strlen( str ); cnt_1++ )
            {
                str[ cnt_1 ] = str[ cnt_1 + 1 ];
            }
        }
    }
}

// ------------------------------------------------------------------------ END
