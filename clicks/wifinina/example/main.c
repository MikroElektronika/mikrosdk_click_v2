/*!
 * @file main.c
 * @brief WiFi NINA Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to a WiFi network and
 * sending TCP/UDP messages to an echo server.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - WIFININA_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *
 *  - WIFININA_CONFIGURE_CONNECTION:
 * Configures connection to WiFi.
 *
 *  - WIFININA_WAIT_FOR_CONNECTION:
 * Checks the connection to WiFi access point.
 *
 *  - WIFININA_EXAMPLE:
 * Sends a TCP/UDP message to an echo server over a WiFi network.
 *
 * ## Additional Function
 * - static void wifinina_clear_app_buf ( void )
 * - static void wifinina_log_app_buf ( void )
 * - static err_t wifinina_process ( wifinina_t *ctx )
 * - static err_t wifinina_read_response ( wifinina_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t wifinina_power_up ( wifinina_t *ctx )
 * - static err_t wifinina_config_connection ( wifinina_t *ctx )
 * - static err_t wifinina_check_connection ( wifinina_t *ctx )
 * - static err_t wifinina_example ( wifinina_t *ctx )
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "wifinina.h"

#ifndef MIKROBUS_POSITION_WIFININA
    #define MIKROBUS_POSITION_WIFININA MIKROBUS_1
#endif

// Message content
#define MESSAGE_CONTENT         "WiFi NINA Click board - demo example."

// TCP/UDP example parameters
#define REMOTE_IP               "54.187.244.144"   // TCP/UDP echo server IP address
#define REMOTE_PORT             "51111"            // TCP/UDP echo server port

// WiFi parameters
#define WIFI_SSID               "MIKROE GUEST"
#define WIFI_PASSWORD           "!guest.mikroe!"

// Application buffer size
#define APP_BUFFER_SIZE         600
#define PROCESS_BUFFER_SIZE     200

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    WIFININA_POWER_UP = 1,
    WIFININA_CONFIGURE_CONNECTION,
    WIFININA_WAIT_FOR_CONNECTION,
    WIFININA_EXAMPLE

} wifinina_app_state_t;

static wifinina_t wifinina;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static wifinina_app_state_t app_state = WIFININA_POWER_UP;

/**
 * @brief WiFi NINA clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void wifinina_clear_app_buf ( void );

/**
 * @brief WiFi NINA log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void wifinina_log_app_buf ( void );

/**
 * @brief WiFi NINA data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifinina_process ( wifinina_t *ctx );

/**
 * @brief WiFi NINA read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifinina_read_response ( wifinina_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief WiFi NINA power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifinina_power_up ( wifinina_t *ctx );

/**
 * @brief WiFi NINA config connection function.
 * @details This function configures connection to WiFi.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifinina_config_connection ( wifinina_t *ctx );

/**
 * @brief WiFi NINA check connection function.
 * @details This function checks the connection to WiFi access point.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifinina_check_connection ( wifinina_t *ctx );

/**
 * @brief WiFi NINA example function.
 * @details This function performs a WiFi TCP/UDP terminal example.
 * @param[in] ctx : Click context object.
 * See #wifinina_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifinina_example ( wifinina_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifinina_cfg_t wifinina_cfg;  /**< Click config object. */

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
    wifinina_cfg_setup( &wifinina_cfg );
    WIFININA_MAP_MIKROBUS( wifinina_cfg, MIKROBUS_POSITION_WIFININA );
    if ( UART_ERROR == wifinina_init( &wifinina, &wifinina_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = WIFININA_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void )
{
    switch ( app_state )
    {
        case WIFININA_POWER_UP:
        {
            if ( WIFININA_OK == wifinina_power_up( &wifinina ) )
            {
                app_state = WIFININA_CONFIGURE_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIGURE CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case WIFININA_CONFIGURE_CONNECTION:
        {
            if ( WIFININA_OK == wifinina_config_connection( &wifinina ) )
            {
                app_state = WIFININA_WAIT_FOR_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case WIFININA_WAIT_FOR_CONNECTION:
        {
            if ( WIFININA_OK == wifinina_check_connection( &wifinina ) )
            {
                app_state = WIFININA_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WIFININA_EXAMPLE:
        {
            wifinina_example( &wifinina );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
            break;
        }
    }
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

static void wifinina_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void wifinina_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t wifinina_process ( wifinina_t *ctx )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = wifinina_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) )
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE )
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            for ( int32_t buf_cnt = 0; buf_cnt < overflow_bytes; buf_cnt++ )
            {
                log_printf( &logger, "%c", app_buf[ buf_cnt ] );
            }
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
        return WIFININA_OK;
    }
    return WIFININA_ERROR;
}

static err_t wifinina_read_response ( wifinina_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
{
    uint32_t timeout_cnt = 0;
    wifinina_clear_app_buf( );
    wifinina_process( ctx );

    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, WIFININA_RSP_ERROR ) ) )
    {
        wifinina_process( ctx );

        if ( timeout_cnt++ > max_rsp_time )
        {
            wifinina_log_app_buf();
            wifinina_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return WIFININA_ERROR_TIMEOUT;
        }

        Delay_ms ( 1 );
    }

    Delay_ms ( 200 );
    wifinina_process( ctx );

    if ( strstr( app_buf, rsp ) )
    {
        wifinina_log_app_buf( );
        log_printf( &logger, "--------------------------------\r\n" );
        return WIFININA_OK;
    }
    else if ( strstr( app_buf, WIFININA_RSP_ERROR ) )
    {
        log_error( &logger, " CMD!" );
        return WIFININA_ERROR_CMD;
    }
    else
    {
        log_error( &logger, " Unknown!" );
        return WIFININA_ERROR_UNKNOWN;
    }
}

static err_t wifinina_power_up ( wifinina_t *ctx )
{
    err_t error_flag = WIFININA_OK;

    log_printf( &logger, ">>> Perform device hardware reset.\r\n" );
    wifinina_hw_reset ( ctx );
    error_flag |= wifinina_read_response( ctx, WIFININA_URC_GREETING, WIFININA_MAX_BOOT_GREETING );

    log_printf( &logger, ">>> Check communication.\r\n" );
    wifinina_cmd_run( ctx, WIFININA_CMD_AT );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Reset to factory settings.\r\n" );
    wifinina_cmd_run( ctx, WIFININA_CMD_FACTORY_RESET );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_FACTORY_RESET );

    log_printf( &logger, ">>> Reboot device.\r\n" );
    wifinina_cmd_run( ctx, WIFININA_CMD_REBOOT_DEVICE );
    error_flag |= wifinina_read_response( ctx, WIFININA_URC_GREETING, WIFININA_MAX_REBOOT );

    log_printf( &logger, ">>> Get device model ID.\r\n" );
    wifinina_cmd_run( ctx, WIFININA_CMD_GET_MODEL_ID );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    wifinina_cmd_run( ctx, WIFININA_CMD_GET_SW_VERSION );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    wifinina_cmd_run( ctx, WIFININA_CMD_GET_SERIAL_NUM );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    return error_flag;
}

static err_t wifinina_config_connection ( wifinina_t *ctx )
{
    err_t error_flag = WIFININA_OK;

    log_printf( &logger, ">>> Get network host name.\r\n" );
    wifinina_cmd_get( ctx, WIFININA_CMD_NETWORK_HOST_NAME );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Set WiFi SSID.\r\n" );
    #define WIFI_CONFIG_ID                  "0"
    #define WIFI_PARAM_TAG_SSID             "2"
    wifinina_clear_app_buf( );
    strcpy ( app_buf, WIFI_CONFIG_ID );
    strcat ( app_buf, "," );
    strcat ( app_buf, WIFI_PARAM_TAG_SSID );
    strcat ( app_buf, ",\"" );
    strcat ( app_buf, WIFI_SSID );
    strcat ( app_buf, "\"" );
    wifinina_cmd_set( ctx, WIFININA_CMD_WIFI_STATION_CONFIG, app_buf );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Set WiFi authentication type to WPA/WPA2/WPA3.\r\n" );
    #define WIFI_PARAM_TAG_AUTH             "5"
    #define WIFI_PARAM_VAL1_WPA_WPA2_WPA3   "2"
    wifinina_clear_app_buf( );
    strcpy ( app_buf, WIFI_CONFIG_ID );
    strcat ( app_buf, "," );
    strcat ( app_buf, WIFI_PARAM_TAG_AUTH );
    strcat ( app_buf, "," );
    strcat ( app_buf, WIFI_PARAM_VAL1_WPA_WPA2_WPA3 );
    wifinina_cmd_set( ctx, WIFININA_CMD_WIFI_STATION_CONFIG, app_buf );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Set WiFi Password.\r\n" );
    #define WIFI_PARAM_TAG_PASSWORD         "8"
    wifinina_clear_app_buf( );
    strcpy ( app_buf, WIFI_CONFIG_ID );
    strcat ( app_buf, "," );
    strcat ( app_buf, WIFI_PARAM_TAG_PASSWORD );
    strcat ( app_buf, ",\"" );
    strcat ( app_buf, WIFI_PASSWORD );
    strcat ( app_buf, "\"" );
    wifinina_cmd_set( ctx, WIFININA_CMD_WIFI_STATION_CONFIG, app_buf );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Activate WiFi config and try to connect.\r\n" );
    #define WIFI_ACTION_ACTIVATE            "3"
    wifinina_clear_app_buf( );
    strcpy ( app_buf, WIFI_CONFIG_ID );
    strcat ( app_buf, "," );
    strcat ( app_buf, WIFI_ACTION_ACTIVATE );
    wifinina_cmd_set( ctx, WIFININA_CMD_WIFI_STATION_CONFIG_ACTION, app_buf );
    error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_WIFI_CONNECT );
    wifinina_clear_app_buf( );

    return error_flag;
}

static err_t wifinina_check_connection ( wifinina_t *ctx )
{
    err_t error_flag = WIFININA_OK;
    uint8_t * __generic_ptr urc_buf_ptr = 0;
    wifinina_process( ctx );

    // Wait for WiFi link connected and two network-up URC events
    urc_buf_ptr = strstr( app_buf, WIFININA_URC_WIFI_LINK_CONNECTED );

    if ( urc_buf_ptr )
    {
        urc_buf_ptr = strstr( urc_buf_ptr + 1, WIFININA_URC_NETWORK_UP );
    }

    if ( urc_buf_ptr )
    {
        if ( strstr( urc_buf_ptr + 1, WIFININA_URC_NETWORK_UP ) )
        {
            Delay_100ms( );
            wifinina_process( ctx );
            wifinina_log_app_buf( );
            wifinina_clear_app_buf( );

            // Check WiFi status
            wifinina_cmd_run( ctx, WIFININA_CMD_WIFI_STATION_STATUS );
            error_flag |= wifinina_read_response( ctx, WIFININA_RSP_OK, WIFININA_MAX_AT_DEFAULT );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
        else
        {
            error_flag |= WIFININA_ERROR;
        }
    }
    else
    {
        error_flag |= WIFININA_ERROR;
    }

    return error_flag;
}

static err_t wifinina_example ( wifinina_t *ctx )
{
    err_t error_flag = WIFININA_OK;
    uint8_t * __generic_ptr urc_buf_ptr = 0;
    uint8_t urc_buf[ 30 ] = { 0 };
    uint8_t tcp_peer_handle[ 2 ] = { 0 };
    uint8_t udp_peer_handle[ 2 ] = { 0 };

    log_printf( &logger, ">>> Create and connect TCP socket to remote IP and port.\r\n" );
    #define SCHEME_AT_TCP           "at-tcp"
    wifinina_clear_app_buf( );
    strcpy ( app_buf, SCHEME_AT_TCP );
    strcat ( app_buf, "://" );
    strcat ( app_buf, REMOTE_IP );
    strcat ( app_buf, ":" );
    strcat ( app_buf, REMOTE_PORT );
    wifinina_cmd_set( ctx, WIFININA_CMD_CONNECT_PEER, app_buf );
    error_flag = wifinina_read_response( ctx, WIFININA_URC_PEER_CONNECTED, WIFININA_MAX_PEER_CONNECT );
    if ( ( WIFININA_OK == error_flag ) && ( strstr( app_buf, WIFININA_URC_PEER_CONNECTED ) ) )
    {
        urc_buf_ptr = strstr( app_buf, WIFININA_URC_PEER_CONNECTED ) + strlen ( WIFININA_URC_PEER_CONNECTED );
        tcp_peer_handle[ 0 ] = *urc_buf_ptr;
    }

    log_printf( &logger, ">>> Create and connect UDP socket to remote IP and port.\r\n" );
    #define SCHEME_AT_UDP           "at-udp"
    wifinina_clear_app_buf( );
    strcpy ( app_buf, SCHEME_AT_UDP );
    strcat ( app_buf, "://" );
    strcat ( app_buf, REMOTE_IP );
    strcat ( app_buf, ":" );
    strcat ( app_buf, REMOTE_PORT );
    wifinina_cmd_set( ctx, WIFININA_CMD_CONNECT_PEER, app_buf );
    error_flag = wifinina_read_response( ctx, WIFININA_URC_PEER_CONNECTED, WIFININA_MAX_PEER_CONNECT );
    if ( ( WIFININA_OK == error_flag ) && ( strstr( app_buf, WIFININA_URC_PEER_CONNECTED ) ) )
    {
        urc_buf_ptr = strstr( app_buf, WIFININA_URC_PEER_CONNECTED ) + strlen ( WIFININA_URC_PEER_CONNECTED );
        udp_peer_handle[ 0 ] = *urc_buf_ptr;
    }

    if ( tcp_peer_handle[ 0 ] )
    {
        log_printf( &logger, ">>> Write message to TCP socket and read response.\r\n" );
        #define DATA_FORMAT_STRING      "0"
        #define DATA_FORMAT_BINARY      "2"
        wifinina_clear_app_buf( );
        strcpy ( app_buf, tcp_peer_handle );
        strcat ( app_buf, "," );
        strcat ( app_buf, DATA_FORMAT_STRING );
        strcat ( app_buf, "," );
        strcat ( app_buf, MESSAGE_CONTENT );
        wifinina_cmd_set( ctx, WIFININA_CMD_WRITE_DATA, app_buf );
        if ( WIFININA_OK == wifinina_read_response( ctx, WIFININA_URC_READ_SOCKET_DATA, WIFININA_MAX_DATA_TXRX ) )
        {
            urc_buf_ptr = strstr( app_buf, WIFININA_URC_READ_SOCKET_DATA ) + strlen ( WIFININA_URC_READ_SOCKET_DATA ) + 2;
            memcpy ( urc_buf, urc_buf_ptr, app_buf_len - ( urc_buf_ptr - app_buf ) - 2 );
            strcpy ( app_buf, tcp_peer_handle );
            strcat ( app_buf, "," );
            strcat ( app_buf, DATA_FORMAT_BINARY );
            strcat ( app_buf, "," );
            strcat ( app_buf, urc_buf );
            wifinina_cmd_set ( ctx, WIFININA_CMD_READ_DATA, app_buf );
            error_flag |= wifinina_read_response( ctx, WIFININA_URC_READ_SOCKET_DATA, WIFININA_MAX_DATA_TXRX );
        }
    }

    if ( udp_peer_handle[ 0 ] )
    {
        log_printf( &logger, ">>> Write message to UDP socket and read response.\r\n" );
        wifinina_clear_app_buf( );
        strcpy ( app_buf, udp_peer_handle );
        strcat ( app_buf, "," );
        strcat ( app_buf, DATA_FORMAT_STRING );
        strcat ( app_buf, "," );
        strcat ( app_buf, MESSAGE_CONTENT );
        wifinina_cmd_set( ctx, WIFININA_CMD_WRITE_DATA, app_buf );
        if ( WIFININA_OK == wifinina_read_response( ctx, WIFININA_URC_READ_SOCKET_DATA, WIFININA_MAX_DATA_TXRX ) )
        {
            urc_buf_ptr = strstr( app_buf, WIFININA_URC_READ_SOCKET_DATA ) + strlen ( WIFININA_URC_READ_SOCKET_DATA ) + 2;
            memcpy ( urc_buf, urc_buf_ptr, app_buf_len - ( urc_buf_ptr - app_buf ) - 2 );
            strcpy ( app_buf, udp_peer_handle );
            strcat ( app_buf, "," );
            strcat ( app_buf, DATA_FORMAT_BINARY );
            strcat ( app_buf, "," );
            strcat ( app_buf, urc_buf );
            wifinina_cmd_set ( ctx, WIFININA_CMD_READ_DATA, app_buf );
            error_flag |= wifinina_read_response( ctx, WIFININA_URC_READ_SOCKET_DATA, WIFININA_MAX_DATA_TXRX );
        }
    }

    if ( tcp_peer_handle[ 0 ] )
    {
        log_printf( &logger, ">>> Close TCP socket.\r\n" );
        wifinina_cmd_set( ctx, WIFININA_CMD_CLOSE_PEER, tcp_peer_handle );
        error_flag |= wifinina_read_response( ctx, WIFININA_URC_PEER_DISCONNECTED, WIFININA_MAX_PEER_CLOSE );
    }

    if ( udp_peer_handle[ 0 ] )
    {
        log_printf( &logger, ">>> Close UDP socket.\r\n" );
        wifinina_cmd_set( ctx, WIFININA_CMD_CLOSE_PEER, udp_peer_handle );
        error_flag |= wifinina_read_response( ctx, WIFININA_URC_PEER_DISCONNECTED, WIFININA_MAX_PEER_CLOSE );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    return error_flag;
}

// ------------------------------------------------------------------------ END
