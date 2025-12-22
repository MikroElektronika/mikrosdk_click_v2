/*!
 * @file main.c
 * @brief LTE IoT 23 Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending SMS or TCP/UDP messages using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LTEIOT23_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *
 *  - LTEIOT23_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - LTEIOT23_CHECK_CONNECTION:
 * Waits for the network registration indicated via CEREG command and then checks 
 * the signal quality report.
 *
 *  - LTEIOT23_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - LTEIOT23_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode)
 * or TCP/UDP message.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void lteiot23_clear_app_buf ( void )
 * - static void lteiot23_log_app_buf ( void )
 * - static err_t lteiot23_process ( lteiot23_t *ctx )
 * - static err_t lteiot23_read_response ( lteiot23_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t lteiot23_power_up ( lteiot23_t *ctx )
 * - static err_t lteiot23_config_connection ( lteiot23_t *ctx )
 * - static err_t lteiot23_check_connection ( lteiot23_t *ctx )
 * - static err_t lteiot23_config_example ( lteiot23_t *ctx )
 * - static err_t lteiot23_example ( lteiot23_t *ctx )
 *
 * @note
 * In order for the examples to work, user needs to set the APN and SMSC (SMS PDU mode only)
 * of entered SIM card as well as the phone number (SMS mode only) to which he wants to send an SMS.
 * Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER.
 * Example:
    SIM_APN "internet"
    SIM_SMSC "+381610401"
    PHONE_NUMBER "+381659999999"
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lteiot23.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM APN config
#define SIM_APN                             ""              // Set valid SIM APN

// SMS example parameters
#define SIM_SMSC                            ""              // Set valid SMS Service Center Address - only in SMS PDU mode
#define PHONE_NUMBER                        ""              // Set Phone number to message
#define SMS_MODE                            "1"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "LTE IoT 23 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTEIOT23_POWER_UP = 1,
    LTEIOT23_CONFIG_CONNECTION,
    LTEIOT23_CHECK_CONNECTION,
    LTEIOT23_CONFIG_EXAMPLE,
    LTEIOT23_EXAMPLE

} lteiot23_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static lteiot23_app_state_t app_state = LTEIOT23_POWER_UP;

static lteiot23_t lteiot23;
static log_t logger;

/**
 * @brief LTE IoT 23 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lteiot23_clear_app_buf ( void );

/**
 * @brief LTE IoT 23 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lteiot23_log_app_buf ( void );

/**
 * @brief LTE IoT 23 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lteiot23_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot23_process ( lteiot23_t *ctx );

/**
 * @brief LTE IoT 23 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lteiot23_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot23_read_response ( lteiot23_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief LTE IoT 23 power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lteiot23_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot23_power_up ( lteiot23_t *ctx );

/**
 * @brief LTE IoT 23 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #lteiot23_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot23_config_connection ( lteiot23_t *ctx );

/**
 * @brief LTE IoT 23 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #lteiot23_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot23_check_connection ( lteiot23_t *ctx );

/**
 * @brief LTE IoT 23 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #lteiot23_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot23_config_example ( lteiot23_t *ctx );

/**
 * @brief LTE IoT 23 example function.
 * @details This function executes SMS or TCP/UDP example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #lteiot23_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot23_example ( lteiot23_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot23_cfg_t lteiot23_cfg;  /**< Click config object. */

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
    lteiot23_cfg_setup( &lteiot23_cfg );
    LTEIOT23_MAP_MIKROBUS( lteiot23_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot23_init( &lteiot23, &lteiot23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT23_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LTEIOT23_POWER_UP:
        {
            if ( LTEIOT23_OK == lteiot23_power_up( &lteiot23 ) )
            {
                app_state = LTEIOT23_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_CONFIG_CONNECTION:
        {
            if ( LTEIOT23_OK == lteiot23_config_connection( &lteiot23 ) )
            {
                app_state = LTEIOT23_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_CHECK_CONNECTION:
        {
            if ( LTEIOT23_OK == lteiot23_check_connection( &lteiot23 ) )
            {
                app_state = LTEIOT23_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_CONFIG_EXAMPLE:
        {
            if ( LTEIOT23_OK == lteiot23_config_example( &lteiot23 ) )
            {
                app_state = LTEIOT23_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_EXAMPLE:
        {
            lteiot23_example( &lteiot23 );
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

static void lteiot23_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lteiot23_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot23_process ( lteiot23_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lteiot23_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTEIOT23_OK;
    }
    return LTEIOT23_ERROR;
}

static err_t lteiot23_read_response ( lteiot23_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    lteiot23_clear_app_buf ( );
    lteiot23_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTEIOT23_RSP_ERROR ) ) )
    {
        lteiot23_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            lteiot23_log_app_buf( );
            lteiot23_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            log_printf( &logger, "--------------------------------\r\n" );
            return LTEIOT23_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lteiot23_process( ctx );
    lteiot23_log_app_buf( );
    log_printf( &logger, "--------------------------------\r\n" );
    if ( strstr( app_buf, rsp ) )
    {
        return LTEIOT23_OK;
    }
    return LTEIOT23_ERROR_CMD;
}

static err_t lteiot23_power_up ( lteiot23_t *ctx )
{
    err_t error_flag = LTEIOT23_ERROR;

    while ( LTEIOT23_OK != error_flag )
    {
        log_printf( &logger, ">>> Power down device.\r\n" );
        lteiot23_set_power_state ( ctx, LTEIOT23_POWER_STATE_OFF );

        log_printf( &logger, ">>> Power up device.\r\n" );
        lteiot23_set_power_state ( ctx, LTEIOT23_POWER_STATE_ON );
        error_flag = lteiot23_read_response( ctx, LTEIOT23_URC_BOOT_EVENT, LTEIOT23_MAX_RSP_TIME_URC );
    }

    log_printf( &logger, ">>> Check communication.\r\n" );
    lteiot23_cmd_run( ctx, LTEIOT23_CMD_AT );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device model ID.\r\n" );
    lteiot23_cmd_run( ctx, LTEIOT23_CMD_GET_MODEL_ID );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    lteiot23_cmd_run( ctx, LTEIOT23_CMD_GET_SW_VERSION );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    lteiot23_cmd_run( ctx, LTEIOT23_CMD_GET_SERIAL_NUM );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t lteiot23_config_connection ( lteiot23_t *ctx )
{
    err_t error_flag = LTEIOT23_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Set minimum functionality.\r\n" );
    #define MIN_FUNCTIONALITY "0"
    lteiot23_cmd_set( ctx, LTEIOT23_CMD_SET_UE_FUNCTIONALITY, MIN_FUNCTIONALITY );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_CFUN );
    
    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    lteiot23_set_sim_apn( ctx, SIM_APN );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_CGDCONT );

    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    lteiot23_cmd_set( ctx, LTEIOT23_CMD_SET_UE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    lteiot23_cmd_set( ctx, LTEIOT23_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );
#endif
    return error_flag;
}

static err_t lteiot23_check_connection ( lteiot23_t *ctx )
{
    err_t error_flag = LTEIOT23_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    lteiot23_cmd_get ( &lteiot23, LTEIOT23_CMD_NETWORK_REGISTRATION );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, LTEIOT23_URC_NETWORK_REGISTERED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        lteiot23_cmd_run( &lteiot23, LTEIOT23_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );
    }
    else
    {
        error_flag = LTEIOT23_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t lteiot23_config_example ( lteiot23_t *ctx )
{
    err_t error_flag = LTEIOT23_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    lteiot23_cmd_set( &lteiot23, LTEIOT23_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Enable socket events.\r\n" );
    #define ENABLE_SOCKET_EVENTS "0,1"
    lteiot23_cmd_set( &lteiot23, LTEIOT23_CMD_SOCKET_EVENTS, ENABLE_SOCKET_EVENTS );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    lteiot23_cmd_set( &lteiot23, LTEIOT23_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );
#endif
    return error_flag;
}

static err_t lteiot23_example ( lteiot23_t *ctx )
{
    err_t error_flag = LTEIOT23_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 200 ] = { 0 };
    log_printf( &logger, ">>> Allocate TCP socket.\r\n" );
    #define SOCKET_CMD_ALLOCATE "ALLOCATE"
    #define SOCKET_CMD_ACTIVATE "ACTIVATE"
    #define SOCKET_CMD_SEND "SEND"
    #define SOCKET_CMD_RECEIVE "RECEIVE"
    #define SOCKET_CMD_DELETE "DELETE"
    #define TCP_SOCKET_NUM "1"
    #define TCP_CONN_TYPE "TCP"
    #define CONN_MODE "OPEN"
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_ALLOCATE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, TCP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, CONN_MODE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_ACTIVATE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_URC );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    uint8_t byte_buf[ 5 ] = { 0 };
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_SEND );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    for ( uint16_t cnt = 0; cnt < message_len; cnt++ ) 
    {
        uint8_to_hex ( MESSAGE_CONTENT[ cnt ], byte_buf );
        strcat ( cmd_buf, byte_buf );
    }
    strcat( cmd_buf, "\"" );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_URC_SOCKET_DATA_EVENT, LTEIOT23_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_RECEIVE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot23_cmd_set( &lteiot23, LTEIOT23_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );

    // Parse response
    uint8_t response[ 100 ] = { 0 };
    uint8_t response_len[ 5 ] = { 0 };
    char * __generic_ptr start_response_len_buf = 0;
    uint8_t response_len_buf_len = 0;
    start_response_len_buf = strstr( app_buf, LTEIOT23_URC_SOCKET_DATA ) + strlen ( LTEIOT23_URC_SOCKET_DATA ) + 2;
    response_len_buf_len = strstr( start_response_len_buf, "," ) - start_response_len_buf;
    memcpy ( response_len, start_response_len_buf, response_len_buf_len );
    memcpy ( response, start_response_len_buf + response_len_buf_len + 4, atoi( response_len ) * 2 );
    for ( uint8_t cnt = 0; cnt < atoi( response_len ); cnt++ )
    {
        response[ cnt ] = hex_to_uint8 ( &response[ cnt * 2 ] );
    }
    response[ atoi( response_len ) ] = 0;
    log_printf( &logger, ">>> Parse response\r\n" );
    log_printf( &logger, "%s\r\n", response );
    log_printf( &logger, "--------------------------------\r\n" );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_DELETE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Allocate UDP socket.\r\n" );
    #define UDP_SOCKET_NUM "1"
    #define UDP_CONN_TYPE "UDP"
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_ALLOCATE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, UDP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, CONN_MODE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_ACTIVATE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_SEND );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    for ( uint16_t cnt = 0; cnt < message_len; cnt++ ) 
    {
        uint8_to_hex ( MESSAGE_CONTENT[ cnt ], byte_buf );
        strcat ( cmd_buf, byte_buf );
    }
    strcat( cmd_buf, "\"" );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_URC_SOCKET_DATA_EVENT, LTEIOT23_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_RECEIVE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot23_cmd_set( &lteiot23, LTEIOT23_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );

    // Parse response
    start_response_len_buf = strstr( app_buf, LTEIOT23_URC_SOCKET_DATA ) + strlen ( LTEIOT23_URC_SOCKET_DATA ) + 2;
    response_len_buf_len = strstr( start_response_len_buf, "," ) - start_response_len_buf;
    memcpy ( response_len, start_response_len_buf, response_len_buf_len );
    memcpy ( response, start_response_len_buf + response_len_buf_len + 4, atoi( response_len ) * 2 );
    for ( uint8_t cnt = 0; cnt < atoi( response_len ); cnt++ )
    {
        response[ cnt ] = hex_to_uint8 ( &response[ cnt * 2 ] );
    }
    response[ atoi( response_len ) ] = 0;
    log_printf( &logger, ">>> Parse response\r\n" );
    log_printf( &logger, "%s\r\n", response );
    log_printf( &logger, "--------------------------------\r\n" );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_DELETE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    lteiot23_cmd_set ( &lteiot23, LTEIOT23_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_URC );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    log_printf( &logger, ">>> Check SMS format.\r\n" );
    lteiot23_cmd_get( &lteiot23, LTEIOT23_CMD_SELECT_SMS_FORMAT );
    error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, LTEIOT23_URC_SMS_FORMAT_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        lteiot23_send_sms_pdu( &lteiot23, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_CMGS );
    }
    else if ( strstr( app_buf, LTEIOT23_URC_SMS_FORMAT_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        lteiot23_send_sms_text ( &lteiot23, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot23_read_response( ctx, LTEIOT23_RSP_OK, LTEIOT23_MAX_RSP_TIME_CMGS );
    }
    // 30 seconds delay
    for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
    {
        Delay_ms ( 1000 );
    }
#else
    #error "No demo example selected"
#endif
    return error_flag;
}

// ------------------------------------------------------------------------ END
