/*!
 * @file main.c
 * @brief LTE Cat.4 Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending SMS or TCP/UDP messages, answering incoming calls, or retrieving data
 * from GNSS using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LTECAT4_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *
 *  - LTECAT4_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network 
 * (used only for SMS, CALL, or TCP/UDP demo examples).
 *
 *  - LTECAT4_CHECK_CONNECTION:
 * Waits for the network registration indicated via CREG command and then checks 
 * the signal quality report (used only for SMS, CALL, or TCP/UDP demo examples).
 *
 *  - LTECAT4_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - LTECAT4_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode)
 * or TCP/UDP message, waits for incoming calls and answers it, or waits for the GPS fix
 * to retrieve location info from GNSS.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void ltecat4_clear_app_buf ( void )
 * - static void ltecat4_log_app_buf ( void )
 * - static err_t ltecat4_process ( ltecat4_t *ctx )
 * - static err_t ltecat4_read_response ( ltecat4_t *ctx, uint8_t *rsp )
 * - static err_t ltecat4_power_up ( ltecat4_t *ctx )
 * - static err_t ltecat4_config_connection ( ltecat4_t *ctx )
 * - static err_t ltecat4_check_connection ( ltecat4_t *ctx )
 * - static err_t ltecat4_config_example ( ltecat4_t *ctx )
 * - static err_t ltecat4_example ( ltecat4_t *ctx )
 *
 * @note
 * In order for the examples to work (except GNSS example), user needs to set the APN and SMSC (SMS PDU mode only)
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
#include "ltecat4.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define EXAMPLE_CALL                        2               // Example of answering incoming calls 
#define EXAMPLE_GNSS                        3               // Example of retrieving location info from GNSS
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM APN config
#define SIM_APN                             "internet"      // Set valid SIM APN

// SMS example parameters
#define SIM_SMSC                            ""              // Set valid SMS Service Center Address - only in SMS PDU mode
#define PHONE_NUMBER                        ""              // Set Phone number to message
#define SMS_MODE                            "1"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "LTE Cat.4 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTECAT4_POWER_UP = 1,
    LTECAT4_CONFIG_CONNECTION,
    LTECAT4_CHECK_CONNECTION,
    LTECAT4_CONFIG_EXAMPLE,
    LTECAT4_EXAMPLE

} ltecat4_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static ltecat4_app_state_t app_state = LTECAT4_POWER_UP;

static ltecat4_t ltecat4;
static log_t logger;

/**
 * @brief LTE Cat.4 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ltecat4_clear_app_buf ( void );

/**
 * @brief LTE Cat.4 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void ltecat4_log_app_buf ( void );

/**
 * @brief LTE Cat.4 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat4_process ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat4_read_response ( ltecat4_t *ctx, uint8_t *rsp );

/**
 * @brief LTE Cat.4 power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat4_power_up ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat4_config_connection ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat4_check_connection ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat4_config_example ( ltecat4_t *ctx );

/**
 * @brief LTE Cat.4 example function.
 * @details This function executes SMS, TCP/UDP, CALL, or GNSS example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #ltecat4_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat4_example ( ltecat4_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat4_cfg_t ltecat4_cfg;  /**< Click config object. */

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
    ltecat4_cfg_setup( &ltecat4_cfg );
    LTECAT4_MAP_MIKROBUS( ltecat4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat4_init( &ltecat4, &ltecat4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTECAT4_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LTECAT4_POWER_UP:
        {
            if ( LTECAT4_OK == ltecat4_power_up( &ltecat4 ) )
            {
                app_state = LTECAT4_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_CONFIG_CONNECTION:
        {
            if ( LTECAT4_OK == ltecat4_config_connection( &ltecat4 ) )
            {
                app_state = LTECAT4_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_CHECK_CONNECTION:
        {
            if ( LTECAT4_OK == ltecat4_check_connection( &ltecat4 ) )
            {
                app_state = LTECAT4_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_CONFIG_EXAMPLE:
        {
            if ( LTECAT4_OK == ltecat4_config_example( &ltecat4 ) )
            {
                app_state = LTECAT4_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_EXAMPLE:
        {
            ltecat4_example( &ltecat4 );
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

static void ltecat4_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ltecat4_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ltecat4_process ( ltecat4_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ltecat4_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTECAT4_OK;
    }
    return LTECAT4_ERROR;
}

static err_t ltecat4_read_response ( ltecat4_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS    120000
    uint32_t timeout_cnt = 0;
    ltecat4_clear_app_buf ( );
    ltecat4_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTECAT4_RSP_ERROR ) ) )
    {
        ltecat4_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            ltecat4_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LTECAT4_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    ltecat4_process( ctx );
    if ( strstr( app_buf, rsp ) )
    {
        ltecat4_log_app_buf( );
        log_printf( &logger, "--------------------------------\r\n" );
        return LTECAT4_OK;
    }
    else if ( strstr( app_buf, LTECAT4_RSP_ERROR ) )
    {
        log_error( &logger, " CMD!" );
        return LTECAT4_ERROR_CMD;
    }
    log_error( &logger, " Unknown!" );
    return LTECAT4_ERROR_UNKNOWN;
}

static err_t ltecat4_power_up ( ltecat4_t *ctx )
{
    err_t error_flag = LTECAT4_OK;

    for ( ; ; )
    {
        ltecat4_process( ctx );
        ltecat4_clear_app_buf ( );
        // Wake up UART interface
        ltecat4_send_cmd( ctx, LTECAT4_CMD_AT );

        log_printf( &logger, ">>> Check communication.\r\n" );
        ltecat4_send_cmd( ctx, LTECAT4_CMD_AT );
        if ( ( ( LTECAT4_OK == ltecat4_process( ctx ) ) && strstr( app_buf, LTECAT4_RSP_OK ) ) )
        {
            break;
        }
        else
        {
            log_printf( &logger, ">>> Power up device.\r\n" );
            ltecat4_set_power_state ( ctx, LTECAT4_POWER_STATE_ON );
        }
    }
    ltecat4_send_cmd( ctx, LTECAT4_CMD_AT );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    
    log_printf( &logger, ">>> Factory reset.\r\n" );
    ltecat4_send_cmd( ctx, LTECAT4_CMD_FACTORY_RESET );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    ltecat4_send_cmd( ctx, LTECAT4_CMD_GET_SW_VERSION );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    ltecat4_send_cmd( ctx, LTECAT4_CMD_GET_SERIAL_NUM );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    return error_flag;
}

static err_t ltecat4_config_connection ( ltecat4_t *ctx )
{
    err_t error_flag = LTECAT4_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) )
    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    ltecat4_send_cmd_par( ctx, LTECAT4_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    ltecat4_set_sim_apn( &ltecat4, SIM_APN );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    ltecat4_send_cmd_par( ctx, LTECAT4_CMD_SET_UE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    ltecat4_send_cmd_par( ctx, LTECAT4_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    ltecat4_send_cmd_par( ctx, LTECAT4_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
#endif
    return error_flag;
}

static err_t ltecat4_check_connection ( ltecat4_t *ctx )
{
    err_t error_flag = LTECAT4_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    #define CONNECTED "+CREG: 2,1"
    ltecat4_send_cmd_check ( &ltecat4, LTECAT4_CMD_NETWORK_REGISTRATION );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        ltecat4_send_cmd( &ltecat4, LTECAT4_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    }
    else
    {
        error_flag = LTECAT4_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t ltecat4_config_example ( ltecat4_t *ctx )
{
    err_t error_flag = LTECAT4_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Activate PDP context.\r\n" );
    #define ACTIVATE_PDP_CONTEXT "1,1"
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_ACTIVATE_PDP_CONTEXT, ACTIVATE_PDP_CONTEXT );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
#elif ( DEMO_EXAMPLE == EXAMPLE_CALL )
    log_printf( &logger, ">>> Configure audio codec.\r\n" );
    if ( LTECAT4_OK != ltecat4_config_codec ( &ltecat4 ) )
    {
        log_error( &logger, " Audio codec config." );
        for ( ; ; );
    }
    log_printf( &logger, ">>> Set MIC gain.\r\n" );
    #define MIC_GAIN "14567,14567"
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_SET_MIC_GAIN, MIC_GAIN );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    log_printf( &logger, ">>> Set MAX9860 as audio codec.\r\n" );
    #define CODEC_MAX9860 "4"
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_CONFIG_AUDIO_INTERFACE, CODEC_MAX9860 );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    log_printf( &logger, ">>> Enable URC for all ports.\r\n" );
    #define URC_INDICATION_ALL_PORTS "\"urcport\",\"all\""
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_CONFIG_URC_INDICATION, URC_INDICATION_ALL_PORTS );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    log_printf( &logger, ">>> Check GNSS power state.\r\n" );
    #define GNSS_TURNED_OFF "+QGPS: 0"
    ltecat4_send_cmd_check( &ltecat4, LTECAT4_CMD_TURN_ON_GNSS );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    if ( strstr ( app_buf, GNSS_TURNED_OFF ) )
    {
        log_printf( &logger, ">>> Turn on GNSS power supply.\r\n" );
        #define GNSS_TURN_ON "1"
        ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_TURN_ON_GNSS, GNSS_TURN_ON );
        error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    }
#endif
    return error_flag;
}

static err_t ltecat4_example ( ltecat4_t *ctx )
{
    err_t error_flag = LTECAT4_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    #define PDP_CID "1"
    #define TCP_SOCKET_NUM "0"
    #define TCP_CONN_TYPE "TCP"
    strcpy( cmd_buf, PDP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, TCP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    ltecat4_send_cmd_par ( &ltecat4, LTECAT4_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    #define UDP_SOCKET_NUM "1"
    #define UDP_CONN_TYPE "UDP"
    strcpy( cmd_buf, PDP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, UDP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    ltecat4_send_cmd_par ( &ltecat4, LTECAT4_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    strcpy( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    ltecat4_send_cmd_par ( &ltecat4, LTECAT4_CMD_SEND_DATA, cmd_buf );
    Delay_ms ( 100 );
    ltecat4_generic_write ( &ltecat4, MESSAGE_CONTENT, message_len );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_URC_RECEIVED_DATA );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_RECEIVE_DATA, cmd_buf );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    ltecat4_send_cmd_par ( &ltecat4, LTECAT4_CMD_SEND_DATA, cmd_buf );
    Delay_ms ( 100 );
    ltecat4_generic_write ( &ltecat4, MESSAGE_CONTENT, message_len );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_URC_RECEIVED_DATA );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    ltecat4_send_cmd_par( &ltecat4, LTECAT4_CMD_RECEIVE_DATA, cmd_buf );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    ltecat4_send_cmd_par ( &ltecat4, LTECAT4_CMD_CLOSE_SOCKET, TCP_SOCKET_NUM );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    ltecat4_send_cmd_par ( &ltecat4, LTECAT4_CMD_CLOSE_SOCKET, UDP_SOCKET_NUM );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
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
    ltecat4_send_cmd_check( &ltecat4, LTECAT4_CMD_SELECT_SMS_FORMAT );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        ltecat4_send_sms_pdu( &ltecat4, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        ltecat4_send_sms_text ( &ltecat4, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    }
    // 30 seconds delay
    for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
    {
        Delay_ms ( 1000 );
    }
#elif ( DEMO_EXAMPLE == EXAMPLE_CALL )
    log_printf( &logger, ">>> Waiting for a ring indication.\r\n" );
    ltecat4_clear_app_buf ( );
    for ( ; ; )
    {
        if ( ( LTECAT4_OK == ltecat4_process ( ctx ) ) && strstr ( app_buf, LTECAT4_URC_RING ) )
        {
            ltecat4_log_app_buf ( );
            Delay_ms ( 1000 );
            break;
        }
    }
    log_printf( &logger, "\r\n--------------------------------\r\n" );
        
    log_printf( &logger, ">>> List calls.\r\n" );
    ltecat4_send_cmd ( &ltecat4, LTECAT4_CMD_LIST_CALLS );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    log_printf( &logger, ">>> Answer an incoming call.\r\n" );
    ltecat4_send_cmd ( &ltecat4, LTECAT4_CMD_ANSWER_CALL );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    log_printf( &logger, ">>> Call in progress.\r\n" );
    if ( LTECAT4_OK != ltecat4_read_response( ctx, LTECAT4_URC_NO_CARRIER ) )
    {
        log_printf( &logger, ">>> Terminate call.\r\n" );
        ltecat4_send_cmd ( &ltecat4, LTECAT4_CMD_TERMINATE_CALL );
        error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    }
    log_printf( &logger, ">>> Call ended.\r\n" );

#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    uint8_t element_buf[ 100 ] = { 0 };
    #define GNSS_NMEA_GGA "\"GGA\""
    log_printf( &logger, ">>> Get GNSS NMEA sentence.\r\n" );
    ltecat4_send_cmd_par ( &ltecat4, LTECAT4_CMD_ACQUIRE_NMEA_SENTENCES, GNSS_NMEA_GGA );
    error_flag |= ltecat4_read_response( ctx, LTECAT4_RSP_OK );
    log_printf( &logger, ">>> Parse GNSS NMEA sentence.\r\n" );
    if ( LTECAT4_OK == ltecat4_parse_gga( app_buf, LTECAT4_GGA_LATITUDE, element_buf ) )
    {
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "Latitude: %.2s degrees, %s minutes\r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            ltecat4_parse_gga( app_buf, LTECAT4_GGA_LONGITUDE, element_buf );
            log_printf( &logger, "Longitude: %.3s degrees, %s minutes\r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            ltecat4_parse_gga( app_buf, LTECAT4_GGA_ALTITUDE, element_buf );
            log_printf( &logger, "Altitude: %s m\r\n", element_buf );
        }
        else
        {
            log_printf( &logger, "No position fix detected.\r\n" );
        }
    }
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
#else
    #error "No demo example selected"
#endif
    return error_flag;
}

// ------------------------------------------------------------------------ END
