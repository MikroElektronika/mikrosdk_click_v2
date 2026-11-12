/*!
 * @file main.c
 * @brief WiFi 4 Click Example.
 *
 * # Description
 * This example connects WiFi 4 Click to a Wi-Fi access point. It sends a message to an echo server
 * over TCP and UDP and compares each reply with the sent message.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - WIFI4_POWER_UP:
 * Resets the device and waits for the AT console. Reads the firmware version before configuring a profile.
 *
 *  - WIFI4_CONFIGURE_CONNECTION:
 * Configures station mode for the selected access point using DHCP.
 * A saved profile starts at module boot and skips this stage.
 *
 *  - WIFI4_WAIT_FOR_CONNECTION:
 * Waits for association and an assigned IPv4 address.
 *
 *  - WIFI4_EXAMPLE:
 * Repeats the TCP and UDP echo exchanges with a five-second pause between rounds.
 * If no UDP reply arrives within the poll limit, it logs a warning and continues after closing the socket.
 *
 * Other errors halt the application until restart.
 *
 * ## Additional Function
 * - static void wifi4_clear_app_buf ( void )
 * - static void wifi4_log_app_buf ( void )
 * - static err_t wifi4_process ( wifi4_t *ctx )
 * - static err_t wifi4_read_response ( wifi4_t *ctx, char *rsp, uint32_t max_rsp_time )
 * - static err_t wifi4_power_up ( wifi4_t *ctx )
 * - static err_t wifi4_config_connection ( wifi4_t *ctx )
 * - static err_t wifi4_check_connection ( wifi4_t *ctx )
 * - static err_t wifi4_example ( wifi4_t *ctx )
 *
 * @note
 * Set WIFI_SSID and WIFI_PASSWORD for a 2.4 GHz network in volatile or save profile mode.
 * An empty password selects an open network; otherwise use an 8-63 character WPA/WPA2 passphrase.
 * Set REMOTE_IP and REMOTE_PORT for a reachable server that echoes the message over both TCP and UDP.
 * Use printable credentials without CR, LF, or commas. Password command echoes are not logged.
 * Select WIFI_PROFILE_VOLATILE for RAM-only configuration. Use WIFI_PROFILE_SAVE for one run to
 * save a configured station profile, including credentials, and restart via the hardware reset pin.
 * Use WIFI_PROFILE_SAVED to boot from the stored station profile without another flash write.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "wifi4.h"
#include "conversions.h"
#include "generic_pointer.h"

#ifndef MIKROBUS_POSITION_WIFI4
    #define MIKROBUS_POSITION_WIFI4 MIKROBUS_1
#endif

// WiFi parameters
#define WIFI_SSID               "MIKROE GUEST"
#define WIFI_PASSWORD           "!guest.mikroe!"

// Station profile selection.
#define WIFI_PROFILE_VOLATILE   0
#define WIFI_PROFILE_SAVE       1
#define WIFI_PROFILE_SAVED      2
#define WIFI_PROFILE_MODE       WIFI_PROFILE_SAVE

// TCP/UDP example parameters
#define MESSAGE_CONTENT         "WiFi 4 Click board - demo example."
#define REMOTE_IP               "54.187.244.144"  // TCP/UDP echo server IP address
#define REMOTE_PORT             "51111"           // TCP/UDP echo server port
#define ECHO_POLL_LIMIT         200
#define ECHO_POLL_DELAY_MS      50
#define ECHO_REPEAT_DELAY_MS    5000
#define ECHO_UART_POLL_MS       10
#define IP_POLL_LIMIT           30
#define IP_POLL_DELAY_MS        1000

// Application buffer size
#define APP_BUFFER_SIZE         1024
#define PROCESS_BUFFER_SIZE     128

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    WIFI4_POWER_UP = 1,
    WIFI4_CONFIGURE_CONNECTION,
    WIFI4_WAIT_FOR_CONNECTION,
    WIFI4_EXAMPLE

} wifi4_app_state_t;

static wifi4_t wifi4;
static log_t logger;

static char app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_logged = 0;
static wifi4_app_state_t app_state = WIFI4_POWER_UP;
static uint8_t app_log_enabled = 1;

/**
 * @brief WiFi 4 clearing application buffer.
 * @details This function clears memory of application buffer and resets its length.
 * @return None.
 * @note None.
 */
static void wifi4_clear_app_buf ( void );

/**
 * @brief WiFi 4 log application buffer.
 * @details This function logs new bytes from the application buffer to USB UART.
 * @return None.
 * @note Logging is suppressed while a password command is pending.
 */
static void wifi4_log_app_buf ( void );

/**
 * @brief WiFi 4 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifi4_process ( wifi4_t *ctx );

/**
 * @brief WiFi 4 read response function.
 * @details This function waits for a complete response line, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @param[in] rsp : Expected response line or WIND prefix, including the leading CR/LF.
 * @param[in] max_rsp_time : Maximum polling delay budget in milliseconds; processing adds execution time.
 * @return @li @c  0 - Expected response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note Clear the application buffer before a new command, not between waits for the same command.
 * Indications received together with OK remain available to the next wait.
 */
static err_t wifi4_read_response ( wifi4_t *ctx, char *rsp, uint32_t max_rsp_time );

/**
 * @brief WiFi 4 power up function.
 * @details This function resets the device and waits for the console. Reads firmware information before configuration.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Command or response error.
 * See #err_t definition for detailed explanation.
 * @note No factory reset or nonvolatile write is performed.
 */
static err_t wifi4_power_up ( wifi4_t *ctx );

/**
 * @brief WiFi 4 config connection function.
 * @details This function configures station mode for the specified access point.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Configuration, command, or response error.
 * See #err_t definition for detailed explanation.
 * @note The radio is stopped before configuration and restarted afterward.
 * WIFI_PROFILE_SAVE also saves the current configuration to module flash and resets the module.
 */
static err_t wifi4_config_connection ( wifi4_t *ctx );

/**
 * @brief WiFi 4 check connection function.
 * @details This function waits for the selected access point connection and an assigned IPv4 address.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @return @li @c    0 - Connection ready.
 *         @li @c != 0 - Command or response error.
 * See #err_t definition for detailed explanation.
 * @note This function runs only when the example is connecting to an access point.
 */
static err_t wifi4_check_connection ( wifi4_t *ctx );

/**
 * @brief WiFi 4 example function.
 * @details This function runs one TCP and UDP echo round and pauses before the next round.
 * @param[in] ctx : Click context object.
 * See #wifi4_t object definition for detailed explanation.
 * @return @li @c    0 - Example completed.
 *         @li @c != 0 - Command or response error.
 * See #err_t definition for detailed explanation.
 * @note Each successful round closes both sockets and polls UART during the pause.
 */
static err_t wifi4_example ( wifi4_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifi4_cfg_t wifi4_cfg;  /**< Click config object. */

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
    wifi4_cfg_setup( &wifi4_cfg );
    WIFI4_MAP_MIKROBUS( wifi4_cfg, MIKROBUS_POSITION_WIFI4 );
    if ( UART_ERROR == wifi4_init( &wifi4, &wifi4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = WIFI4_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void )
{
    err_t error_flag = WIFI4_OK;

    switch ( app_state )
    {
        case WIFI4_POWER_UP:
        {
            error_flag = wifi4_power_up( &wifi4 );
            if ( WIFI4_OK == error_flag )
            {
                if ( WIFI_PROFILE_SAVED == WIFI_PROFILE_MODE )
                {
                    app_state = WIFI4_WAIT_FOR_CONNECTION;
                    log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
                }
                else
                {
                    app_state = WIFI4_CONFIGURE_CONNECTION;
                    log_printf( &logger, ">>> APP STATE - CONFIGURE CONNECTION <<<\r\n\n" );
                }
            }
            break;
        }
        case WIFI4_CONFIGURE_CONNECTION:
        {
            error_flag = wifi4_config_connection( &wifi4 );
            if ( WIFI4_OK == error_flag )
            {
                app_state = WIFI4_WAIT_FOR_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case WIFI4_WAIT_FOR_CONNECTION:
        {
            error_flag = wifi4_check_connection( &wifi4 );
            if ( WIFI4_OK == error_flag )
            {
                app_state = WIFI4_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WIFI4_EXAMPLE:
        {
            error_flag = wifi4_example( &wifi4 );
            break;
        }
        default:
        {
            error_flag = WIFI4_ERROR;
            break;
        }
    }

    if ( WIFI4_OK != error_flag )
    {
        log_error( &logger, " Example failed (%d). Restart the application to retry.",
                   ( int16_t ) error_flag );
        for ( ; ; );
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

static void wifi4_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_logged = 0;
    app_buf[ 0 ] = 0;
}

static void wifi4_log_app_buf ( void )
{
    if ( app_log_enabled )
    {
        while ( app_buf_logged < app_buf_len )
        {
            log_printf( &logger, "%c", app_buf[ app_buf_logged++ ] );
        }
    }
}

static err_t wifi4_process ( wifi4_t *ctx )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    err_t error_flag = WIFI4_ERROR;
    int32_t rx_size = wifi4_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );

    if ( ( rx_size > 0 ) && ( rx_size <= PROCESS_BUFFER_SIZE ) )
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE )
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            if ( app_log_enabled )
            {
                while ( app_buf_logged < overflow_bytes )
                {
                    log_printf( &logger, "%c", app_buf[ app_buf_logged++ ] );
                }
            }
            app_buf_logged -= overflow_bytes;
            if ( app_buf_logged < 0 )
            {
                app_buf_logged = 0;
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
        app_buf[ app_buf_len ] = 0;
        error_flag = WIFI4_OK;
    }

    return error_flag;
}

static err_t wifi4_read_response ( wifi4_t *ctx, char *rsp, uint32_t max_rsp_time )
{
    uint32_t timeout_cnt = 0;
    err_t error_flag = WIFI4_ERROR_TIMEOUT;
    char * __generic_ptr rsp_ptr = NULL;

    while ( timeout_cnt < max_rsp_time )
    {
        wifi4_process( ctx );
        rsp_ptr = strstr( app_buf, WIFI4_RSP_ERROR );
        if ( rsp_ptr )
        {
            if ( strstr( rsp_ptr + 2, "\r\n" ) )
            {
                error_flag = WIFI4_ERROR_CMD;
                break;
            }
        }
        else
        {
            rsp_ptr = strstr( app_buf, rsp );
            if ( ( NULL == rsp_ptr ) && ( 0 == strcmp( rsp, WIFI4_RSP_OK ) ) )
            {
                rsp_ptr = strstr( app_buf, WIFI4_RSP_SOCKET_OK );
            }
            if ( rsp_ptr && strstr( rsp_ptr + 2, "\r\n" ) )
            {
                error_flag = WIFI4_OK;
                break;
            }
        }
        timeout_cnt++;
        Delay_ms( 1 );
    }

    wifi4_log_app_buf( );
    if ( WIFI4_ERROR_TIMEOUT == error_flag )
    {
        log_error( &logger, " Module response timed out." );
    }

    return error_flag;
}

static err_t wifi4_power_up ( wifi4_t *ctx )
{
    err_t error_flag = WIFI4_OK;

    if ( WIFI_PROFILE_SAVED == WIFI_PROFILE_MODE )
    {
        log_printf( &logger, ">>> Boot using the saved station profile.\r\n" );
    }
    log_printf( &logger, ">>> Perform device hardware reset.\r\n" );
    wifi4_clear_app_buf( );
    wifi4_hw_reset( ctx );
    error_flag = wifi4_read_response( ctx, WIFI4_RSP_CONSOLE_READY, WIFI4_MAX_BOOT_GREETING );

    // Keep the boot indications available to the connection check in saved profile mode.
    if ( ( WIFI_PROFILE_SAVED != WIFI_PROFILE_MODE ) && ( WIFI4_OK == error_flag ) )
    {
        log_printf( &logger, ">>> Check communication.\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_run( ctx, WIFI4_CMD_AT );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
        if ( WIFI4_OK == error_flag )
        {
            log_printf( &logger, ">>> Disable UART hardware flow control.\r\n" );
            wifi4_clear_app_buf( );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SET_CFG, WIFI4_CFG_FLOW_CONTROL_OFF );
            if ( WIFI4_OK == error_flag )
            {
                error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
            }
        }
        if ( WIFI4_OK == error_flag )
        {
            log_printf( &logger, ">>> Get device software version.\r\n" );
            wifi4_clear_app_buf( );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_STATUS, WIFI4_STATUS_VERSION );
            if ( WIFI4_OK == error_flag )
            {
                error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
            }
        }
    }

    return error_flag;
}

static err_t wifi4_config_connection ( wifi4_t *ctx )
{
    err_t error_flag = WIFI4_OK;
    size_t ssid_len = strlen( WIFI_SSID );
    size_t password_len = strlen( WIFI_PASSWORD );

    if ( ( 0 == ssid_len ) || ( ssid_len > WIFI4_SSID_MAX_SIZE ) || strpbrk( WIFI_SSID, ",\r\n" ) )
    {
        log_error( &logger, " WIFI_SSID must be 1-32 bytes long and contain no commas or line breaks." );
        error_flag = WIFI4_ERROR;
    }
    else if ( 0 != password_len )
    {
        if ( ( password_len < WIFI4_PASSWORD_MIN_SIZE ) || ( password_len > WIFI4_PASSWORD_MAX_SIZE ) )
        {
            log_error( &logger, " WIFI_PASSWORD must be empty or 8-63 characters long." );
            error_flag = WIFI4_ERROR;
        }
        else if ( strpbrk( WIFI_PASSWORD, ",\r\n" ) )
        {
            log_error( &logger, " WIFI_PASSWORD must contain no commas or line breaks." );
            error_flag = WIFI4_ERROR;
        }
    }

    if ( WIFI4_OK == error_flag )
    {
        log_printf( &logger, ">>> Stop radio before configuration.\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_WIFI, WIFI4_WIFI_DISABLE );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_WIFI_DOWN, WIFI4_MAX_BOOT_GREETING );
        }
    }
    if ( WIFI4_OK == error_flag )
    {
        log_printf( &logger, ">>> Set Wi-Fi station mode.\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SET_CFG, WIFI4_CFG_STATION_MODE );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
    }
    if ( WIFI4_OK == error_flag )
    {
        log_printf( &logger, ">>> Set open-system authentication.\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SET_CFG, WIFI4_CFG_AUTH_OPEN );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
    }
    if ( WIFI4_OK == error_flag )
    {
        log_printf( &logger, ">>> Enable DHCP.\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SET_CFG, WIFI4_CFG_DHCP_ON );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
    }
    if ( WIFI4_OK == error_flag )
    {
        log_printf( &logger, ">>> Set WiFi SSID.\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SSID, WIFI_SSID );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
    }
    if ( WIFI4_OK == error_flag )
    {
        wifi4_clear_app_buf( );
        if ( 0 == password_len )
        {
            log_printf( &logger, ">>> Select open network security.\r\n" );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SET_CFG, WIFI4_CFG_SECURITY_OPEN );
        }
        else
        {
            log_printf( &logger, ">>> Select WPA/WPA2 security.\r\n" );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SET_CFG, WIFI4_CFG_SECURITY_WPA );
        }
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
    }
    if ( ( WIFI4_OK == error_flag ) && ( 0 != password_len ) )
    {
        log_printf( &logger, ">>> Set WiFi password.\r\n" );
        wifi4_clear_app_buf( );
        strcpy( app_buf, WIFI4_CFG_WPA_PASSWORD );
        strcat( app_buf, WIFI_PASSWORD );
        app_buf_len = ( int32_t ) strlen( app_buf );
        app_log_enabled = 0;
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SET_CFG, app_buf );
        wifi4_clear_app_buf( );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
        wifi4_clear_app_buf( );
        memset( ctx->cmd_buffer, 0, sizeof( ctx->cmd_buffer ) );
        if ( WIFI4_OK == error_flag )
        {
            app_log_enabled = 1;
            log_printf( &logger, "Password set.\r\n" );
        }
        else
        {
            log_error( &logger, " Password configuration failed." );
        }
    }
    if ( WIFI4_OK == error_flag )
    {
        log_printf( &logger, ">>> Start WiFi radio.\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_WIFI, WIFI4_WIFI_ENABLE );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_WIFI_READY, WIFI4_MAX_BOOT_GREETING );
        }
    }
    if ( ( WIFI_PROFILE_SAVE == WIFI_PROFILE_MODE ) && ( WIFI4_OK == error_flag ) )
    {
        log_printf( &logger, ">>> Save station configuration to module flash (AT&W).\r\n" );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_run( ctx, WIFI4_CMD_SAVE_CFG );
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
        }
        if ( WIFI4_OK == error_flag )
        {
            log_printf( &logger, ">>> Hardware reset with saved station configuration.\r\n" );
            wifi4_clear_app_buf( );
            wifi4_hw_reset( ctx );
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_CONSOLE_READY, WIFI4_MAX_BOOT_GREETING );
            if ( WIFI4_OK == error_flag )
            {
                error_flag = wifi4_read_response( ctx, WIFI4_RSP_WIFI_READY, WIFI4_MAX_BOOT_GREETING );
            }
        }
    }

    return error_flag;
}

static err_t wifi4_check_connection ( wifi4_t *ctx )
{
    err_t error_flag = WIFI4_OK;
    char * __generic_ptr ip_ptr = NULL;

    log_printf( &logger, ">>> Wait for Wi-Fi association.\r\n" );
    error_flag = wifi4_read_response( ctx, WIFI4_RSP_WIFI_UP, WIFI4_MAX_WIFI_CONNECT );
    if ( WIFI4_OK == error_flag )
    {
        log_printf( &logger, ">>> Wait for an IPv4 address.\r\n" );
    }

    // WIND:24 may arrive before DHCP has assigned an address.
    for ( uint8_t poll_cnt = 0; ( poll_cnt < IP_POLL_LIMIT ) && ( WIFI4_OK == error_flag ); poll_cnt++ )
    {
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_STATUS, WIFI4_STATUS_IP );
        if ( WIFI4_OK == error_flag )
        {
            app_log_enabled = 0;
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
            app_log_enabled = 1;
        }
        if ( WIFI4_OK != error_flag )
        {
            wifi4_log_app_buf( );
            break;
        }

        ip_ptr = strstr( app_buf, WIFI4_STATUS_IP " = " );
        if ( ip_ptr )
        {
            ip_ptr += strlen( WIFI4_STATUS_IP " = " );
        }
        if ( ( NULL == ip_ptr ) || ( *ip_ptr < '0' ) || ( *ip_ptr > '9' ) )
        {
            wifi4_log_app_buf( );
            log_error( &logger, " Missing IPv4 address in the module response." );
            error_flag = WIFI4_ERROR;
            break;
        }
        if ( 0 != strncmp( ip_ptr, "0.0.0.0", strlen( "0.0.0.0" ) ) )
        {
            wifi4_log_app_buf( );
            break;
        }
        ip_ptr = NULL;
        Delay_ms( IP_POLL_DELAY_MS );
    }
    if ( ( WIFI4_OK == error_flag ) && ( NULL == ip_ptr ) )
    {
        log_error( &logger, " DHCP wait ended with IPv4 address 0.0.0.0." );
        error_flag = WIFI4_ERROR_TIMEOUT;
    }

    return error_flag;
}

static err_t wifi4_example ( wifi4_t *ctx )
{
    err_t error_flag = WIFI4_OK;
    char message[] = MESSAGE_CONTENT;
    uint16_t message_len = ( uint16_t ) strlen( message );
    char message_len_buf[ 10 ] = { 0 };
    char socket_id[ 3 ] = { 0 };
    char cmd_buf[ 10 ] = { 0 };

    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    // Complete the TCP exchange before opening the UDP socket.
    for ( uint8_t udp = 0; ( udp < 2 ) && ( WIFI4_OK == error_flag ); udp++ )
    {
        char * __generic_ptr rsp_ptr = NULL;
        uint16_t received_len = 0;
        err_t close_flag = WIFI4_OK;

        wifi4_clear_app_buf( );
        if ( 0 == udp )
        {
            log_printf( &logger, ">>> Open TCP socket.\r\n" );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SOCKET_OPEN, REMOTE_IP "," REMOTE_PORT "," WIFI4_SOCKET_TCP );
        }
        else
        {
            log_printf( &logger, ">>> Open UDP socket.\r\n" );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SOCKET_OPEN, REMOTE_IP "," REMOTE_PORT "," WIFI4_SOCKET_UDP );
        }
        if ( WIFI4_OK == error_flag )
        {
            error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_SOCKET_OPEN );
        }
        if ( WIFI4_OK != error_flag )
        {
            break;
        }

        rsp_ptr = strstr( app_buf, WIFI4_RSP_SOCKET_ID );
        if ( rsp_ptr )
        {
            rsp_ptr += strlen( WIFI4_RSP_SOCKET_ID );
        }
        if ( ( NULL == rsp_ptr ) || ( rsp_ptr[ 0 ] < '0' ) || ( rsp_ptr[ 0 ] > '9' ) ||
             ( rsp_ptr[ 1 ] < '0' ) || ( rsp_ptr[ 1 ] > '9' ) || ( 0 != strncmp( rsp_ptr + 2, "\r\n", 2 ) ) )
        {
            log_error( &logger, " Missing or invalid socket identifier." );
            error_flag = WIFI4_ERROR;
            break;
        }
        memcpy( socket_id, rsp_ptr, 2 );

        log_printf( &logger, ">>> Write echo message.\r\n" );
        strcpy( cmd_buf, socket_id );
        strcat( cmd_buf, "," );
        strcat( cmd_buf, message_len_buf );
        wifi4_clear_app_buf( );
        error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SOCKET_WRITE, cmd_buf );
        if ( WIFI4_OK == error_flag )
        {
            // SOCKW consumes exactly message_len bytes immediately after the command CR.
            if ( message_len != wifi4_generic_write( ctx, ( uint8_t * ) message, message_len ) )
            {
                error_flag = WIFI4_ERROR;
            }
            else
            {
                error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
            }
        }

        if ( WIFI4_OK != error_flag )
        {
            break;
        }

        log_printf( &logger, ">>> Wait for echo bytes.\r\n" );
        // TCP may deliver the echo in fragments. Read the pending bytes as they arrive.
        for ( uint16_t poll = 0; ( poll < ECHO_POLL_LIMIT ) && ( received_len < message_len ); poll++ )
        {
            char * __generic_ptr len_ptr = NULL;
            uint32_t pending_len = 0;

            wifi4_clear_app_buf( );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SOCKET_QUERY, socket_id );
            if ( WIFI4_OK == error_flag )
            {
                app_log_enabled = 0;
                error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
                app_log_enabled = 1;
            }
            if ( WIFI4_OK != error_flag )
            {
                wifi4_log_app_buf( );
                break;
            }

            len_ptr = strstr( app_buf, WIFI4_RSP_SOCKET_LENGTH );
            if ( len_ptr )
            {
                len_ptr += strlen( WIFI4_RSP_SOCKET_LENGTH );
                rsp_ptr = len_ptr;
                while ( ( *rsp_ptr >= '0' ) && ( *rsp_ptr <= '9' ) && ( pending_len <= message_len ) )
                {
                    pending_len = pending_len * 10ul + ( uint16_t ) ( *rsp_ptr++ - '0' );
                }
            }
            if ( ( NULL == len_ptr ) || ( rsp_ptr == len_ptr ) || ( ( rsp_ptr - len_ptr ) > 5 ) ||
                 ( 0 != strncmp( rsp_ptr, "\r\n", 2 ) ) || ( pending_len > ( message_len - received_len ) ) )
            {
                log_error( &logger, " Invalid or unexpected socket byte count." );
                error_flag = WIFI4_ERROR;
                break;
            }
            if ( 0 == pending_len )
            {
                Delay_ms( ECHO_POLL_DELAY_MS );
                continue;
            }

            // Reuse the decimal length from SOCKQ to build the SOCKR arguments.
            *rsp_ptr = 0;
            strcpy( cmd_buf, socket_id );
            strcat( cmd_buf, "," );
            strcat( cmd_buf, len_ptr );
            wifi4_clear_app_buf( );
            log_printf( &logger, ">>> Read echo bytes.\r\n" );
            error_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SOCKET_READ, cmd_buf );
            if ( WIFI4_OK == error_flag )
            {
                error_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
            }
            if ( WIFI4_OK != error_flag )
            {
                break;
            }

            rsp_ptr = strstr( app_buf, WIFI4_RSP_OK );
            if ( NULL == rsp_ptr )
            {
                rsp_ptr = strstr( app_buf, WIFI4_RSP_SOCKET_OK );
            }
            if ( ( NULL == rsp_ptr ) || ( ( rsp_ptr - app_buf ) < ( int32_t ) pending_len ) ||
                 ( 0 != memcmp( rsp_ptr - pending_len, &message[ received_len ], pending_len ) ) )
            {
                log_error( &logger, " Echo does not match the sent message." );
                error_flag = WIFI4_ERROR;
                break;
            }
            received_len += ( uint16_t ) pending_len;
        }

        // Close only after the last command has completed.
        if ( WIFI4_OK == error_flag )
        {
            if ( received_len != message_len )
            {
                if ( ( 0 != udp ) && ( 0 == received_len ) )
                {
                    log_warning( &logger, " No UDP echo before the poll limit. AT+S.SOCKQ reported 0 pending bytes." );
                }
                else
                {
                    log_error( &logger, " Echo timed out before the full message was received." );
                    error_flag = WIFI4_ERROR_TIMEOUT;
                }
            }
            log_printf( &logger, ">>> Close echo socket.\r\n" );
            wifi4_clear_app_buf( );
            close_flag = wifi4_cmd_set( ctx, WIFI4_CMD_SOCKET_CLOSE, socket_id );
            if ( WIFI4_OK == close_flag )
            {
                close_flag = wifi4_read_response( ctx, WIFI4_RSP_OK, WIFI4_MAX_AT_DEFAULT );
            }
            if ( WIFI4_OK == error_flag )
            {
                error_flag = close_flag;
            }
        }
    }
    wifi4_clear_app_buf( );

    if ( WIFI4_OK == error_flag )
    {
        // Keep receiving asynchronous indications between echo rounds.
        for ( uint16_t wait_ms = 0; wait_ms < ECHO_REPEAT_DELAY_MS; wait_ms += ECHO_UART_POLL_MS )
        {
            Delay_ms( ECHO_UART_POLL_MS );
            if ( WIFI4_OK == wifi4_process( ctx ) )
            {
                wifi4_log_app_buf( );
                wifi4_clear_app_buf( );
            }
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------ END
