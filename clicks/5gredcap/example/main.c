/*!
 * @file main.c
 * @brief 5G RedCap Click Example.
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
 *  - C5GREDCAP_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *
 *  - C5GREDCAP_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network 
 * (used only for SMS, CALL, or TCP/UDP demo examples).
 *
 *  - C5GREDCAP_CHECK_CONNECTION:
 * Waits for the network registration indicated via CEREG command and then checks 
 * the signal quality report (used only for SMS, CALL, or TCP/UDP demo examples).
 *
 *  - C5GREDCAP_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - C5GREDCAP_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode)
 * or TCP/UDP message, waits for incoming calls and answers it, or waits for the GPS fix
 * to retrieve location info from GNSS.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void c5gredcap_clear_app_buf ( void )
 * - static void c5gredcap_log_app_buf ( void )
 * - static err_t c5gredcap_process ( c5gredcap_t *ctx )
 * - static err_t c5gredcap_read_response ( c5gredcap_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t c5gredcap_power_up ( c5gredcap_t *ctx )
 * - static err_t c5gredcap_config_connection ( c5gredcap_t *ctx )
 * - static err_t c5gredcap_check_connection ( c5gredcap_t *ctx )
 * - static err_t c5gredcap_config_example ( c5gredcap_t *ctx )
 * - static err_t c5gredcap_example ( c5gredcap_t *ctx )
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
#include "c5gredcap.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_5GREDCAP
    #define MIKROBUS_POSITION_5GREDCAP MIKROBUS_1
#endif

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define EXAMPLE_CALL                        2               // Example of answering incoming calls 
#define EXAMPLE_GNSS                        3               // Example of retrieving location info from GNSS
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
#define MESSAGE_CONTENT                     "5G RedCap Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    C5GREDCAP_POWER_UP = 1,
    C5GREDCAP_CONFIG_CONNECTION,
    C5GREDCAP_CHECK_CONNECTION,
    C5GREDCAP_CONFIG_EXAMPLE,
    C5GREDCAP_EXAMPLE

} c5gredcap_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static c5gredcap_app_state_t app_state = C5GREDCAP_POWER_UP;

static c5gredcap_t c5gredcap;
static log_t logger;

/**
 * @brief 5G RedCap clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void c5gredcap_clear_app_buf ( void );

/**
 * @brief 5G RedCap log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void c5gredcap_log_app_buf ( void );

/**
 * @brief 5G RedCap data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c5gredcap_process ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c5gredcap_read_response ( c5gredcap_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief 5G RedCap power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c5gredcap_power_up ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c5gredcap_config_connection ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap check connection function.
 * @details This function checks the connection to network.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c5gredcap_check_connection ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap config example function.
 * @details This function configures device for the selected example.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c5gredcap_config_example ( c5gredcap_t *ctx );

/**
 * @brief 5G RedCap example function.
 * @details This function executes SMS, TCP/UDP, CALL, or GNSS example depending on the DEMO_EXAMPLE macro.
 * @param[in] ctx : Click context object.
 * See #c5gredcap_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c5gredcap_example ( c5gredcap_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c5gredcap_cfg_t c5gredcap_cfg;  /**< Click config object. */

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
    c5gredcap_cfg_setup( &c5gredcap_cfg );
    C5GREDCAP_MAP_MIKROBUS( c5gredcap_cfg, MIKROBUS_POSITION_5GREDCAP );
    if ( UART_ERROR == c5gredcap_init( &c5gredcap, &c5gredcap_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = C5GREDCAP_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case C5GREDCAP_POWER_UP:
        {
            if ( C5GREDCAP_OK == c5gredcap_power_up( &c5gredcap ) )
            {
                app_state = C5GREDCAP_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_CONFIG_CONNECTION:
        {
            if ( C5GREDCAP_OK == c5gredcap_config_connection( &c5gredcap ) )
            {
                app_state = C5GREDCAP_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_CHECK_CONNECTION:
        {
            if ( C5GREDCAP_OK == c5gredcap_check_connection( &c5gredcap ) )
            {
                app_state = C5GREDCAP_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_CONFIG_EXAMPLE:
        {
            if ( C5GREDCAP_OK == c5gredcap_config_example( &c5gredcap ) )
            {
                app_state = C5GREDCAP_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_EXAMPLE:
        {
            c5gredcap_example( &c5gredcap );
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

static void c5gredcap_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void c5gredcap_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t c5gredcap_process ( c5gredcap_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = c5gredcap_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return C5GREDCAP_OK;
    }
    return C5GREDCAP_ERROR;
}

static err_t c5gredcap_read_response ( c5gredcap_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    c5gredcap_clear_app_buf ( );
    c5gredcap_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, C5GREDCAP_RSP_ERROR ) ) )
    {
        c5gredcap_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            c5gredcap_log_app_buf( );
            c5gredcap_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return C5GREDCAP_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    if ( strstr( rsp, C5GREDCAP_URC_RDY ) )
    {
        Delay_ms ( 500 );
    }
    Delay_ms ( 200 );
    c5gredcap_process( ctx );
    c5gredcap_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return C5GREDCAP_OK;
    }
    return C5GREDCAP_ERROR_CMD;
}

static err_t c5gredcap_power_up ( c5gredcap_t *ctx )
{
    err_t error_flag = C5GREDCAP_OK;

    uint8_t power_state = C5GREDCAP_POWER_STATE_OFF;
    for ( ; ; )
    {
        // Wake up UART interface
        c5gredcap_cmd_run( ctx, C5GREDCAP_CMD_AT );
        c5gredcap_process( ctx );
        c5gredcap_clear_app_buf( );

        log_printf( &logger, ">>> Check communication.\r\n" );
        c5gredcap_cmd_run( ctx, C5GREDCAP_CMD_AT );  
        if ( ( ( C5GREDCAP_OK == c5gredcap_process( ctx ) ) && strstr( app_buf, C5GREDCAP_RSP_OK ) ) )
        {
            power_state = C5GREDCAP_POWER_STATE_ON;
            break;
        }
        else if ( ( C5GREDCAP_POWER_STATE_OFF == power_state ) || 
                  ( C5GREDCAP_POWER_STATE_RESET == power_state ) )
        {
            power_state = C5GREDCAP_POWER_STATE_ON;
            log_printf( &logger, ">>> Power up device.\r\n" );
            c5gredcap_set_power_state ( ctx, power_state );
            c5gredcap_read_response( ctx, C5GREDCAP_URC_RDY, C5GREDCAP_MAX_RSP_TIME_READY );
        }
        else if ( C5GREDCAP_POWER_STATE_ON == power_state )
        {
            power_state = C5GREDCAP_POWER_STATE_RESET;
            log_printf( &logger, ">>> Reset device.\r\n" );
            c5gredcap_set_power_state ( ctx, power_state );
            c5gredcap_read_response( ctx, C5GREDCAP_URC_RDY, C5GREDCAP_MAX_RSP_TIME_READY );
        }
    }
    c5gredcap_cmd_run( ctx, C5GREDCAP_CMD_AT );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    c5gredcap_cmd_run( ctx, C5GREDCAP_CMD_FACTORY_RESET );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    c5gredcap_cmd_run( ctx, C5GREDCAP_CMD_GET_SW_VERSION );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    c5gredcap_cmd_run( ctx, C5GREDCAP_CMD_GET_SERIAL_NUM );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t c5gredcap_config_connection ( c5gredcap_t *ctx )
{
    err_t error_flag = C5GREDCAP_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) )
    log_printf( &logger, ">>> Deregister from network.\r\n" );
    #define DEREGISTER_FROM_NETWORK "2"
    c5gredcap_cmd_set( ctx, C5GREDCAP_CMD_OPERATOR_SELECTION, DEREGISTER_FROM_NETWORK );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_COPS );

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    c5gredcap_set_sim_apn( &c5gredcap, SIM_APN );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Enable full functionality.\r\n" );
    #define FULL_FUNCTIONALITY "1"
    c5gredcap_cmd_set( ctx, C5GREDCAP_CMD_SET_UE_FUNCTIONALITY, FULL_FUNCTIONALITY );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_CFUN );

    log_printf( &logger, ">>> Enable network registration.\r\n" );
    #define ENABLE_REG "2"
    c5gredcap_cmd_set( ctx, C5GREDCAP_CMD_NETWORK_REGISTRATION, ENABLE_REG );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    #define AUTOMATIC_REGISTRATION "0"
    c5gredcap_cmd_set( ctx, C5GREDCAP_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_COPS );
#endif
    return error_flag;
}

static err_t c5gredcap_check_connection ( c5gredcap_t *ctx )
{
    err_t error_flag = C5GREDCAP_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) )
    log_printf( &logger, ">>> Check network registration.\r\n" );
    c5gredcap_cmd_get ( &c5gredcap, C5GREDCAP_CMD_NETWORK_REGISTRATION );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, C5GREDCAP_URC_NETWORK_REGISTERED ) )
    {
        Delay_ms ( 1000 );
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        c5gredcap_cmd_run( &c5gredcap, C5GREDCAP_CMD_SIGNAL_QUALITY_REPORT );
        error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    }
    else
    {
        error_flag = C5GREDCAP_ERROR;
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
#endif
    return error_flag;
}

static err_t c5gredcap_config_example ( c5gredcap_t *ctx )
{
    err_t error_flag = C5GREDCAP_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    log_printf( &logger, ">>> Activate PDP context.\r\n" );
    #define ACTIVATE_PDP_CONTEXT "1,1"
    c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_ACTIVATE_PDP_CONTEXT, ACTIVATE_PDP_CONTEXT );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_QIACT );
    log_printf( &logger, ">>> Show PDP address.\r\n" );
    #define PDP_CID "1"
    c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_SHOW_PDP_ADDRESS, PDP_CID );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    log_printf( &logger, ">>> Select SMS format.\r\n" );
    c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_SELECT_SMS_FORMAT, SMS_MODE );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_CALL )
    log_printf( &logger, ">>> Configure audio codec.\r\n" );
    if ( C5GREDCAP_OK != c5gredcap_config_codec ( &c5gredcap ) )
    {
        log_error( &logger, " Audio codec config." );
        for ( ; ; );
    }
    log_printf( &logger, ">>> Set MIC gain.\r\n" );
    #define MIC_GAIN "14567,14567"
    c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_SET_MIC_GAIN, MIC_GAIN );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Enable URC for all ports.\r\n" );
    #define URC_INDICATION_ALL_PORTS "\"urcport\",\"all\""
    c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_CONFIG_URC_INDICATION, URC_INDICATION_ALL_PORTS );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    log_printf( &logger, ">>> Check GNSS power state.\r\n" );
    #define GNSS_TURNED_OFF "+QGPS: 0"
    c5gredcap_cmd_get( &c5gredcap, C5GREDCAP_CMD_TURN_ON_GNSS );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    if ( strstr ( app_buf, GNSS_TURNED_OFF ) )
    {
        log_printf( &logger, ">>> Turn on GNSS power supply.\r\n" );
        #define GNSS_TURN_ON "1"
        c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_TURN_ON_GNSS, GNSS_TURN_ON );
        error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    }
#endif
    return error_flag;
}

static err_t c5gredcap_example ( c5gredcap_t *ctx )
{
    err_t error_flag = C5GREDCAP_OK;
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
    c5gredcap_cmd_set ( &c5gredcap, C5GREDCAP_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_URC_OPEN_SOCKET, C5GREDCAP_MAX_RSP_TIME_URC );

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
    c5gredcap_cmd_set ( &c5gredcap, C5GREDCAP_CMD_OPEN_SOCKET, cmd_buf );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_URC_OPEN_SOCKET, C5GREDCAP_MAX_RSP_TIME_URC );

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
    c5gredcap_cmd_set ( &c5gredcap, C5GREDCAP_CMD_SEND_DATA, cmd_buf );
    Delay_ms ( 100 );
    c5gredcap_generic_write ( &c5gredcap, MESSAGE_CONTENT, message_len );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_URC_RECEIVED_DATA, C5GREDCAP_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from TCP connection.\r\n" );
    c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_RECEIVE_DATA, cmd_buf );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Write message to UDP connection.\r\n" );
    strcpy( cmd_buf, UDP_SOCKET_NUM );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    c5gredcap_cmd_set ( &c5gredcap, C5GREDCAP_CMD_SEND_DATA, cmd_buf );
    Delay_ms ( 100 );
    c5gredcap_generic_write ( &c5gredcap, MESSAGE_CONTENT, message_len );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_URC_RECEIVED_DATA, C5GREDCAP_MAX_RSP_TIME_URC );
    log_printf( &logger, ">>> Read response from UDP connection.\r\n" );
    c5gredcap_cmd_set( &c5gredcap, C5GREDCAP_CMD_RECEIVE_DATA, cmd_buf );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Close TCP connection.\r\n" );
    c5gredcap_cmd_set ( &c5gredcap, C5GREDCAP_CMD_CLOSE_SOCKET, TCP_SOCKET_NUM );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_QICLOSE );
    
    log_printf( &logger, ">>> Close UDP connection.\r\n" );
    c5gredcap_cmd_set ( &c5gredcap, C5GREDCAP_CMD_CLOSE_SOCKET, UDP_SOCKET_NUM );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_QICLOSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    log_printf( &logger, ">>> Check SMS format.\r\n" );
    c5gredcap_cmd_get( &c5gredcap, C5GREDCAP_CMD_SELECT_SMS_FORMAT );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    if ( strstr( app_buf, C5GREDCAP_URC_SMS_FORMAT_PDU ) )
    {
        // Send SMS in PDU mode
        log_printf( &logger, ">>> Send SMS in PDU mode.\r\n" );
        c5gredcap_send_sms_pdu( &c5gredcap, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_CMGS );
    }
    else if ( strstr( app_buf, C5GREDCAP_URC_SMS_FORMAT_TXT ) )
    {
        // Send SMS in TXT mode
        log_printf( &logger, ">>> Send SMS in TXT mode.\r\n" );
        c5gredcap_send_sms_text ( &c5gredcap, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_CMGS );
    }
    // 30 seconds delay
    for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
    {
        Delay_ms ( 1000 );
    }
#elif ( DEMO_EXAMPLE == EXAMPLE_CALL )
    log_printf( &logger, ">>> Waiting for a ring indication.\r\n" );
    c5gredcap_clear_app_buf ( );
    for ( ; ; )
    {
        if ( ( C5GREDCAP_OK == c5gredcap_process ( ctx ) ) && strstr ( app_buf, C5GREDCAP_URC_RING ) )
        {
            c5gredcap_log_app_buf ( );
            Delay_ms ( 1000 );
            break;
        }
    }
    log_printf( &logger, "\r\n--------------------------------\r\n" );
        
    log_printf( &logger, ">>> List calls.\r\n" );
    c5gredcap_cmd_run ( &c5gredcap, C5GREDCAP_CMD_LIST_CALLS );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Answer an incoming call.\r\n" );
    c5gredcap_cmd_run ( &c5gredcap, C5GREDCAP_CMD_ANSWER_CALL );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Call in progress.\r\n" );
    if ( C5GREDCAP_OK != c5gredcap_read_response( ctx, C5GREDCAP_URC_NO_CARRIER, C5GREDCAP_MAX_RSP_TIME_URC ) )
    {
        log_printf( &logger, ">>> Terminate call.\r\n" );
        c5gredcap_cmd_run ( &c5gredcap, C5GREDCAP_CMD_TERMINATE_CALL );
        error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    }
    log_printf( &logger, ">>> Call ended.\r\n" );

#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    uint8_t element_buf[ 100 ] = { 0 };
    #define GNSS_NMEA_GGA "\"GGA\""
    log_printf( &logger, ">>> Get GNSS NMEA sentence.\r\n" );
    c5gredcap_cmd_set ( &c5gredcap, C5GREDCAP_CMD_ACQUIRE_NMEA_SENTENCES, GNSS_NMEA_GGA );
    error_flag |= c5gredcap_read_response( ctx, C5GREDCAP_RSP_OK, C5GREDCAP_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, ">>> Parse GNSS NMEA sentence.\r\n" );
    if ( C5GREDCAP_OK == c5gredcap_parse_gga( app_buf, C5GREDCAP_GGA_LATITUDE, element_buf ) )
    {
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "Latitude: %.2s degrees, %s minutes\r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            c5gredcap_parse_gga( app_buf, C5GREDCAP_GGA_LONGITUDE, element_buf );
            log_printf( &logger, "Longitude: %.3s degrees, %s minutes\r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            c5gredcap_parse_gga( app_buf, C5GREDCAP_GGA_ALTITUDE, element_buf );
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
