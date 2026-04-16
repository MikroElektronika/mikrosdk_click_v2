/*!
 * @file main.c
 * @brief LTE IoT 24 Click Example.
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
 *  - LTEIOT24_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *
 *  - LTEIOT24_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network 
 * (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT24_CHECK_CONNECTION:
 * Waits for the network registration indicated via CREG command and then checks 
 * the signal quality report (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT24_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - LTEIOT24_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode)
 * or TCP/UDP message, or waits for the GPS fix to retrieve location info from GNSS.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void lteiot24_clear_app_buf ( void )
 * - static void lteiot24_log_app_buf ( void )
 * - static err_t lteiot24_process ( lteiot24_t *ctx )
 * - static err_t lteiot24_read_response ( lteiot24_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t lteiot24_power_up ( lteiot24_t *ctx )
 * - static err_t lteiot24_config_connection ( lteiot24_t *ctx )
 * - static err_t lteiot24_check_connection ( lteiot24_t *ctx )
 * - static err_t lteiot24_config_example ( lteiot24_t *ctx )
 * - static err_t lteiot24_example ( lteiot24_t *ctx )
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
#include "lteiot24.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_LTEIOT24
    #define MIKROBUS_POSITION_LTEIOT24 MIKROBUS_1
#endif

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
#define MESSAGE_CONTENT                     "LTE IoT 24 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTEIOT24_POWER_UP = 1,
    LTEIOT24_CONFIG_CONNECTION,
    LTEIOT24_CHECK_CONNECTION,
    LTEIOT24_CONFIG_EXAMPLE,
    LTEIOT24_EXAMPLE

} lteiot24_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static lteiot24_app_state_t app_state = LTEIOT24_POWER_UP;

static lteiot24_t lteiot24;
static log_t logger;

/**
 * @brief LTE IoT 24 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void lteiot24_clear_app_buf ( void );

/**
 * @brief LTE IoT 24 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void lteiot24_log_app_buf ( void );

/**
 * @brief LTE IoT 24 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot24_process ( lteiot24_t *ctx );

/**
 * @brief LTE IoT 24 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot24_read_response ( lteiot24_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief LTE IoT 24 power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot24_power_up ( lteiot24_t *ctx );

/**
 * @brief LTE IoT 24 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot24_config_connection ( lteiot24_t *ctx );

/**
 * @brief LTE IoT 24 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot24_check_connection ( lteiot24_t *ctx );

/**
 * @brief LTE IoT 24 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot24_config_example ( lteiot24_t *ctx );

/**
 * @brief LTE IoT 24 example function.
 * @details This function executes SMS, TCP/UDP, or GNSS example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #lteiot24_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot24_example ( lteiot24_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot24_cfg_t lteiot24_cfg;  /**< Click config object. */

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
    lteiot24_cfg_setup( &lteiot24_cfg );
    LTEIOT24_MAP_MIKROBUS( lteiot24_cfg, MIKROBUS_POSITION_LTEIOT24 );
    if ( UART_ERROR == lteiot24_init( &lteiot24, &lteiot24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT24_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LTEIOT24_POWER_UP:
        {
            if ( LTEIOT24_OK == lteiot24_power_up( &lteiot24 ) )
            {
                app_state = LTEIOT24_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT24_CONFIG_CONNECTION:
        {
            if ( LTEIOT24_OK == lteiot24_config_connection( &lteiot24 ) )
            {
                app_state = LTEIOT24_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT24_CHECK_CONNECTION:
        {
            if ( LTEIOT24_OK == lteiot24_check_connection( &lteiot24 ) )
            {
                app_state = LTEIOT24_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT24_CONFIG_EXAMPLE:
        {
            if ( LTEIOT24_OK == lteiot24_config_example( &lteiot24 ) )
            {
                app_state = LTEIOT24_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT24_EXAMPLE:
        {
            lteiot24_example( &lteiot24 );
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

static void lteiot24_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lteiot24_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot24_process ( lteiot24_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lteiot24_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTEIOT24_OK;
    }
    return LTEIOT24_ERROR;
}

static err_t lteiot24_read_response ( lteiot24_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    lteiot24_clear_app_buf ( );
    lteiot24_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTEIOT24_RSP_ERROR ) ) )
    {
        lteiot24_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            lteiot24_log_app_buf( );
            lteiot24_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LTEIOT24_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lteiot24_process( ctx );
    lteiot24_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return LTEIOT24_OK;
    }
    return LTEIOT24_ERROR_CMD;
}

static err_t lteiot24_power_up ( lteiot24_t *ctx )
{
    err_t error_flag = LTEIOT24_OK;

    for ( ; ; )
    {
        // Wake up UART interface
        lteiot24_cmd_run( ctx, LTEIOT24_CMD_AT );
        lteiot24_process( ctx );
        lteiot24_clear_app_buf( );

        log_printf( &logger, ">>> Check communication.\r\n" );
        lteiot24_cmd_run( ctx, LTEIOT24_CMD_AT );
        error_flag = lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
        if ( LTEIOT24_OK == error_flag )
        {
            break;
        }
        else
        {
            log_printf( &logger, ">>> Power up device.\r\n" );
            lteiot24_set_power_state ( ctx, LTEIOT24_POWER_STATE_ON );
        }
    }

    log_printf( &logger, ">>> Factory reset.\r\n" );
    lteiot24_cmd_run( ctx, LTEIOT24_CMD_FACTORY_RESET );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    lteiot24_cmd_run( ctx, LTEIOT24_CMD_GET_SW_VERSION );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    lteiot24_cmd_run( ctx, LTEIOT24_CMD_GET_SERIAL_NUM );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t lteiot24_config_connection ( lteiot24_t *ctx )
{
    err_t error_flag = LTEIOT24_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    lteiot24_cmd_set( ctx, LTEIOT24_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_COPS );

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    lteiot24_set_sim_apn( &lteiot24, SIM_APN );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    lteiot24_cmd_set( ctx, LTEIOT24_CMD_SET_PHONE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    lteiot24_cmd_set( ctx, LTEIOT24_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    lteiot24_cmd_set( ctx, LTEIOT24_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_COPS );
#endif
    return error_flag;
}

static err_t lteiot24_check_connection ( lteiot24_t *ctx )
{
    err_t error_flag = LTEIOT24_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    lteiot24_cmd_get ( &lteiot24, LTEIOT24_CMD_NETWORK_REGISTRATION );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, LTEIOT24_URC_NETWORK_REGISTERED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        lteiot24_cmd_run( &lteiot24, LTEIOT24_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
    }
    else
    {
        error_flag = LTEIOT24_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t lteiot24_config_example ( lteiot24_t *ctx )
{
    err_t error_flag = LTEIOT24_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Activate PDP context.\r\n" );
    #define ACTIVATE_PDP_CONTEXT "1,1"
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_ACTIVATE_PDP_CONTEXT, ACTIVATE_PDP_CONTEXT );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_SGACT );
    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    lteiot24_cmd_set( ctx, LTEIOT24_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_COPS );
    log_printf( &logger, ">>> Disable GNSS functionality.\r\n" );
    #define DEACTIVATE_GNSS "0"
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_GNSS_SET_POWER, DEACTIVATE_GNSS );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_GNSS );
    log_printf( &logger, ">>> Set NMEA GGA.\r\n" );
    #define SET_NMEA_GGA "1,02"
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_GNSS_SET_NMEA_OUTPUT, SET_NMEA_GGA );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_GNSS );
    log_printf( &logger, ">>> Enable GNSS functionality.\r\n" );
    #define ACTIVATE_GNSS "1"
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_GNSS_SET_POWER, ACTIVATE_GNSS );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_GNSS );
#endif
    return error_flag;
}

static err_t lteiot24_example ( lteiot24_t *ctx )
{
    err_t error_flag = LTEIOT24_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    #define CONN_ID_TCP "1"
    #define TX_PROT_TCP "0"
    #define CLOSURE_TYPE "0"
    #define LOCAL_PORT "1000"
    #define CONN_MODE_CMD "1"
    strcpy( cmd_buf, CONN_ID_TCP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, TX_PROT_TCP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, CLOSURE_TYPE );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, LOCAL_PORT );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, CONN_MODE_CMD );
    lteiot24_cmd_set ( &lteiot24, LTEIOT24_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_SD );

    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    #define CONN_ID_UDP "2"
    #define TX_PROT_UDP "1"
    strcpy( cmd_buf, CONN_ID_UDP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, TX_PROT_UDP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, CLOSURE_TYPE );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, LOCAL_PORT );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, CONN_MODE_CMD );
    lteiot24_cmd_set ( &lteiot24, LTEIOT24_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_SD );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    strcpy( cmd_buf, CONN_ID_TCP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot24_cmd_set ( &lteiot24, LTEIOT24_CMD_SEND_DATA, cmd_buf );
    Delay_ms ( 100 );
    lteiot24_generic_write ( &lteiot24, MESSAGE_CONTENT, message_len );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_URC_RECEIVED_DATA, LTEIOT24_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_RECEIVE_DATA, cmd_buf );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, CONN_ID_UDP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot24_cmd_set ( &lteiot24, LTEIOT24_CMD_SEND_DATA, cmd_buf );
    Delay_ms ( 100 );
    lteiot24_generic_write ( &lteiot24, MESSAGE_CONTENT, message_len );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_URC_RECEIVED_DATA, LTEIOT24_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    lteiot24_cmd_set( &lteiot24, LTEIOT24_CMD_RECEIVE_DATA, cmd_buf );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    lteiot24_cmd_set ( &lteiot24, LTEIOT24_CMD_CLOSE_SOCKET, CONN_ID_TCP );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_SH );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    lteiot24_cmd_set ( &lteiot24, LTEIOT24_CMD_CLOSE_SOCKET, CONN_ID_UDP );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_SH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    log_printf( &logger, ">>> Check SMS format.\r\n" );
    lteiot24_cmd_get( &lteiot24, LTEIOT24_CMD_SELECT_SMS_FORMAT );
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, LTEIOT24_URC_SMS_FORMAT_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        lteiot24_send_sms_pdu( &lteiot24, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_CMGS );
    }
    else if ( strstr( app_buf, LTEIOT24_URC_SMS_FORMAT_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        lteiot24_send_sms_text ( &lteiot24, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_OK, LTEIOT24_MAX_RSP_TIME_CMGS );
    }
    // 30 seconds delay
    for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
    {
        Delay_ms ( 1000 );
    }
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    uint8_t element_buf[ 100 ] = { 0 };
    error_flag |= lteiot24_read_response( ctx, LTEIOT24_RSP_GGA, LTEIOT24_MAX_RSP_TIME_GNSS );
    log_printf( &logger, ">>> Parse GNSS NMEA sentence.\r\n" );
    if ( LTEIOT24_OK == lteiot24_parse_gga( app_buf, LTEIOT24_GGA_LATITUDE, element_buf ) )
    {
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "Latitude: %.2s degrees, %s minutes\r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            lteiot24_parse_gga( app_buf, LTEIOT24_GGA_LONGITUDE, element_buf );
            log_printf( &logger, "Longitude: %.3s degrees, %s minutes\r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            lteiot24_parse_gga( app_buf, LTEIOT24_GGA_ALTITUDE, element_buf );
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
