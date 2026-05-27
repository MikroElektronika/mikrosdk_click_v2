/*!
 * @file main.c
 * @brief ST67W Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to a WiFi network and
 * sending TCP/UDP messages to an echo server, or processing data from a connected BLE device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - ST67W_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *
 *  - ST67W_CONFIG_CONNECTION:
 * Configures connection to WiFi or BLE depending on the selected example.
 *
 *  - ST67W_EXAMPLE:
 * Depending on the selected demo example, it sends a TCP/UDP message to an echo server over a WiFi network or 
 * processes all data from a connected BLE device and sends back an adequate response message.
 *
 * By default, the WiFi TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void st67w_clear_app_buf ( void )
 * - static void st67w_log_app_buf ( void )
 * - static err_t st67w_process ( st67w_t *ctx )
 * - static err_t st67w_read_response ( st67w_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t st67w_power_up ( st67w_t *ctx )
 * - static err_t st67w_config_connection ( st67w_t *ctx )
 * - static err_t st67w_example ( st67w_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the BLE example test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "st67w.h"
#include "conversions.h"
#include "generic_pointer.h"

#ifndef MIKROBUS_POSITION_ST67W
    #define MIKROBUS_POSITION_ST67W MIKROBUS_1
#endif

// Example selection macros
#define EXAMPLE_WIFI            0               // Example of sending messages to a TCP/UDP echo server over WiFi
#define EXAMPLE_BLE             1               // Example of processing data from BLE connected device
#define DEMO_EXAMPLE            EXAMPLE_WIFI    // Example selection macro

// WiFi credentials
#define WIFI_SSID               "MIKROE GUEST"
#define WIFI_PASSWORD           "!guest.mikroe!"

// WiFi TCP/UDP example parameters
#define REMOTE_IP               "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT             "51111"         // TCP/UDP echo server port

// BLE device name
#define BLE_NAME                "ST67W Click"

// Message content
#define MESSAGE_CONTENT         "ST67W Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE         600
#define PROCESS_BUFFER_SIZE     200

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    ST67W_POWER_UP = 1,
    ST67W_CONFIG_CONNECTION,
    ST67W_EXAMPLE

} st67w_app_state_t;

static st67w_t st67w;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static st67w_app_state_t app_state = ST67W_POWER_UP;

/**
 * @brief ST67W clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void st67w_clear_app_buf ( void );

/**
 * @brief ST67W log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void st67w_log_app_buf ( void );

/**
 * @brief ST67W data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t st67w_process ( st67w_t *ctx );

/**
 * @brief ST67W read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t st67w_read_response ( st67w_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief ST67W power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t st67w_power_up ( st67w_t *ctx );

/**
 * @brief ST67W config connection function.
 * @details This function configures connection to WiFi or BLE depending on the selected example.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t st67w_config_connection ( st67w_t *ctx );

/**
 * @brief ST67W example function.
 * @details This function performs a WiFi TCP/UDP or a BLE device terminal example.
 * @param[in] ctx : Click context object.
 * See #st67w_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t st67w_example ( st67w_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    st67w_cfg_t st67w_cfg;  /**< Click config object. */

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
    st67w_cfg_setup( &st67w_cfg );
    ST67W_MAP_MIKROBUS( st67w_cfg, MIKROBUS_POSITION_ST67W );
    if ( SPI_MASTER_ERROR == st67w_init( &st67w, &st67w_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = ST67W_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case ST67W_POWER_UP:
        {
            if ( ST67W_OK == st67w_power_up( &st67w ) )
            {
                app_state = ST67W_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case ST67W_CONFIG_CONNECTION:
        {
            if ( ST67W_OK == st67w_config_connection( &st67w ) )
            {
                app_state = ST67W_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case ST67W_EXAMPLE:
        {
            st67w_example( &st67w );
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

static void st67w_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void st67w_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t st67w_process ( st67w_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = st67w_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return ST67W_OK;
    }
    return ST67W_ERROR;
}

static err_t st67w_read_response ( st67w_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    st67w_clear_app_buf( );
    st67w_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, ST67W_RSP_ERROR ) ) &&
            ( 0 == strstr( app_buf, ST67W_RSP_SEND_FAIL ) ) )
    {
        st67w_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            st67w_log_app_buf( );
            st67w_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return ST67W_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    st67w_process( ctx );
    st67w_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return ST67W_OK;
    }
    return ST67W_ERROR_CMD;
}

static err_t st67w_power_up ( st67w_t *ctx )
{
    err_t error_flag = ST67W_OK;

    log_printf( &logger, ">>> Perform device hardware reset.\r\n" );
    st67w_reset_device ( ctx );
    error_flag |= st67w_read_response( ctx, ST67W_URC_READY, ST67W_MAX_RSP_TIME_READY );
    
    log_printf( &logger, ">>> Check communication.\r\n" );
    st67w_cmd_run( ctx, ST67W_CMD_AT );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Reset to factory settings.\r\n" );
    st67w_cmd_run( ctx, ST67W_CMD_FACTORY_RESET );
    error_flag |= st67w_read_response( ctx, ST67W_URC_READY, ST67W_MAX_RSP_TIME_FACTORY_RESET );
    
    log_printf( &logger, ">>> Get device version.\r\n" );
    st67w_cmd_run( ctx, ST67W_CMD_GET_VERSION );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t st67w_config_connection ( st67w_t *ctx )
{
    err_t error_flag = ST67W_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_WIFI )
    log_printf( &logger, ">>> Set WiFi mode to station.\r\n" );
    #define WIFI_MODE_STATION "1"
    st67w_cmd_set( ctx, ST67W_CMD_SET_WIFI_MODE, WIFI_MODE_STATION );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Connect to WiFi access point.\r\n" );
    st67w_clear_app_buf( );
    strcpy ( app_buf, "\"" );
    strcat ( app_buf, WIFI_SSID );
    strcat ( app_buf, "\",\"" );
    strcat ( app_buf, WIFI_PASSWORD );
    strcat ( app_buf, "\"" );
    st67w_cmd_set( ctx, ST67W_CMD_CONNECT_TO_AP, app_buf );
    error_flag |= st67w_read_response( ctx, ST67W_URC_WIFI_CONNECTED, ST67W_MAX_RSP_TIME_WIFI_CONNECT );
    
    log_printf( &logger, ">>> Enable multiple connections.\r\n" );
    #define CONNECTION_MODE_MULTIPLE "1"
    st67w_cmd_set( ctx, ST67W_CMD_SET_MULTIPLE_CONNECTION_MODE, CONNECTION_MODE_MULTIPLE );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Set socket receiving mode to passive.\r\n" );
    #define RECEIVING_MODE_PASSIVE "1"
    st67w_cmd_set( ctx, ST67W_CMD_SET_SOCKET_RECEIVING_MODE, RECEIVING_MODE_PASSIVE );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_BLE )
    log_printf( &logger, ">>> Initialize BLE role as server.\r\n" );
    #define BLE_INIT_SERVER "2"
    st67w_cmd_set( ctx, ST67W_CMD_BLE_INIT, BLE_INIT_SERVER );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set BLE device name.\r\n" );
    st67w_clear_app_buf( );
    strcpy ( app_buf, "\"" );
    strcat ( app_buf, BLE_NAME );
    strcat ( app_buf, "\"" );
    st67w_cmd_set( ctx, ST67W_CMD_BLE_NAME, app_buf );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get BLE address.\r\n" );
    st67w_cmd_get( ctx, ST67W_CMD_BLE_ADDRESS );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Create GATT server.\r\n" );
    #define BLE_GATT_SERVER "0,\"6E400001C35211E5953D0002A5D5C51B\",1,2"
    st67w_cmd_set( ctx, ST67W_CMD_BLE_GATTS_SERVICE_CREATE, BLE_GATT_SERVER );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Create GATT service write characteristics.\r\n" );
    #define BLE_GATT_SERVICE_CHAR_WR_WO_RSP "0,0,\"6E400001C35211E5953D0002A5D5C51C\",4,2,2"
    st67w_cmd_set( ctx, ST67W_CMD_BLE_GATTS_CHAR_CREATE, BLE_GATT_SERVICE_CHAR_WR_WO_RSP );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Create GATT service notify characteristics.\r\n" );
    #define BLE_GATT_SERVICE_CHAR_NTFY "0,1,\"6E400001C35211E5953D0002A5D5C51D\",16,2,2"
    st67w_cmd_set( ctx, ST67W_CMD_BLE_GATTS_CHAR_CREATE, BLE_GATT_SERVICE_CHAR_NTFY );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Register GATT service.\r\n" );
    st67w_cmd_set( ctx, "AT+BLEGATTSREGISTER", "1" );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Start BLE advertising.\r\n" );
    st67w_cmd_run( ctx, ST67W_CMD_BLE_START_ADVERTISING );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set BLE advertising data.\r\n" );
    #define BLE_ADV_DATA_FLAGS "020106"
    #define BLE_ADV_DATA_COMPLETE_LOCAL_NAME "09"
    uint8_t ble_name[ 32 ] = { 0 };
    uint8_t hex_buf[ 3 ] = { 0 };
    st67w_clear_app_buf( );
    strcpy ( app_buf, "\"" );
    strcat ( app_buf, BLE_ADV_DATA_FLAGS );
    uint8_to_hex( strlen( BLE_NAME ) + 1, hex_buf );
    strcat ( app_buf, hex_buf );
    strcat ( app_buf, BLE_ADV_DATA_COMPLETE_LOCAL_NAME );
    strcpy ( ble_name, BLE_NAME );
    for ( int16_t cnt = 0; cnt < strlen( BLE_NAME ); cnt++ ) 
    {
        uint8_to_hex ( ble_name[ cnt ], hex_buf );
        strcat ( app_buf, hex_buf );
    }
    strcat ( app_buf, "\"" );
    st67w_cmd_set( ctx, ST67W_CMD_BLE_SET_ADVERTISING_DATA, app_buf );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

#else
    #error "No demo example selected"
#endif
    return error_flag;
}

static err_t st67w_example ( st67w_t *ctx )
{
    err_t error_flag = ST67W_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_WIFI )
    uint8_t cmd_buf[ 100 ] = { 0 };
    
    log_printf( &logger, ">>> Start TCP connection.\r\n" );
    #define TCP_LINK_NUM "0"
    #define TCP_CONN_TYPE "TCP"
    strcpy( cmd_buf, TCP_LINK_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, TCP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    st67w_cmd_set( &st67w, ST67W_CMD_ESTABLISH_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_TCP_CONNECT );

    log_printf( &logger, ">>> Start UDP connection.\r\n" );
    #define UDP_LINK_NUM "1"
    #define UDP_CONN_TYPE "UDP"
    strcpy( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, UDP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    st67w_cmd_set( &st67w, ST67W_CMD_ESTABLISH_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    strcpy( cmd_buf, TCP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    st67w_cmd_set( &st67w, ST67W_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 100 );
    st67w_generic_write ( &st67w, MESSAGE_CONTENT, message_len );
    error_flag |= st67w_read_response( ctx, ST67W_URC_RECEIVED_DATA, ST67W_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    strcpy( cmd_buf, TCP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    st67w_cmd_set( &st67w, ST67W_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    st67w_cmd_set( &st67w, ST67W_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 100 );
    st67w_generic_write ( &st67w, MESSAGE_CONTENT, message_len );
    error_flag |= st67w_read_response( ctx, ST67W_URC_RECEIVED_DATA, ST67W_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    st67w_cmd_set( &st67w, ST67W_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    st67w_cmd_set( &st67w, ST67W_CMD_CLOSE_TCP_UDP_CONNECTION, TCP_LINK_NUM );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    st67w_cmd_set( &st67w, ST67W_CMD_CLOSE_TCP_UDP_CONNECTION, UDP_LINK_NUM );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_BLE )
    uint8_t * __generic_ptr urc_buf_ptr = 0;
    uint8_t ble_conn_index[ 2 ] = { 0 };
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint32_t timeout_cnt = 0;

    #define BLE_TERMINAL_TIMEOUT_MS         60000
    #define BLE_TERMINAL_MESSAGE_FREQ_MS    5000
    #define TERMINATION_CMD                 "END"
    #define TERMINATION_RESPONSE            "Acknowledged, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT             "Timeout, closing the connection in a few seconds."
    #define SRV_AND_CHAR_INDEX              "0,1"

    log_printf( &logger, ">>> Get BLE name.\r\n" );
    st67w_cmd_get( ctx, ST67W_CMD_BLE_NAME );
    error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Waiting for a BLE peer to establish connection with the Click board...\r\n" );
    while ( ST67W_OK != st67w_read_response( ctx, ST67W_URC_BLE_CONNECTED, ST67W_MAX_RSP_TIME_BLE_CONNECT ) );

    urc_buf_ptr = strstr( app_buf, ST67W_URC_BLE_CONNECTED ) + strlen ( ST67W_URC_BLE_CONNECTED );
    ble_conn_index[ 0 ] = *urc_buf_ptr;

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        st67w_clear_app_buf( );
        if ( ST67W_OK == st67w_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            st67w_process( ctx );
            st67w_log_app_buf( );
            if ( strstr( app_buf, ST67W_URC_BLE_DISCONNECTED ) )
            {
                log_printf( &logger, ">>> BLE client has terminated the connection.\r\n" );
                break;
            }
            else if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminate connection on demand.\r\n" );
                st67w_clear_app_buf( );
                strcpy( app_buf, SRV_AND_CHAR_INDEX );
                strcat( app_buf, "," );
                uint16_to_str( strlen( TERMINATION_RESPONSE ) + 2, message_len_buf );
                l_trim( message_len_buf );
                r_trim( message_len_buf );
                strcat( app_buf, message_len_buf );
                st67w_cmd_set( &st67w, ST67W_CMD_BLE_GATTS_NOTIFY, app_buf );
                st67w_cmd_run ( ctx, TERMINATION_RESPONSE );
                error_flag |= st67w_read_response( ctx, ST67W_RSP_SEND_OK, ST67W_MAX_RSP_TIME_DEFAULT );
                log_printf( &logger, ">>> Disconnecting device.\r\n" );
                st67w_cmd_set( &st67w, ST67W_CMD_BLE_DISCONNECT, ble_conn_index );
                error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BLE_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            st67w_clear_app_buf( );
            strcpy( app_buf, SRV_AND_CHAR_INDEX );
            strcat( app_buf, "," );
            uint16_to_str( strlen( MESSAGE_CONTENT ) + 2, message_len_buf );
            l_trim( message_len_buf );
            r_trim( message_len_buf );
            strcat( app_buf, message_len_buf );
            st67w_cmd_set( &st67w, ST67W_CMD_BLE_GATTS_NOTIFY, app_buf );
            st67w_cmd_run ( ctx, MESSAGE_CONTENT );
            error_flag |= st67w_read_response( ctx, ST67W_RSP_SEND_OK, ST67W_MAX_RSP_TIME_DEFAULT );
        }
        if ( BLE_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminate connection due to 60s timeout expiration.\r\n" );
            st67w_clear_app_buf( );
            strcpy( app_buf, SRV_AND_CHAR_INDEX );
            strcat( app_buf, "," );
            uint16_to_str( strlen( TERMINATION_TIMEOUT ) + 2, message_len_buf );
            l_trim( message_len_buf );
            r_trim( message_len_buf );
            strcat( app_buf, message_len_buf );
            st67w_cmd_set( &st67w, ST67W_CMD_BLE_GATTS_NOTIFY, app_buf );
            st67w_cmd_run ( ctx, TERMINATION_TIMEOUT );
            error_flag |= st67w_read_response( ctx, ST67W_RSP_SEND_OK, ST67W_MAX_RSP_TIME_DEFAULT );
            log_printf( &logger, ">>> Disconnecting device.\r\n" );
            st67w_cmd_set( &st67w, ST67W_CMD_BLE_DISCONNECT, ble_conn_index );
            error_flag |= st67w_read_response( ctx, ST67W_RSP_OK, ST67W_MAX_RSP_TIME_DEFAULT );
            break;
        }
        Delay_ms ( 1 );
    }
#else
    #error "No demo example selected"
#endif
    return error_flag;
}

// ------------------------------------------------------------------------ END
