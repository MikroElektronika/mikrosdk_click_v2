/*!
 * @file main.c
 * @brief WiFi 10 Click Example.
 *
 * # Description
 * This example connects WiFi 10 Click to a Wi-Fi access point, obtains an IPv4 address using DHCP,
 * and exchanges numbered messages with a configurable TCP and UDP echo server.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and driver GPIO/SPI interface.
 *
 * ## Application Task
 * Starts hosted firmware, joins Wi-Fi, obtains an IPv4 address via DHCP, and verifies TCP and UDP echoes.
 * Retries a TCP connect response timeout once and a UDP echo timeout up to twice.
 *
 * @note
 * Set WIFI_SSID, WIFI_PASSWORD, and WIFI_AUTH for a 2.4 GHz access point.
 * WPA2 accepts 8-63 printable ASCII characters or a 64-digit hexadecimal key.
 * For an open network, select WIFI10_AUTH_OPEN and use an empty password.
 * Set REMOTE_IP in dotted-decimal format and REMOTE_PORT for a TCP and UDP echo server.
 * Set COMM SEL to SPI and use QCA4004 hosted firmware with ABI 1.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "wifi10.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_WIFI10
    #define MIKROBUS_POSITION_WIFI10 MIKROBUS_1
#endif

// Set these values for your local network and echo server.
#define WIFI_SSID                   "MIKROE GUEST"
#define WIFI_PASSWORD               "!guest.mikroe!"
#define WIFI_AUTH                   WIFI10_AUTH_WPA2_PSK
#define REMOTE_IP                   "54.187.244.144"
#define REMOTE_PORT                 51111u

// Echo message prefix and buffer capacity for a decimal uint32_t counter and CRLF.
#define APP_TEXT_MESSAGE            "Hello from WiFi 10 Click! Packet: "
#define APP_TEXT_MESSAGE_LENGTH     34u
#define APP_PACKET_COUNTER_DIGITS   10u
#define APP_MESSAGE_LINE_END_SIZE   2u
#define APP_MESSAGE_SIZE            ( APP_TEXT_MESSAGE_LENGTH + APP_PACKET_COUNTER_DIGITS + \
                                      APP_MESSAGE_LINE_END_SIZE + 1u )

// Echo receive and polling limits.
#define ECHO_TIMEOUT                10000ul
#define ECHO_UDP_RETRY_LIMIT        2u
#define ECHO_PAUSE_POLL_MS          10u
#define ECHO_PAUSE_POLLS            500u

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    WIFI10_POWER_UP = 1,
    WIFI10_CONFIGURE_CONNECTION,
    WIFI10_EXAMPLE,
    WIFI10_WAIT

} wifi10_app_state_t;

static wifi10_t wifi10;                                 /**< Click context object. */
static log_t logger;                                    /**< Logger context object. */
static wifi10_app_state_t app_state = WIFI10_POWER_UP;  /**< Current example state. */
static uint16_t pause_count = 0;                        /**< Task polls since the last echo round. */
static uint32_t app_packet_count = 1;                   /**< Number appended to the next echo message. */
static uint8_t tcp_connect_retried = 0;                 /**< 1 after using the current TCP connect retry. */
static uint32_t remote_address;                         /**< Echo server address in host numeric order. */

/**
 * @brief WiFi 10 remote IPv4 address conversion.
 * @details Converts a dotted-decimal address to the host numeric order used by the driver.
 * @param[in] address : Null-terminated IPv4 address string.
 * @return Converted IPv4 address, or 0 if the address is invalid or all zeros.
 */
static uint32_t wifi10_parse_ipv4 ( char *address );

/**
 * @brief WiFi 10 echo exchange.
 * @details Opens a TCP or UDP socket, sends a numbered message, verifies the echo, and closes the socket.
 * @param[in] type : WIFI10_SOCKET_TCP or WIFI10_SOCKET_UDP.
 * @return @li @c 0 - Echo verified and socket closed,
 *         @li @c -2 - TCP connect timed out waiting for a firmware response.
 * See #wifi10_return_value_t definition for detailed explanation.
 * @note TCP replies may arrive in several frames. A UDP receive timeout can trigger a retry on the same socket.
 * Other failures report the operation and stop the example.
 */
static err_t wifi10_example ( uint8_t type );

/**
 * @brief WiFi 10 error reporting.
 * @details Logs the failed operation and stops without automatically retrying a pending device command.
 * @param[in] operation : Failed operation description.
 * @param[in] result : Driver error value.
 * @return Nothing.
 * @note Restart only after resolving the reported failure.
 */
static void wifi10_stop ( char *operation, err_t result );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifi10_cfg_t wifi10_cfg;  /**< Click config object. */
    err_t result;

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
    wifi10_cfg_setup( &wifi10_cfg );
    WIFI10_MAP_MIKROBUS( wifi10_cfg, MIKROBUS_POSITION_WIFI10 );
    result = wifi10_init( &wifi10, &wifi10_cfg );
    if ( ( SPI_MASTER_ERROR == result ) || ( WIFI10_ERROR == result ) )
    {
        wifi10_stop( "Communication init", result );
    }

    remote_address = wifi10_parse_ipv4( REMOTE_IP );
    if ( 0ul == remote_address )
    {
        log_error( &logger, " Invalid REMOTE_IP. Use a nonzero IPv4 address in dotted-decimal format." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\r\n" );
}

void application_task ( void )
{
    wifi10_ip_cfg_t ip;
    err_t result = WIFI10_OK;

    switch ( app_state )
    {
        case WIFI10_POWER_UP:
        {
            result = wifi10_default_cfg( &wifi10 );
            if ( WIFI10_OK != result )
            {
                wifi10_stop( "Firmware setup", result );
            }
            log_printf( &logger, "Firmware: 0x%.2X%.2X%.2X%.2X\r\n",
                        ( uint16_t ) ( wifi10.state.firmware_version >> 24 ),
                        ( uint16_t ) ( ( wifi10.state.firmware_version >> 16 ) & 0xFFul ),
                        ( uint16_t ) ( ( wifi10.state.firmware_version >> 8 ) & 0xFFul ),
                        ( uint16_t ) ( wifi10.state.firmware_version & 0xFFul ) );
            log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                        ( uint16_t ) wifi10.state.mac[ 0 ], ( uint16_t ) wifi10.state.mac[ 1 ],
                        ( uint16_t ) wifi10.state.mac[ 2 ], ( uint16_t ) wifi10.state.mac[ 3 ],
                        ( uint16_t ) wifi10.state.mac[ 4 ], ( uint16_t ) wifi10.state.mac[ 5 ] );
            app_state = WIFI10_CONFIGURE_CONNECTION;
            log_printf( &logger, "\r\n>>> APP STATE - CONFIGURE CONNECTION <<<\r\n\r\n" );
            break;
        }
        case WIFI10_CONFIGURE_CONNECTION:
        {
            log_info( &logger, " Connecting to access point..." );
            result = wifi10_connect( &wifi10, WIFI_SSID, WIFI_PASSWORD, WIFI_AUTH );
            if ( WIFI10_OK != result )
            {
                if ( ( WIFI10_ERROR_TIMEOUT == result ) && wifi10.state.associated )
                {
                    wifi10_stop( "WPA2 handshake", result );
                }
                else
                {
                    wifi10_stop( "Wi-Fi association", result );
                }
            }
            log_info( &logger, " Associated. Waiting for DHCP..." );
            result = wifi10_dhcp( &wifi10, &ip );
            if ( WIFI10_OK != result )
            {
                wifi10_stop( "DHCP", result );
            }
            log_printf( &logger, "IPv4: %u.%u.%u.%u\r\n",
                        ( uint16_t ) ( ip.address >> 24 ),
                        ( uint16_t ) ( ( ip.address >> 16 ) & 0xFFul ),
                        ( uint16_t ) ( ( ip.address >> 8 ) & 0xFFul ),
                        ( uint16_t ) ( ip.address & 0xFFul ) );
            app_state = WIFI10_EXAMPLE;
            log_printf( &logger, "\r\n>>> APP STATE - EXAMPLE <<<\r\n" );
            break;
        }
        case WIFI10_EXAMPLE:
        {
            result = wifi10_example( WIFI10_SOCKET_TCP );
            if ( WIFI10_ERROR_TIMEOUT == result )
            {
                if ( tcp_connect_retried )
                {
                    wifi10_stop( "TCP connect retry", result );
                }

                tcp_connect_retried = 1;
                log_warning( &logger, " TCP connect response timed out. Resetting the module for one retry." );
                // Reset clears the outstanding socket command before the example opens another socket.
                result = wifi10_hw_reset( &wifi10 );
                if ( WIFI10_OK != result )
                {
                    wifi10_stop( "Hardware reset", result );
                }
                app_state = WIFI10_POWER_UP;
                log_printf( &logger, "\r\n>>> APP STATE - POWER UP <<<\r\n\r\n" );
                break;
            }
            tcp_connect_retried = 0;
            wifi10_example( WIFI10_SOCKET_UDP );
            pause_count = 0;
            app_state = WIFI10_WAIT;
            break;
        }
        case WIFI10_WAIT:
        {
            result = wifi10_process( &wifi10 );
            if ( WIFI10_OK != result )
            {
                wifi10_stop( "Firmware event", result );
            }
            if ( 0u == wifi10.state.connected )
            {
                wifi10_stop( "Wi-Fi disconnected", WIFI10_ERROR_DISCONNECTED );
            }
            Delay_ms( ECHO_PAUSE_POLL_MS );
            pause_count++;
            if ( pause_count >= ECHO_PAUSE_POLLS )
            {
                app_state = WIFI10_EXAMPLE;
            }
            break;
        }
        default:
        {
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

static uint32_t wifi10_parse_ipv4 ( char *address )
{
    uint32_t ipv4 = 0;

    for ( uint8_t index = 0; index < 4u; index++ )
    {
        uint16_t octet = 0;
        uint8_t digits = 0;

        while ( ( digits < 3u ) && ( *address >= '0' ) && ( *address <= '9' ) )
        {
            octet = 10u * octet + ( uint8_t ) ( *address - '0' );
            address++;
            digits++;
        }
        if ( ( 0u == digits ) || ( octet > 255u ) ||
             ( ( index < 3u ) && ( '.' != *address ) ) || ( ( 3u == index ) && ( '\0' != *address ) ) )
        {
            ipv4 = 0;
            break;
        }

        ipv4 = ( ipv4 << 8 ) | octet;
        if ( index < 3u )
        {
            address++;
        }
    }

    return ipv4;
}

static err_t wifi10_example ( uint8_t type )
{
    char message[ APP_MESSAGE_SIZE ] = APP_TEXT_MESSAGE;
    char reply[ APP_MESSAGE_SIZE ];
    char *counter_text = &message[ APP_TEXT_MESSAGE_LENGTH ];
    char *protocol = "TCP";
    char *operation = "Socket open";
    uint16_t received = 0;
    uint16_t total = 0;
    uint16_t expected;
    uint8_t connect_timeout = 0;
    int32_t handle = 0;
    err_t close_result;
    err_t result;

    uint32_to_str( app_packet_count, counter_text );
    l_trim( counter_text );
    r_trim( counter_text );
    strcat( message, "\r\n" );
    expected = ( uint16_t ) strlen( message );

    if ( WIFI10_SOCKET_UDP == type )
    {
        protocol = "UDP";
    }
    log_printf( &logger, "\r\n>>> Open %s socket %s:%u.\r\n", protocol, REMOTE_IP, ( uint16_t ) REMOTE_PORT );
    result = wifi10_socket_open( &wifi10, type, &handle );

    if ( ( WIFI10_OK == result ) && ( WIFI10_SOCKET_TCP == type ) )
    {
        operation = "TCP connect";
        result = wifi10_socket_connect( &wifi10, handle, remote_address, REMOTE_PORT );
        connect_timeout = ( WIFI10_ERROR_TIMEOUT == result ) && wifi10.state.response_pending;
    }
    for ( uint8_t retry = 0; WIFI10_OK == result; retry++ )
    {
        operation = "Echo send";
        if ( WIFI10_SOCKET_TCP == type )
        {
            result = wifi10_socket_send( &wifi10, handle, ( uint8_t * ) message, expected );
        }
        else
        {
            result = wifi10_socket_sendto( &wifi10, handle, ( uint8_t * ) message, expected, remote_address, REMOTE_PORT );
        }
        if ( WIFI10_OK != result )
        {
            break;
        }
        log_printf( &logger, ">>> TX: %s", message );

        operation = "Echo receive";
        while ( ( WIFI10_OK == result ) && ( total < expected ) )
        {
            result = wifi10_socket_recv( &wifi10, handle, ( uint8_t * ) reply + total, expected + 1u - total,
                                        &received, ECHO_TIMEOUT );
            total += received;
            if ( ( WIFI10_OK == result ) && ( WIFI10_SOCKET_UDP == type ) )
            {
                for ( uint8_t index = 0; index < WIFI10_MAX_SOCKETS; index++ )
                {
                    if ( wifi10.state.sockets[ index ].handle == handle )
                    {
                        if ( ( wifi10.state.sockets[ index ].peer_address != remote_address ) ||
                             ( wifi10.state.sockets[ index ].peer_port != REMOTE_PORT ) )
                        {
                            result = WIFI10_ERROR_PROTOCOL;
                        }
                        break;
                    }
                }
                break;
            }
        }
        if ( ( WIFI10_SOCKET_UDP == type ) && ( WIFI10_ERROR_TIMEOUT == result ) &&
             ( WIFI10_OK == wifi10.state.fault ) && ( retry < ECHO_UDP_RETRY_LIMIT ) )
        {
            log_printf( &logger, ">>> UDP echo timeout. Resending packet, retry %u/%u.\r\n",
                        ( uint16_t ) ( retry + 1u ), ( uint16_t ) ECHO_UDP_RETRY_LIMIT );
            result = WIFI10_OK;
        }
        else
        {
            break;
        }
    }
    if ( ( WIFI10_OK == result ) && ( ( total != expected ) || ( 0 != memcmp( reply, message, expected ) ) ) )
    {
        operation = "Echo validation";
        result = WIFI10_ERROR_PROTOCOL;
    }
    if ( WIFI10_OK == result )
    {
        reply[ total ] = 0;
        log_printf( &logger, "<<< Echo: %s", reply );
        app_packet_count++;
    }
    if ( ( handle > 0 ) && ( WIFI10_OK == wifi10.state.fault ) )
    {
        close_result = wifi10_socket_close( &wifi10, handle );
        if ( WIFI10_OK == result )
        {
            operation = "Socket close";
            result = close_result;
        }
    }
    if ( ( WIFI10_OK != result ) && ( 0u == connect_timeout ) )
    {
        wifi10_stop( operation, result );
    }

    return result;
}

static void wifi10_stop ( char *operation, err_t result )
{
    log_error( &logger, "%s failed (%d).", operation, ( int16_t ) result );
    if ( ( WIFI10_ERROR_TIMEOUT == result ) && wifi10.state.response_pending )
    {
        log_printf( &logger, "Timed out waiting for the firmware socket response.\r\n" );
    }
    if ( ( WIFI10_ERROR_PROTOCOL == result ) && ( NULL != wifi10.state.protocol_fault ) )
    {
        log_printf( &logger, "Protocol fault in %s (detail 0x%.4X).\r\n",
                    wifi10.state.protocol_fault, ( uint16_t ) wifi10.state.protocol_detail );
    }
    if ( wifi10.state.command_error )
    {
        log_printf( &logger, "Rejected command: 0x%.4X, reason: %u\r\n",
                    ( uint16_t ) wifi10.state.command_error, ( uint16_t ) wifi10.state.command_reason );
    }
    else if ( ( WIFI10_ERROR_COMMAND == result ) && wifi10.state.response_ready && wifi10.state.response_result )
    {
        uint32_t status = ( uint32_t ) wifi10.state.response_result;
        log_printf( &logger, "Socket command status: 0x%.4X%.4X\r\n",
                    ( uint16_t ) ( status >> 16 ), ( uint16_t ) status );
    }
    if ( wifi10.state.disconnect_reason )
    {
        log_printf( &logger, "Disconnect reason: %u\r\n", ( uint16_t ) wifi10.state.disconnect_reason );
    }
    for ( ; ; );
}

// ------------------------------------------------------------------------ END
