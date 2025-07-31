/*!
 * @file main.c
 * @brief LTE Cat.1 2 Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and 
 * sending SMS, TCP/UDP messages or calling the selected number using standard "AT" commands. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Sets the device configuration for sending SMS, TCP/UDP messages or calling the selected number.
 *
 * ## Application Task
 * Depending on the selected demo example, it sends an SMS message 
 * (in PDU or TXT mode) or a TCP/UDP message or calls the selected number.
 *
 * ## Additional Function
 * - static void ltecat12_clear_app_buf ( void )
 * - static err_t ltecat12_process ( void )
 * - static void ltecat12_error_check( err_t error_flag )
 * - static void ltecat12_log_app_buf ( void )
 * - static err_t ltecat12_rsp_check ( uint8_t *rsp )
 * - static err_t ltecat12_cfg_for_network ( void )
 * - static err_t ltecat12_check_connection ( void )
 * - static err_t ltecat12_cfg_for_example ( void )
 * - static err_t ltecat12_example ( void )
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
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ltecat12.h"
#include "generic_pointer.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define EXAMPLE_CALL                        2               // Example of calling selected phone number
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM APN config
#define SIM_APN                             "internet"      // Set valid SIM APN

// SMS/CALL example parameters
#define SIM_SMSC                            ""              // Set valid SMS Service Center Address - only in SMS PDU mode
#define PHONE_NUMBER                        ""              // Set Phone number to message or call
#define SMS_MODE                            "1"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "LTE Cat.1 2 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTECAT12_CONFIGURE_FOR_NETWORK = 1,
    LTECAT12_WAIT_FOR_CONNECTION,
    LTECAT12_CONFIGURE_FOR_EXAMPLE,
    LTECAT12_EXAMPLE

} ltecat12_example_state_t;

static ltecat12_t ltecat12;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;
static ltecat12_example_state_t example_state;

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application
 * buffer and reset its length and counter.
 */
static void ltecat12_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and
 * appends it to the application buffer.
 * @return @li @c  0 - Some data is read.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat12_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void ltecat12_error_check( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void ltecat12_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat12_rsp_check ( uint8_t *rsp );

/**
 * @brief Configure device for connection to the network.
 * @details Sends commands to configure and enable
 * connection to the specified network.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat12_cfg_for_network ( void );

/**
 * @brief Wait for connection signal.
 * @details Wait for connection signal from CREG URC.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat12_check_connection ( void );

/**
 * @brief Configure device for example.
 * @details Configure device for the specified example.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat12_cfg_for_example ( void );

/**
 * @brief Execute example.
 * @details This function executes SMS, TCP/UDP or CALL example depending on the DEMO_EXAMPLE macro.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat12_example( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat12_cfg_t ltecat12_cfg;  /**< Click config object. */

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
    ltecat12_cfg_setup( &ltecat12_cfg );
    LTECAT12_MAP_MIKROBUS( ltecat12_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat12_init( &ltecat12, &ltecat12_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    ltecat12_process( );
    ltecat12_clear_app_buf( );

    // Restart device
    #define RESTART_DEVICE "1,1"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_CFUN, RESTART_DEVICE );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_SYSSTART );
    ltecat12_error_check( error_flag );
    
    // Check communication
    ltecat12_send_cmd( &ltecat12, LTECAT12_CMD_AT );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    ltecat12_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTECAT12_CONFIGURE_FOR_NETWORK;
}

void application_task ( void )
{
    switch ( example_state )
    {
        case LTECAT12_CONFIGURE_FOR_NETWORK:
        {
            if ( LTECAT12_OK == ltecat12_cfg_for_network( ) )
            {
                example_state = LTECAT12_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTECAT12_WAIT_FOR_CONNECTION:
        {
            if ( LTECAT12_OK == ltecat12_check_connection( ) )
            {
                example_state = LTECAT12_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTECAT12_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTECAT12_OK == ltecat12_cfg_for_example( ) )
            {
                example_state = LTECAT12_EXAMPLE;
            }
            break;
        }
        case LTECAT12_EXAMPLE:
        {
            ltecat12_example( );
            break;
        }
        default:
        {
            log_error( &logger, " Example state." );
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

static void ltecat12_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t ltecat12_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ltecat12_generic_read( &ltecat12, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTECAT12_OK;
    }
    return LTECAT12_ERROR;
}

static err_t ltecat12_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    err_t error_flag = ltecat12_process( );
    if ( ( LTECAT12_OK != error_flag ) && ( LTECAT12_ERROR != error_flag ) )
    {
        return error_flag;
    }
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTECAT12_RSP_ERROR ) ) )
    {
        error_flag = ltecat12_process( );
        if ( ( LTECAT12_OK != error_flag ) && ( LTECAT12_ERROR != error_flag ) )
        {
            return error_flag;
        }
        if ( timeout_cnt++ > timeout )
        {
            ltecat12_clear_app_buf( );
            return LTECAT12_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    if ( strstr( app_buf, rsp ) )
    {
        return LTECAT12_OK;
    }
    else if ( strstr( app_buf, LTECAT12_RSP_ERROR ) )
    {
        return LTECAT12_ERROR_CMD;
    }
    else
    {
        return LTECAT12_ERROR_UNKNOWN;
    }
}

static void ltecat12_error_check( err_t error_flag )
{
    switch ( error_flag )
    {
        case LTECAT12_OK:
        {
            ltecat12_log_app_buf( );
            break;
        }
        case LTECAT12_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case LTECAT12_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case LTECAT12_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case LTECAT12_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    ltecat12_clear_app_buf(  );
    Delay_ms ( 500 );
}

static void ltecat12_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "============================\r\n" );
}

static err_t ltecat12_cfg_for_network( void )
{
    err_t func_error = LTECAT12_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) )
    // Deregister from network
    #define DEREGISTER_FROM_NETWORK "2"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_COPS, DEREGISTER_FROM_NETWORK );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Set SIM APN
    ltecat12_set_sim_apn( &ltecat12, SIM_APN );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );

    // Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );

    // Enable network registartion
    #define ENABLE_REG "2"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_CREG, ENABLE_REG );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Automatic registration
    #define AUTOMATIC_REGISTRATION "0"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_COPS, AUTOMATIC_REGISTRATION );
#endif
    return func_error;
}

static err_t ltecat12_check_connection( void )
{
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) )
    #define CONNECTED "+CREG: 1"
    ltecat12_process( );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms ( 100 );
        ltecat12_process( );
        ltecat12_log_app_buf( );
        log_printf( &logger, "\r\n" );
        ltecat12_clear_app_buf( );
        // Check signal quality
        ltecat12_send_cmd( &ltecat12, LTECAT12_CMD_CESQ );
        error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
        ltecat12_error_check( error_flag );
        return error_flag;
    }
    return LTECAT12_ERROR;
#endif
    return LTECAT12_OK;
}

static err_t ltecat12_cfg_for_example ( void )
{
    err_t func_error = LTECAT12_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    #define ACTIVATE_PDP_CONTEXT "1,1"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SICA, ACTIVATE_PDP_CONTEXT );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    #define REQ_DYNAMIC_IP "1"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_CGPADDR, REQ_DYNAMIC_IP );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_CMGF, SMS_MODE );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_CALL )
    if ( LTECAT12_OK != ltecat12_max9860_cfg( &ltecat12 ) )
    {
        log_error( &logger, " MAX9860 configuration." );
        for ( ; ; );
    }
    #define ENABLE_DAI "\"GPIO/mode/DAI\",\"std\""
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SCFG, ENABLE_DAI );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    #define ENABLE_MCLK "\"GPIO/mode/MCLK\",\"std\""
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SCFG, ENABLE_MCLK );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    #define ENABLE_I2S "3,1,1,1,0,0,1,0,0"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SAIC, ENABLE_I2S );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    #define AUDIO_MODE "6"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SNFS, AUDIO_MODE );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

static err_t ltecat12_example ( void )
{
    err_t func_error = LTECAT12_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t tcp_socket_num[ 2 ] = { '0', 0 };
    uint8_t udp_socket_num[ 2 ] = { '1', 0 };

    // Select service type Socket.
    #define SRVTYPE_SOCKET ",srvtype,\"socket\""
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, SRVTYPE_SOCKET );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );

    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, SRVTYPE_SOCKET );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );

    // Select connection profile.
    #define CONN_PROFILE ",conid,\"1\""
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, CONN_PROFILE );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, CONN_PROFILE );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Choose ASCII alphabet.
    #define ASCII_ALPHABET ",alphabet,1"
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, ASCII_ALPHABET );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, ASCII_ALPHABET );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );

    // Specify the TCP remote IP and port
    #define ADDRESS_TCP ",address,\"socktcp://"
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, ADDRESS_TCP );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, ":" );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, "\"" );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Specify the UDP remote IP and port
    #define ADDRESS_UDP ",address,\"sockudp://"
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, ADDRESS_UDP );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, ":" );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, "\"" );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISS, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Open TCP socket
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISO, tcp_socket_num );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Open UDP socket
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISO, udp_socket_num );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    // Write message to TCP socket and read response
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISW, cmd_buf );
    Delay_ms ( 100 );
    ltecat12_generic_write ( &ltecat12, MESSAGE_CONTENT, message_len );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    Delay_ms ( 1000 );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISR, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );

    // Write message to UDP socket and read response
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISW, cmd_buf );
    Delay_ms ( 100 );
    ltecat12_generic_write ( &ltecat12, MESSAGE_CONTENT, message_len );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    Delay_ms ( 1000 );
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISR, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Close TCP socket
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISC, tcp_socket_num );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // Close UDP socket
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_SISC, udp_socket_num );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    ltecat12_send_cmd_check( &ltecat12, LTECAT12_CMD_CMGF );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        ltecat12_error_check( error_flag );
        // Send SMS in PDU mode
        ltecat12_send_sms_pdu( &ltecat12, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
        func_error |= error_flag;
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        ltecat12_error_check( error_flag );
        // Send SMS in TXT mode
        ltecat12_send_sms_text ( &ltecat12, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
        func_error |= error_flag;
    }
    ltecat12_error_check( error_flag );
    // 30 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_CALL )
    uint8_t cmd_buf[ 100 ] = { 0 };
    
    strcpy( cmd_buf, LTECAT12_CMD_ATD );
    ltecat12_clear_app_buf( );
    strcat( cmd_buf, PHONE_NUMBER );
    strcat( cmd_buf, ";" );
    
    log_printf( &logger, " Calling selected number \r\n" );
    ltecat12_send_cmd( &ltecat12, cmd_buf );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    ltecat12_clear_app_buf( );
    log_printf( &logger, "Dialing \r\n" );
    #define CHECK_DIALING "+CLCC: 1, 0, 2, "      
    error_flag = ltecat12_rsp_check( CHECK_DIALING );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    log_printf( &logger, "Ringing \r\n" );
    #define CHECK_RINGING "+CLCC: 1, 0, 3, "      
    error_flag = ltecat12_rsp_check( CHECK_RINGING );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Hanging up \r\n" );
    ltecat12_send_cmd( &ltecat12, LTECAT12_CMD_CHUP );
    ltecat12_clear_app_buf( );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    func_error |= error_flag;
    ltecat12_error_check( error_flag );
    ltecat12_clear_app_buf( );
    
    // 20 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

// ------------------------------------------------------------------------ END

