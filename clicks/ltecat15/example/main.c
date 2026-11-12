/*!
 * @file main.c
 * @brief LTE Cat.1 5 Click Example.
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
 *  - LTECAT15_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *
 *  - LTECAT15_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - LTECAT15_CHECK_CONNECTION:
 * Waits for the network registration indicated via CEREG command and then checks the signal quality report.
 *
 *  - LTECAT15_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - LTECAT15_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void ltecat15_clear_app_buf ( void )
 * - static void ltecat15_log_app_buf ( void )
 * - static err_t ltecat15_process ( ltecat15_t *ctx )
 * - static err_t ltecat15_read_response ( ltecat15_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t ltecat15_power_up ( ltecat15_t *ctx )
 * - static err_t ltecat15_config_connection ( ltecat15_t *ctx )
 * - static err_t ltecat15_check_connection ( ltecat15_t *ctx )
 * - static err_t ltecat15_config_example ( ltecat15_t *ctx )
 * - static err_t ltecat15_example ( ltecat15_t *ctx )
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
#include "ltecat15.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_LTECAT15
    #define MIKROBUS_POSITION_LTECAT15 MIKROBUS_1
#endif

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
#define MESSAGE_CONTENT                     "LTE Cat.1 5 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTECAT15_POWER_UP = 1,
    LTECAT15_CONFIG_CONNECTION,
    LTECAT15_CHECK_CONNECTION,
    LTECAT15_CONFIG_EXAMPLE,
    LTECAT15_EXAMPLE

} ltecat15_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static ltecat15_app_state_t app_state = LTECAT15_POWER_UP;

static ltecat15_t ltecat15;
static log_t logger;

/**
 * @brief LTE Cat.1 5 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void ltecat15_clear_app_buf ( void );

/**
 * @brief LTE Cat.1 5 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void ltecat15_log_app_buf ( void );

/**
 * @brief LTE Cat.1 5 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ltecat15_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat15_process ( ltecat15_t *ctx );

/**
 * @brief LTE Cat.1 5 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #ltecat15_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat15_read_response ( ltecat15_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief LTE Cat.1 5 power up function.
 * @details This function powers up the device, performs device factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #ltecat15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat15_power_up ( ltecat15_t *ctx );

/**
 * @brief LTE Cat.1 5 config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #ltecat15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat15_config_connection ( ltecat15_t *ctx );

/**
 * @brief LTE Cat.1 5 check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #ltecat15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat15_check_connection ( ltecat15_t *ctx );

/**
 * @brief LTE Cat.1 5 config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #ltecat15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat15_config_example ( ltecat15_t *ctx );

/**
 * @brief LTE Cat.1 5 example function.
 * @details This function executes SMS or TCP/UDP example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #ltecat15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat15_example ( ltecat15_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat15_cfg_t ltecat15_cfg;  /**< Click config object. */

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
    ltecat15_cfg_setup( &ltecat15_cfg );
    LTECAT15_MAP_MIKROBUS( ltecat15_cfg, MIKROBUS_POSITION_LTECAT15 );
    if ( UART_ERROR == ltecat15_init( &ltecat15, &ltecat15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTECAT15_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LTECAT15_POWER_UP:
        {
            if ( LTECAT15_OK == ltecat15_power_up( &ltecat15 ) )
            {
                app_state = LTECAT15_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT15_CONFIG_CONNECTION:
        {
            if ( LTECAT15_OK == ltecat15_config_connection( &ltecat15 ) )
            {
                app_state = LTECAT15_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT15_CHECK_CONNECTION:
        {
            if ( LTECAT15_OK == ltecat15_check_connection( &ltecat15 ) )
            {
                app_state = LTECAT15_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT15_CONFIG_EXAMPLE:
        {
            if ( LTECAT15_OK == ltecat15_config_example( &ltecat15 ) )
            {
                app_state = LTECAT15_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT15_EXAMPLE:
        {
            ltecat15_example( &ltecat15 );
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

static void ltecat15_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ltecat15_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ltecat15_process ( ltecat15_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ltecat15_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTECAT15_OK;
    }
    return LTECAT15_ERROR;
}

static err_t ltecat15_read_response ( ltecat15_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    ltecat15_clear_app_buf( );
    ltecat15_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTECAT15_RSP_ERROR ) ) )
    {
        ltecat15_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            ltecat15_log_app_buf( );
            ltecat15_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LTECAT15_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    ltecat15_process( ctx );
    ltecat15_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return LTECAT15_OK;
    }
    return LTECAT15_ERROR_CMD;
}

static err_t ltecat15_power_up ( ltecat15_t *ctx )
{
    err_t error_flag = LTECAT15_OK;
    
    log_printf( &logger, ">>> HW reset device.\r\n" );
    ltecat15_reset_device( ctx );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_URC_READY, LTECAT15_MAX_RSP_TIME_HARD_RESET );

    log_printf( &logger, ">>> Check communication.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_AT );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_FIRST_RSP );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_FACTORY_RESET );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_FACT_RESET );

    log_printf( &logger, ">>> SW reset device.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_HARD_RESET );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_URC_READY, LTECAT15_MAX_RSP_TIME_HARD_RESET );

    log_printf( &logger, ">>> Enable command echo.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_ENABLE_ECHO );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_FIRST_RSP );

    log_printf( &logger, ">>> Get device model ID.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_GET_MODEL_ID );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_GET_SW_VERSION );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_GET_SERIAL_NUM );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Enter manufacturing mode.\r\n" );
    #define MANUFACTURING_MODE "5"
    ltecat15_cmd_set( ctx, LTECAT15_CMD_SET_PHONE_FUNCTIONALITY, MANUFACTURING_MODE );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable STAT LED.\r\n" );
    #define ENABLE_STAT_LED "\"status_led\",\"enable\""
    ltecat15_cmd_set( ctx, LTECAT15_CMD_HW_FUNCTION_CONFIG, ENABLE_STAT_LED );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Enable LED blink mode.\r\n" );
    #define BLINK_MODE_ON "1"
    ltecat15_cmd_set( ctx, LTECAT15_CMD_SET_LED_BLINK_MODE, BLINK_MODE_ON );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> SW reset device.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_HARD_RESET );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_URC_READY, LTECAT15_MAX_RSP_TIME_HARD_RESET );

    log_printf( &logger, ">>> Enable command echo.\r\n" );
    ltecat15_cmd_run( ctx, LTECAT15_CMD_ENABLE_ECHO );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_FIRST_RSP );

    return error_flag;
}

static err_t ltecat15_config_connection ( ltecat15_t *ctx )
{
    err_t error_flag = LTECAT15_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    ltecat15_set_sim_apn( &ltecat15, SIM_APN );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    ltecat15_cmd_set( ctx, LTECAT15_CMD_SET_PHONE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    ltecat15_cmd_set( ctx, LTECAT15_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    ltecat15_cmd_set( ctx, LTECAT15_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_COPS );
#endif
    return error_flag;
}

static err_t ltecat15_check_connection ( ltecat15_t *ctx )
{
    err_t error_flag = LTECAT15_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    ltecat15_cmd_get( &ltecat15, LTECAT15_CMD_NETWORK_REGISTRATION );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, LTECAT15_URC_NETWORK_REGISTERED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        ltecat15_cmd_run( &ltecat15, LTECAT15_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
    }
    else
    {
        error_flag = LTECAT15_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t ltecat15_config_example ( ltecat15_t *ctx )
{
    err_t error_flag = LTECAT15_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Activate PDP context.\r\n" );
    #define ACTIVATE_PDP_CONTEXT "1,1"
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_ACTIVATE_PDP_CONTEXT, ACTIVATE_PDP_CONTEXT );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_CGACT );

    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
#endif
    return error_flag;
}

static err_t ltecat15_example ( ltecat15_t *ctx )
{
    err_t error_flag = LTECAT15_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t ctrl_z = 0x1A;
    
    log_printf( &logger, ">>> Open TCP connection.\r\n" );
    #define TCP_LINK_NUM "1"
    #define TCP_CONN_TYPE "0"
    strcpy( cmd_buf, TCP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, TCP_CONN_TYPE );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\",0,0,1" ); // Closure type, local port, and connection mode CMD.
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_OPEN_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_SQNSD );

    log_printf( &logger, ">>> Open UDP connection.\r\n" );
    #define UDP_LINK_NUM "2"
    #define UDP_CONN_TYPE "1"
    strcpy( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, UDP_CONN_TYPE );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\",0,5000,1" ); // Closure type, local port, and connection mode CMD.
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_OPEN_TCP_UDP_CONNECTION, cmd_buf );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_SQNSD );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    log_printf( &logger, ">>> Write message to TCP connection.\r\n" );
    strcpy( cmd_buf, TCP_LINK_NUM );
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 100 );
    ltecat15_generic_write ( &ltecat15, MESSAGE_CONTENT, message_len );
    ltecat15_generic_write ( &ltecat15, &ctrl_z, 1 );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_URC_RECEIVED_DATA, LTECAT15_MAX_RSP_TIME_SQNSSEND );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    strcpy( cmd_buf, TCP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_LINK_NUM );
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_SEND_DATA_VIA_CONNECTION, cmd_buf );
    Delay_ms ( 100 );
    ltecat15_generic_write ( &ltecat15, MESSAGE_CONTENT, message_len );
    ltecat15_generic_write ( &ltecat15, &ctrl_z, 1 );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_URC_RECEIVED_DATA, LTECAT15_MAX_RSP_TIME_SQNSSEND );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_LINK_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_RECEIVE_DATA_VIA_CONNECTION, cmd_buf );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_CLOSE_TCP_UDP_CONNECTION, TCP_LINK_NUM );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    ltecat15_cmd_set( &ltecat15, LTECAT15_CMD_CLOSE_TCP_UDP_CONNECTION, UDP_LINK_NUM );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
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
    ltecat15_cmd_get( &ltecat15, LTECAT15_CMD_SELECT_SMS_FORMAT );
    error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        ltecat15_send_sms_pdu( &ltecat15, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_CMGS );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        ltecat15_send_sms_text ( &ltecat15, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= ltecat15_read_response( ctx, LTECAT15_RSP_OK, LTECAT15_MAX_RSP_TIME_CMGS );
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
