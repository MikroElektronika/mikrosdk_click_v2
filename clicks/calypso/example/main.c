/*!
 * @file main.c
 * @brief Calypso Click Example.
 *
 * # Description
 * This example demonstrates the use of Calypso click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and places AT command mode, tests the communication, 
 * and after that restarts the device, and performs example configuration.
 *
 * ## Application Task
 * It creates a connection to the TCP-UDP echo server, sends a message to it reads it back, 
 * displaces it on the UART terminal, and then closes the connection.
 *
 * ## Additional Function
 * - static void calypso_clear_app_buf ( void )
 * - static void calypso_log_app_buf ( void )
 * - static err_t calypso_process ( void )
 * - static err_t calypso_rsp_check ( uint8_t *rsp )
 * - static void calypso_error_check ( err_t error_flag )
 * - static void calypso_configure_for_example ( void )
 * - static void calypso_example ( void )
 *
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "calypso.h"
#include "conversions.h"

// Message content
#define MESSAGE_CONTENT                     "Calypso click board - demo example."

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// WiFi parameters
#define WIFI_SSID                           "MikroE Public"
#define WIFI_PWD                            "mikroe.guest"

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

static calypso_t calypso;
static log_t logger;
static err_t error_flag;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Calypso clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void calypso_clear_app_buf ( void );

/**
 * @brief Calypso log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void calypso_log_app_buf ( void );

/**
 * @brief Calypso data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t calypso_process ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp : Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Error response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t calypso_rsp_check ( uint8_t *rsp );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag : Error flag to check.
 */
static void calypso_error_check ( err_t error_flag );

/**
 * @brief Calypso configure for example function.
 * @details This function is used to configure device for example.
 */
static void calypso_configure_for_example ( void );

/**
 * @brief Calypso execute example function.
 * @details This function executes TCP/UDP Example.
 */
static void calypso_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    calypso_cfg_t calypso_cfg;  /**< Click config object. */

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
    calypso_cfg_setup( &calypso_cfg );
    CALYPSO_MAP_MIKROBUS( calypso_cfg, MIKROBUS_1 );
    if ( UART_ERROR == calypso_init( &calypso, &calypso_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CALYPSO_ERROR == calypso_default_cfg ( &calypso ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    calypso_configure_for_example( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    calypso_example( );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void calypso_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void calypso_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t calypso_process ( void ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = calypso_generic_read( &calypso, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            memmove ( app_buf, &app_buf[ overflow_bytes ], app_buf_len );
            memset ( &app_buf[ app_buf_len ], 0, overflow_bytes );
        }
        for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return CALYPSO_OK;
    }
    return CALYPSO_ERROR;
}

static err_t calypso_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    calypso_clear_app_buf( );
    calypso_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, CALYPSO_RSP_ERROR ) ) )
    {
        calypso_process( );
        if ( timeout_cnt++ > timeout )
        {
            calypso_clear_app_buf( );
            return CALYPSO_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    calypso_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return CALYPSO_OK;
    }
    else if ( strstr( app_buf, CALYPSO_RSP_ERROR ) )
    {
        return CALYPSO_ERROR_CMD;
    }
    else
    {
        return CALYPSO_ERROR_UNKNOWN;
    }
}

static void calypso_error_check ( err_t error_flag )
{    
    switch ( error_flag )
    {
        case CALYPSO_OK:
        {
            calypso_log_app_buf( );
            break;
        }
        case CALYPSO_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case CALYPSO_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case CALYPSO_ERROR_CMD:
        {
            log_error( &logger, " ERROR Response!" );
            break;
        }
        case CALYPSO_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 500 );
}

static void calypso_configure_for_example ( void )
{
    uint8_t command_data[ APP_BUFFER_SIZE ] = { 0 };

    log_printf( &logger, " Hardware reset. \r\n" );
    calypso_hw_reset( &calypso );
    error_flag = calypso_rsp_check( CALYPSO_RSP_READY );
    calypso_error_check( error_flag );

    log_printf( &logger, " Performing Test. \r\n" );
    calypso_send_cmd( &calypso, CALYPSO_CMD_AT_TEST );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );

    log_printf( &logger, " Setting WLAN Mode. \r\n" );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_WLAN_SET_MODE, "STA" );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );

    #define SECURITY_TYPE           "WPA_WPA2" 
    strcpy( command_data, WIFI_SSID );
    strcat( command_data, ",," );
    strcat( command_data, SECURITY_TYPE );
    strcat( command_data, "," );
    strcat( command_data, WIFI_PWD );
    strcat( command_data, ",,," );

    log_printf( &logger, " WLAN Connect. \r\n" );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_WLAN_CONNECT, command_data );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );
    error_flag = calypso_rsp_check( CALYPSO_RSP_CONNECTED );
    calypso_error_check( error_flag );
}

static void calypso_example ( void )
{
    uint8_t command_data[ APP_BUFFER_SIZE ] = { 0 };
    uint8_t socket_num[ 4 ] = { 0 };
    uint8_t * __generic_ptr socket_num_buf = 0;
    #define SOCKET_OPEN             "+socket:"
    #define SOCKET_CONNECTED        "+connect:"
    #define SOCKET_FAMILY           "INET"
    #define SOCKET_TYPE             "STREAM"
    #define SOCKET_PROTOCOL_TCP     "TCP"
    #define SOCKET_PROTOCOL_UDP     "UDP"
    #define SOCKET_FORMAT_BINATY    "0"
    
    log_printf( &logger, " Create TCP socket. \r\n" );
    strcpy( command_data, SOCKET_FAMILY );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_TYPE );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_PROTOCOL_TCP );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_SOCKET, command_data );
    error_flag = calypso_rsp_check( SOCKET_OPEN );
    calypso_error_check( error_flag );

    socket_num_buf = strstr( app_buf, SOCKET_OPEN ) + strlen ( SOCKET_OPEN );
    if ( socket_num_buf )
    {
        memcpy ( socket_num, socket_num_buf, 2 );
        if ( socket_num[ 1 ] < '0' || socket_num[ 1 ] > '9' )
        {
            socket_num[ 1 ] = 0;
        }
    }
    
    log_printf( &logger, " Connect to the TCP server. \r\n" );
    strcpy( command_data, socket_num );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_FAMILY );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_PORT );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_IP );

    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_CONNECT, command_data );
    error_flag = calypso_rsp_check( SOCKET_CONNECTED );
    calypso_error_check( error_flag );
    
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, " Send data to the TCP server. \r\n" );
    strcpy( command_data, socket_num );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_FORMAT_BINATY );
    strcat( command_data, "," );
    strcat( command_data, message_len_buf );
    strcat( command_data, "," );
    strcat( command_data, MESSAGE_CONTENT );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_SEND, command_data );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );

    log_printf( &logger, " Read data from the TCP server. \r\n" );
    strcpy( command_data, socket_num );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_FORMAT_BINATY );
    strcat( command_data, "," );
    strcat( command_data, message_len_buf );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_RECV, command_data );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );
    
    log_printf( &logger, " Closing the TCP connection. \r\n" );
    strcpy( command_data, socket_num );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_CLOSE, command_data );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );

    log_printf( &logger, " Create UDP socket. \r\n" );
    strcpy( command_data, SOCKET_FAMILY );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_TYPE );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_PROTOCOL_UDP );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_SOCKET, command_data );
    error_flag = calypso_rsp_check( SOCKET_OPEN );
    calypso_error_check( error_flag );

    socket_num_buf = strstr( app_buf, SOCKET_OPEN ) + strlen ( SOCKET_OPEN );
    if ( socket_num_buf )
    {
        memcpy ( socket_num, socket_num_buf, 2 );
        if ( socket_num[ 1 ] < '0' || socket_num[ 1 ] > '9' )
        {
            socket_num[ 1 ] = 0;
        }
    }
    
    log_printf( &logger, " Connect to the UDP server. \r\n" );
    strcpy( command_data, socket_num );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_FAMILY );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_PORT );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_IP );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_CONNECT, command_data );
    error_flag = calypso_rsp_check( SOCKET_CONNECTED );
    calypso_error_check( error_flag );
    
    log_printf( &logger, " Send data to the UDP server. \r\n" );
    strcpy( command_data, socket_num );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_FORMAT_BINATY );
    strcat( command_data, "," );
    strcat( command_data, message_len_buf );
    strcat( command_data, "," );
    strcat( command_data, MESSAGE_CONTENT );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_SEND, command_data );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );

    log_printf( &logger, " Read data from the UDP server. \r\n" );
    strcpy( command_data, socket_num );
    strcat( command_data, "," );
    strcat( command_data, SOCKET_FORMAT_BINATY );
    strcat( command_data, "," );
    strcat( command_data, message_len_buf );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_RECV, command_data );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );
    
    log_printf( &logger, " Closing the UDP connection. \r\n" );
    strcpy( command_data, socket_num );
    calypso_send_cmd_with_par( &calypso, CALYPSO_CMD_AT_CLOSE, command_data );
    error_flag = calypso_rsp_check( CALYPSO_RSP_OK );
    calypso_error_check( error_flag );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

// ------------------------------------------------------------------------ END
