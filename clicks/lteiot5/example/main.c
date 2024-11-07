/*!
 * @file main.c
 * @brief LTE IoT 5 Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LTEIOT5_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *
 *  - LTEIOT5_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT5_CHECK_CONNECTION:
 * Waits for the network registration indicated via CEREG command and then checks the signal quality report 
 * (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT5_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - LTEIOT5_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or 
 * waits for the GPS fix to retrieve location info from GNSS.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void lteiot5_clear_app_buf ( void )
 * - static void lteiot5_log_app_buf ( void )
 * - static err_t lteiot5_process ( lteiot5_t *ctx )
 * - static err_t lteiot5_read_response ( lteiot5_t *ctx, uint8_t *rsp )
 * - static err_t lteiot5_power_up ( lteiot5_t *ctx )
 * - static err_t lteiot5_config_connection ( lteiot5_t *ctx )
 * - static err_t lteiot5_check_connection ( lteiot5_t *ctx )
 * - static err_t lteiot5_config_example ( lteiot5_t *ctx )
 * - static err_t lteiot5_example ( lteiot5_t *ctx )
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
#include "lteiot5.h"
#include "generic_pointer.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define EXAMPLE_GNSS                        2               // Example of retrieving location info from GNSS
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
#define MESSAGE_CONTENT                     "LTE IoT 5 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTEIOT5_POWER_UP = 1,
    LTEIOT5_CONFIG_CONNECTION,
    LTEIOT5_CHECK_CONNECTION,
    LTEIOT5_CONFIG_EXAMPLE,
    LTEIOT5_EXAMPLE

} lteiot5_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static lteiot5_app_state_t app_state = LTEIOT5_POWER_UP;

static lteiot5_t lteiot5;
static log_t logger;

/**
 * @brief LTE IoT 5 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lteiot5_clear_app_buf ( void );

/**
 * @brief LTE IoT 5 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lteiot5_log_app_buf ( void );

/**
 * @brief LTE IoT 5 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_process ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_read_response ( lteiot5_t *ctx, uint8_t *rsp );

/**
 * @brief LTE IoT 5 power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_power_up ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_config_connection ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_check_connection ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_config_example ( lteiot5_t *ctx );

/**
 * @brief LTE IoT 5 example function.
 * @details This function executes SMS or TCP/UDP depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #lteiot5_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_example ( lteiot5_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot5_cfg_t lteiot5_cfg;  /**< Click config object. */

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
    lteiot5_cfg_setup( &lteiot5_cfg );
    LTEIOT5_MAP_MIKROBUS( lteiot5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot5_init( &lteiot5, &lteiot5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT5_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LTEIOT5_POWER_UP:
        {
            if ( LTEIOT5_OK == lteiot5_power_up( &lteiot5 ) )
            {
                app_state = LTEIOT5_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_CONFIG_CONNECTION:
        {
            if ( LTEIOT5_OK == lteiot5_config_connection( &lteiot5 ) )
            {
                app_state = LTEIOT5_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_CHECK_CONNECTION:
        {
            if ( LTEIOT5_OK == lteiot5_check_connection( &lteiot5 ) )
            {
                app_state = LTEIOT5_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_CONFIG_EXAMPLE:
        {
            if ( LTEIOT5_OK == lteiot5_config_example( &lteiot5 ) )
            {
                app_state = LTEIOT5_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_EXAMPLE:
        {
            lteiot5_example( &lteiot5 );
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

static void lteiot5_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lteiot5_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot5_process ( lteiot5_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lteiot5_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTEIOT5_OK;
    }
    return LTEIOT5_ERROR;
}

static err_t lteiot5_read_response ( lteiot5_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS    120000
    uint32_t timeout_cnt = 0;
    lteiot5_clear_app_buf ( );
    lteiot5_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTEIOT5_RSP_ERROR ) ) )
    {
        lteiot5_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            lteiot5_log_app_buf( );
            lteiot5_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LTEIOT5_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lteiot5_process( ctx );
    lteiot5_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return LTEIOT5_OK;
    }
    return LTEIOT5_ERROR_CMD;
}

static err_t lteiot5_power_up ( lteiot5_t *ctx )
{
    err_t error_flag = LTEIOT5_OK;

    uint8_t power_state = LTEIOT5_POWER_STATE_OFF;
    for ( ; ; )
    {
        lteiot5_process( ctx );
        lteiot5_log_app_buf ( );
        lteiot5_clear_app_buf ( );
        // Wake up UART interface
        lteiot5_cmd_run( ctx, LTEIOT5_CMD_AT );

        log_printf( &logger, ">>> Check communication.\r\n" );
        lteiot5_cmd_run( ctx, LTEIOT5_CMD_AT );
        if ( ( ( LTEIOT5_OK == lteiot5_process( ctx ) ) && strstr( app_buf, LTEIOT5_RSP_OK ) ) )
        {
            power_state = LTEIOT5_POWER_STATE_ON;
            break;
        }
        else if ( LTEIOT5_POWER_STATE_OFF == power_state )
        {
            power_state = LTEIOT5_POWER_STATE_ON;
            log_printf( &logger, ">>> Power up device.\r\n" );
            lteiot5_set_power_state ( ctx, LTEIOT5_POWER_STATE_ON );
        }
        else if ( LTEIOT5_POWER_STATE_ON == power_state )
        {
            power_state = LTEIOT5_POWER_STATE_OFF;
            log_printf( &logger, ">>> Power down device.\r\n" );
            lteiot5_set_power_state ( ctx, LTEIOT5_POWER_STATE_OFF );
        }
    }
    lteiot5_cmd_run( ctx, LTEIOT5_CMD_AT );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    
    log_printf( &logger, ">>> Factory reset.\r\n" );
    lteiot5_cmd_run( ctx, LTEIOT5_CMD_FACTORY_RESET );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    lteiot5_cmd_run( ctx, LTEIOT5_CMD_GET_SW_VERSION );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    lteiot5_cmd_run( ctx, LTEIOT5_CMD_GET_SERIAL_NUM );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    return error_flag;
}

static err_t lteiot5_config_connection ( lteiot5_t *ctx )
{
    err_t error_flag = LTEIOT5_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    lteiot5_cmd_set( ctx, LTEIOT5_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    lteiot5_set_sim_apn( &lteiot5, SIM_APN );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    lteiot5_cmd_set( ctx, LTEIOT5_CMD_SET_MODULE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    lteiot5_cmd_set( ctx, LTEIOT5_CMD_EPS_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    lteiot5_cmd_set( ctx, LTEIOT5_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
#endif
    return error_flag;
}

static err_t lteiot5_check_connection ( lteiot5_t *ctx )
{
    err_t error_flag = LTEIOT5_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    #define CONNECTED "+CEREG: 2,1"
    lteiot5_cmd_get ( &lteiot5, LTEIOT5_CMD_EPS_NETWORK_REGISTRATION );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        lteiot5_cmd_run ( &lteiot5, LTEIOT5_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    }
    else
    {
        error_flag = LTEIOT5_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t lteiot5_config_example ( lteiot5_t *ctx )
{
    err_t error_flag = LTEIOT5_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Activate PDP context.\r\n" );
    #define ACTIVATE_PDP_CONTEXT "1,1"
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_ACTIVATE_PDP_CONTEXT, ACTIVATE_PDP_CONTEXT );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    log_printf( &logger, ">>> Set PDP type to IPv4.\r\n" );
    #define SET_PDP_TYPE_IPV4 "0,0,0"
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_PSD_CONFIG, SET_PDP_TYPE_IPV4 );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    log_printf( &logger, ">>> Map PSD profile to CID.\r\n" );
    #define MAP_PSD_PROFILE "0,100,1"
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_PSD_CONFIG, MAP_PSD_PROFILE );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    log_printf( &logger, ">>> Activate PSD profile.\r\n" );
    #define ACTIVATE_PSD_PROFILE "0,3"
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_PSD_ACTION, ACTIVATE_PSD_PROFILE );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    log_printf( &logger, ">>> Check GNSS enable.\r\n" );
    lteiot5_cmd_get( &lteiot5, LTEIOT5_CMD_GNSS_POWER_MANAGEMENT );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    #define GNSS_POWERED_OFF "+UGPS: 0"
    if ( strstr( app_buf, GNSS_POWERED_OFF ) )
    {
        log_printf( &logger, ">>> Enable GNSS.\r\n" );
        #define ENABLE_GNSS "1,0,1"
        lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_GNSS_POWER_MANAGEMENT, ENABLE_GNSS );
        error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, ">>> Enable NMEA $GGA messages.\r\n" );
    #define ENABLE_NMEA_GGA "1"
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_GET_GNSS_FIX_DATA, ENABLE_NMEA_GGA );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
#endif
    return error_flag;
}

static err_t lteiot5_example ( lteiot5_t *ctx )
{
    err_t error_flag = LTEIOT5_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t * __generic_ptr socket_num_buf = 0;
    uint8_t tcp_socket_num[ 2 ] = { 0 };
    uint8_t udp_socket_num[ 2 ] = { 0 };
    log_printf( &logger, ">>> Create TCP socket.\r\n" );
    #define TCP_PROTOCOL "6"
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_CREATE_SOCKET, TCP_PROTOCOL );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    socket_num_buf = strstr( app_buf, LTEIOT5_URC_CREATE_SOCKET ) + strlen ( LTEIOT5_URC_CREATE_SOCKET );
    if ( NULL != socket_num_buf )
    {
        tcp_socket_num[ 0 ] = *socket_num_buf;
    }

    log_printf( &logger, ">>> Create UDP socket.\r\n" );
    #define UDP_PROTOCOL "17"
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_CREATE_SOCKET, UDP_PROTOCOL );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    socket_num_buf = strstr( app_buf, LTEIOT5_URC_CREATE_SOCKET ) + strlen ( LTEIOT5_URC_CREATE_SOCKET );
    if ( NULL != socket_num_buf )
    {
        udp_socket_num[ 0 ] = *socket_num_buf;
    }

    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_CONNECT_SOCKET, cmd_buf );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_CONNECT_SOCKET, cmd_buf );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, MESSAGE_CONTENT );
    strcat( cmd_buf, "\"" );
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_WRITE_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_URC_RECEIVED_DATA );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_READ_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, MESSAGE_CONTENT );
    strcat( cmd_buf, "\"" );
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_WRITE_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_URC_RECEIVED_DATA );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot5_cmd_set( &lteiot5, LTEIOT5_CMD_READ_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_CLOSE_SOCKET, tcp_socket_num );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    lteiot5_cmd_set ( &lteiot5, LTEIOT5_CMD_CLOSE_SOCKET, udp_socket_num );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    log_printf( &logger, ">>> Check SMS format.\r\n" );
    lteiot5_cmd_get( &lteiot5, LTEIOT5_CMD_SELECT_SMS_FORMAT );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        lteiot5_send_sms_pdu( &lteiot5, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        lteiot5_send_sms_text ( &lteiot5, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    }
    // 30 seconds delay
    for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
    {
        Delay_ms ( 1000 );
    }
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    log_printf( &logger, ">>> Get GNSS fix data.\r\n" );
    lteiot5_cmd_get( &lteiot5, LTEIOT5_CMD_GET_GNSS_FIX_DATA );
    error_flag |= lteiot5_read_response( ctx, LTEIOT5_RSP_OK );
    if ( app_buf_len > ( sizeof ( LTEIOT5_RSP_GGA ) + LTEIOT5_GGA_ELEMENT_SIZE ) ) 
    {
        uint8_t element_buf[ 100 ] = { 0 };
        if ( LTEIOT5_OK == lteiot5_parse_gga( app_buf, LTEIOT5_GGA_LATITUDE, element_buf ) )
        {
            if ( strlen( element_buf ) > 0 )
            {
                log_printf( &logger, "Latitude: %.2s degrees, %s minutes\r\n", element_buf, &element_buf[ 2 ] );
                lteiot5_parse_gga( app_buf, LTEIOT5_GGA_LONGITUDE, element_buf );
                log_printf( &logger, "Longitude: %.3s degrees, %s minutes\r\n", element_buf, &element_buf[ 3 ] );
                memset( element_buf, 0, sizeof( element_buf ) );
                lteiot5_parse_gga( app_buf, LTEIOT5_GGA_ALTITUDE, element_buf );
                log_printf( &logger, "Altitude: %s m\r\n", element_buf );
            }
            else
            {
                log_printf( &logger, "Waiting for the position fix...\r\n" );
            }
            Delay_ms ( 5 );
            log_printf( &logger, "--------------------------------\r\n" );
            lteiot5_clear_app_buf(  );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    #error "No demo example selected"
#endif
    return error_flag;
}

// ------------------------------------------------------------------------ END
