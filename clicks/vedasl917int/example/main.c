/*!
 * @file main.c
 * @brief Veda SL917 INT Click example
 *
 * # Description
 * This example demonstrates the use of Veda SL917 INT Click board by exchanging
 * numbered messages with an echo server over TCP and UDP.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 * Displays the firmware version and MAC address. Joins the configured Wi-Fi network and obtains an IPv4 address.
 *
 * ## Application Task
 * Sends a message over TCP and verifies the echo. Repeats the exchange over UDP,
 * then waits before starting the next pair of exchanges.
 * If the firmware reports no TCP listener, logs the status and attempts UDP.
 *
 * @note
 * Set APP_WLAN_SSID, APP_WLAN_AUTH, and APP_WLAN_PSK for your 2.4 GHz network.
 * Set APP_SERVER_IP and APP_SERVER_PORT if you use a different echo server.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vedasl917int.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_VEDASL917INT
    #define MIKROBUS_POSITION_VEDASL917INT MIKROBUS_1
#endif

/**
 * @brief Veda SL917 INT WLAN settings.
 * @details SSID, authentication mode, and WPA2 passphrase. Leave the passphrase empty for open Wi-Fi.
 */
#define APP_WLAN_SSID                   "MIKROE GUEST"
#define APP_WLAN_AUTH                   VEDASL917INT_WIFI_WPA2
#define APP_WLAN_PSK                    "!guest.mikroe!"

/**
 * @brief Veda SL917 INT echo server settings.
 * @details IPv4 address as four comma-separated octets and the common TCP and UDP port.
 */
#define APP_SERVER_IP                   54, 187, 244, 144
#define APP_SERVER_PORT                 51111u
#define APP_LOCAL_PORT                  0

/**
 * @brief Veda SL917 INT echo message settings.
 * @details The buffer holds the text prefix, a 32-bit decimal packet number, CRLF, and a null terminator.
 */
#define APP_TEXT_MESSAGE                "Hello from Veda SL917 INT Click! Packet: "
#define APP_TEXT_MESSAGE_LENGTH         41
#define APP_PACKET_COUNTER_MAX_DIGITS   10
#define APP_MESSAGE_LINE_END_SIZE       2
#define APP_MESSAGE_SIZE                ( APP_TEXT_MESSAGE_LENGTH + APP_PACKET_COUNTER_MAX_DIGITS + \
                                          APP_MESSAGE_LINE_END_SIZE + 1 )

/**
 * @brief Veda SL917 INT echo wait settings.
 * @details Receive limits count roughly 1 ms polls. The pause is in milliseconds.
 */
#define APP_ECHO_POLLS                  5000
#define APP_ECHO_UDP_RETRY_LIMIT        2
#define APP_ECHO_PAUSE_MS               3000

static vedasl917int_t vedasl917int;
static log_t logger;
static char app_ssid[] = APP_WLAN_SSID;
static char app_psk[] = APP_WLAN_PSK;
static uint8_t app_server_ip[ VEDASL917INT_IPV4_SIZE ] = { APP_SERVER_IP };
static uint32_t app_packet_count = 1;

/**
 * @brief Veda SL917 INT application echo function.
 * @details This function opens a client socket, exchanges one numbered message, and closes the socket.
 * @param[in] type : VEDASL917INT_SOCKET_TCP or VEDASL917INT_SOCKET_UDP.
 * @return Nothing.
 * @note A TCP echo can span multiple frames. A UDP timeout retries the same message up to twice.
 * A no-listener response skips the TCP exchange and leaves UDP available.
 */
static void vedasl917int_echo ( uint8_t type );

/**
 * @brief Veda SL917 INT application error function.
 * @details This function logs the failed operation and stops the example until restart.
 * @param[in] operation : Name of the failed operation.
 * @param[in] result : Driver result.
 * @param[in] status : Device status associated with the operation.
 * @return Nothing.
 */
static void vedasl917int_stop ( char *operation, err_t result, uint16_t status );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vedasl917int_cfg_t vedasl917int_cfg;  /**< Click config object. */

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
    vedasl917int_cfg_setup( &vedasl917int_cfg );
    VEDASL917INT_MAP_MIKROBUS( vedasl917int_cfg, MIKROBUS_POSITION_VEDASL917INT );
    if ( SPI_MASTER_ERROR == vedasl917int_init( &vedasl917int, &vedasl917int_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    err_t error_flag = vedasl917int_default_cfg( &vedasl917int );
    if ( VEDASL917INT_OK != error_flag )
    {
        vedasl917int_stop( "Default configuration", error_flag, vedasl917int.last_status );
    }

    vedasl917int_version_t version;
    error_flag = vedasl917int_get_fw_version( &vedasl917int, &version );
    if ( VEDASL917INT_OK != error_flag )
    {
        vedasl917int_stop( "Firmware version read", error_flag, vedasl917int.last_status );
    }
    log_printf( &logger, "Firmware: %u.%u.%u, build %u\r\n",
                ( uint16_t ) version.major, ( uint16_t ) version.minor, ( uint16_t ) version.patch, version.build );

    uint8_t mac[ VEDASL917INT_MAC_SIZE ];
    error_flag = vedasl917int_get_mac_address( &vedasl917int, mac );
    if ( VEDASL917INT_OK != error_flag )
    {
        vedasl917int_stop( "MAC address read", error_flag, vedasl917int.last_status );
    }
    log_printf( &logger, "MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",
                ( uint16_t ) mac[ 0 ], ( uint16_t ) mac[ 1 ], ( uint16_t ) mac[ 2 ],
                ( uint16_t ) mac[ 3 ], ( uint16_t ) mac[ 4 ], ( uint16_t ) mac[ 5 ] );

    if ( ( VEDASL917INT_WIFI_WPA2 == APP_WLAN_AUTH ) && ( 0 == app_psk[ 0 ] ) )
    {
        log_error( &logger, " Set APP_WLAN_PSK for the configured WPA2 network." );
        for ( ; ; );
    }
    log_printf( &logger, "Joining Wi-Fi: %s\r\n", app_ssid );
    error_flag = vedasl917int_join( &vedasl917int, app_ssid, APP_WLAN_AUTH, app_psk );
    if ( VEDASL917INT_OK != error_flag )
    {
        vedasl917int_stop( "Wi-Fi join", error_flag, vedasl917int.last_status );
    }

    uint8_t address[ VEDASL917INT_IPV4_SIZE ];
    log_info( &logger, " Associated. Waiting for DHCP..." );
    error_flag = vedasl917int_dhcp( &vedasl917int, address );
    if ( VEDASL917INT_OK != error_flag )
    {
        vedasl917int_stop( "DHCP", error_flag, vedasl917int.last_status );
    }
    log_printf( &logger, "IPv4: %u.%u.%u.%u\r\n", ( uint16_t ) address[ 0 ], ( uint16_t ) address[ 1 ],
                ( uint16_t ) address[ 2 ], ( uint16_t ) address[ 3 ] );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    vedasl917int_echo( VEDASL917INT_SOCKET_TCP );
    vedasl917int_echo( VEDASL917INT_SOCKET_UDP );
    Delay_ms( APP_ECHO_PAUSE_MS );
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

static void vedasl917int_echo ( uint8_t type )
{
    char message[ APP_MESSAGE_SIZE ] = APP_TEXT_MESSAGE;
    char reply[ APP_MESSAGE_SIZE ];
    char *counter_text = &message[ APP_TEXT_MESSAGE_LENGTH ];
    char *protocol = "TCP";
    char *operation = "Socket open";
    vedasl917int_socket_t socket = { 0 };
    uint16_t expected;
    uint16_t received;
    uint16_t total = 0;
    uint16_t status;
    uint8_t retry = 0;
    err_t result;
    err_t close_result;

    uint32_to_str( app_packet_count, counter_text );
    l_trim( counter_text );
    r_trim( counter_text );
    strcat( message, "\r\n" );
    expected = ( uint16_t ) strlen( message );

    if ( VEDASL917INT_SOCKET_UDP == type )
    {
        protocol = "UDP";
    }
    log_printf( &logger, "\r\n>>> Open %s socket %u.%u.%u.%u:%u\r\n", protocol,
                ( uint16_t ) app_server_ip[ 0 ], ( uint16_t ) app_server_ip[ 1 ],
                ( uint16_t ) app_server_ip[ 2 ], ( uint16_t ) app_server_ip[ 3 ], ( uint16_t ) APP_SERVER_PORT );
    result = vedasl917int_socket_open( &vedasl917int, &socket, type, app_server_ip, APP_SERVER_PORT, APP_LOCAL_PORT );

    while ( VEDASL917INT_OK == result )
    {
        operation = "Echo send";
        result = vedasl917int_socket_send( &vedasl917int, &socket, ( uint8_t * ) message, expected );
        if ( VEDASL917INT_OK != result )
        {
            break;
        }
        log_printf( &logger, ">>> TX: %s", message );

        operation = "Echo receive";
        total = 0;
        while ( ( VEDASL917INT_OK == result ) && ( total < expected ) )
        {
            result = vedasl917int_socket_recv( &vedasl917int, &socket, ( uint8_t * ) &reply[ total ],
                                               expected + 1u - total, &received, APP_ECHO_POLLS );
            total += received;
            if ( VEDASL917INT_SOCKET_UDP == type )
            {
                break;
            }
        }
        if ( ( VEDASL917INT_SOCKET_UDP == type ) && ( VEDASL917INT_TIMEOUT == result ) &&
             vedasl917int.ready && ( retry < APP_ECHO_UDP_RETRY_LIMIT ) )
        {
            retry++;
            log_printf( &logger, "UDP echo timeout. Retry %u/%u.\r\n",
                        ( uint16_t ) retry, ( uint16_t ) APP_ECHO_UDP_RETRY_LIMIT );
            result = VEDASL917INT_OK;
        }
        else
        {
            break;
        }
    }

    if ( ( VEDASL917INT_OK == result ) && ( ( expected != total ) || ( 0 != memcmp( reply, message, expected ) ) ) )
    {
        operation = "Echo verification";
        result = VEDASL917INT_PROTOCOL_ERROR;
    }
    if ( VEDASL917INT_OK == result )
    {
        reply[ total ] = 0;
        log_printf( &logger, "<<< %s echo verified: %s", protocol, reply );
        app_packet_count++;
    }

    status = vedasl917int.last_status;
    if ( socket.open && vedasl917int.ready )
    {
        close_result = vedasl917int_socket_close( &vedasl917int, &socket );
        if ( VEDASL917INT_OK == result )
        {
            operation = "Socket close";
            result = close_result;
            status = vedasl917int.last_status;
        }
    }
    if ( ( VEDASL917INT_SOCKET_TCP == type ) && ( VEDASL917INT_NO_TCP_SERVER == result ) )
    {
        log_warning( &logger, " Firmware reported no TCP listener (0x%.4X). Trying UDP.", status );
    }
    else if ( VEDASL917INT_OK != result )
    {
        vedasl917int_stop( operation, result, status );
    }
}

static void vedasl917int_stop ( char *operation, err_t result, uint16_t status )
{
    log_error( &logger, " %s failed. Restart the example.", operation );
    log_printf( &logger, "Driver result: %d, device status: 0x%.4X\r\n", ( int16_t ) result, status );
    for ( ; ; );
}

// ------------------------------------------------------------------------ END
