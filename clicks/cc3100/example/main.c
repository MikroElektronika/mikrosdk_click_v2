/*!
 * @file main.c
 * @brief CC3100 Click Example.
 *
 * # Description
 * This example demonstrates CC3100 Click Wi-Fi communication by exchanging numbered messages
 * with the MIKROE echo server over TCP and UDP.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and CC3100 Click driver, maps the Click pins, and selects SPI or UART.
 *
 * ## Application Task
 * Starts the network processor, displays its firmware and MAC address, joins the configured WLAN,
 * and waits for DHCP. It then alternates numbered TCP and UDP echo exchanges with
 * 54.187.244.144:51111, closing each socket before switching protocols. It assembles partial TCP
 * responses and restarts the network processor after communication errors.
 *
 * @note
 * Set APP_WIFI_SSID and APP_WIFI_PASSWORD for a 2.4 GHz WLAN with Internet access.
 * The example uses the echo service at 54.187.244.144:51111; the network must allow TCP and UDP.
 * A one-second non-blocking pause separates exchanges when the protocol changes. UDP does not
 * guarantee delivery, and the test messages are unencrypted; do not send sensitive data.
 * Select SPI or UART with APP_DRIVER_INTERFACE and set J1A/J2A to 1-2 for SPI or 2-3 for UART.
 * UART uses 115200 baud, 8 data bits, no parity, one stop bit, and software CTS/RTS flow control.
 * Connect the logger to a UART peripheral different from the one used by CC3100 Click.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "cc3100.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_CC3100
    #define MIKROBUS_POSITION_CC3100 MIKROBUS_1
#endif

/** WLAN credentials and authentication settings used by the example. */
#define APP_WIFI_SSID                   "MIKROE GUEST"
#define APP_WIFI_PASSWORD               "!guest.mikroe!"
#define APP_WIFI_SECURITY               CC3100_SECURITY_WPA_WPA2

/** Host interface and echo server endpoint used by the example. */
#define APP_DRIVER_INTERFACE            CC3100_DRV_SEL_SPI
#define APP_SERVER_IP                   54, 187, 244, 144
#define APP_SERVER_PORT                 51111

/** Local port bound by UDP; the TCP connection selects its local port automatically. */
#define APP_LOCAL_PORT                  50000

/** Text prefix followed by the packet counter and a CRLF line ending. */
#define APP_TEXT_MESSAGE                "Hello from CC3100 Click! Packet: "

/** Application timeouts and log cadence, expressed in APP_TASK_INTERVAL_MS ticks. */
#define APP_WAIT_IP_TIMEOUT_TICKS       3000
#define APP_WAIT_IP_LOG_TICKS           500
#define APP_ECHO_TIMEOUT_TICKS          3000
#define APP_RECOVERY_TICKS              300
#define APP_PROTOCOL_TRANSITION_TICKS   100

/** Delay at the end of each task call; tick-based waits are approximate multiples of this value. */
#define APP_TASK_INTERVAL_MS            10

/**
 * @brief CC3100 Click example application states.
 * @details These states sequence module startup, Wi-Fi connection, echo exchanges, and recovery.
 */
typedef enum
{
    APP_STATE_POWER_UP,             /**< Configure and identify the network processor. */
    APP_STATE_CONNECT_WIFI,         /**< Request association with the configured WLAN. */
    APP_STATE_WAIT_IP,              /**< Process events until DHCP supplies an IP address. */
    APP_STATE_OPEN_SOCKET,          /**< Open a socket using the active transport. */
    APP_STATE_SEND_MESSAGE,         /**< Send one message containing its packet counter. */
    APP_STATE_WAIT_ECHO,            /**< Poll until the matching echo is received. */
    APP_STATE_CLOSE_SOCKET,         /**< Close the socket after the exchange. */
    APP_STATE_PROTOCOL_TRANSITION,  /**< Pause before switching between TCP and UDP. */
    APP_STATE_RECOVERY              /**< Wait before restarting after an error. */

} app_state_t;

static cc3100_t cc3100;                           /**< CC3100 Click driver context. */
static log_t logger;                              /**< Example logger context. */
static app_state_t app_state = APP_STATE_POWER_UP; /**< Current state of the example. */
static uint8_t app_protocol = CC3100_PROTOCOL_TCP; /**< Transport for the current exchange. */
static uint8_t app_server_ip[ 4 ] = { APP_SERVER_IP }; /**< MIKROE echo server IPv4 address. */
static char app_rx_line[ CC3100_DATA_SIZE + 1 ];   /**< Accumulates a TCP echo until its line ending. */
static uint16_t app_rx_used = 0;                   /**< Number of bytes currently in app_rx_line. */
static uint32_t app_packet_count = 1;              /**< Counter appended to each transmitted message. */
static uint16_t app_wait_ticks = 0;                /**< DHCP or recovery elapsed task ticks. */
static uint16_t app_echo_ticks = 0;                /**< Elapsed task ticks while waiting for an echo. */
static uint16_t app_transition_ticks = 0;          /**< Elapsed task ticks between protocols. */

/**
 * @brief CC3100 Click application stage dispatcher function.
 * @details This function executes the handler assigned to the current application state.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - The current stage continues or completes,
 *         @li @c != 0 - An application stage returned an error.
 * See #err_t definition for detailed explanation.
 * @note Only one state handler is called per application task invocation.
 */
static err_t cc3100_app_run_stage ( cc3100_t *ctx );

/**
 * @brief CC3100 Click startup function.
 * @details This function configures the network processor and reads its firmware version and MAC address.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - Module startup and identification read completed,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note Wi-Fi connection begins in the following application state.
 */
static err_t cc3100_app_power_up ( cc3100_t *ctx );

/**
 * @brief CC3100 Click Wi-Fi connection function.
 * @details This function requests a connection to the configured WLAN and advances to DHCP wait.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - Wi-Fi connection request accepted,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note An accepted request does not confirm that DHCP has supplied an IP address.
 */
static err_t cc3100_app_connect_wifi ( cc3100_t *ctx );

/**
 * @brief CC3100 Click DHCP wait function.
 * @details This function processes network events until an IP address is acquired or the wait expires.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - DHCP is pending or an IP address was acquired,
 *         @li @c != 0 - Communication error or DHCP timeout.
 * See #err_t definition for detailed explanation.
 * @note The timeout is measured using APP_TASK_INTERVAL_MS task ticks.
 */
static err_t cc3100_app_wait_ip ( cc3100_t *ctx );

/**
 * @brief CC3100 Click echo socket opening function.
 * @details This function connects a TCP socket or binds a UDP socket for the next echo exchange.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - Socket opened,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note The UDP socket binds APP_LOCAL_PORT; TCP selects its local port automatically.
 */
static err_t cc3100_app_open_socket ( cc3100_t *ctx );

/**
 * @brief CC3100 Click echo request transmission function.
 * @details This function appends the packet counter and sends the message over the active socket.
 * If transmit credit is unavailable, the message is retried on the next task call.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - Message sent or waiting for transmit credit,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note The packet counter advances only after the driver accepts the message.
 */
static err_t cc3100_app_send_message ( cc3100_t *ctx );

/**
 * @brief CC3100 Click echo response reading function.
 * @details This function polls the active socket, validates the response, and advances when the echo arrives.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - Waiting for or received the expected echo,
 *         @li @c != 0 - Communication error or response timeout.
 * See #err_t definition for detailed explanation.
 * @note TCP stream chunks are accumulated until a newline; UDP is handled as a datagram.
 */
static err_t cc3100_app_wait_echo ( cc3100_t *ctx );

/**
 * @brief CC3100 Click echo socket closing function.
 * @details This function closes the active socket, selects the other transport, and starts the transition wait.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @return @li @c 0 - Socket closed,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note The next socket is not opened until the protocol transition wait completes.
 */
static err_t cc3100_app_close_socket ( cc3100_t *ctx );

/**
 * @brief CC3100 Click protocol transition wait function.
 * @details This function waits about one second before opening a socket with the other transport.
 * @return None.
 * @note The delay is set by APP_PROTOCOL_TRANSITION_TICKS and APP_TASK_INTERVAL_MS.
 */
static void cc3100_app_protocol_transition ( void );

/**
 * @brief CC3100 Click application recovery wait function.
 * @details This function waits before returning the application to the module startup state.
 * @return None.
 * @note The recovery interval is set by APP_RECOVERY_TICKS and APP_TASK_INTERVAL_MS.
 */
static void cc3100_app_recovery ( void );

/**
 * @brief CC3100 Click application error handling function.
 * @details This function logs the error, closes the socket, clears exchange state, and schedules recovery.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in] error_flag : Error returned by the active application stage.
 * @return Nothing.
 * @note The module is restarted after APP_RECOVERY_TICKS task intervals.
 */
static void cc3100_app_handle_error ( cc3100_t *ctx, err_t error_flag );

/**
 * @brief CC3100 Click echo response processing function.
 * @details This function validates the remote endpoint, logs UDP datagrams, and assembles TCP lines.
 * @param[in] ctx : Click context object.
 * See #cc3100_t object definition for detailed explanation.
 * @param[in,out] rx_buffer : Received data buffer with space for one extra local terminator.
 * @param[in] packet : Received data length and source address. See #cc3100_packet_t.
 * @param[in] protocol : Active socket protocol, either TCP or UDP.
 * @return 1 when a complete response from the configured echo server is received; otherwise 0.
 * @note Only data from the peer configured in ctx is treated as the echo; UDP data is null-terminated locally.
 */
static uint8_t cc3100_app_log_received ( cc3100_t *ctx, uint8_t *rx_buffer, cc3100_packet_t *packet,
                                         uint8_t protocol );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cc3100_cfg_t cc3100_cfg;  /**< Click config object. */

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
    cc3100_cfg_setup( &cc3100_cfg );
    CC3100_MAP_MIKROBUS( cc3100_cfg, MIKROBUS_POSITION_CC3100 );
    cc3100_drv_interface_sel( &cc3100_cfg, APP_DRIVER_INTERFACE );
    if ( CC3100_OK != cc3100_init( &cc3100, &cc3100_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag = cc3100_app_run_stage( &cc3100 );
    if ( error_flag < 0 )
    {
        cc3100_app_handle_error( &cc3100, error_flag );
    }
    Delay_ms( APP_TASK_INTERVAL_MS );
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

static err_t cc3100_app_run_stage ( cc3100_t *ctx )
{
    err_t error_flag = CC3100_OK;
    switch ( app_state )
    {
        case APP_STATE_POWER_UP:
        { 
            error_flag = cc3100_app_power_up( ctx );
            break;
        }
        case APP_STATE_CONNECT_WIFI:
        {
            error_flag = cc3100_app_connect_wifi( ctx );
            break;
        }
        case APP_STATE_WAIT_IP:
        {
            error_flag = cc3100_app_wait_ip( ctx );
            break;
        }
        case APP_STATE_OPEN_SOCKET:
        {
            error_flag = cc3100_app_open_socket( ctx );
            break;
        }
        case APP_STATE_SEND_MESSAGE:
        {
            error_flag = cc3100_app_send_message( ctx );
            break;
        }
        case APP_STATE_WAIT_ECHO:
        {
            error_flag = cc3100_app_wait_echo( ctx );
            break;
        }
        case APP_STATE_CLOSE_SOCKET:
        {
            error_flag = cc3100_app_close_socket( ctx );
            break;
        }
        case APP_STATE_PROTOCOL_TRANSITION:
        {
            cc3100_app_protocol_transition( );
            break;
        }
        case APP_STATE_RECOVERY: 
        {
            cc3100_app_recovery( );
            break;
        }
        default:
        {
            app_state = APP_STATE_POWER_UP;
            break;
        }
    }
    return error_flag;
}

static err_t cc3100_app_power_up ( cc3100_t *ctx )
{
    cc3100_version_t version; /**< Firmware and hardware identification returned by the module. */
    uint8_t mac[ 6 ]; /**< Output buffer for the module MAC address. */
    err_t error_flag;

    log_printf( &logger, " >>> APP STATE - POWER UP <<<\r\n\n" );
    log_printf( &logger, " >>> Start module in station mode with DHCP.\r\n" );
    error_flag = cc3100_default_cfg( ctx );
    if ( CC3100_OK == error_flag )
    {
        error_flag = cc3100_get_version( ctx, &version );
    }
    if ( CC3100_OK == error_flag )
    {
        log_printf( &logger, " Firmware: %lu.%lu.%lu.%lu\r\n",
                    version.nwp[ 0 ], version.nwp[ 1 ], version.nwp[ 2 ], version.nwp[ 3 ] );
        error_flag = cc3100_get_mac( ctx, mac );
    }
    if ( CC3100_OK == error_flag )
    {
        log_printf( &logger, " MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                    ( uint16_t ) mac[ 0 ], ( uint16_t ) mac[ 1 ], ( uint16_t ) mac[ 2 ],
                    ( uint16_t ) mac[ 3 ], ( uint16_t ) mac[ 4 ], ( uint16_t ) mac[ 5 ] );
        app_state = APP_STATE_CONNECT_WIFI;
    }
    return error_flag;
}

static err_t cc3100_app_connect_wifi ( cc3100_t *ctx )
{
    err_t error_flag;

    log_printf( &logger, " >>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
    log_printf( &logger, " >>> Connect to Wi-Fi: %s\r\n", APP_WIFI_SSID );
    error_flag = cc3100_connect( ctx, APP_WIFI_SSID, APP_WIFI_PASSWORD, APP_WIFI_SECURITY );
    if ( CC3100_OK == error_flag )
    {
        app_wait_ticks = 0;
        app_state = APP_STATE_WAIT_IP;
    }
    return error_flag;
}

static err_t cc3100_app_wait_ip ( cc3100_t *ctx )
{
    err_t error_flag = cc3100_process( ctx );

    if ( ( CC3100_OK == error_flag ) || ( CC3100_NO_DATA == error_flag ) )
    {
        if ( ctx->network.ip_acquired )
        {
            log_printf( &logger, " IP: %u.%u.%u.%u\r\n",
                        ( uint16_t ) ctx->network.ip[ 0 ], ( uint16_t ) ctx->network.ip[ 1 ],
                        ( uint16_t ) ctx->network.ip[ 2 ], ( uint16_t ) ctx->network.ip[ 3 ] );
            app_state = APP_STATE_OPEN_SOCKET;
            error_flag = CC3100_OK;
        }
        else
        {
            if ( 0 == ( app_wait_ticks % APP_WAIT_IP_LOG_TICKS ) )
            {
                log_printf( &logger, " >>> Waiting for Wi-Fi connection and DHCP address...\r\n" );
            }
            if ( ++app_wait_ticks >= APP_WAIT_IP_TIMEOUT_TICKS )
            {
                log_error( &logger, " Wi-Fi connection failed. Check credentials, 2.4 GHz coverage, and DHCP." );
                error_flag = CC3100_TIMEOUT;
            }
            else
            {
                error_flag = CC3100_OK;
            }
        }
    }
    return error_flag;
}

static err_t cc3100_app_open_socket ( cc3100_t *ctx )
{
    err_t error_flag;

    if ( CC3100_PROTOCOL_TCP == app_protocol )
    {
        log_printf( &logger, " >>> Connect to TCP echo server 54.187.244.144:51111.\r\n" );
    }
    else
    {
        log_printf( &logger, " >>> Open UDP socket for echo server 54.187.244.144:51111.\r\n" );
    }
    error_flag = cc3100_open_socket( ctx, app_protocol, APP_LOCAL_PORT, app_server_ip, APP_SERVER_PORT );
    if ( CC3100_OK == error_flag )
    {
        app_rx_used = 0;
        app_echo_ticks = 0;
        app_state = APP_STATE_SEND_MESSAGE;
    }
    return error_flag;
}

static err_t cc3100_app_send_message ( cc3100_t *ctx )
{
    uint8_t tx_data[ CC3100_DATA_SIZE ]; /**< Prefix, uint32 counter, CRLF, and null terminator. */
    uint8_t counter_text[ 11 ]; /**< Up to ten decimal digits and a null terminator. */
    err_t error_flag;

    strcpy( tx_data, APP_TEXT_MESSAGE );
    uint32_to_str( app_packet_count, counter_text );
    l_trim( counter_text );
    r_trim( counter_text );
    strcat( tx_data, counter_text );
    strcat( tx_data, "\r\n" );
    error_flag = cc3100_send( ctx, tx_data, strlen( tx_data ) );
    if ( CC3100_OK == error_flag )
    {
        if ( CC3100_PROTOCOL_TCP == app_protocol )
        {
            log_printf( &logger, " >>> TX TCP: %s", ( char * ) tx_data );
        }
        else
        {
            log_printf( &logger, " >>> TX UDP: %s", ( char * ) tx_data );
        }
        app_packet_count++;
        app_echo_ticks = 0;
        app_state = APP_STATE_WAIT_ECHO;
    }
    else if ( CC3100_NO_DATA == error_flag )
    {
        // Retry the same message when the network processor has no transmit credit.
        error_flag = CC3100_OK;
    }
    return error_flag;
}

static err_t cc3100_app_wait_echo ( cc3100_t *ctx )
{
    cc3100_packet_t packet; /**< Received length and source endpoint. */
    uint8_t rx_data[ CC3100_DATA_SIZE + 1 ]; /**< Driver-sized payload with one extra terminator byte. */
    err_t error_flag;

    error_flag = cc3100_receive( ctx, rx_data, CC3100_DATA_SIZE, &packet );
    if ( CC3100_OK == error_flag )
    {
        if ( cc3100_app_log_received( ctx, rx_data, &packet, app_protocol ) )
        {
            app_state = APP_STATE_CLOSE_SOCKET;
            app_echo_ticks = 0;
        }
        else
        {
            error_flag = CC3100_NO_DATA;
        }
    }
    if ( CC3100_NO_DATA == error_flag )
    {
        if ( ++app_echo_ticks >= APP_ECHO_TIMEOUT_TICKS )
        {
            error_flag = CC3100_TIMEOUT;
        }
        else
        {
            error_flag = CC3100_OK;
        }
    }
    else if ( CC3100_CLOSED == error_flag )
    {
        log_printf( &logger, " >>> TCP peer closed before the echo was received.\r\n" );
        app_state = APP_STATE_CLOSE_SOCKET;
        error_flag = CC3100_OK;
    }
    return error_flag;
}

static err_t cc3100_app_close_socket ( cc3100_t *ctx )
{
    err_t error_flag;

    if ( CC3100_PROTOCOL_TCP == app_protocol )
    {
        log_printf( &logger, " >>> Close TCP socket.\r\n\n" );
    }
    else
    {
        log_printf( &logger, " >>> Close UDP socket.\r\n\n" );
    }
    error_flag = cc3100_close_socket( ctx );
    if ( CC3100_OK == error_flag )
    {
        app_rx_used = 0;
        if ( CC3100_PROTOCOL_TCP == app_protocol )
        {
            app_protocol = CC3100_PROTOCOL_UDP;
        }
        else
        {
            app_protocol = CC3100_PROTOCOL_TCP;
        }
        app_transition_ticks = 0;
        app_state = APP_STATE_PROTOCOL_TRANSITION;
    }
    return error_flag;
}

static void cc3100_app_protocol_transition ( void )
{
    if ( ++app_transition_ticks >= APP_PROTOCOL_TRANSITION_TICKS )
    {
        app_transition_ticks = 0;
        app_state = APP_STATE_OPEN_SOCKET;
    }
}

static void cc3100_app_recovery ( void )
{
    if ( 0 == app_wait_ticks )
    {
        log_printf( &logger, " >>> Restarting module shortly...\r\n\n" );
    }
    if ( ++app_wait_ticks >= APP_RECOVERY_TICKS )
    {
        app_state = APP_STATE_POWER_UP;
    }
}

static void cc3100_app_handle_error ( cc3100_t *ctx, err_t error_flag )
{
    if ( CC3100_MODULE_ERROR == error_flag )
    {
        log_error( &logger, " Driver error: %d | Module status: %d", error_flag, ctx->module_error );
    }
    else
    {
        log_error( &logger, " Driver error: %d", error_flag );
    }
    cc3100_close_socket( ctx );
    app_rx_used = 0;
    app_wait_ticks = 0;
    app_echo_ticks = 0;
    app_transition_ticks = 0;
    app_state = APP_STATE_RECOVERY;
}

static uint8_t cc3100_app_log_received ( cc3100_t *ctx, uint8_t *rx_buffer, cc3100_packet_t *packet,
                                         uint8_t protocol )
{
    uint16_t index;
    uint16_t length = packet->length;
    uint8_t complete = 0;

    if ( ( 0 != memcmp( packet->ip, ctx->peer_ip, 4 ) ) || ( ctx->peer_port != packet->port ) )
    {
        return 0;
    }

    if ( CC3100_PROTOCOL_UDP == protocol )
    {
        while ( length && ( ( '\r' == rx_buffer[ length - 1 ] ) || ( '\n' == rx_buffer[ length - 1 ] ) ) )
        {
            length--;
        }
        rx_buffer[ length ] = '\0';
        log_printf( &logger, " <<< UDP echo: %s\r\n", ( char * ) rx_buffer );
        complete = 1;
    }
    else
    {
        // TCP delivers a byte stream: a single read may contain part of a line or several complete lines.
        for ( index = 0; index < length; index++ )
        {
            if ( '\n' == rx_buffer[ index ] )
            {
                app_rx_line[ app_rx_used ] = '\0';
                log_printf( &logger, " <<< TCP echo: %s\r\n", app_rx_line );
                app_rx_used = 0;
                complete = 1;
            }
            else if ( '\r' != rx_buffer[ index ] )
            {
                if ( app_rx_used < CC3100_DATA_SIZE )
                {
                    app_rx_line[ app_rx_used++ ] = ( char ) rx_buffer[ index ];
                }
                else
                {
                    log_error( &logger, " Echo line exceeds the receive buffer." );
                    app_rx_used = 0;
                }
            }
        }
    }

    return complete;
}

// ------------------------------------------------------------------------ END
