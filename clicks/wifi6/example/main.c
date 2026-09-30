/*!
 * @file main.c
 * @brief WiFi 6 Click Example.
 *
 * # Description
 * This example demonstrates WiFi 6 Click communication by exchanging numbered messages
 * with the MIKROE echo server over TCP and UDP.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, maps the Click pins, and opens the UART with software RTS/CTS flow control.
 *
 * ## Application Task
 * Resets the WF121, displays its firmware and MAC address, connects to the configured WLAN,
 * and waits for DHCP. It then opens a TCP connection, sends a numbered message, verifies its echo,
 * and closes the connection. The same exchange is repeated over UDP before returning to TCP.
 * Partial TCP responses are assembled; eligible application-level wait timeouts receive bounded retries.
 *
 * @note
 * Set APP_WIFI_SSID and APP_WIFI_PASSWORD for a 2.4 GHz WLAN with Internet access.
 * Use an empty password for an open network. Set all four IO SEL jumpers to UART (positions 1-2).
 * The module must run WF121 BGAPI firmware on UART2 at 115200 baud, 8 data bits, no parity,
 * and one stop bit, with RTS/CTS enabled. This example uses binary BGAPI commands, not AT commands.
 * Module CTS is driven through MikroBUS INT; module RTS is read through MikroBUS CS.
 * Module reset is not connected to MikroBUS RST, so the driver uses a BGAPI software reset.
 * Connect the logger to a UART peripheral different from the one used by WiFi 6 Click.
 * The network must allow TCP and UDP traffic to 54.187.244.144:51111. A one-second pause separates
 * exchanges. UDP does not guarantee delivery, and messages are unencrypted; do not send sensitive data.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "wifi6.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_WIFI6
    #define MIKROBUS_POSITION_WIFI6 MIKROBUS_1
#endif

/**
 * @brief WiFi 6 Click example network settings.
 * @details These macros select the WLAN, remote echo server, and local UDP listening port.
 */
#define APP_WIFI_SSID                   "MIKROE GUEST"
#define APP_WIFI_PASSWORD               "!guest.mikroe!"
#define APP_SERVER_IP                   54, 187, 244, 144
#define APP_SERVER_PORT                 51111
#define APP_LOCAL_PORT                  50000

/**
 * @brief WiFi 6 Click example message settings.
 * @details The text prefix is 33 characters excluding its null terminator, followed by the decimal
 * counter and CRLF. Buffer capacity allows the maximum uint32_t decimal width, both line-ending
 * bytes, and the terminating null byte.
 */
#define APP_TEXT_MESSAGE                "Hello from WiFi 6 Click! Packet: "
#define APP_TEXT_MESSAGE_LENGTH         33
#define APP_PACKET_COUNTER_MAX_DIGITS   10
#define APP_MESSAGE_LINE_END_SIZE       2
#define APP_MESSAGE_SIZE                ( APP_TEXT_MESSAGE_LENGTH + APP_PACKET_COUNTER_MAX_DIGITS + \
                                          APP_MESSAGE_LINE_END_SIZE + 1 )

/**
 * @brief WiFi 6 Click example timing settings.
 * @details These macros define the task interval, network and TX/RX wait budgets, transition pause,
 * and recovery pause in task ticks. Driver processing and logging add to the elapsed time.
 */
#define APP_TASK_INTERVAL_MS            10
#define APP_WAIT_IP_TIMEOUT_TICKS       5000
#define APP_WAIT_TXRX_TIMEOUT_TICKS     500
#define APP_WAIT_LOG_TICKS              2000
#define APP_TRANSITION_TICKS            300
#define APP_RECOVERY_TICKS              300

/**
 * @brief WiFi 6 Click example retry settings.
 * @details These limits bound retries for an inactive TX endpoint and missing echoes before recovery.
 */
#define APP_TX_RETRY_LIMIT              2
#define APP_RX_RETRY_LIMIT              2

/**
 * @brief WiFi 6 Click example application states.
 * @details These states sequence module startup, Wi-Fi connection, TCP/UDP exchanges, and recovery.
 */
typedef enum
{
    APP_STATE_POWER_UP,       /**< Reset and configure the module. */
    APP_STATE_CONNECT_WIFI,   /**< Request association with the access point. */
    APP_STATE_WAIT_IP,        /**< Wait for the interface and DHCP events. */
    APP_STATE_OPEN_SOCKET,    /**< Open TCP or paired UDP endpoints. */
    APP_STATE_SEND_MESSAGE,   /**< Send the next numbered message. */
    APP_STATE_WAIT_ECHO,      /**< Collect and verify the echo. */
    APP_STATE_CLOSE_SOCKET,   /**< Release all endpoints for this exchange. */
    APP_STATE_TRANSITION,     /**< Pause before changing transport. */
    APP_STATE_RECOVERY        /**< Wait before resetting after an error. */

} app_state_t;

static wifi6_t wifi6;                                   /**< WiFi 6 Click context object. */
static log_t logger;                                    /**< Logger context object. */
static app_state_t app_state = APP_STATE_POWER_UP;      /**< Current application stage. */
static uint8_t app_protocol = WIFI6_PROTOCOL_TCP;       /**< Transport selected for the next exchange. */
static uint8_t app_server_ip[ 4 ] = { APP_SERVER_IP };  /**< Echo server IPv4 address. */
static uint32_t app_packet_count = 1;                   /**< Number appended to the next new message. */
static uint16_t app_wait_ticks = 0;                     /**< Elapsed task ticks in the current wait stage. */
static char app_tx_message[ APP_MESSAGE_SIZE ];         /**< Staged TX payload for retry and comparison. */
static char app_rx_message[ APP_MESSAGE_SIZE ];         /**< RX echo buffer including terminator space. */
static uint16_t app_tx_length = 0;                      /**< Transmitted bytes, excluding the null byte. */
static uint16_t app_rx_length = 0;                      /**< Echo bytes collected so far. */
static uint8_t app_tx_accepted = 0;                     /**< Current message was accepted by the module. */
static uint8_t app_tx_retry_count = 0;                  /**< TX wait retries for the current message. */
static uint8_t app_rx_retry_count = 0;                  /**< Echo wait retries for the current message. */
static uint8_t app_retryable_timeout = 0;               /**< Example TX/RX wait expired; retry is safe. */

/**
 * @brief WiFi 6 Click application stage dispatcher function.
 * @details This function calls the handler for the current application stage.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Stage continues or completes,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Exactly one stage is executed per application task call.
 */
static err_t wifi6_app_run_stage ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click startup function.
 * @details This function resets the module, configures station mode and DHCP, and displays its identity.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Startup completed,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Module readiness is confirmed by BGAPI events rather than a fixed boot delay.
 */
static err_t wifi6_app_power_up ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click WLAN connection function.
 * @details This function submits the configured credentials and advances to the network wait stage.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Connection requested,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note An accepted request does not confirm association or DHCP completion.
 */
static err_t wifi6_app_connect_wifi ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click network wait function.
 * @details This function processes events until the interface is up and an IPv4 address is available.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Waiting or network ready,
 *         @li @c <0 - Error or timeout.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note The interface and DHCP events can arrive in either order.
 */
static err_t wifi6_app_wait_ip ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click echo socket opening function.
 * @details This function opens and waits for the endpoints required by the selected transport.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Socket ready,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note UDP requires a listener and a transmit endpoint bound to the same local port.
 */
static err_t wifi6_app_open_socket ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click message transmission function.
 * @details This function appends the packet counter to the text and sends it to the echo server.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Sent or waiting for endpoint readiness,
 *         @li @c <0 - Error or timeout.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note The counter advances only after the module accepts the message.
 */
static err_t wifi6_app_send_message ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click echo reception function.
 * @details This function collects the response and checks its length and contents against the sent message.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Waiting or echo verified,
 *         @li @c <0 - Error or timeout.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note TCP is a byte stream; several receives can be needed for one complete message.
 */
static err_t wifi6_app_wait_echo ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click echo socket closing function.
 * @details This function releases the TCP endpoint or both UDP endpoints after a verified echo.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Socket closed,
 *         @li @c <0 - Error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note A pause follows before the next transport is selected.
 */
static err_t wifi6_app_close_socket ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click protocol transition function.
 * @details This function continues event processing during the pause, then switches TCP and UDP.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Waiting or transition completed,
 *         @li @c <0 - Communication or network error.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Regular polling prevents module notifications from remaining paused for the entire interval.
 */
static err_t wifi6_app_transition ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click recovery function.
 * @details This function waits before starting another module reset and configuration sequence.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @return @li @c 0 - Waiting or recovery delay completed.
 * See #wifi6_return_value_t definition for detailed explanation.
 * @note Protocol processing resumes after reset, since a failed transaction can leave an incomplete frame.
 */
static err_t wifi6_app_recovery ( wifi6_t *ctx );

/**
 * @brief WiFi 6 Click application retry function.
 * @details This function retries timed-out transmissions and echo waits before module recovery.
 * @param[in,out] ctx : Click context object.
 * See #wifi6_t object definition for detailed explanation.
 * @param[in] error_flag : Error returned by the current application stage.
 * @return @li @c 1 - Retry scheduled,
 *         @li @c 0 - No retry scheduled.
 * @note UDP echo retries retransmit the same packet number; TCP retries continue waiting for data.
 */
static uint8_t wifi6_app_retry ( wifi6_t *ctx, err_t error_flag );

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    wifi6_cfg_t wifi6_cfg;  /**< Click config object. */

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

    // Click initialization; module startup is handled by the first task stage.
    wifi6_cfg_setup( &wifi6_cfg );
    WIFI6_MAP_MIKROBUS( wifi6_cfg, MIKROBUS_POSITION_WIFI6 );
    if ( WIFI6_OK != wifi6_init( &wifi6, &wifi6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag;

    // Distinguish application wait expiry from a driver timeout while reading a BGAPI frame.
    app_retryable_timeout = 0;
    error_flag = wifi6_app_run_stage( &wifi6 );

    if ( ( WIFI6_OK != error_flag ) && !wifi6_app_retry( &wifi6, error_flag ) )
    {
        log_error( &logger, " Communication error: %ld | Module result: %.4X",
                   error_flag, wifi6.module_error );
        log_printf( &logger, ">>> Restarting module shortly...\r\n\r\n" );
        app_wait_ticks = 0;
        app_state = APP_STATE_RECOVERY;
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

static err_t wifi6_app_run_stage ( wifi6_t *ctx )
{
    err_t error_flag = WIFI6_ARGUMENT_ERROR;

    switch ( app_state )
    {
        case APP_STATE_POWER_UP:
            error_flag = wifi6_app_power_up( ctx );
            break;
        case APP_STATE_CONNECT_WIFI:
            error_flag = wifi6_app_connect_wifi( ctx );
            break;
        case APP_STATE_WAIT_IP:
            error_flag = wifi6_app_wait_ip( ctx );
            break;
        case APP_STATE_OPEN_SOCKET:
            error_flag = wifi6_app_open_socket( ctx );
            break;
        case APP_STATE_SEND_MESSAGE:
            error_flag = wifi6_app_send_message( ctx );
            break;
        case APP_STATE_WAIT_ECHO:
            error_flag = wifi6_app_wait_echo( ctx );
            break;
        case APP_STATE_CLOSE_SOCKET:
            error_flag = wifi6_app_close_socket( ctx );
            break;
        case APP_STATE_TRANSITION:
            error_flag = wifi6_app_transition( ctx );
            break;
        case APP_STATE_RECOVERY:
            error_flag = wifi6_app_recovery( ctx );
            break;
        default:
            break;
    }
    return error_flag;
}

static err_t wifi6_app_power_up ( wifi6_t *ctx )
{
    err_t error_flag;

    log_printf( &logger, ">>> Start WF121 in station mode with DHCP.\r\n" );
    error_flag = wifi6_default_cfg( ctx );
    if ( WIFI6_OK == error_flag )
    {
        log_printf( &logger, "Firmware: %u.%u.%u.%u\r\n", ctx->version.major, ctx->version.minor,
                    ctx->version.patch, ctx->version.build );
        log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                    ( uint16_t ) ctx->mac[ 0 ], ( uint16_t ) ctx->mac[ 1 ], ( uint16_t ) ctx->mac[ 2 ],
                    ( uint16_t ) ctx->mac[ 3 ], ( uint16_t ) ctx->mac[ 4 ], ( uint16_t ) ctx->mac[ 5 ] );
        app_tx_length = 0;
        app_rx_length = 0;
        app_tx_accepted = 0;
        app_tx_retry_count = 0;
        app_rx_retry_count = 0;
        app_protocol = WIFI6_PROTOCOL_TCP;
        app_state = APP_STATE_CONNECT_WIFI;
    }
    return error_flag;
}

static err_t wifi6_app_connect_wifi ( wifi6_t *ctx )
{
    err_t error_flag;

    log_printf( &logger, ">>> Connect to Wi-Fi: %s\r\n", APP_WIFI_SSID );
    error_flag = wifi6_connect( ctx, APP_WIFI_SSID, APP_WIFI_PASSWORD );
    if ( WIFI6_OK == error_flag )
    {
        app_wait_ticks = 0;
        app_state = APP_STATE_WAIT_IP;
    }
    return error_flag;
}

static err_t wifi6_app_wait_ip ( wifi6_t *ctx )
{
    err_t error_flag = wifi6_process( ctx );

    if ( error_flag >= 0 )
    {
        error_flag = WIFI6_OK;
        if ( ctx->network.up && ctx->network.ip_acquired )
        {
            log_printf( &logger, "IP: %u.%u.%u.%u\r\n",
                        ( uint16_t ) ctx->network.ip[ 0 ], ( uint16_t ) ctx->network.ip[ 1 ],
                        ( uint16_t ) ctx->network.ip[ 2 ], ( uint16_t ) ctx->network.ip[ 3 ] );
            app_state = APP_STATE_OPEN_SOCKET;
        }
        else
        {
            if ( 0 == ( app_wait_ticks % APP_WAIT_LOG_TICKS ) )
            {
                log_printf( &logger, ">>> Waiting for Wi-Fi connection and DHCP address...\r\n" );
            }
            if ( ++app_wait_ticks >= APP_WAIT_IP_TIMEOUT_TICKS )
            {
                error_flag = WIFI6_TIMEOUT;
            }
        }
    }
    return error_flag;
}

static err_t wifi6_app_open_socket ( wifi6_t *ctx )
{
    err_t error_flag;

    if ( WIFI6_PROTOCOL_TCP == app_protocol )
    {
        log_printf( &logger, "\r\n>>> Open TCP connection " );
    }
    else
    {
        log_printf( &logger, "\r\n>>> Open UDP endpoints " );
    }
    log_printf( &logger, "%u.%u.%u.%u:%u.\r\n", ( uint16_t ) app_server_ip[ 0 ], ( uint16_t ) app_server_ip[ 1 ],
                ( uint16_t ) app_server_ip[ 2 ], ( uint16_t ) app_server_ip[ 3 ], APP_SERVER_PORT );
    error_flag = wifi6_open_socket( ctx, app_protocol, APP_LOCAL_PORT, app_server_ip, APP_SERVER_PORT );
    if ( WIFI6_OK == error_flag )
    {
        app_wait_ticks = 0;
        app_rx_length = 0;
        app_state = APP_STATE_SEND_MESSAGE;
    }
    return error_flag;
}

static err_t wifi6_app_send_message ( wifi6_t *ctx )
{
    char *counter_text;
    err_t error_flag;

    // Keep the same payload through send retries and UDP echo retransmissions.
    if ( !app_tx_length )
    {
        strcpy( app_tx_message, APP_TEXT_MESSAGE );
        counter_text = &app_tx_message[ APP_TEXT_MESSAGE_LENGTH ];
        uint32_to_str( app_packet_count, counter_text );
        l_trim( counter_text );
        r_trim( counter_text );
        strcat( app_tx_message, "\r\n" );
        app_tx_length = strlen( app_tx_message );
        app_rx_length = 0;
        app_tx_accepted = 0;
        app_tx_retry_count = 0;
        app_rx_retry_count = 0;
    }

    error_flag = wifi6_send( ctx, ( uint8_t * ) app_tx_message, app_tx_length );
    if ( WIFI6_NO_DATA == error_flag )
    {
        if ( ++app_wait_ticks >= APP_WAIT_TXRX_TIMEOUT_TICKS )
        {
            app_retryable_timeout = 1;
            error_flag = WIFI6_TIMEOUT;
        }
        else
        {
            error_flag = WIFI6_OK;
        }
    }
    else if ( WIFI6_OK == error_flag )
    {
        log_printf( &logger, ">>> TX: %s", app_tx_message );
        if ( !app_tx_accepted )
        {
            app_packet_count++;
            app_tx_accepted = 1;
        }
        app_tx_retry_count = 0;
        app_wait_ticks = 0;
        app_state = APP_STATE_WAIT_ECHO;
    }
    return error_flag;
}

static err_t wifi6_app_wait_echo ( wifi6_t *ctx )
{
    wifi6_packet_t packet;
    err_t error_flag;

    // Leave room for a null terminator while accumulating a possibly fragmented TCP echo.
    error_flag = wifi6_receive( ctx, ( uint8_t * ) &app_rx_message[ app_rx_length ],
                                sizeof( app_rx_message ) - 1 - app_rx_length, &packet );
    if ( error_flag >= 0 )
    {
        if ( WIFI6_OK == error_flag )
        {
            app_rx_length += packet.length;
            if ( ( app_rx_length > app_tx_length ) ||
                 ( ( WIFI6_PROTOCOL_UDP == app_protocol ) && ( app_rx_length != app_tx_length ) ) ||
                 memcmp( app_rx_message, app_tx_message, app_rx_length ) )
            {
                log_error( &logger, " Echo does not match the transmitted message." );
                error_flag = WIFI6_PROTOCOL_ERROR;
            }
            else if ( app_rx_length == app_tx_length )
            {
                app_rx_message[ app_rx_length ] = 0;
                log_printf( &logger, "<<< Echo: %s", app_rx_message );
                app_tx_length = 0;
                app_rx_length = 0;
                app_tx_accepted = 0;
                app_tx_retry_count = 0;
                app_rx_retry_count = 0;
                app_state = APP_STATE_CLOSE_SOCKET;
            }
        }
        if ( error_flag >= 0 )
        {
            if ( APP_STATE_WAIT_ECHO == app_state &&
                 ++app_wait_ticks >= APP_WAIT_TXRX_TIMEOUT_TICKS )
            {
                app_retryable_timeout = 1;
                error_flag = WIFI6_TIMEOUT;
            }
            else
            {
                error_flag = WIFI6_OK;
            }
        }
    }
    return error_flag;
}

static err_t wifi6_app_close_socket ( wifi6_t *ctx )
{
    err_t error_flag = wifi6_close_socket( ctx );

    if ( WIFI6_OK == error_flag )
    {
        log_printf( &logger, ">>> Socket closed.\r\n" );
        app_wait_ticks = 0;
        app_state = APP_STATE_TRANSITION;
    }
    return error_flag;
}

static err_t wifi6_app_transition ( wifi6_t *ctx )
{
    err_t error_flag = wifi6_process( ctx );

    if ( error_flag >= 0 )
    {
        error_flag = WIFI6_OK;
        if ( !ctx->network.up || !ctx->network.ip_acquired )
        {
            error_flag = WIFI6_CLOSED;
        }
        else if ( ++app_wait_ticks >= APP_TRANSITION_TICKS )
        {
            if ( WIFI6_PROTOCOL_TCP == app_protocol )
            {
                app_protocol = WIFI6_PROTOCOL_UDP;
            }
            else
            {
                app_protocol = WIFI6_PROTOCOL_TCP;
            }
            app_state = APP_STATE_OPEN_SOCKET;
        }
    }
    return error_flag;
}

static err_t wifi6_app_recovery ( wifi6_t *ctx )
{
    // Stop module output while waiting; reset will discard the old UART and protocol state.
    digital_out_high( &ctx->cts );
    if ( ++app_wait_ticks >= APP_RECOVERY_TICKS )
    {
        app_state = APP_STATE_POWER_UP;
    }
    return WIFI6_OK;
}

static uint8_t wifi6_app_retry ( wifi6_t *ctx, err_t error_flag )
{
    uint8_t retry_scheduled = 0;

    if ( ( WIFI6_TIMEOUT == error_flag ) && app_retryable_timeout &&
         ctx->network.up && ctx->network.ip_acquired &&
         ( WIFI6_ENDPOINT_INVALID != ctx->tx_endpoint ) )
    {
        if ( APP_STATE_SEND_MESSAGE == app_state )
        {
            if ( app_tx_retry_count < APP_TX_RETRY_LIMIT )
            {
                app_tx_retry_count++;
                app_wait_ticks = 0;
                log_printf( &logger, ">>> TX timeout; retry %u/%u.\r\n",
                            ( uint16_t ) app_tx_retry_count, ( uint16_t ) APP_TX_RETRY_LIMIT );
                retry_scheduled = 1;
            }
        }
        else if ( APP_STATE_WAIT_ECHO == app_state )
        {
            if ( app_rx_retry_count < APP_RX_RETRY_LIMIT )
            {
                app_rx_retry_count++;
                app_wait_ticks = 0;
                if ( WIFI6_PROTOCOL_UDP == app_protocol )
                {
                    app_rx_length = 0;
                    app_state = APP_STATE_SEND_MESSAGE;
                    log_printf( &logger, ">>> UDP echo timeout; retransmit same packet, retry %u/%u.\r\n",
                                ( uint16_t ) app_rx_retry_count, ( uint16_t ) APP_RX_RETRY_LIMIT );
                }
                else
                {
                    log_printf( &logger, ">>> Echo timeout; retry receive, %u/%u.\r\n",
                                ( uint16_t ) app_rx_retry_count, ( uint16_t ) APP_RX_RETRY_LIMIT );
                }
                retry_scheduled = 1;
            }
        }
    }
    return retry_scheduled;
}

// ------------------------------------------------------------------------ END
