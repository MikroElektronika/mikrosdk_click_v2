/*!
 * @file main.c
 * @brief LTE IoT 17 Click Example.
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
 *  - LTEIOT17_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *
 *  - LTEIOT17_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - LTEIOT17_CHECK_CONNECTION:
 * Waits for the network registration indicated via CREG command and then checks the signal quality report.
 *
 *  - LTEIOT17_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - LTEIOT17_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void lteiot17_clear_app_buf ( void )
 * - static void lteiot17_log_app_buf ( void )
 * - static err_t lteiot17_process ( lteiot17_t *ctx )
 * - static err_t lteiot17_read_response ( lteiot17_t *ctx, uint8_t *rsp )
 * - static err_t lteiot17_power_up ( lteiot17_t *ctx )
 * - static err_t lteiot17_config_connection ( lteiot17_t *ctx )
 * - static err_t lteiot17_check_connection ( lteiot17_t *ctx )
 * - static err_t lteiot17_config_example ( lteiot17_t *ctx )
 * - static err_t lteiot17_example ( lteiot17_t *ctx )
 *
 * @note
 * In order for the examples to work, user needs to set the APN and SMSC (SMS PDU mode only)
 * of entered SIM card as well as the phone number (SMS mode only) to which he wants to send an SMS.
 * Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
 * Example:
    SIM_APN "internet"
    SIM_SMSC "+381610401"
    PHONE_NUMBER_TO_MESSAGE "+381659999999"
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lteiot17.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM APN config
#define SIM_APN                             "internet"      // Set valid SIM APN

// SMS example parameters
#define SIM_SMSC                            ""              // Set valid SMS Service Center Address - only in SMS PDU mode
#define PHONE_NUMBER_TO_MESSAGE             ""              // Set Phone number to message
#define SMS_MODE                            "1"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "LTE IoT 17 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTEIOT17_POWER_UP = 1,
    LTEIOT17_CONFIG_CONNECTION,
    LTEIOT17_CHECK_CONNECTION,
    LTEIOT17_CONFIG_EXAMPLE,
    LTEIOT17_EXAMPLE

} lteiot17_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static lteiot17_app_state_t app_state = LTEIOT17_POWER_UP;

static lteiot17_t lteiot17;
static log_t logger;

/**
 * @brief LTE IoT 17 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lteiot17_clear_app_buf ( void );

/**
 * @brief LTE IoT 17 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lteiot17_log_app_buf ( void );

/**
 * @brief LTE IoT 17 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lteiot17_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot17_process ( lteiot17_t *ctx );

/**
 * @brief LTE IoT 17 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lteiot17_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot17_read_response ( lteiot17_t *ctx, uint8_t *rsp );

/**
 * @brief LTE IoT 17 power up function.
 * @details This function powers up the device, performs device factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lteiot17_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot17_power_up ( lteiot17_t *ctx );

/**
 * @brief LTE IoT 17 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #lteiot17_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot17_config_connection ( lteiot17_t *ctx );

/**
 * @brief LTE IoT 17 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #lteiot17_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot17_check_connection ( lteiot17_t *ctx );

/**
 * @brief LTE IoT 17 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #lteiot17_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot17_config_example ( lteiot17_t *ctx );

/**
 * @brief LTE IoT 17 example function.
 * @details This function executes SMS or TCP/UDP example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #lteiot17_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot17_example ( lteiot17_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot17_cfg_t lteiot17_cfg;  /**< Click config object. */

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
    lteiot17_cfg_setup( &lteiot17_cfg );
    LTEIOT17_MAP_MIKROBUS( lteiot17_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot17_init( &lteiot17, &lteiot17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT17_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LTEIOT17_POWER_UP:
        {
            if ( LTEIOT17_OK == lteiot17_power_up( &lteiot17 ) )
            {
                app_state = LTEIOT17_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_CONFIG_CONNECTION:
        {
            if ( LTEIOT17_OK == lteiot17_config_connection( &lteiot17 ) )
            {
                app_state = LTEIOT17_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_CHECK_CONNECTION:
        {
            if ( LTEIOT17_OK == lteiot17_check_connection( &lteiot17 ) )
            {
                app_state = LTEIOT17_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_CONFIG_EXAMPLE:
        {
            if ( LTEIOT17_OK == lteiot17_config_example( &lteiot17 ) )
            {
                app_state = LTEIOT17_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_EXAMPLE:
        {
            lteiot17_example( &lteiot17 );
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

static void lteiot17_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lteiot17_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot17_process ( lteiot17_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lteiot17_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTEIOT17_OK;
    }
    return LTEIOT17_ERROR;
}

static err_t lteiot17_read_response ( lteiot17_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS    120000
    uint32_t timeout_cnt = 0;
    lteiot17_clear_app_buf ( );
    lteiot17_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTEIOT17_RSP_ERROR ) ) )
    {
        lteiot17_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            lteiot17_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LTEIOT17_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lteiot17_process( ctx );
    if ( strstr( app_buf, rsp ) )
    {
        lteiot17_log_app_buf( );
        log_printf( &logger, "--------------------------------\r\n" );
        return LTEIOT17_OK;
    }
    else if ( strstr( app_buf, LTEIOT17_RSP_ERROR ) )
    {
        log_error( &logger, " CMD!" );
        return LTEIOT17_ERROR_CMD;
    }
    log_error( &logger, " Unknown!" );
    return LTEIOT17_ERROR_UNKNOWN;
}

static err_t lteiot17_power_up ( lteiot17_t *ctx )
{
    err_t error_flag = LTEIOT17_OK;
    
    uint8_t power_state = LTEIOT17_POWER_STATE_OFF;
    for ( ; ; )
    {
        lteiot17_process( ctx );
        lteiot17_clear_app_buf ( );
        // Wake up UART interface
        lteiot17_send_cmd( ctx, LTEIOT17_CMD_AT );
        Delay_ms ( 500 );

        log_printf( &logger, ">>> Check communication.\r\n" );
        lteiot17_send_cmd( ctx, LTEIOT17_CMD_AT );
        if ( ( ( LTEIOT17_OK == lteiot17_process( ctx ) ) && strstr( app_buf, LTEIOT17_RSP_OK ) ) )
        {
            power_state = LTEIOT17_POWER_STATE_ON;
            break;
        }
        else if ( LTEIOT17_POWER_STATE_OFF == power_state )
        {
            power_state = LTEIOT17_POWER_STATE_ON;
            log_printf( &logger, ">>> Power up device.\r\n" );
            lteiot17_set_power_state ( ctx, LTEIOT17_POWER_STATE_ON );
        }
        else if ( LTEIOT17_POWER_STATE_ON == power_state )
        {
            power_state = LTEIOT17_POWER_STATE_OFF;
            log_printf( &logger, ">>> Power down device.\r\n" );
            lteiot17_set_power_state ( ctx, LTEIOT17_POWER_STATE_OFF );
        }
    }
    lteiot17_send_cmd( ctx, LTEIOT17_CMD_AT );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    
    log_printf( &logger, ">>> Get device model ID.\r\n" );
    lteiot17_send_cmd( ctx, LTEIOT17_CMD_GET_MODEL_ID );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    lteiot17_send_cmd( ctx, LTEIOT17_CMD_GET_SW_VERSION );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    lteiot17_send_cmd( ctx, LTEIOT17_CMD_GET_SERIAL_NUM );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );

    return error_flag;
}

static err_t lteiot17_config_connection ( lteiot17_t *ctx )
{
    err_t error_flag = LTEIOT17_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    lteiot17_send_cmd_par( ctx, LTEIOT17_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    lteiot17_set_sim_apn( &lteiot17, SIM_APN );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    lteiot17_send_cmd_par( ctx, LTEIOT17_CMD_SET_PHONE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    lteiot17_send_cmd_par( ctx, LTEIOT17_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    lteiot17_send_cmd_par( ctx, LTEIOT17_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
#endif
    return error_flag;
}

static err_t lteiot17_check_connection ( lteiot17_t *ctx )
{
    err_t error_flag = LTEIOT17_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    #define CONNECTED "+CREG: 2,1"
    lteiot17_send_cmd_check ( &lteiot17, LTEIOT17_CMD_NETWORK_REGISTRATION );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        lteiot17_send_cmd( &lteiot17, LTEIOT17_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    }
    else
    {
        error_flag = LTEIOT17_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t lteiot17_config_example ( lteiot17_t *ctx )
{
    err_t error_flag = LTEIOT17_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Config APP network.\r\n" );
    #define CONFIG_APP_NETWORK "1,1"
    lteiot17_send_cmd_par( &lteiot17, LTEIOT17_CMD_APP_NETWORK_CONFIG, CONFIG_APP_NETWORK );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    
    log_printf( &logger, ">>> Activate APP network.\r\n" );
    #define ACTIVATE_APP_NETWORK "1,1"
    lteiot17_send_cmd_par( &lteiot17, LTEIOT17_CMD_APP_NETWORK_ACTIVE, ACTIVATE_APP_NETWORK );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    if ( strstr ( app_buf, "DEACTIVE" ) )
    {
        error_flag |= LTEIOT17_ERROR;
    }
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    lteiot17_send_cmd_par( &lteiot17, LTEIOT17_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
#endif
    return error_flag;
}

static err_t lteiot17_example ( lteiot17_t *ctx )
{
    err_t error_flag = LTEIOT17_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    log_printf( &logger, ">>> Set TCP ID.\r\n" );
    #define TCP_CID "1"
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_SET_TCP_UDP_ID, TCP_CID );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    
    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    #define PDP_CID "1"
    #define TCP_CONN_TYPE "TCP"
    strcpy( cmd_buf, TCP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, PDP_CID );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, TCP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_OPEN_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_URC_CONNECTION_OPEN );

    log_printf( &logger, ">>> Set UDP ID.\r\n" );
    #define UDP_CID "2"
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_SET_TCP_UDP_ID, UDP_CID );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    
    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    #define UDP_CONN_TYPE "UDP"
    strcpy( cmd_buf, UDP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, PDP_CID );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, UDP_CONN_TYPE );
    strcat( cmd_buf, "\",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_OPEN_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_URC_CONNECTION_OPEN );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    strcpy( cmd_buf, TCP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 200 );
    lteiot17_generic_write ( &lteiot17, MESSAGE_CONTENT, message_len );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_URC_RECEIVED_DATA );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    lteiot17_send_cmd_par( &lteiot17, LTEIOT17_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_CID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 200 );
    lteiot17_generic_write ( &lteiot17, MESSAGE_CONTENT, message_len );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_URC_RECEIVED_DATA );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    lteiot17_send_cmd_par( &lteiot17, LTEIOT17_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_CLOSE_TCP_UDP_CONNECTION, TCP_CID );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    lteiot17_send_cmd_par ( &lteiot17, LTEIOT17_CMD_CLOSE_TCP_UDP_CONNECTION, UDP_CID );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
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
    lteiot17_send_cmd_check( &lteiot17, LTEIOT17_CMD_SELECT_SMS_FORMAT );
    error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        lteiot17_send_sms_pdu( &lteiot17, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        lteiot17_send_sms_text ( &lteiot17, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag |= lteiot17_read_response( ctx, LTEIOT17_RSP_OK );
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
