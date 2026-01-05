/*!
 * @file main.c
 * @brief NB IoT 7 Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending TCP/UDP messages using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - NBIOT7_POWER_UP:
 * Powers up the device, enables command echo, and reads system information.
 *
 *  - NBIOT7_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - NBIOT7_CHECK_CONNECTION:
 * Waits for the network registration indicated via CEREG command and then checks the signal quality report.
 *
 *  - NBIOT7_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - NBIOT7_EXAMPLE:
 * Sends a TCP/UDP message to the echo server.
 *
 * ## Additional Function
 * - static void nbiot7_clear_app_buf ( void )
 * - static void nbiot7_log_app_buf ( void )
 * - static err_t nbiot7_process ( nbiot7_t *ctx )
 * - static err_t nbiot7_read_response ( nbiot7_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t nbiot7_power_up ( nbiot7_t *ctx )
 * - static err_t nbiot7_config_connection ( nbiot7_t *ctx )
 * - static err_t nbiot7_check_connection ( nbiot7_t *ctx )
 * - static err_t nbiot7_config_example ( nbiot7_t *ctx )
 * - static err_t nbiot7_example ( nbiot7_t *ctx )
 *
 * @note
 * In order for the example to work, user needs to set the SIM_APN of entered SIM card.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nbiot7.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM APN config
#define SIM_APN                             ""              // Set valid SIM APN

// TCP/UDP example parameters
#define REMOTE_IP                           "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "NB IoT 7 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    NBIOT7_POWER_UP = 1,
    NBIOT7_CONFIG_CONNECTION,
    NBIOT7_CHECK_CONNECTION,
    NBIOT7_CONFIG_EXAMPLE,
    NBIOT7_EXAMPLE

} nbiot7_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static nbiot7_app_state_t app_state = NBIOT7_POWER_UP;

static nbiot7_t nbiot7;
static log_t logger;

/**
 * @brief NB IoT 7 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void nbiot7_clear_app_buf ( void );

/**
 * @brief NB IoT 7 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void nbiot7_log_app_buf ( void );

/**
 * @brief NB IoT 7 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot7_process ( nbiot7_t *ctx );

/**
 * @brief NB IoT 7 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot7_read_response ( nbiot7_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief NB IoT 7 power up function.
 * @details This function powers up the device, enables command echo and reads system information.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot7_power_up ( nbiot7_t *ctx );

/**
 * @brief NB IoT 7 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot7_config_connection ( nbiot7_t *ctx );

/**
 * @brief NB IoT 7 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot7_check_connection ( nbiot7_t *ctx );

/**
 * @brief NB IoT 7 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot7_config_example ( nbiot7_t *ctx );

/**
 * @brief NB IoT 7 example function.
 * @details This function executes TCP/UDP example.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot7_example ( nbiot7_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot7_cfg_t nbiot7_cfg;  /**< Click config object. */

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
    nbiot7_cfg_setup( &nbiot7_cfg );
    NBIOT7_MAP_MIKROBUS( nbiot7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot7_init( &nbiot7, &nbiot7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = NBIOT7_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case NBIOT7_POWER_UP:
        {
            if ( NBIOT7_OK == nbiot7_power_up( &nbiot7 ) )
            {
                app_state = NBIOT7_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_CONFIG_CONNECTION:
        {
            if ( NBIOT7_OK == nbiot7_config_connection( &nbiot7 ) )
            {
                app_state = NBIOT7_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_CHECK_CONNECTION:
        {
            if ( NBIOT7_OK == nbiot7_check_connection( &nbiot7 ) )
            {
                app_state = NBIOT7_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_CONFIG_EXAMPLE:
        {
            if ( NBIOT7_OK == nbiot7_config_example( &nbiot7 ) )
            {
                app_state = NBIOT7_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_EXAMPLE:
        {
            nbiot7_example( &nbiot7 );
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

static void nbiot7_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void nbiot7_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t nbiot7_process ( nbiot7_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = nbiot7_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return NBIOT7_OK;
    }
    return NBIOT7_ERROR;
}

static err_t nbiot7_read_response ( nbiot7_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    nbiot7_clear_app_buf ( );
    nbiot7_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, NBIOT7_RSP_ERROR ) ) )
    {
        nbiot7_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            nbiot7_log_app_buf( );
            nbiot7_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return NBIOT7_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    nbiot7_process( ctx );
    nbiot7_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return NBIOT7_OK;
    }
    return NBIOT7_ERROR_CMD;
}

static err_t nbiot7_power_up ( nbiot7_t *ctx )
{
    err_t error_flag = NBIOT7_ERROR;

    while ( NBIOT7_OK != error_flag )
    {
        log_printf( &logger, ">>> Power down device.\r\n" );
        nbiot7_set_power_state ( ctx, NBIOT7_POWER_STATE_OFF );

        log_printf( &logger, ">>> Power up device.\r\n" );
        nbiot7_set_power_state ( ctx, NBIOT7_POWER_STATE_ON );
        error_flag = nbiot7_read_response( ctx, NBIOT7_URC_AT_READY, NBIOT7_MAX_RSP_TIME_URC );

        if ( NBIOT7_OK == error_flag )
        {
            log_printf( &logger, ">>> Check communication.\r\n" );
            nbiot7_cmd_run( ctx, NBIOT7_CMD_AT );
            error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );
        }
    }
    log_printf( &logger, ">>> Enable command echo.\r\n" );
    nbiot7_cmd_run( ctx, NBIOT7_CMD_ENABLE_ECHO );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device model ID.\r\n" );
    nbiot7_cmd_run( ctx, NBIOT7_CMD_GET_MODEL_ID );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    nbiot7_cmd_run( ctx, NBIOT7_CMD_GET_SW_VERSION );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    nbiot7_cmd_run( ctx, NBIOT7_CMD_GET_SERIAL_NUM );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t nbiot7_config_connection ( nbiot7_t *ctx )
{
    err_t error_flag = NBIOT7_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    nbiot7_cmd_set( ctx, NBIOT7_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_COPS );

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    nbiot7_set_sim_apn( &nbiot7, SIM_APN );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    nbiot7_cmd_set( ctx, NBIOT7_CMD_SET_PHONE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    nbiot7_cmd_set( ctx, NBIOT7_CMD_EPS_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    nbiot7_cmd_set( ctx, NBIOT7_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_COPS );
#endif
    return error_flag;
}

static err_t nbiot7_check_connection ( nbiot7_t *ctx )
{
    err_t error_flag = NBIOT7_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    nbiot7_cmd_get ( &nbiot7, NBIOT7_CMD_EPS_NETWORK_REGISTRATION );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, NBIOT7_URC_NETWORK_REGISTERED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        nbiot7_cmd_run ( &nbiot7, NBIOT7_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_DEFAULT );
    }
    else
    {
        error_flag = NBIOT7_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t nbiot7_config_example ( nbiot7_t *ctx )
{
    err_t error_flag = NBIOT7_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Check TCPIP service.\r\n" );
    nbiot7_cmd_get ( &nbiot7, NBIOT7_CMD_START_TCPIP_SERVICE );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_NETOPEN );
    if ( !strstr ( app_buf, NBIOT7_URC_NETWORK_OPEN ) )
    {
        log_printf( &logger, ">>> Start TCPIP service.\r\n" );
        nbiot7_cmd_run ( &nbiot7, NBIOT7_CMD_START_TCPIP_SERVICE );
        error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_NETOPEN );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, ">>> Show PDP address.\r\n" );
    nbiot7_cmd_run( &nbiot7, NBIOT7_CMD_SHOW_PDP_ADDRESS );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_IPADDR );

    log_printf( &logger, ">>> Set RX mode to manually.\r\n" );
    #define RX_MODE_MANUALLY "1"
    nbiot7_cmd_set( &nbiot7, NBIOT7_CMD_RECEIVE_DATA_VIA_CONNECTION, RX_MODE_MANUALLY );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_CIPRXGET );
#endif
    return error_flag;
}

static err_t nbiot7_example ( nbiot7_t *ctx )
{
    err_t error_flag = NBIOT7_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    
    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    #define TCP_LINK_NUM "0"
    #define TCP_CONN_TYPE "TCP"
    strcpy( cmd_buf, TCP_LINK_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, TCP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    nbiot7_cmd_set ( &nbiot7, NBIOT7_CMD_OPEN_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_URC_CONNECTION_OPEN, NBIOT7_MAX_RSP_TIME_CIPOPEN );
    
    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    #define UDP_LINK_NUM "1"
    #define UDP_CONN_TYPE "UDP"
    #define UDP_LOCAL_PORT "5000"
    strcpy( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, UDP_CONN_TYPE );
    strcat( cmd_buf, "\",,," );
    strcat( cmd_buf, UDP_LOCAL_PORT );
    nbiot7_cmd_set ( &nbiot7, NBIOT7_CMD_OPEN_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_URC_CONNECTION_OPEN, NBIOT7_MAX_RSP_TIME_CIPOPEN );

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
    nbiot7_cmd_set ( &nbiot7, NBIOT7_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 100 );
    nbiot7_generic_write ( &nbiot7, MESSAGE_CONTENT, message_len );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_URC_RECEIVED_DATA, NBIOT7_MAX_RSP_TIME_CIPSEND );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    #define RX_DATA_READ "2"
    strcpy( cmd_buf, RX_DATA_READ );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, TCP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    nbiot7_cmd_set( &nbiot7, NBIOT7_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_CIPRXGET );
    
    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    nbiot7_cmd_set ( &nbiot7, NBIOT7_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 100 );
    nbiot7_generic_write ( &nbiot7, MESSAGE_CONTENT, message_len );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_URC_RECEIVED_DATA, NBIOT7_MAX_RSP_TIME_CIPSEND );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    strcpy( cmd_buf, RX_DATA_READ );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    nbiot7_cmd_set( &nbiot7, NBIOT7_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_RSP_OK, NBIOT7_MAX_RSP_TIME_CIPRXGET );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    nbiot7_cmd_set ( &nbiot7, NBIOT7_CMD_CLOSE_TCP_UDP_CONNECTION, TCP_LINK_NUM );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_URC_CONNECTION_CLOSED, NBIOT7_MAX_RSP_TIME_CIPCLOSE );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    nbiot7_cmd_set ( &nbiot7, NBIOT7_CMD_CLOSE_TCP_UDP_CONNECTION, UDP_LINK_NUM );
    error_flag |= nbiot7_read_response( ctx, NBIOT7_URC_CONNECTION_CLOSED, NBIOT7_MAX_RSP_TIME_CIPCLOSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    #error "No demo example selected"
#endif
    return error_flag;
}

// ------------------------------------------------------------------------ END
