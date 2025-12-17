/*!
 * @file main.c
 * @brief LTE IoT 13 Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending SMS or TCP/UDP messages or retrieving data from GNSS using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LTEIOT13_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *
 *  - LTEIOT13_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network 
 * (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT13_CHECK_CONNECTION:
 * Waits for the network registration indicated via CEREG command and then checks 
 * the signal quality report (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT13_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - LTEIOT13_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode)
 * or TCP/UDP message, or waits for the GPS fix to retrieve location info from GNSS.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void lteiot13_clear_app_buf ( void )
 * - static void lteiot13_log_app_buf ( void )
 * - static err_t lteiot13_process ( lteiot13_t *ctx )
 * - static err_t lteiot13_read_response ( lteiot13_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t lteiot13_power_up ( lteiot13_t *ctx )
 * - static err_t lteiot13_config_connection ( lteiot13_t *ctx )
 * - static err_t lteiot13_check_connection ( lteiot13_t *ctx )
 * - static err_t lteiot13_config_example ( lteiot13_t *ctx )
 * - static err_t lteiot13_example ( lteiot13_t *ctx )
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
#include "lteiot13.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define EXAMPLE_GNSS                        2               // Example of retrieving location info from GNSS
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
#define MESSAGE_CONTENT                     "LTE IoT 13 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTEIOT13_POWER_UP = 1,
    LTEIOT13_CONFIG_CONNECTION,
    LTEIOT13_CHECK_CONNECTION,
    LTEIOT13_CONFIG_EXAMPLE,
    LTEIOT13_EXAMPLE

} lteiot13_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static lteiot13_app_state_t app_state = LTEIOT13_POWER_UP;

static lteiot13_t lteiot13;
static log_t logger;

/**
 * @brief LTE IoT 13 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lteiot13_clear_app_buf ( void );

/**
 * @brief LTE IoT 13 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lteiot13_log_app_buf ( void );

/**
 * @brief LTE IoT 13 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lteiot13_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot13_process ( lteiot13_t *ctx );

/**
 * @brief LTE IoT 13 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lteiot13_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot13_read_response ( lteiot13_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief LTE IoT 13 power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lteiot13_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot13_power_up ( lteiot13_t *ctx );

/**
 * @brief LTE IoT 13 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #lteiot13_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot13_config_connection ( lteiot13_t *ctx );

/**
 * @brief LTE IoT 13 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #lteiot13_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot13_check_connection ( lteiot13_t *ctx );

/**
 * @brief LTE IoT 13 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #lteiot13_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot13_config_example ( lteiot13_t *ctx );

/**
 * @brief LTE IoT 13 example function.
 * @details This function executes SMS, TCP/UDP, or GNSS example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #lteiot13_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot13_example ( lteiot13_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot13_cfg_t lteiot13_cfg;  /**< Click config object. */

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
    lteiot13_cfg_setup( &lteiot13_cfg );
    LTEIOT13_MAP_MIKROBUS( lteiot13_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot13_init( &lteiot13, &lteiot13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT13_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LTEIOT13_POWER_UP:
        {
            if ( LTEIOT13_OK == lteiot13_power_up( &lteiot13 ) )
            {
                app_state = LTEIOT13_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT13_CONFIG_CONNECTION:
        {
            if ( LTEIOT13_OK == lteiot13_config_connection( &lteiot13 ) )
            {
                app_state = LTEIOT13_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT13_CHECK_CONNECTION:
        {
            if ( LTEIOT13_OK == lteiot13_check_connection( &lteiot13 ) )
            {
                app_state = LTEIOT13_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT13_CONFIG_EXAMPLE:
        {
            if ( LTEIOT13_OK == lteiot13_config_example( &lteiot13 ) )
            {
                app_state = LTEIOT13_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT13_EXAMPLE:
        {
            lteiot13_example( &lteiot13 );
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

static void lteiot13_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lteiot13_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot13_process ( lteiot13_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lteiot13_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTEIOT13_OK;
    }
    return LTEIOT13_ERROR;
}

static err_t lteiot13_read_response ( lteiot13_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    lteiot13_clear_app_buf ( );
    lteiot13_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTEIOT13_RSP_ERROR ) ) )
    {
        lteiot13_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            lteiot13_log_app_buf( );
            lteiot13_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LTEIOT13_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lteiot13_process( ctx );
    lteiot13_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        if ( strstr ( rsp, LTEIOT13_URC_CONSOLE_READY ) )
        {
            log_printf( &logger, "\r\n" );
        }
        log_printf( &logger, "--------------------------------\r\n" );
        return LTEIOT13_OK;
    }
    return LTEIOT13_ERROR_CMD;
}

static err_t lteiot13_power_up ( lteiot13_t *ctx )
{
    err_t error_flag = LTEIOT13_ERROR;

    while ( LTEIOT13_OK != error_flag )
    {
        log_printf( &logger, ">>> Power down device.\r\n" );
        lteiot13_set_power_state ( ctx, LTEIOT13_POWER_STATE_OFF );

        log_printf( &logger, ">>> Power up device.\r\n" );
        lteiot13_set_power_state ( ctx, LTEIOT13_POWER_STATE_ON );
        error_flag = lteiot13_read_response( ctx, LTEIOT13_URC_CONSOLE_READY, LTEIOT13_MAX_RSP_TIME_URC );
    }

    log_printf( &logger, ">>> Switch to AT mode.\r\n" );
    lteiot13_cmd_run( ctx, LTEIOT13_CMD_SWITCH_TO_AT );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_URC_AT_READY, LTEIOT13_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Check communication.\r\n" );
    lteiot13_cmd_run( ctx, LTEIOT13_CMD_AT );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    lteiot13_cmd_run( ctx, LTEIOT13_CMD_GET_SW_VERSION );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    lteiot13_cmd_run( ctx, LTEIOT13_CMD_GET_SERIAL_NUM );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t lteiot13_config_connection ( lteiot13_t *ctx )
{
    err_t error_flag = LTEIOT13_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Set minimum functionality.\r\n" );
    #define MIN_FUNCTIONALITY "0"
    lteiot13_cmd_set( ctx, LTEIOT13_CMD_SET_UE_FUNCTIONALITY, MIN_FUNCTIONALITY );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_CFUN );
    
    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    lteiot13_set_sim_apn( ctx, SIM_APN );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    lteiot13_cmd_set( ctx, LTEIOT13_CMD_SET_UE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    lteiot13_cmd_set( ctx, LTEIOT13_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );
#endif
    return error_flag;
}

static err_t lteiot13_check_connection ( lteiot13_t *ctx )
{
    err_t error_flag = LTEIOT13_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    lteiot13_cmd_get ( &lteiot13, LTEIOT13_CMD_NETWORK_REGISTRATION );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, LTEIOT13_URC_NETWORK_REGISTERED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        lteiot13_cmd_run( &lteiot13, LTEIOT13_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );
    }
    else
    {
        error_flag = LTEIOT13_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t lteiot13_config_example ( lteiot13_t *ctx )
{
    err_t error_flag = LTEIOT13_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Enable socket events.\r\n" );
    #define ENABLE_SOCKET_EVENTS "0,1"
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_SOCKET_EVENTS, ENABLE_SOCKET_EVENTS );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    log_printf( &logger, ">>> Set minimum functionality.\r\n" );
    #define MIN_FUNCTIONALITY "0"
    lteiot13_cmd_set( ctx, LTEIOT13_CMD_SET_UE_FUNCTIONALITY, MIN_FUNCTIONALITY );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_CFUN );
    log_printf( &logger, ">>> Disable GNSS functionality.\r\n" );
    #define DEACTIVATE_GNSS "0"
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_GNSS_ACTIVATE, DEACTIVATE_GNSS );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_GNSS );
    log_printf( &logger, ">>> Set NMEA GGA.\r\n" );
    #define SET_NMEA_GGA "\"SET\",\"NMEA\",\"GGA\""
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_GNSS_CONFIG, SET_NMEA_GGA );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_GNSS );
    log_printf( &logger, ">>> Enable NMEA report.\r\n" );
    #define EN_NMEA_REPORT "\"NMEA\",1"
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_GNSS_EVENTS, EN_NMEA_REPORT );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_GNSS );
    log_printf( &logger, ">>> Enable GNSS functionality.\r\n" );
    #define ACTIVATE_GNSS "1"
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_GNSS_ACTIVATE, ACTIVATE_GNSS );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_GNSS );
#endif
    return error_flag;
}

static err_t lteiot13_example ( lteiot13_t *ctx )
{
    err_t error_flag = LTEIOT13_OK;
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
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_ACTIVATE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_URC );

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
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_URC_SOCKET_DATA_EVENT, LTEIOT13_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_RECEIVE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, TCP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );

    // Parse response
    uint8_t response[ 100 ] = { 0 };
    uint8_t response_len[ 5 ] = { 0 };
    char * __generic_ptr start_response_len_buf = 0;
    uint8_t response_len_buf_len = 0;
    start_response_len_buf = strstr( app_buf, LTEIOT13_URC_SOCKET_DATA ) + strlen ( LTEIOT13_URC_SOCKET_DATA ) + 2;
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
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_URC );

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
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_URC );

    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_ACTIVATE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_URC );

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
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_URC_SOCKET_DATA_EVENT, LTEIOT13_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    strcpy( cmd_buf, "\"" );
    strcat( cmd_buf, SOCKET_CMD_RECEIVE );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot13_cmd_set( &lteiot13, LTEIOT13_CMD_SOCKET_DATA, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );

    // Parse response
    start_response_len_buf = strstr( app_buf, LTEIOT13_URC_SOCKET_DATA ) + strlen ( LTEIOT13_URC_SOCKET_DATA ) + 2;
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
    lteiot13_cmd_set ( &lteiot13, LTEIOT13_CMD_SOCKET_CMD, cmd_buf );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_URC );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    log_printf( &logger, ">>> Check SMS format.\r\n" );
    lteiot13_cmd_get( &lteiot13, LTEIOT13_CMD_SELECT_SMS_FORMAT );
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, LTEIOT13_URC_SMS_FORMAT_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        lteiot13_send_sms_pdu( &lteiot13, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_CMGS );
    }
    else if ( strstr( app_buf, LTEIOT13_URC_SMS_FORMAT_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        lteiot13_send_sms_text ( &lteiot13, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot13_read_response( ctx, LTEIOT13_RSP_OK, LTEIOT13_MAX_RSP_TIME_CMGS );
    }
    // 30 seconds delay
    for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
    {
        Delay_ms ( 1000 );
    }
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    uint8_t element_buf[ 100 ] = { 0 };
    error_flag |= lteiot13_read_response( ctx, LTEIOT13_URC_GNSS, LTEIOT13_MAX_RSP_TIME_GNSS );
    log_printf( &logger, ">>> Parse GNSS NMEA sentence.\r\n" );
    if ( LTEIOT13_OK == lteiot13_parse_gga( app_buf, LTEIOT13_GGA_LATITUDE, element_buf ) )
    {
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "Latitude: %.2s degrees, %s minutes\r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            lteiot13_parse_gga( app_buf, LTEIOT13_GGA_LONGITUDE, element_buf );
            log_printf( &logger, "Longitude: %.3s degrees, %s minutes\r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            lteiot13_parse_gga( app_buf, LTEIOT13_GGA_ALTITUDE, element_buf );
            log_printf( &logger, "Altitude: %s m\r\n", element_buf );
        }
        else
        {
            log_printf( &logger, "No position fix detected.\r\n" );
        }
    }
    log_printf( &logger, "--------------------------------\r\n" );
#else
    #error "No demo example selected"
#endif
    return error_flag;
}

// ------------------------------------------------------------------------ END
