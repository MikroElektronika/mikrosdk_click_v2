/*!
 * @file main.c
 * @brief WiFly Click Example.
 *
 * # Description
 * This example demonstrates WiFly Click communication by exchanging numbered messages
 * with the MIKROE echo server over TCP and UDP.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, maps the Click pins, and opens the UART at 9600 baud.
 *
 * ## Application Task
 * Resets and configures the RN-131, displays its firmware and MAC address, and connects to Wi-Fi.
 * It opens a TCP connection, sends a numbered message, verifies the echo, and closes the connection.
 * The same exchange is repeated over UDP, with a two-second pause between transports.
 * A protocol change rejoins the WLAN to apply the new network settings.
 *
 * @note
 * Configure APP_WIFI_SSID and APP_WIFI_PASSWORD for 2.4 GHz Wi-Fi.
 * The network must allow TCP and UDP traffic to 54.187.244.144:51111.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "wifly.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_WIFLY
    #define MIKROBUS_POSITION_WIFLY MIKROBUS_1
#endif

/**
 * @brief WiFly Click example network settings.
 * @details These macros select the WLAN, echo server, and local listening port.
 */
#define APP_WIFI_SSID                   "MIKROE GUEST"
#define APP_WIFI_PASSWORD               "!guest.mikroe!"
#define APP_SERVER_IP                   "54.187.244.144"
#define APP_SERVER_PORT                 51111
#define APP_LOCAL_PORT                  50000

/**
 * @brief WiFly Click example message settings.
 * @details These macros define the message prefix and buffers for a single echo exchange.
 * @note The prefix and a ten-digit packet counter must fit within WIFLY_DATA_SIZE.
 */
#define APP_TEXT_MESSAGE                "Hello from WiFly Click! Packet: "
#define APP_BUFFER_SIZE                 WIFLY_DATA_SIZE

/**
 * @brief WiFly Click example wait limits.
 * @details These macros count ten-millisecond task intervals for echo, transition, and recovery waits.
 * @note Socket and association commands have separate bounded waits in the library.
 */
#define APP_ECHO_WAIT_TICKS             1000
#define APP_TRANSITION_TICKS            200
#define APP_RECOVERY_TICKS              300
#define APP_ECHO_RETRIES                2

/**
 * @brief WiFly Click example stages.
 * @details These values sequence startup, network connection, and alternating TCP/UDP exchanges.
 */
typedef enum
{
    APP_STATE_POWER_UP,
    APP_STATE_CONNECT,
    APP_STATE_OPEN,
    APP_STATE_SEND,
    APP_STATE_RECEIVE,
    APP_STATE_CLOSE,
    APP_STATE_WAIT,
    APP_STATE_RECOVERY

} wifly_app_state_t;

static wifly_t wifly;                           /**< Click context object. */
static log_t logger;                            /**< Logger context object. */
static wifly_app_state_t app_state = APP_STATE_POWER_UP;    /**< Current example stage. */
static uint8_t app_protocol = WIFLY_PROTOCOL_TCP;   /**< Transport used for the next exchange. */
static uint32_t packet_count = 0;               /**< Message number, retained across recovery. */
static char app_tx_message[ APP_BUFFER_SIZE + 1 ]; /**< Message retained for UDP retries. */
static char app_rx_message[ APP_BUFFER_SIZE + 1 ]; /**< Accumulated UART echo. */
static uint16_t app_tx_length = 0;              /**< Expected echo length, excluding terminator. */
static uint16_t app_rx_length = 0;              /**< Number of accumulated echo bytes. */
static uint16_t app_wait_ticks = 0;             /**< Current stage wait counter. */
static uint8_t app_retry_count = 0;             /**< Additional waits or UDP sends for this message. */

/**
 * @brief WiFly Click example stage function.
 * @details This function executes the current example stage and advances its wait counters.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note One stage is executed per application task call.
 */
static err_t wifly_app_run_stage ( wifly_t *ctx );

/**
 * @brief WiFly Click example startup function.
 * @details This function configures the module and displays its firmware version and MAC address.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note Recovery restarts the TCP/UDP sequence without resetting the packet counter.
 */
static err_t wifly_app_power_up ( wifly_t *ctx );

/**
 * @brief WiFly Click example WLAN connection function.
 * @details This function joins the configured WLAN, waits for DHCP, and displays the IP settings.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note The application credentials are not printed to the logger.
 */
static err_t wifly_app_connect ( wifly_t *ctx );

/**
 * @brief WiFly Click example socket opening function.
 * @details This function starts the selected transport and prepares the next numbered message.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note UDP selects a remote destination and local port without a connection handshake.
 */
static err_t wifly_app_open ( wifly_t *ctx );

/**
 * @brief WiFly Click example transmission function.
 * @details This function transmits the prepared message and starts a new echo wait.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note A partial UART transmission error requires recovery instead of blindly resending bytes.
 */
static err_t wifly_app_send ( wifly_t *ctx );

/**
 * @brief WiFly Click example reception function.
 * @details This function assembles the echo and applies bounded retries when no complete reply arrives.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success while waiting or after a valid echo; otherwise a negative #wifly_return_value_t error.
 * @note UDP retries reuse the packet number. TCP retries preserve bytes already received.
 */
static err_t wifly_app_receive ( wifly_t *ctx );

/**
 * @brief WiFly Click example socket closing function.
 * @details This function closes the data session and schedules the next transport after a pause.
 * @param[in,out] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Success or a negative #wifly_return_value_t error.
 * @note The WLAN remains associated until the next protocol change.
 */
static err_t wifly_app_close ( wifly_t *ctx );

/**
 * @brief WiFly Click example reply logging function.
 * @details This function prints module information with terminal-compatible CR/LF line endings.
 * @param[in] ctx : Click context object.
 * See #wifly_t object definition for detailed explanation.
 * @return Nothing.
 * @note Empty lines and the final version prompt are omitted from the log.
 */
static void wifly_app_log_reply ( wifly_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;       /**< Logger config object. */
    wifly_cfg_t wifly_cfg;   /**< Click config object. */

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

    // Module configuration is performed by the first task stage.
    wifly_cfg_setup( &wifly_cfg );
    WIFLY_MAP_MIKROBUS( wifly_cfg, MIKROBUS_POSITION_WIFLY );
    if ( WIFLY_OK != wifly_init( &wifly, &wifly_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag;

    error_flag = wifly_app_run_stage( &wifly );
    if ( WIFLY_OK != error_flag )
    {
        log_error( &logger, " Communication error: %ld", error_flag );
        log_printf( &logger, ">>> Restarting module shortly...\r\n\r\n" );
        app_wait_ticks = 0;
        app_state = APP_STATE_RECOVERY;
    }
    Delay_ms( 10 );
}

int main ( void )
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif

    application_init();
    for ( ; ; )
    {
        application_task();
    }
    return 0;
}

static err_t wifly_app_run_stage ( wifly_t *ctx )
{
    err_t error_flag = WIFLY_OK;

    switch ( app_state )
    {
        case APP_STATE_POWER_UP:
            error_flag = wifly_app_power_up( ctx );
            break;
        case APP_STATE_CONNECT:
            error_flag = wifly_app_connect( ctx );
            break;
        case APP_STATE_OPEN:
            error_flag = wifly_app_open( ctx );
            break;
        case APP_STATE_SEND:
            error_flag = wifly_app_send( ctx );
            break;
        case APP_STATE_RECEIVE:
            error_flag = wifly_app_receive( ctx );
            break;
        case APP_STATE_CLOSE:
            error_flag = wifly_app_close( ctx );
            break;
        case APP_STATE_WAIT:
            if ( ++app_wait_ticks >= APP_TRANSITION_TICKS )
            {
                app_state = APP_STATE_OPEN;
            }
            break;
        case APP_STATE_RECOVERY:
            if ( ++app_wait_ticks >= APP_RECOVERY_TICKS )
            {
                app_state = APP_STATE_POWER_UP;
            }
            break;
        default:
            app_state = APP_STATE_POWER_UP;
            break;
    }
    return error_flag;
}

static err_t wifly_app_power_up ( wifly_t *ctx )
{
    err_t error_flag;

    log_printf( &logger, ">>> Start RN-131 in station mode with DHCP.\r\n" );
    error_flag = wifly_default_cfg( ctx );
    if ( WIFLY_OK == error_flag )
    {
        error_flag = wifly_send_command( ctx, WIFLY_CMD_GET_VERSION, WIFLY_REPLY_PROMPT, WIFLY_COMMAND_TIMEOUT );
    }
    if ( WIFLY_OK == error_flag )
    {
        wifly_app_log_reply( ctx );
        error_flag = wifly_send_command( ctx, WIFLY_CMD_GET_MAC, WIFLY_REPLY_PROMPT, WIFLY_COMMAND_TIMEOUT );
    }
    if ( WIFLY_OK == error_flag )
    {
        wifly_app_log_reply( ctx );
        app_protocol = WIFLY_PROTOCOL_TCP;
        app_state = APP_STATE_CONNECT;
    }
    return error_flag;
}

static err_t wifly_app_connect ( wifly_t *ctx )
{
    err_t error_flag;

    log_printf( &logger, ">>> Connect to Wi-Fi: %s\r\n", ( char * ) APP_WIFI_SSID );
    error_flag = wifly_connect( ctx, APP_WIFI_SSID, APP_WIFI_PASSWORD );
    if ( WIFLY_OK == error_flag )
    {
        wifly_app_log_reply( ctx );
        app_state = APP_STATE_OPEN;
    }
    return error_flag;
}

static err_t wifly_app_open ( wifly_t *ctx )
{
    err_t error_flag;
    uint16_t text_length;
    char *counter_text;

    if ( WIFLY_PROTOCOL_TCP == app_protocol )
    {
        log_printf( &logger, "\r\n>>> Open TCP connection %s:%u.\r\n", ( char * ) APP_SERVER_IP, ( uint16_t ) APP_SERVER_PORT );
    }
    else
    {
        log_printf( &logger, "\r\n>>> Open UDP endpoint %s:%u.\r\n", ( char * ) APP_SERVER_IP, ( uint16_t ) APP_SERVER_PORT );
    }
    error_flag = wifly_open_socket( ctx, app_protocol, APP_SERVER_IP, APP_SERVER_PORT, APP_LOCAL_PORT );
    if ( WIFLY_OK == error_flag )
    {
        // Convert directly into the message tail; no separate counter string is needed.
        strcpy( app_tx_message, APP_TEXT_MESSAGE );
        text_length = strlen( app_tx_message );
        uint32_to_str( ++packet_count, &app_tx_message[ text_length ] );
        counter_text = l_trim( r_trim( &app_tx_message[ text_length ] ) );
        memmove( &app_tx_message[ text_length ], counter_text, strlen( counter_text ) + 1 );
        app_tx_length = strlen( app_tx_message );
        app_retry_count = 0;
        app_state = APP_STATE_SEND;
    }
    return error_flag;
}

static err_t wifly_app_send ( wifly_t *ctx )
{
    err_t error_flag;

    log_printf( &logger, ">>> TX: %s\r\n", app_tx_message );
    app_rx_length = 0;
    app_rx_message[ 0 ] = 0;
    app_wait_ticks = 0;
    error_flag = wifly_send( ctx, ( uint8_t * ) app_tx_message, app_tx_length );
    if ( WIFLY_OK == error_flag )
    {
        app_state = APP_STATE_RECEIVE;
    }
    return error_flag;
}

static err_t wifly_app_receive ( wifly_t *ctx )
{
    err_t error_flag = WIFLY_OK;
    err_t read_size;
    uint16_t leading_bytes;

    // Keep partial TCP bytes between task calls until the full echo is assembled.
    read_size = wifly_receive( ctx, ( uint8_t * ) &app_rx_message[ app_rx_length ],
                               APP_BUFFER_SIZE - app_rx_length );
    if ( read_size < 0 )
    {
        error_flag = read_size;
    }
    else if ( read_size > 0 )
    {
        // Ignore command-mode line endings that can trail EXIT into UDP data mode.
        if ( ( WIFLY_PROTOCOL_UDP == app_protocol ) && ( 0 == app_rx_length ) )
        {
            leading_bytes = 0;
            while ( ( leading_bytes < read_size ) &&
                    ( ( '\r' == app_rx_message[ leading_bytes ] ) ||
                      ( '\n' == app_rx_message[ leading_bytes ] ) ) )
            {
                leading_bytes++;
            }
            if ( leading_bytes )
            {
                read_size -= leading_bytes;
                memmove( app_rx_message, &app_rx_message[ leading_bytes ], read_size );
            }
        }

        if ( read_size > 0 )
        {
            app_rx_length += read_size;
            app_rx_message[ app_rx_length ] = 0;
            if ( app_rx_length >= app_tx_length )
            {
                if ( 0 == memcmp( app_rx_message, app_tx_message, app_tx_length ) )
                {
                    app_rx_message[ app_tx_length ] = 0;
                    log_printf( &logger, "<<< Echo: %s\r\n", app_rx_message );
                    app_state = APP_STATE_CLOSE;
                }
                else if ( ( WIFLY_PROTOCOL_UDP == app_protocol ) &&
                          ( app_retry_count < APP_ECHO_RETRIES ) )
                {
                    app_retry_count++;
                    app_rx_length = 0;
                    app_rx_message[ 0 ] = 0;
                    app_wait_ticks = 0;
                    log_printf( &logger, ">>> UDP echo mismatch. Retry %u of %u.\r\n",
                                ( uint16_t ) app_retry_count, ( uint16_t ) APP_ECHO_RETRIES );
                    app_state = APP_STATE_SEND;
                }
                else
                {
                    error_flag = WIFLY_ERROR_DATA;
                }
            }
            else if ( strstr( app_rx_message, WIFLY_REPLY_CLOSED ) )
            {
                error_flag = WIFLY_ERROR_CLOSED;
            }
        }
    }
    if ( ( WIFLY_OK == error_flag ) && ( APP_STATE_RECEIVE == app_state ) &&
         ( ++app_wait_ticks >= APP_ECHO_WAIT_TICKS ) )
    {
        if ( app_retry_count < APP_ECHO_RETRIES )
        {
            app_retry_count++;
            app_wait_ticks = 0;
            if ( WIFLY_PROTOCOL_UDP == app_protocol )
            {
                log_printf( &logger, ">>> UDP echo timeout. Retry %u of %u.\r\n",
                            ( uint16_t ) app_retry_count, ( uint16_t ) APP_ECHO_RETRIES );
                app_state = APP_STATE_SEND;
            }
            else
            {
                // TCP is a stream. Retain partial bytes and do not inject a duplicate message.
                log_printf( &logger, ">>> Still waiting for TCP echo. Retry %u of %u.\r\n",
                            ( uint16_t ) app_retry_count, ( uint16_t ) APP_ECHO_RETRIES );
            }
        }
        else
        {
            error_flag = WIFLY_TIMEOUT;
        }
    }
    return error_flag;
}

static err_t wifly_app_close ( wifly_t *ctx )
{
    err_t error_flag;

    error_flag = wifly_close_socket( ctx );
    if ( WIFLY_OK == error_flag )
    {
        log_printf( &logger, "<<< Data session closed.\r\n" );
        if ( WIFLY_PROTOCOL_TCP == app_protocol )
        {
            app_protocol = WIFLY_PROTOCOL_UDP;
        }
        else
        {
            app_protocol = WIFLY_PROTOCOL_TCP;
        }
        app_wait_ticks = 0;
        app_state = APP_STATE_WAIT;
    }
    return error_flag;
}

static void wifly_app_log_reply ( wifly_t *ctx )
{
    uint16_t index;
    uint8_t line_started = 0;

    for ( index = 0; index < ctx->response_length; index++ )
    {
        if ( '<' == ctx->response[ index ] )
        {
            break;
        }
        if ( '\n' == ctx->response[ index ] )
        {
            if ( line_started )
            {
                log_printf( &logger, "\r\n" );
                line_started = 0;
            }
        }
        else if ( '\r' != ctx->response[ index ] )
        {
            log_printf( &logger, "%c", ( uint16_t ) ctx->response[ index ] );
            line_started = 1;
        }
    }
    if ( line_started )
    {
        log_printf( &logger, "\r\n" );
    }
}

// ------------------------------------------------------------------------ END
