/*!
 * @file main.c
 * @brief Cordelia-I Click example
 *
 * # Description
 * This example demonstrates the use of the Cordelia-I Click board to connect to
 * a WiFi access point and establish an MQTT connection to a public broker. After
 * the initial device setup and network configuration, the application publishes
 * a predefined message to the selected MQTT topic and waits for an echo/receive
 * indication from the module, printing all responses on the UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Cordelia-I Click driver, then prepares the example
 * state machine. The application starts in the POWER UP state, where the device
 * is reset, communication is verified, factory settings are restored, and system
 * information is read. After successful initialization, the application proceeds
 * to the connection configuration state.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - CORDELIAI_POWER_UP: 
 * Performs device reset, factory reset, and reads version info.
 *
 *  - CORDELIAI_CONFIG_CONNECTION:
 * Connects to the configured WiFi network and sets MQTT parameters (endpoint, port, client ID,
 * flags, subscribe/publish topic names), then connects to the MQTT server.
 *
 *  - CORDELIAI_EXAMPLE: 
 * Periodically publishes a message to the MQTT topic and waits for the module receive indication,
 * logging all traffic to the UART terminal.
 *
 * ## Additional Function
 * - static void cordeliai_clear_app_buf ( void )
 * - static void cordeliai_log_app_buf ( void )
 * - static err_t cordeliai_process ( cordeliai_t *ctx )
 * - static err_t cordeliai_read_response ( cordeliai_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t cordeliai_power_up ( cordeliai_t *ctx )
 * - static err_t cordeliai_config_connection ( cordeliai_t *ctx )
 * - static err_t cordeliai_example ( cordeliai_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "cordeliai.h"

#ifndef MIKROBUS_POSITION_CORDELIAI
    #define MIKROBUS_POSITION_CORDELIAI MIKROBUS_1
#endif

// WiFi credentials
#define WIFI_SSID               "MIKROE GUEST"
#define WIFI_PASSWORD           "!guest.mikroe!"
#define WIFI_SECURITY           "WPA_WPA2"

// MQTT parameters
#define MQTT_ENDPOINT           "test.mosquitto.org"
#define MQTT_PORT               "1883"
#define MQTT_CLIENT_ID          "Cordelia-I_Click"
#define MQTT_FLAGS              "url"
#define MQTT_TOPIC_NAME         "apple"

// Message content
#define MESSAGE_CONTENT         "Cordelia-I Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE         256
#define PROCESS_BUFFER_SIZE     256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    CORDELIAI_POWER_UP = 1,
    CORDELIAI_CONFIG_CONNECTION,
    CORDELIAI_EXAMPLE

} cordeliai_app_state_t;

static cordeliai_t cordeliai;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static cordeliai_app_state_t app_state = CORDELIAI_POWER_UP;

/**
 * @brief Cordelia-I clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void cordeliai_clear_app_buf ( void );

/**
 * @brief Cordelia-I log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void cordeliai_log_app_buf ( void );

/**
 * @brief Cordelia-I data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t cordeliai_process ( cordeliai_t *ctx );

/**
 * @brief Cordelia-I read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t cordeliai_read_response ( cordeliai_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief Cordelia-I power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t cordeliai_power_up ( cordeliai_t *ctx );

/**
 * @brief Cordelia-I config connection function.
 * @details This function configures connection to network and MQTT test server parameters.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t cordeliai_config_connection ( cordeliai_t *ctx );

/**
 * @brief Cordelia-I example function.
 * @details This function performs sends message to MQTT test server and reads response.
 * @param[in] ctx : Click context object.
 * See #cordeliai_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t cordeliai_example ( cordeliai_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cordeliai_cfg_t cordeliai_cfg;  /**< Click config object. */

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
    cordeliai_cfg_setup( &cordeliai_cfg );
    CORDELIAI_MAP_MIKROBUS( cordeliai_cfg, MIKROBUS_POSITION_CORDELIAI );
    if ( UART_ERROR == cordeliai_init( &cordeliai, &cordeliai_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = CORDELIAI_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case CORDELIAI_POWER_UP:
        {
            if ( CORDELIAI_OK == cordeliai_power_up( &cordeliai ) )
            {
                app_state = CORDELIAI_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case CORDELIAI_CONFIG_CONNECTION:
        {
            if ( CORDELIAI_OK == cordeliai_config_connection( &cordeliai ) )
            {
                app_state = CORDELIAI_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case CORDELIAI_EXAMPLE:
        {
            cordeliai_example( &cordeliai );
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

static void cordeliai_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void cordeliai_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t cordeliai_process ( cordeliai_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = cordeliai_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return CORDELIAI_OK;
    }
    return CORDELIAI_ERROR;
}

static err_t cordeliai_read_response ( cordeliai_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    cordeliai_clear_app_buf ( );
    cordeliai_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, CORDELIAI_RSP_ERROR ) ) )
    {
        cordeliai_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            cordeliai_log_app_buf( );
            cordeliai_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return CORDELIAI_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    cordeliai_process( ctx );
    cordeliai_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return CORDELIAI_OK;
    }
    return CORDELIAI_ERROR_CMD;
}

static err_t cordeliai_power_up ( cordeliai_t *ctx )
{
    err_t error_flag = CORDELIAI_OK;

    log_printf( &logger, ">>> Perform device hardware reset.\r\n" );
    cordeliai_reset_device ( ctx );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_URC_READY, CORDELIAI_MAX_RSP_TIME_READY );
    
    log_printf( &logger, ">>> Check communication.\r\n" );
    cordeliai_cmd_run( ctx, CORDELIAI_CMD_TEST );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Reset to factory settings.\r\n" );
    cordeliai_cmd_run( ctx, CORDELIAI_CMD_FACTORY_RESET );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_URC_READY, CORDELIAI_MAX_RSP_TIME_FACTORY_RESET );
    
    log_printf( &logger, ">>> Get device version.\r\n" );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_GET, "general,version" );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t cordeliai_config_connection ( cordeliai_t *ctx )
{
    err_t error_flag = CORDELIAI_OK;
    log_printf( &logger, ">>> Connect to WiFi access point.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, WIFI_SSID );
    strcat ( app_buf, ",," );
    strcat ( app_buf, WIFI_SECURITY );
    strcat ( app_buf, "," );
    strcat ( app_buf, WIFI_PASSWORD );
    strcat ( app_buf, ",,," );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_WLAN_CONNECT, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_URC_WLAN_CONNECTED, CORDELIAI_MAX_RSP_TIME_WLAN_CONNECT );

    log_printf( &logger, ">>> Set MQTT endpoint.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, "MQTT,iotHubEndpoint,\"" );
    strcat ( app_buf, MQTT_ENDPOINT );
    strcat ( app_buf, "\"" );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_SET, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set MQTT port.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, "MQTT,iotHubPort," );
    strcat ( app_buf, MQTT_PORT );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_SET, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set MQTT client ID.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, "MQTT,clientId,\"" );
    strcat ( app_buf, MQTT_CLIENT_ID );
    strcat ( app_buf, "\"" );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_SET, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set MQTT flags.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, "MQTT,flags,\"" );
    strcat ( app_buf, MQTT_FLAGS );
    strcat ( app_buf, "\"" );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_SET, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set subtopic name.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, "SUBTOPIC0,name,\"" );
    strcat ( app_buf, MQTT_TOPIC_NAME );
    strcat ( app_buf, "\"" );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_SET, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set pubtopic name.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, "PUBTOPIC0,name,\"" );
    strcat ( app_buf, MQTT_TOPIC_NAME );
    strcat ( app_buf, "\"" );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_SET, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_RSP_OK, CORDELIAI_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Connect to MQTT server.\r\n" );
    cordeliai_cmd_run( ctx, CORDELIAI_CMD_IOT_CONNECT );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_URC_MQTT_CONNECTED, CORDELIAI_MAX_RSP_TIME_MQTT_CONNECT );
    return error_flag;
}

static err_t cordeliai_example ( cordeliai_t *ctx )
{
    err_t error_flag = CORDELIAI_OK;
    log_printf( &logger, ">>> Write message to MQTT server.\r\n" );
    cordeliai_clear_app_buf( );
    strcpy ( app_buf, "0,\"" );
    strcat ( app_buf, MESSAGE_CONTENT );
    strcat ( app_buf, "\"" );
    cordeliai_cmd_set( ctx, CORDELIAI_CMD_IOT_PUBLISH, app_buf );
    error_flag |= cordeliai_read_response( ctx, CORDELIAI_URC_MQTT_RECV_DATA, CORDELIAI_MAX_RSP_TIME_MQTT_ECHO_RECV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    return error_flag;
}

// ------------------------------------------------------------------------ END
