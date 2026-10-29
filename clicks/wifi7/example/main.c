/*!
 * @file main.c
 * @brief WiFi 7 Click example
 *
 * # Description
 * This example exchanges numbered messages with the MIKROE echo server over TCP and UDP.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and SPI interface, resets the module, checks firmware compatibility,
 * reports the firmware version, and requests a connection to the configured Wi-Fi network.
 *
 * ## Application Task
 * Processes module events and waits for DHCP. It opens a TCP connection, sends a numbered
 * message, verifies its echo, and closes the socket. The exchange then repeats over UDP.
 * Partial TCP responses and firmware receive chunks are assembled before checking the complete echo.
 * Missing UDP echoes retransmit the same message; TCP receive retries keep the accumulated bytes.
 *
 * @note
 * Set MAIN_WLAN_SSID and MAIN_WLAN_PSK for a 2.4 GHz WPA/WPA2 personal network with Internet access.
 * The network must allow TCP and UDP traffic to 54.187.244.144:51111.
 * UDP binds local port 50000. Module events continue to be processed during the pause between exchanges.
 * The module must have WINC15x0 firmware compatible with host driver 19.5.4.
 * This example does not update firmware or save credentials to module flash.
 * Wait counters measure task calls; driver processing and logging add to the elapsed time.
 * A connection wait limit, exhausted echo retries, or communication failure stops the example until restart.
 *
 * @author Stefan Filipovic
 */

#include "board.h"
#include "log.h"
#include "wifi7.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_WIFI7
    #define MIKROBUS_POSITION_WIFI7 MIKROBUS_1
#endif

/**
 * @brief WiFi 7 WLAN settings.
 * @details SSID, authentication type, and password used by the station connection request.
 */
#define MAIN_WLAN_SSID                  "MIKROE GUEST"
#define MAIN_WLAN_AUTH                  WIFI7_M2M_WIFI_SEC_WPA_PSK
#define MAIN_WLAN_PSK                   "!guest.mikroe!"

/**
 * @brief WiFi 7 echo server settings.
 * @details Remote IPv4 address as four comma-separated octets, remote TCP/UDP port, and the local UDP listening
 * port.
 */
#define APP_SERVER_IP                   54, 187, 244, 144
#define APP_SERVER_PORT                 51111
#define APP_LOCAL_PORT                  50000

/**
 * @brief WiFi 7 echo message settings.
 * @details The text prefix is 33 characters excluding its null terminator, followed by the decimal
 * counter and CRLF. Buffer capacity allows the maximum uint32_t decimal width, both line-ending
 * bytes, and the terminating null byte.
 */
#define APP_TEXT_MESSAGE                "Hello from WiFi 7 Click! Packet: "
#define APP_TEXT_MESSAGE_LENGTH         33
#define APP_PACKET_COUNTER_MAX_DIGITS   10
#define APP_MESSAGE_LINE_END_SIZE       2
#define APP_MESSAGE_SIZE                ( APP_TEXT_MESSAGE_LENGTH + APP_PACKET_COUNTER_MAX_DIGITS + \
                                          APP_MESSAGE_LINE_END_SIZE + 1 )

/**
 * @brief WiFi 7 application wait limits.
 * @details Connection and socket limits count task polls. Each normal task includes a ten-millisecond delay plus
 * protocol and logging work.
 */
#define MAIN_CONNECT_POLL_LIMIT         6000
#define MAIN_SOCKET_POLL_LIMIT          1000
#define MAIN_RX_BUFFER_SIZE             512

/**
 * @brief WiFi 7 receive timeout and retry settings.
 * @details The firmware receive timeout is in milliseconds. Additional echo retries and protocol-transition waits
 * are bounded by their macros.
 */
#define APP_RECV_TIMEOUT_MS             5000
#define APP_ECHO_RETRY_LIMIT            2
#define APP_TRANSITION_TICKS            300
#define APP_SOCKET_TIMEOUT_ERROR        ( -13 ) /**< WINC15x0 SOCK_ERR_TIMEOUT receive status. */

/**
 * @brief WiFi 7 echo example states.
 * @details Sequences socket opening, transmission, echo verification, and transport changes.
 */
typedef enum
{
    APP_STATE_WAIT_IP,          /**< Wait for DHCP after requesting association. */
    APP_STATE_OPEN_SOCKET,      /**< Allocate and connect TCP, or bind UDP. */
    APP_STATE_WAIT_SOCKET,      /**< Wait for TCP connection or UDP bind completion. */
    APP_STATE_SEND_MESSAGE,     /**< Prepare a message, queue reception, and request transmission. */
    APP_STATE_WAIT_SEND,        /**< Wait for send completion; an echo can arrive first. */
    APP_STATE_RECEIVE,          /**< Queue another receive after a partial reply or timeout. */
    APP_STATE_WAIT_ECHO,        /**< Wait for a complete verified echo. */
    APP_STATE_CLOSE_SOCKET,     /**< Close the socket after send and echo completion. */
    APP_STATE_TRANSITION        /**< Continue polling during the pause, then switch transport. */

} wifi7_app_state_t;

static wifi7_t wifi7;                                       /**< WiFi 7 Click context object. */
static log_t logger;                                        /**< Logger context object. */
static wifi7_app_state_t app_state = APP_STATE_WAIT_IP;     /**< Current echo example stage. */
static uint8_t app_protocol = WIFI7_SOCK_STREAM;            /**< WIFI7_SOCK_STREAM for TCP or WIFI7_SOCK_DGRAM for UDP. */
static uint8_t app_server_ip[ 4 ] = { APP_SERVER_IP };      /**< Echo server IPv4 octets in network order. */
static wifi7_sockaddr_in_t remote_addr;                     /**< Remote echo server address and port. */
static wifi7_sockaddr_in_t local_addr;                      /**< Local IPv4 address and port used for UDP binding. */
static int8_t echo_socket = -1;                             /**< Current allocated descriptor, or -1 when no socket is open. */
static uint8_t wifi_connected = 0;                          /**< 1 after the DHCP callback provides an address. */
static uint8_t demo_failed = 0;                             /**< 1 stops the example after an unrecovered error. */
static uint8_t app_tx_accepted = 0;                         /**< 1 once this message has advanced the packet counter. */
static uint8_t send_pending = 0;                            /**< 1 while the current transmission awaits its callback. */
static uint8_t app_rx_pending = 0;                          /**< 1 while a receive request or its chunks are pending. */
static uint8_t app_echo_verified = 0;                       /**< 1 once every expected echo byte has matched. */
static uint8_t app_rx_retry_count = 0;                      /**< Additional receive waits or UDP retransmissions used. */
static uint16_t app_wait_ticks = 0;                         /**< Task polls spent in the current wait or transition. */
static uint32_t app_packet_count = 1;                       /**< Number appended to the next new message. */
static uint8_t socket_buffer[ MAIN_RX_BUFFER_SIZE ];        /**< Receive chunk storage retained by the socket driver. */
static char app_tx_message[ APP_MESSAGE_SIZE ];             /**< Message retained for comparison and UDP retries. */
static char app_rx_message[ APP_MESSAGE_SIZE ];             /**< Assembled echo with space for the terminating zero. */
static uint16_t app_tx_length = 0;                          /**< Expected echo byte count, excluding the terminator. */
static uint16_t app_rx_length = 0;                          /**< Matching echo bytes accumulated for this message. */

/**
 * @brief WiFi 7 application Wi-Fi callback.
 * @details This function logs association and DHCP information and stops the example after disconnection or an IPv4
 * address conflict.
 * @param[in] u8_msg_type : Wi-Fi event identifier.
 * @param[in] pv_msg : Event payload supplied by the driver.
 * @return Nothing.
 * @note The callback only consumes the current payload and updates application state; it does not reenter event
 * processing.
 */
static void wifi7_wifi_cb ( uint8_t u8_msg_type, void *pv_msg );

/**
 * @brief WiFi 7 application socket callback.
 * @details This function validates bind, connect, send, and receive results, assembles echoes, and advances the
 * example state.
 * @param[in] sock : Descriptor associated with the socket event.
 * @param[in] u8_msg : Socket callback event identifier.
 * @param[in] pv_msg : Event payload valid during this callback.
 * @return Nothing.
 * @note Send and receive completions can arrive in either order. Socket operations run later in application_task;
 * UDP retries retain the same message and TCP retries retain accumulated bytes.
 */
static void wifi7_socket_cb ( int8_t sock, uint8_t u8_msg, void *pv_msg );

/**
 * @brief WiFi 7 Click stage processing function.
 * @details This function runs one echo stage after module event processing.
 * @param[in,out] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t wifi7_app_run_stage ( wifi7_t *ctx );

/**
 * @brief WiFi 7 Click echo socket opening function.
 * @details This function allocates a socket and requests TCP connection or UDP binding.
 * @param[in,out] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t wifi7_app_open_socket ( wifi7_t *ctx );

/**
 * @brief WiFi 7 Click message transmission function.
 * @details This function prepares a numbered message, queues reception, and requests transmission.
 * @param[in,out] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t wifi7_app_send_message ( wifi7_t *ctx );

/**
 * @brief WiFi 7 Click echo reception function.
 * @details This function queues a TCP or UDP receive using the persistent socket buffer.
 * @param[in,out] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t wifi7_app_receive ( wifi7_t *ctx );

/**
 * @brief WiFi 7 Click echo socket closing function.
 * @details This function logs the verified echo, closes the socket, and starts the transport pause.
 * @param[in,out] ctx : Click context object.
 * See #wifi7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t wifi7_app_close_socket ( wifi7_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi7_cfg_t wifi7_cfg;

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

    wifi7_cfg_setup( &wifi7_cfg );
    WIFI7_MAP_MIKROBUS( wifi7_cfg, MIKROBUS_POSITION_WIFI7 );
    if ( WIFI7_OK != wifi7_init( &wifi7, &wifi7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    err_t result = wifi7_default_cfg( &wifi7 );
    if ( result != WIFI7_OK )
    {
        if ( result == WIFI7_ERROR_FW_VERSION )
        {
            log_error( &logger, " Firmware incompatible with WINC15x0 driver 19.5.4." );
        }
        else
        {
            log_error( &logger, " Module initialization failed. Check power, pins, and firmware." );
        }
        for ( ; ; );
    }
    wifi7.app_wifi_cb   = wifi7_wifi_cb;
    wifi7.app_socket_cb = wifi7_socket_cb;
    wifi7_socket_init( &wifi7 );

    wifi7_m2m_rev_t fw_version;
    if ( WIFI7_OK != wifi7_get_full_firmware_version( &wifi7, &fw_version ) )
    {
        log_error( &logger, " Firmware version read failed." );
        for ( ; ; );
    }
    log_printf( &logger, "Firmware: %u.%u.%u\r\n",
                ( uint16_t ) fw_version.u8_firmware_major, ( uint16_t ) fw_version.u8_firmware_minor,
                ( uint16_t ) fw_version.u8_firmware_patch );
    log_printf( &logger, "Build: %s %s\r\n", ( char * ) fw_version.build_date, ( char * ) fw_version.build_time );

    remote_addr.sin_family = WIFI7_AF_INET;
    remote_addr.sin_port = ( uint16_t ) ( ( ( uint16_t ) APP_SERVER_PORT << 8 ) |
                                          ( ( uint16_t ) APP_SERVER_PORT >> 8 ) );
    memcpy( &remote_addr.sin_addr.s_addr, app_server_ip, sizeof( app_server_ip ) );
    local_addr.sin_family = WIFI7_AF_INET;
    local_addr.sin_port = ( uint16_t ) ( ( ( uint16_t ) APP_LOCAL_PORT << 8 ) |
                                         ( ( uint16_t ) APP_LOCAL_PORT >> 8 ) );
    local_addr.sin_addr.s_addr = 0;
    /* Count characters explicitly; string-literal sizeof differs on mikroC. */
    if ( WIFI7_OK != wifi7_connect( &wifi7, MAIN_WLAN_SSID, ( uint8_t ) strlen( MAIN_WLAN_SSID ),
                                    MAIN_WLAN_AUTH, MAIN_WLAN_PSK, WIFI7_M2M_WIFI_CH_ALL ) )
    {
        log_error( &logger, " Connection request failed." );
        for ( ; ; );
    }
    log_info( &logger, " Connecting..." );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( demo_failed )
    {
        Delay_100ms( );
        return;
    }
    if ( WIFI7_OK != wifi7_handle_events( &wifi7 ) )
    {
        log_error( &logger, " Module event handling failed. Restart the example." );
        demo_failed = 1;
        return;
    }
    if ( demo_failed )
    {
        return;
    }
    if ( WIFI7_OK != wifi7_app_run_stage( &wifi7 ) )
    {
        demo_failed = 1;
    }
    Delay_10ms( );
}

int main ( void )
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit( );
    #endif

    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
    return 0;
}

static err_t wifi7_app_run_stage ( wifi7_t *ctx )
{
    switch ( app_state )
    {
        case APP_STATE_WAIT_IP:
        {
            if ( wifi_connected )
            {
                app_wait_ticks = 0;
                app_state = APP_STATE_OPEN_SOCKET;
            }
            else if ( ++app_wait_ticks >= MAIN_CONNECT_POLL_LIMIT )
            {
                log_error( &logger, " Connection wait limit reached. Check credentials and restart." );
                return WIFI7_ERROR;
            }
            break;
        }
        case APP_STATE_OPEN_SOCKET:
            return wifi7_app_open_socket( ctx );
        case APP_STATE_SEND_MESSAGE:
            return wifi7_app_send_message( ctx );
        case APP_STATE_RECEIVE:
        {
            if ( WIFI7_OK != wifi7_app_receive( ctx ) )
            {
                return WIFI7_ERROR;
            }
            app_wait_ticks = 0;
            app_state = APP_STATE_WAIT_ECHO;
            break;
        }
        case APP_STATE_WAIT_SOCKET:
        case APP_STATE_WAIT_SEND:
        case APP_STATE_WAIT_ECHO:
        {
            if ( ++app_wait_ticks >= MAIN_SOCKET_POLL_LIMIT )
            {
                log_error( &logger, " Socket operation wait limit reached. Restart the example." );
                return WIFI7_ERROR;
            }
            break;
        }
        case APP_STATE_CLOSE_SOCKET:
            return wifi7_app_close_socket( ctx );
        case APP_STATE_TRANSITION:
        {
            if ( ++app_wait_ticks >= APP_TRANSITION_TICKS )
            {
                if ( app_protocol == WIFI7_SOCK_STREAM )
                {
                    app_protocol = WIFI7_SOCK_DGRAM;
                }
                else
                {
                    app_protocol = WIFI7_SOCK_STREAM;
                }
                app_wait_ticks = 0;
                app_state = APP_STATE_OPEN_SOCKET;
            }
            break;
        }
        default:
            return WIFI7_ERROR;
    }
    return WIFI7_OK;
}

static err_t wifi7_app_open_socket ( wifi7_t *ctx )
{
    err_t result;

    if ( app_protocol == WIFI7_SOCK_STREAM )
    {
        log_printf( &logger, "\r\n>>> Open TCP connection " );
    }
    else
    {
        log_printf( &logger, "\r\n>>> Open UDP socket " );
    }
    log_printf( &logger, "%u.%u.%u.%u:%u.\r\n",
                ( uint16_t ) app_server_ip[ 0 ], ( uint16_t ) app_server_ip[ 1 ],
                ( uint16_t ) app_server_ip[ 2 ], ( uint16_t ) app_server_ip[ 3 ],
                ( uint16_t ) APP_SERVER_PORT );
    echo_socket = ( int8_t ) wifi7_socket_create( ctx, WIFI7_AF_INET, app_protocol, 0 );
    if ( echo_socket < 0 )
    {
        log_error( &logger, " Echo socket creation failed." );
        return WIFI7_ERROR;
    }
    if ( app_protocol == WIFI7_SOCK_STREAM )
    {
        result = wifi7_socket_connect( ctx, echo_socket, ( wifi7_sockaddr_t * ) &remote_addr,
                                       sizeof( remote_addr ) );
    }
    else
    {
        result = wifi7_socket_bind( ctx, echo_socket, ( wifi7_sockaddr_t * ) &local_addr,
                                    sizeof( local_addr ) );
    }
    if ( result != WIFI7_OK )
    {
        log_error( &logger, " Echo socket connect/bind request failed." );
        return WIFI7_ERROR;
    }
    app_wait_ticks = 0;
    app_state = APP_STATE_WAIT_SOCKET;
    return WIFI7_OK;
}

static err_t wifi7_app_send_message ( wifi7_t *ctx )
{
    err_t result;
    char *counter_text;

    if ( app_tx_length == 0 )
    {
        strcpy( app_tx_message, APP_TEXT_MESSAGE );
        counter_text = &app_tx_message[ APP_TEXT_MESSAGE_LENGTH ];
        uint32_to_str( app_packet_count, counter_text );
        l_trim( counter_text );
        r_trim( counter_text );
        strcat( app_tx_message, "\r\n" );
        app_tx_length = ( uint16_t ) strlen( app_tx_message );
        app_rx_length = 0;
        app_tx_accepted = 0;
        app_rx_retry_count = 0;
        app_echo_verified = 0;
    }
    /* Queue reception before transmission so a fast echo already has a receive request. */
    if ( WIFI7_OK != wifi7_app_receive( ctx ) )
    {
        return WIFI7_ERROR;
    }
    if ( app_protocol == WIFI7_SOCK_STREAM )
    {
        result = wifi7_socket_send( ctx, echo_socket, app_tx_message, app_tx_length );
    }
    else
    {
        result = wifi7_socket_send_to( ctx, echo_socket, app_tx_message, app_tx_length,
                                       ( wifi7_sockaddr_t * ) &remote_addr, sizeof( remote_addr ) );
    }
    if ( result != WIFI7_OK )
    {
        log_error( &logger, " Echo send request failed." );
        return WIFI7_ERROR;
    }
    app_wait_ticks = 0;
    send_pending = 1;
    app_state = APP_STATE_WAIT_SEND;
    return WIFI7_OK;
}

static err_t wifi7_app_receive ( wifi7_t *ctx )
{
    err_t result;

    if ( app_protocol == WIFI7_SOCK_STREAM )
    {
        result = wifi7_socket_receive( ctx, echo_socket, socket_buffer, sizeof( socket_buffer ),
                                       APP_RECV_TIMEOUT_MS );
    }
    else
    {
        result = wifi7_socket_receive_from( ctx, echo_socket, socket_buffer, sizeof( socket_buffer ),
                                            APP_RECV_TIMEOUT_MS );
    }
    if ( result != WIFI7_OK )
    {
        log_error( &logger, " Echo receive request failed." );
        return WIFI7_ERROR;
    }
    app_rx_pending = 1;
    return WIFI7_OK;
}

static err_t wifi7_app_close_socket ( wifi7_t *ctx )
{
    err_t result;

    log_printf( &logger, "<<< Echo: %s", app_rx_message );
    result = wifi7_socket_close( ctx, echo_socket );
    if ( result != WIFI7_OK )
    {
        log_error( &logger, " Echo socket close failed." );
        return WIFI7_ERROR;
    }
    echo_socket = -1;
    app_tx_length = 0;
    app_rx_length = 0;
    app_tx_accepted = 0;
    app_echo_verified = 0;
    app_wait_ticks = 0;
    app_state = APP_STATE_TRANSITION;
    log_printf( &logger, ">>> Socket close requested.\r\n" );
    return WIFI7_OK;
}

static void wifi7_wifi_cb ( uint8_t u8_msg_type, void *pv_msg )
{
    switch ( u8_msg_type )
    {
        case WIFI7_M2M_WIFI_RESP_CON_STATE_CHANGED:
        {
            wifi7_m2m_wifi_state_changed_t *state = ( wifi7_m2m_wifi_state_changed_t * ) pv_msg;
            if ( state->u8_curr_state == WIFI7_M2M_WIFI_CONNECTED )
            {
                log_info( &logger, " Associated. Waiting for DHCP..." );
            }
            else
            {
                log_printf( &logger, "Wi-Fi disconnected, reason %u. Restart the example.\r\n",
                            ( uint16_t ) state->u8_err_code );
                wifi_connected = 0;
                demo_failed = 1;
            }
            break;
        }
        case WIFI7_M2M_WIFI_REQ_DHCP_CONF:
        {
            uint8_t *ip_address = ( uint8_t * ) pv_msg;
            log_printf( &logger, "IP: %u.%u.%u.%u\r\n",
                        ( uint16_t ) ip_address[ 0 ], ( uint16_t ) ip_address[ 1 ],
                        ( uint16_t ) ip_address[ 2 ], ( uint16_t ) ip_address[ 3 ] );
            wifi_connected = 1;
            break;
        }
        case WIFI7_M2M_WIFI_RESP_IP_CONFLICT:
        {
            log_error( &logger, " IP address conflict. Restart the example." );
            demo_failed = 1;
            break;
        }
        default:
        {
            break;
        }
    }
}

static void wifi7_socket_cb ( int8_t sock, uint8_t u8_msg, void *pv_msg )
{
    if ( demo_failed || ( sock != echo_socket ) )
    {
        return;
    }
    switch ( u8_msg )
    {
        case WIFI7_SOCKET_MSG_BIND:
        {
            wifi7_socket_bind_msg_t *bound = ( wifi7_socket_bind_msg_t * ) pv_msg;
            if ( ( app_protocol != WIFI7_SOCK_DGRAM ) || ( app_state != APP_STATE_WAIT_SOCKET ) )
            {
                break;
            }
            if ( bound->status != 0 )
            {
                log_printf( &logger, "UDP bind failed (%d).\r\n", ( int16_t ) bound->status );
                demo_failed = 1;
                break;
            }
            app_wait_ticks = 0;
            app_state = APP_STATE_SEND_MESSAGE;
            break;
        }
        case WIFI7_SOCKET_MSG_CONNECT:
        {
            wifi7_socket_connect_msg_t *connected = ( wifi7_socket_connect_msg_t * ) pv_msg;
            if ( ( app_protocol != WIFI7_SOCK_STREAM ) || ( app_state != APP_STATE_WAIT_SOCKET ) )
            {
                break;
            }
            if ( connected->s8_error != 0 )
            {
                log_printf( &logger, "TCP connection failed (%d).\r\n", ( int16_t ) connected->s8_error );
                demo_failed = 1;
                break;
            }
            app_wait_ticks = 0;
            app_state = APP_STATE_SEND_MESSAGE;
            break;
        }
        case WIFI7_SOCKET_MSG_SEND:
        case WIFI7_SOCKET_MSG_SENDTO:
        {
            int16_t sent = *( int16_t * ) pv_msg;
            if ( !send_pending ||
                 ( ( app_protocol == WIFI7_SOCK_STREAM ) && ( u8_msg != WIFI7_SOCKET_MSG_SEND ) ) ||
                 ( ( app_protocol == WIFI7_SOCK_DGRAM ) && ( u8_msg != WIFI7_SOCKET_MSG_SENDTO ) ) )
            {
                break;
            }
            if ( sent != ( int16_t ) app_tx_length )
            {
                log_printf( &logger, "Echo send failed or incomplete (%d).\r\n", sent );
                demo_failed = 1;
                break;
            }
            send_pending = 0;
            if ( !app_tx_accepted )
            {
                app_packet_count++;
                app_tx_accepted = 1;
            }
            log_printf( &logger, ">>> TX: %s", app_tx_message );
            app_wait_ticks = 0;
            if ( app_echo_verified )
            {
                app_state = APP_STATE_CLOSE_SOCKET;
            }
            else if ( app_rx_pending )
            {
                app_state = APP_STATE_WAIT_ECHO;
            }
            else
            {
                app_state = APP_STATE_RECEIVE;
            }
            break;
        }
        case WIFI7_SOCKET_MSG_RECV:
        case WIFI7_SOCKET_MSG_RECVFROM:
        {
            wifi7_socket_recv_msg_t *received = ( wifi7_socket_recv_msg_t * ) pv_msg;
            uint16_t length;

            if ( !app_rx_pending ||
                 ( ( app_protocol == WIFI7_SOCK_STREAM ) && ( u8_msg != WIFI7_SOCKET_MSG_RECV ) ) ||
                 ( ( app_protocol == WIFI7_SOCK_DGRAM ) && ( u8_msg != WIFI7_SOCKET_MSG_RECVFROM ) ) )
            {
                break;
            }
            if ( received->u16_remaining_size == 0 )
            {
                app_rx_pending = 0;
            }
            if ( ( received->s16_buffer_size == APP_SOCKET_TIMEOUT_ERROR ) &&
                 !send_pending && ( app_rx_retry_count < APP_ECHO_RETRY_LIMIT ) )
            {
                app_rx_retry_count++;
                app_wait_ticks = 0;
                if ( app_protocol == WIFI7_SOCK_DGRAM )
                {
                    app_rx_length = 0;
                    app_state = APP_STATE_SEND_MESSAGE;
                    log_printf( &logger, ">>> UDP echo timeout; resend same packet, retry %u/%u.\r\n",
                                ( uint16_t ) app_rx_retry_count, ( uint16_t ) APP_ECHO_RETRY_LIMIT );
                }
                else
                {
                    app_state = APP_STATE_RECEIVE;
                    log_printf( &logger, ">>> TCP echo timeout; continue receiving, retry %u/%u.\r\n",
                                ( uint16_t ) app_rx_retry_count, ( uint16_t ) APP_ECHO_RETRY_LIMIT );
                }
                break;
            }
            if ( received->s16_buffer_size <= 0 )
            {
                log_printf( &logger, "Echo receive closed or failed (%d). Restart the example.\r\n",
                            ( int16_t ) received->s16_buffer_size );
                demo_failed = 1;
                break;
            }
            if ( ( app_protocol == WIFI7_SOCK_DGRAM ) &&
                 ( ( received->str_remote_addr.sin_port != remote_addr.sin_port ) ||
                   ( received->str_remote_addr.sin_addr.s_addr != remote_addr.sin_addr.s_addr ) ) )
            {
                log_error( &logger, " UDP response did not come from the configured echo server." );
                demo_failed = 1;
                break;
            }
            length = ( uint16_t ) received->s16_buffer_size;
            if ( ( app_rx_length > app_tx_length ) || ( length > app_tx_length - app_rx_length ) ||
                 memcmp( received->pu8_buffer, &app_tx_message[ app_rx_length ], length ) )
            {
                log_error( &logger, " Echo does not match the transmitted message." );
                demo_failed = 1;
                break;
            }
            memcpy( &app_rx_message[ app_rx_length ], received->pu8_buffer, length );
            app_rx_length += length;
            if ( received->u16_remaining_size != 0 )
            {
                break;
            }
            if ( app_rx_length == app_tx_length )
            {
                app_rx_message[ app_rx_length ] = 0;
                app_echo_verified = 1;
                if ( !send_pending )
                {
                    app_state = APP_STATE_CLOSE_SOCKET;
                }
            }
            else if ( app_protocol == WIFI7_SOCK_STREAM )
            {
                if ( !send_pending )
                {
                    app_state = APP_STATE_RECEIVE;
                }
            }
            else
            {
                log_error( &logger, " UDP echo length does not match the transmitted datagram." );
                demo_failed = 1;
            }
            app_wait_ticks = 0;
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
