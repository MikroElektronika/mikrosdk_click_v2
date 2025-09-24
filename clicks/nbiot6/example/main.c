/*!
 * @file main.c
 * @brief NB IoT 6 Click Example.
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
 *  - NBIOT6_POWER_UP:
 * Powers up the device and reads system information.
 *
 *  - NBIOT6_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - NBIOT6_CHECK_CONNECTION:
 * Waits for the network registration indicated via CEREG command and then checks the signal quality report.
 *
 *  - NBIOT6_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - NBIOT6_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void nbiot6_clear_app_buf ( void )
 * - static void nbiot6_log_app_buf ( void )
 * - static err_t nbiot6_process ( nbiot6_t *ctx )
 * - static err_t nbiot6_read_response ( nbiot6_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t nbiot6_power_up ( nbiot6_t *ctx )
 * - static err_t nbiot6_config_connection ( nbiot6_t *ctx )
 * - static err_t nbiot6_check_connection ( nbiot6_t *ctx )
 * - static err_t nbiot6_config_example ( nbiot6_t *ctx )
 * - static err_t nbiot6_example ( nbiot6_t *ctx )
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
#include "nbiot6.h"
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
#define MESSAGE_CONTENT                     "NB IoT 6 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    NBIOT6_POWER_UP = 1,
    NBIOT6_CONFIG_CONNECTION,
    NBIOT6_CHECK_CONNECTION,
    NBIOT6_CONFIG_EXAMPLE,
    NBIOT6_EXAMPLE

} nbiot6_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static nbiot6_app_state_t app_state = NBIOT6_POWER_UP;

static nbiot6_t nbiot6;
static log_t logger;

/**
 * @brief NB IoT 6 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void nbiot6_clear_app_buf ( void );

/**
 * @brief NB IoT 6 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void nbiot6_log_app_buf ( void );

/**
 * @brief NB IoT 6 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot6_process ( nbiot6_t *ctx );

/**
 * @brief NB IoT 6 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot6_read_response ( nbiot6_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief NB IoT 6 power up function.
 * @details This function powers up the device and reads system information.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot6_power_up ( nbiot6_t *ctx );

/**
 * @brief NB IoT 6 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot6_config_connection ( nbiot6_t *ctx );

/**
 * @brief NB IoT 6 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot6_check_connection ( nbiot6_t *ctx );

/**
 * @brief NB IoT 6 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot6_config_example ( nbiot6_t *ctx );

/**
 * @brief NB IoT 6 example function.
 * @details This function executes SMS or TCP/UDP example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #nbiot6_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot6_example ( nbiot6_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot6_cfg_t nbiot6_cfg;  /**< Click config object. */

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
    nbiot6_cfg_setup( &nbiot6_cfg );
    NBIOT6_MAP_MIKROBUS( nbiot6_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot6_init( &nbiot6, &nbiot6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = NBIOT6_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case NBIOT6_POWER_UP:
        {
            if ( NBIOT6_OK == nbiot6_power_up( &nbiot6 ) )
            {
                app_state = NBIOT6_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_CONFIG_CONNECTION:
        {
            if ( NBIOT6_OK == nbiot6_config_connection( &nbiot6 ) )
            {
                app_state = NBIOT6_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_CHECK_CONNECTION:
        {
            if ( NBIOT6_OK == nbiot6_check_connection( &nbiot6 ) )
            {
                app_state = NBIOT6_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_CONFIG_EXAMPLE:
        {
            if ( NBIOT6_OK == nbiot6_config_example( &nbiot6 ) )
            {
                app_state = NBIOT6_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_EXAMPLE:
        {
            nbiot6_example( &nbiot6 );
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

static void nbiot6_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void nbiot6_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t nbiot6_process ( nbiot6_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = nbiot6_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
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
        return NBIOT6_OK;
    }
    return NBIOT6_ERROR;
}

static err_t nbiot6_read_response ( nbiot6_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    nbiot6_clear_app_buf( );
    nbiot6_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, NBIOT6_RSP_ERROR ) ) )
    {
        nbiot6_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            nbiot6_log_app_buf( );
            nbiot6_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return NBIOT6_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    nbiot6_process( ctx );
    nbiot6_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return NBIOT6_OK;
    }
    return NBIOT6_ERROR_CMD;
}

static err_t nbiot6_power_up ( nbiot6_t *ctx )
{
    err_t error_flag = NBIOT6_OK;
    
    log_printf( &logger, ">>> Power up device.\r\n" );
    nbiot6_set_power_state ( ctx, NBIOT6_POWER_STATE_ON );

    log_printf( &logger, ">>> Perform device hardware reset.\r\n" );
    nbiot6_set_power_state ( ctx, NBIOT6_POWER_STATE_RESET );
    
    log_printf( &logger, ">>> Check communication.\r\n" );
    nbiot6_clear_app_buf ( );
    for ( ; ; )
    {
        // Wake up AT interface
        nbiot6_set_power_state ( ctx, NBIOT6_POWER_STATE_WAKEUP );
        nbiot6_cmd_run( ctx, NBIOT6_CMD_AT );
        nbiot6_process( ctx );
        if ( app_buf_len > 0 )
        {
            break;
        }
    }
    nbiot6_cmd_run( ctx, NBIOT6_CMD_AT );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Get device model ID.\r\n" );
    nbiot6_cmd_run( ctx, NBIOT6_CMD_GET_MODEL_ID );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get manufacturer revision number.\r\n" );
    nbiot6_cmd_run( ctx, NBIOT6_CMD_GET_MANUFACTURER_REVISION );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    nbiot6_cmd_run( ctx, NBIOT6_CMD_GET_SERIAL_NUM );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t nbiot6_config_connection ( nbiot6_t *ctx )
{
    err_t error_flag = NBIOT6_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Enable NETLIGHT indication.\r\n" );
    #define NETLIGHT_ENABLE "1"
    nbiot6_cmd_set( ctx, NBIOT6_CMD_CONFIG_NETLIGHT_LED, NETLIGHT_ENABLE );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    nbiot6_cmd_set( ctx, NBIOT6_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_COPS );

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    nbiot6_set_sim_apn( &nbiot6, SIM_APN );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    nbiot6_cmd_set( ctx, NBIOT6_CMD_SET_UE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    nbiot6_cmd_set( ctx, NBIOT6_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    nbiot6_cmd_set( ctx, NBIOT6_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_COPS );
#endif
    return error_flag;
}

static err_t nbiot6_check_connection ( nbiot6_t *ctx )
{
    err_t error_flag = NBIOT6_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    nbiot6_cmd_get( &nbiot6, NBIOT6_CMD_NETWORK_REGISTRATION );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, NBIOT6_URC_NETWORK_REGISTERED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        nbiot6_cmd_run( &nbiot6, NBIOT6_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
    }
    else
    {
        error_flag = NBIOT6_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t nbiot6_config_example ( nbiot6_t *ctx )
{
    err_t error_flag = NBIOT6_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Activate PDP context.\r\n" );
    #define ACTIVATE_PDP_CONTEXT "1,1"
    nbiot6_cmd_set( &nbiot6, NBIOT6_CMD_ACTIVATE_PDP_CONTEXT, ACTIVATE_PDP_CONTEXT );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_CGACT );

    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    nbiot6_cmd_set( &nbiot6, NBIOT6_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    nbiot6_cmd_set( &nbiot6, NBIOT6_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
#endif
    return error_flag;
}

static err_t nbiot6_example ( nbiot6_t *ctx )
{
    err_t error_flag = NBIOT6_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ NBIOT6_TX_DRV_BUFFER_SIZE ] = { 0 };

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );
    
    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    #define PDP_CID "1"
    #define TCP_SOCKET_NUM   "0"
    #define TCP_SERVICE_TYPE "TCP"
    strcpy( cmd_buf, PDP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, TCP_SERVICE_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    nbiot6_cmd_set ( &nbiot6, NBIOT6_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_URC_OPEN_SOCKET, NBIOT6_MAX_RSP_TIME_URC );
    
    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    #define UDP_SOCKET_NUM   "1"
    #define UDP_SERVICE_TYPE "UDP"
    strcpy( cmd_buf, PDP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, UDP_SERVICE_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    nbiot6_cmd_set ( &nbiot6, NBIOT6_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_URC_OPEN_SOCKET, NBIOT6_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    strcpy( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    nbiot6_cmd_set ( &nbiot6, NBIOT6_CMD_SEND_TCP_IP_TEXT_DATA, cmd_buf );
    Delay_ms ( 100 );
    nbiot6_generic_write ( &nbiot6, MESSAGE_CONTENT, message_len );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_URC_RECEIVED_DATA, NBIOT6_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    nbiot6_cmd_set( &nbiot6, NBIOT6_CMD_RECEIVE_TCP_IP_DATA, cmd_buf );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    nbiot6_cmd_set ( &nbiot6, NBIOT6_CMD_SEND_TCP_IP_TEXT_DATA, cmd_buf );
    Delay_ms ( 100 );
    nbiot6_generic_write ( &nbiot6, MESSAGE_CONTENT, message_len );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_URC_RECEIVED_DATA, NBIOT6_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    nbiot6_cmd_set( &nbiot6, NBIOT6_CMD_RECEIVE_TCP_IP_DATA, cmd_buf );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    nbiot6_cmd_set ( &nbiot6, NBIOT6_CMD_CLOSE_SOCKET, TCP_SOCKET_NUM );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_CLOSE_OK, NBIOT6_MAX_RSP_TIME_QICLOSE );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    nbiot6_cmd_set ( &nbiot6, NBIOT6_CMD_CLOSE_SOCKET, UDP_SOCKET_NUM );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_CLOSE_OK, NBIOT6_MAX_RSP_TIME_QICLOSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    log_printf( &logger, ">>> Check SMS format.\r\n" );
    nbiot6_cmd_get( &nbiot6, NBIOT6_CMD_SELECT_SMS_FORMAT );
    error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        nbiot6_send_sms_pdu( &nbiot6, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_CMGS );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        nbiot6_send_sms_text ( &nbiot6, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= nbiot6_read_response( ctx, NBIOT6_RSP_OK, NBIOT6_MAX_RSP_TIME_CMGS );
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
