/*!
 * @file main.c
 * @brief DeviceDrive Click Example.
 *
 * # Description
 * This example demonstrates the use of DeviceDrive Click by sending numbered
 * JSON messages to an HTTPS echo endpoint and displaying the server responses.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click UART driver.
 *
 * ## Application Task
 * Application task is split into four states:
 *  - DEVICEDRIVE_POWER_UP:
 * Resets the module and waits for its startup-ready sequence.
 *  - DEVICEDRIVE_CONFIG_EXAMPLE:
 * Configures the HTTPS endpoint and WiFi network without using the DeviceDrive cloud.
 *  - DEVICEDRIVE_EXAMPLE:
 * Checks the WiFi connection, sends a numbered message, and displays the echo response.
 *  - DEVICEDRIVE_STOPPED:
 * Stops cloud transfers after an unexpected module restart.
 *
 * ## Additional Function
 * - static void devicedrive_clear_app_buf ( void )
 * - static void devicedrive_log_app_buf ( void )
 * - static void devicedrive_log_json ( char *json, uint16_t len )
 * - static err_t devicedrive_process ( devicedrive_t *ctx )
 * - static err_t devicedrive_read_response ( devicedrive_t *ctx, char *rsp, uint32_t max_rsp_time )
 * - static err_t devicedrive_power_up ( devicedrive_t *ctx )
 * - static err_t devicedrive_config_example ( devicedrive_t *ctx )
 * - static err_t devicedrive_example ( devicedrive_t *ctx )
 *
 * @note
 * Set APP_WIFI_SSID and APP_WIFI_PASSWORD for a 2.4 GHz WiFi network before running.
 * The example uses the WRF01 native JSON protocol; command availability depends
 * on the installed firmware.
 * HTTPBin (https://httpbin.org/post) is a public test service; send demo data only.
 * Its fixed-length response supports WRF01 firmware without chunked HTTP support.
 * The module sends its MAC address and firmware information with each HTTPS request.
 * The example replaces saved WiFi/server settings and clears token and product_key.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "devicedrive.h"

#ifndef MIKROBUS_POSITION_DEVICEDRIVE
    #define MIKROBUS_POSITION_DEVICEDRIVE       MIKROBUS_1
#endif

// WiFi credentials and HTTPS endpoint used by the example.
#define APP_WIFI_SSID                           "MIKROE GUEST"
#define APP_WIFI_PASSWORD                       "!guest.mikroe!"
#define APP_SERVER_URL                          "https://httpbin.org/post"
#define APP_TEXT_MESSAGE                        "Hello from DeviceDrive Click!"

/** Complete JSON response buffer size, excluding the terminating null byte. */
#define APP_BUFFER_SIZE                         2048

static devicedrive_t devicedrive;                /**< Click context object. */
static log_t logger;                             /**< Logger object. */
static char app_buf[ APP_BUFFER_SIZE + 1 ];      /**< Complete module response. */
static uint16_t app_buf_len = 0;                 /**< Buffered response length. */
static bool app_buf_overflow = false;            /**< Discard the current oversized frame. */
static bool app_startup_stx = false;             /**< First startup byte received. */
static uint32_t packet_counter = 0;              /**< Number included in each transmitted message. */

/**
 * @brief DeviceDrive example states.
 * @details States used to sequence module startup, configuration, and HTTPS transfers.
 */
typedef enum
{
    DEVICEDRIVE_POWER_UP = 1,
    DEVICEDRIVE_CONFIG_EXAMPLE,
    DEVICEDRIVE_EXAMPLE,
    DEVICEDRIVE_STOPPED

} devicedrive_app_state_t;

static devicedrive_app_state_t app_state = DEVICEDRIVE_POWER_UP; /**< Current example state. */

/**
 * @brief DeviceDrive application buffer clearing function.
 * @details This function clears the application buffer and resets the frame state.
 * @return Nothing.
 * @note The UART ring buffer is preserved.
 */
static void devicedrive_clear_app_buf ( void );

/**
 * @brief DeviceDrive application buffer logging function.
 * @details This function displays a complete response with terminal-safe line endings.
 * @return Nothing.
 * @note The binary startup sequence is displayed as a readable ready message.
 */
static void devicedrive_log_app_buf ( void );

/**
 * @brief DeviceDrive JSON response logging function.
 * @details This function streams and formats JSON objects or arrays embedded in
 * string values with four-space indentation, without modifying the response.
 * @param[in] json : JSON response data.
 * @param[in] len : Number of response bytes, excluding the terminating null byte.
 * @return Nothing.
 * @note The received response buffer is not modified.
 */
static void devicedrive_log_json ( char *json, uint16_t len );

/**
 * @brief DeviceDrive response processing function.
 * @details This function collects one EOT-terminated JSON response or the two-byte
 * startup sequence, preserving partial frames between calls.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @return @li @c  0 - Complete frame received,
 *         @li @c -1 - No complete frame available,
 *         @li @c -4 - Oversized frame discarded.
 * See #err_t definition for detailed explanation.
 * @note Bytes following the completed frame remain in the UART ring buffer.
 */
static err_t devicedrive_process ( devicedrive_t *ctx );

/**
 * @brief DeviceDrive response reading function.
 * @details This function waits for an expected response and logs complete module
 * frames, including asynchronous connection notifications.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @param[in] rsp : Identifier expected in the completed response.
 * @param[in] max_rsp_time : Maximum polling delay in milliseconds.
 * @return @li @c  0 - Expected response received,
 *         @li @c -2 - Response timeout,
 *         @li @c -3 - Module error response,
 *         @li @c -4 - Oversized response,
 *         @li @c -5 - Command is not supported by the installed firmware,
 *         @li @c -6 - Module restarted before replying.
 * See #err_t definition for detailed explanation.
 * @note The matching response remains in the application buffer for inspection.
 */
static err_t devicedrive_read_response ( devicedrive_t *ctx, char *rsp, uint32_t max_rsp_time );

/**
 * @brief DeviceDrive power-up function.
 * @details This function resets the module and waits for its startup-ready
 * sequence before configuration begins.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @return @li @c    0 - Success,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note Saved settings are preserved during reset.
 */
static err_t devicedrive_power_up ( devicedrive_t *ctx );

/**
 * @brief DeviceDrive example configuration function.
 * @details This function enables error reporting, clears cloud credentials, and
 * configures the HTTPS endpoint and WiFi connection.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @return @li @c    0 - Success,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note Configuration changes are saved in the module.
 */
static err_t devicedrive_config_example ( devicedrive_t *ctx );

/**
 * @brief DeviceDrive echo example function.
 * @details This function checks the connection and sends a numbered JSON message
 * when the module has an IP address, then displays the echoed response.
 * @param[in] ctx : Click context object.
 * See #devicedrive_t object definition for detailed explanation.
 * @return @li @c    0 - Transfer completed or WiFi connection still pending,
 *         @li @c != 0 - Communication error.
 * See #err_t definition for detailed explanation.
 * @note The next connection check or transfer starts after a five-second delay.
 */
static err_t devicedrive_example ( devicedrive_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    devicedrive_cfg_t devicedrive_cfg;  /**< Click config object. */

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
    devicedrive_cfg_setup( &devicedrive_cfg );
    DEVICEDRIVE_MAP_MIKROBUS( devicedrive_cfg, MIKROBUS_POSITION_DEVICEDRIVE );
    if ( UART_ERROR == devicedrive_init( &devicedrive, &devicedrive_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag = DEVICEDRIVE_OK;

    switch ( app_state )
    {
        case DEVICEDRIVE_POWER_UP:
        {
            log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\r\n" );
            error_flag = devicedrive_power_up( &devicedrive );
            if ( DEVICEDRIVE_OK == error_flag )
            {
                app_state = DEVICEDRIVE_CONFIG_EXAMPLE;
            }
            break;
        }
        case DEVICEDRIVE_CONFIG_EXAMPLE:
        {
            log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\r\n" );
            error_flag = devicedrive_config_example( &devicedrive );
            if ( DEVICEDRIVE_OK == error_flag )
            {
                app_state = DEVICEDRIVE_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\r\n" );
            }
            break;
        }
        case DEVICEDRIVE_EXAMPLE:
        {
            error_flag = devicedrive_example( &devicedrive );
            break;
        }
        case DEVICEDRIVE_STOPPED:
        {
            break;
        }
        default:
        {
            app_state = DEVICEDRIVE_POWER_UP;
            break;
        }
    }

    if ( DEVICEDRIVE_ERROR_RESTARTED == error_flag )
    {
        log_error( &logger, " Module restarted during the cloud request. Transfers stopped." );
        log_info( &logger, " Check module firmware and 3.3 V supply before restarting." );
        app_state = DEVICEDRIVE_STOPPED;
    }
    else if ( DEVICEDRIVE_OK != error_flag )
    {
        log_error( &logger, " Communication error: %d. Restarting module.", ( int16_t ) error_flag );
        app_state = DEVICEDRIVE_POWER_UP;
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
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

static void devicedrive_clear_app_buf ( void )
{
    app_buf[ 0 ] = 0;
    app_buf_len = 0;
    app_buf_overflow = false;
    app_startup_stx = false;
}

static void devicedrive_log_app_buf ( void )
{
    if ( 0 == strcmp( app_buf, DEVICEDRIVE_RSP_READY ) )
    {
        log_printf( &logger, "<<< Module ready.\r\n" );
    }
    else if ( app_buf_len )
    {
        devicedrive_log_json( app_buf, app_buf_len );
        log_printf( &logger, "\r\n" );
    }
}

static void devicedrive_log_json ( char *json, uint16_t len )
{
    uint16_t index = 0;
    uint16_t scan_index;
    uint16_t value_start;
    uint16_t next_index;
    uint16_t embedded_index = 0;
    uint16_t embedded_end = 0;
    uint16_t depth = 0;
    uint16_t indent;
    bool in_string = false;
    bool escaped = false;
    bool scan_escaped;
    bool is_json_value;
    bool embedded_json = false;
    bool pending_open = false;
    char pending_open_char;
    char character;

    // Decode embedded JSON values as a stream; the response buffer is untouched.
    while ( ( index < len ) || embedded_json )
    {
        if ( embedded_json )
        {
            if ( embedded_index >= embedded_end )
            {
                embedded_json = false;
                continue;
            }

            // Decode one outer string escape while preserving inner JSON escapes.
            if ( ( '\\' == json[ embedded_index ] ) && ( embedded_index + 1 < embedded_end ) )
            {
                embedded_index++;
                character = json[ embedded_index++ ];
                switch ( character )
                {
                    case 'n': character = '\n'; break;
                    case 'r': character = '\r'; break;
                    case 't': character = '\t'; break;
                    case 'b': character = '\b'; break;
                    case 'f': character = '\f'; break;
                    case 'u': embedded_index--; character = '\\'; break;
                    default: break;
                }
            }
            else
            {
                character = json[ embedded_index++ ];
            }
        }
        else if ( !in_string && ( '"' == json[ index ] ) )
        {
            // Find the closing quote without treating escaped quotes as terminators.
            scan_index = index + 1;
            scan_escaped = false;
            while ( scan_index < len )
            {
                character = json[ scan_index ];
                if ( scan_escaped )
                {
                    scan_escaped = false;
                }
                else if ( '\\' == character )
                {
                    scan_escaped = true;
                }
                else if ( '"' == character )
                {
                    break;
                }
                scan_index++;
            }

            is_json_value = false;
            if ( scan_index < len )
            {
                value_start = index + 1;
                while ( ( value_start < scan_index ) &&
                        ( ( ' ' == json[ value_start ] ) || ( '\r' == json[ value_start ] ) ||
                          ( '\n' == json[ value_start ] ) || ( '\t' == json[ value_start ] ) ) )
                {
                    value_start++;
                }
                next_index = scan_index + 1;
                while ( ( next_index < len ) &&
                        ( ( ' ' == json[ next_index ] ) || ( '\r' == json[ next_index ] ) ||
                          ( '\n' == json[ next_index ] ) || ( '\t' == json[ next_index ] ) ) )
                {
                    next_index++;
                }
                // A colon after the string identifies a property name, not a value.
                is_json_value = ( value_start < scan_index ) &&
                                ( ( '{' == json[ value_start ] ) ||
                                  ( '[' == json[ value_start ] ) ) &&
                                ( ( next_index >= len ) || ( ':' != json[ next_index ] ) );
            }

            if ( is_json_value )
            {
                embedded_index = index + 1;
                embedded_end = scan_index;
                embedded_json = true;
                index = scan_index + 1;
                continue;
            }
            character = json[ index++ ];
        }
        else
        {
            character = json[ index++ ];
        }

        if ( pending_open )
        {
            // Delay an opening token until the next non-whitespace byte identifies an empty pair.
            if ( ( ' ' == character ) || ( '\r' == character ) ||
                 ( '\n' == character ) || ( '\t' == character ) )
            {
                continue;
            }
            if ( ( ( '{' == pending_open_char ) && ( '}' == character ) ) ||
                 ( ( '[' == pending_open_char ) && ( ']' == character ) ) )
            {
                log_printf( &logger, "%c%c", pending_open_char, character );
                pending_open = false;
                continue;
            }
            depth++;
            log_printf( &logger, "%c\r\n", pending_open_char );
            for ( indent = 0; indent < depth; indent++ )
            {
                log_printf( &logger, "    " );
            }
            pending_open = false;
        }

        if ( in_string )
        {
            log_printf( &logger, "%c", character );
            if ( escaped )
            {
                escaped = false;
            }
            else if ( '\\' == character )
            {
                escaped = true;
            }
            else if ( '"' == character )
            {
                in_string = false;
            }
        }
        else if ( '"' == character )
        {
            in_string = true;
            log_printf( &logger, "%c", character );
        }
        else if ( ( '{' == character ) || ( '[' == character ) )
        {
            pending_open = true;
            pending_open_char = character;
        }
        else if ( ( ',' == character ) || ( '}' == character ) || ( ']' == character ) )
        {
            if ( ',' == character )
            {
                log_printf( &logger, ",\r\n" );
            }
            else
            {
                if ( depth )
                {
                    depth--;
                }
                log_printf( &logger, "\r\n" );
            }
            for ( indent = 0; indent < depth; indent++ )
            {
                log_printf( &logger, "    " );
            }
            if ( ',' != character )
            {
                log_printf( &logger, "%c", character );
            }
        }
        else if ( ':' == character )
        {
            log_printf( &logger, ": " );
        }
        else if ( ( ' ' == character ) || ( '\r' == character ) ||
                  ( '\n' == character ) || ( '\t' == character ) )
        {
            // Ignore source whitespace outside strings; the logger supplies its own layout.
        }
        else
        {
            log_printf( &logger, "%c", character );
        }
    }

    // Keep a final opening token visible if the received JSON is incomplete.
    if ( pending_open )
    {
        log_printf( &logger, "%c", pending_open_char );
    }
}

static err_t devicedrive_process ( devicedrive_t *ctx )
{
    #define PROCESS_BYTE_LIMIT      200

    uint8_t rx_byte;
    uint16_t index;
    err_t error_flag = DEVICEDRIVE_ERROR;

    for ( index = 0; ( index < PROCESS_BYTE_LIMIT ) && ( DEVICEDRIVE_ERROR == error_flag ); index++ )
    {
        if ( 1 != devicedrive_generic_read( ctx, &rx_byte, 1 ) )
        {
            break;
        }

        if ( DEVICEDRIVE_STX == rx_byte )
        {
            devicedrive_clear_app_buf( );
            app_startup_stx = true;
        }
        else if ( app_startup_stx && ( DEVICEDRIVE_ETX == rx_byte ) )
        {
            strcpy( app_buf, DEVICEDRIVE_RSP_READY );
            app_buf_len = 2;
            app_startup_stx = false;
            error_flag = DEVICEDRIVE_OK;
        }
        else
        {
            app_startup_stx = false;
            if ( DEVICEDRIVE_EOT == rx_byte )
            {
                // Terminate the complete frame before response matching and logging.
                app_buf[ app_buf_len ] = 0;
                if ( app_buf_overflow )
                {
                    error_flag = DEVICEDRIVE_ERROR_OVERFLOW;
                }
                else
                {
                    error_flag = DEVICEDRIVE_OK;
                }
            }
            else if ( app_buf_len || ( '{' == rx_byte ) )
            {
                // Ignore boot ROM output before JSON. Drain oversized frames through EOT.
                if ( app_buf_len < APP_BUFFER_SIZE )
                {
                    app_buf[ app_buf_len++ ] = rx_byte;
                }
                else
                {
                    app_buf_overflow = true;
                }
            }
        }
    }
    return error_flag;
}

static err_t devicedrive_read_response ( devicedrive_t *ctx, char *rsp, uint32_t max_rsp_time )
{
    uint32_t elapsed;
    err_t process_result;
    err_t error_flag = DEVICEDRIVE_ERROR_TIMEOUT;

    devicedrive_clear_app_buf( );
    for ( elapsed = 0; ( elapsed < max_rsp_time ) && ( DEVICEDRIVE_ERROR_TIMEOUT == error_flag ); elapsed++ )
    {
        process_result = devicedrive_process( ctx );
        if ( DEVICEDRIVE_OK == process_result )
        {
            devicedrive_log_app_buf( );
            if ( 0 == strncmp( app_buf, DEVICEDRIVE_RSP_ERROR, strlen( DEVICEDRIVE_RSP_ERROR ) ) )
            {
                if ( strstr( app_buf, DEVICEDRIVE_RSP_UNKNOWN_COMMAND ) )
                {
                    error_flag = DEVICEDRIVE_ERROR_UNSUPPORTED;
                }
                else
                {
                    error_flag = DEVICEDRIVE_ERROR_RESPONSE;
                }
            }
            else if ( strstr( app_buf, rsp ) )
            {
                error_flag = DEVICEDRIVE_OK;
            }
            else if ( 0 == strcmp( app_buf, DEVICEDRIVE_RSP_READY ) )
            {
                error_flag = DEVICEDRIVE_ERROR_RESTARTED;
            }
            else
            {
                // An asynchronous notification is not the pending command's response.
                devicedrive_clear_app_buf( );
            }
        }
        else if ( DEVICEDRIVE_ERROR_OVERFLOW == process_result )
        {
            log_error( &logger, " Response exceeds APP_BUFFER_SIZE." );
            error_flag = process_result;
        }
        Delay_1ms( );
    }
    if ( DEVICEDRIVE_ERROR_TIMEOUT == error_flag )
    {
        log_error( &logger, " Response timeout." );
    }
    return error_flag;
}

static err_t devicedrive_power_up ( devicedrive_t *ctx )
{
    #define STARTUP_TIMEOUT_MS      5000

    err_t error_flag;

    log_printf( &logger, ">>> Reset module.\r\n" );
    devicedrive_clear_app_buf( );
    devicedrive_hw_reset( ctx );
    error_flag = devicedrive_read_response( ctx, DEVICEDRIVE_RSP_READY, STARTUP_TIMEOUT_MS );
    return error_flag;
}

static err_t devicedrive_config_example ( devicedrive_t *ctx )
{
    #define CONFIG_TIMEOUT_MS       10000

    err_t error_flag;

    log_printf( &logger, ">>> Configure error reporting and clear saved cloud credentials.\r\n" );
    // Never forward a previously provisioned token or product key to the public echo service.
    error_flag = devicedrive_cmd_set( ctx, DEVICEDRIVE_CMD_SETUP,
                                     "\"error_mode\":\"all\",\"debug_mode\":\"none\",\"silent_connect\":1,\"visibility\":0,"
                                     "\"token\":\"\",\"product_key\":\"\"" );
    if ( DEVICEDRIVE_OK == error_flag )
    {
        error_flag = devicedrive_read_response( ctx, DEVICEDRIVE_RSP_OK, CONFIG_TIMEOUT_MS );
    }
    if ( DEVICEDRIVE_OK == error_flag )
    {
        log_printf( &logger, ">>> Set HTTPS endpoint: %s\r\n", APP_SERVER_URL );
        error_flag = devicedrive_set_server( ctx, APP_SERVER_URL );
    }
    if ( DEVICEDRIVE_OK == error_flag )
    {
        error_flag = devicedrive_read_response( ctx, DEVICEDRIVE_RSP_OK, CONFIG_TIMEOUT_MS );
    }
    if ( DEVICEDRIVE_OK == error_flag )
    {
        log_printf( &logger, ">>> Configure WiFi network.\r\n" );
        error_flag = devicedrive_set_network( ctx, APP_WIFI_SSID, APP_WIFI_PASSWORD );
    }
    if ( DEVICEDRIVE_OK == error_flag )
    {
        error_flag = devicedrive_read_response( ctx, DEVICEDRIVE_RSP_OK, CONFIG_TIMEOUT_MS );
    }
    return error_flag;
}

static err_t devicedrive_example ( devicedrive_t *ctx )
{
    #define STATUS_TIMEOUT_MS       5000
    #define ECHO_TIMEOUT_MS         60000

    char message[ sizeof( APP_TEXT_MESSAGE ) + 48 ];
    char packet_digits[ 10 ];
    uint16_t message_index;
    uint8_t digit_count;
    uint8_t digit_index;
    uint32_t packet_value;
    err_t error_flag;

    log_printf( &logger, ">>> Get connection status.\r\n" );
    error_flag = devicedrive_cmd_run( ctx, DEVICEDRIVE_CMD_STATUS );
    if ( DEVICEDRIVE_OK == error_flag )
    {
        error_flag = devicedrive_read_response( ctx, DEVICEDRIVE_RSP_STATUS, STATUS_TIMEOUT_MS );
    }
    if ( DEVICEDRIVE_OK == error_flag )
    {
        if ( strstr( app_buf, DEVICEDRIVE_RSP_GOT_IP ) )
        {
            packet_counter++;
            strcpy( message, "{\"message\":\"" APP_TEXT_MESSAGE "\",\"packet\":" );
            message_index = strlen( message );
            packet_value = packet_counter;
            digit_count = 0;
            do
            {
                packet_digits[ digit_count++ ] = '0' + ( packet_value % 10 );
                packet_value /= 10;
            }
            while ( packet_value && ( digit_count < sizeof( packet_digits ) ) );
            for ( digit_index = 0; digit_index < digit_count; digit_index++ )
            {
                message[ message_index++ ] = packet_digits[ digit_count - digit_index - 1 ];
            }
            message[ message_index ] = 0;
            log_printf( &logger, ">>> Send message: %s\r\n", message );
            error_flag = devicedrive_send_message( ctx, message, DEVICEDRIVE_SEND_RECEIVE );
            if ( DEVICEDRIVE_OK == error_flag )
            {
                error_flag = devicedrive_read_response( ctx, "\"json\":", ECHO_TIMEOUT_MS );
            }
        }
        else
        {
            log_printf( &logger, ">>> Waiting for WiFi connection. Check the network credentials and signal.\r\n" );
        }
    }
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    return error_flag;
}

// ------------------------------------------------------------------------ END
