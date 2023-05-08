/*!
 * @file main.c
 * @brief 3G SARA Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending SMS or TCP/UDP messages using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, tests the communication by sending "AT" command, and after that restarts the device.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - C3GSARA_CONFIGURE_FOR_NETWORK:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - C3GSARA_WAIT_FOR_CONNECTION:
 * Waits for the network registration indicated via CREG URC event and then checks
 * the connection status.
 *
 *  - C3GSARA_CONFIGURE_FOR_EXAMPLE:
 * Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 *
 *  - C3GSARA_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void c3gsara_clear_app_buf ( void )
 * - static err_t c3gsara_process ( void )
 * - static void c3gsara_error_check( err_t error_flag )
 * - static void c3gsara_log_app_buf ( void )
 * - static err_t c3gsara_rsp_check ( uint8_t *rsp )
 * - static err_t c3gsara_configure_for_connection( void )
 * - static err_t c3gsara_check_connection( void )
 * - static err_t c3gsara_configure_for_messages( void )
 * - static err_t c3gsara_send_message( void )
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
#include "c3gsara.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM APN config
#define SIM_APN                             ""              // Set valid SIM APN

// SMS example parameters
#define SIM_SMSC                            ""              // Set valid SMS Service Center Address - only in SMS PDU mode
#define PHONE_NUMBER_TO_MESSAGE             ""              // Set Phone number to message
#define SMS_MODE                            "1"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "3G SARA click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    C3GSARA_CONFIGURE_FOR_NETWORK = 1,
    C3GSARA_WAIT_FOR_CONNECTION,
    C3GSARA_CONFIGURE_FOR_EXAMPLE,
    C3GSARA_EXAMPLE

} c3gsara_example_state_t;

static c3gsara_t c3gsara;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;
static c3gsara_example_state_t example_state;

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application
 * buffer and reset its length and counter.
 */
static void c3gsara_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and
 * appends it to the application buffer.
 * @return @li @c  0 - Some data is read.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 */
static err_t c3gsara_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void c3gsara_error_check ( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void c3gsara_log_app_buf ( void );

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
static err_t c3gsara_rsp_check ( uint8_t *rsp );

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
static err_t c3gsara_configure_for_network ( void );

/**
 * @brief Wait for connection signal.
 * @details Wait for connection signal from CREG URC.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t c3gsara_check_connection ( void );

/**
 * @brief Configure device for example.
 * @details Configure device for the specified example.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t c3gsara_configure_for_example ( void );

/**
 * @brief Execute example.
 * @details This function executes SMS or TCP/UDP example depending on the DEMO_EXAMPLE macro.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t c3gsara_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3gsara_cfg_t c3gsara_cfg;  /**< Click config object. */

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
    c3gsara_cfg_setup( &c3gsara_cfg );
    C3GSARA_MAP_MIKROBUS( c3gsara_cfg, MIKROBUS_1 );
    if ( UART_ERROR == c3gsara_init( &c3gsara, &c3gsara_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    c3gsara_set_power_state ( &c3gsara, C3GSARA_POWER_STATE_ON );
    
    c3gsara_process( );
    c3gsara_clear_app_buf( );

    // Check communication
    c3gsara_send_cmd( &c3gsara, C3GSARA_CMD_AT );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    c3gsara_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_CFUN, RESTART_DEVICE );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    c3gsara_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = C3GSARA_CONFIGURE_FOR_NETWORK;
}

void application_task ( void )
{
    switch ( example_state )
    {
        case C3GSARA_CONFIGURE_FOR_NETWORK:
        {
            if ( C3GSARA_OK == c3gsara_configure_for_network( ) )
            {
                example_state = C3GSARA_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case C3GSARA_WAIT_FOR_CONNECTION:
        {
            if ( C3GSARA_OK == c3gsara_check_connection( ) )
            {
                example_state = C3GSARA_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case C3GSARA_CONFIGURE_FOR_EXAMPLE:
        {
            if ( C3GSARA_OK == c3gsara_configure_for_example( ) )
            {
                example_state = C3GSARA_EXAMPLE;
            }
            break;
        }
        case C3GSARA_EXAMPLE:
        {
            c3gsara_example( );
            break;
        }
        default:
        {
            log_error( &logger, " Example state." );
            break;
        }
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static void c3gsara_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t c3gsara_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = c3gsara_generic_read( &c3gsara, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = APP_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - APP_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ APP_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < APP_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return C3GSARA_OK;
    }
    return C3GSARA_ERROR;
}

static err_t c3gsara_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    c3gsara_clear_app_buf( );
    c3gsara_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, C3GSARA_RSP_ERROR ) ) )
    {
        c3gsara_process( );
        if ( timeout_cnt++ > timeout )
        {
            c3gsara_clear_app_buf( );
            return C3GSARA_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 100 );
    c3gsara_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return C3GSARA_OK;
    }
    else if ( strstr( app_buf, C3GSARA_RSP_ERROR ) )
    {
        return C3GSARA_ERROR_CMD;
    }
    else
    {
        return C3GSARA_ERROR_UNKNOWN;
    }
}

static void c3gsara_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case C3GSARA_OK:
        {
            c3gsara_log_app_buf( );
            break;
        }
        case C3GSARA_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case C3GSARA_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case C3GSARA_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case C3GSARA_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    Delay_ms( 500 );
}

static void c3gsara_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t c3gsara_configure_for_network ( void )
{
    err_t func_error = C3GSARA_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    Delay_ms ( 5000 );
    // Deregister from network
    #define DEREGISTER_FROM_NETWORK "2"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_COPS, DEREGISTER_FROM_NETWORK );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
    
    // Set SIM APN
    c3gsara_set_sim_apn( &c3gsara, SIM_APN );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );

    // Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );

    // Enable network registartion
    #define ENABLE_REG "2"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_CREG, ENABLE_REG );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
    
    // Automatic registration
    #define AUTOMATIC_REGISTRATION "0"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_COPS, AUTOMATIC_REGISTRATION );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
#endif
    return func_error;
}

static err_t c3gsara_check_connection ( void )
{
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    #define CONNECTED "+CREG: 2,1"
    c3gsara_send_cmd_check ( &c3gsara, C3GSARA_CMD_CREG );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    c3gsara_error_check( error_flag );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms( 100 );
        c3gsara_process( );
        c3gsara_log_app_buf( );
        log_printf( &logger, "\r\n" );
        c3gsara_clear_app_buf( );
        // Check signal quality
        c3gsara_send_cmd( &c3gsara, C3GSARA_CMD_CSQ );
        error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
        c3gsara_error_check( error_flag );
        return error_flag;
    }
    Delay_ms ( 1000 );
    return C3GSARA_ERROR;
#endif
    return C3GSARA_OK;
}

static err_t c3gsara_configure_for_example ( void )
{
    err_t func_error = C3GSARA_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    #define ACTIVATE_PDP_CONTEXT "1,1"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_CGACT, ACTIVATE_PDP_CONTEXT );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
    #define ACTIVATE_PDP_PROFILE "1,3"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_UPSDA, ACTIVATE_PDP_PROFILE );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_CMGF, SMS_MODE );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

static err_t c3gsara_example ( void )
{
    err_t func_error = C3GSARA_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t urc_buf[ 20 ] = { 0 };
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 30000;
    uint8_t * __generic_ptr socket_num_buf = 0;
    uint8_t tcp_socket_num[ 2 ] = { 0 };
    uint8_t udp_socket_num[ 2 ] = { 0 };

    // Create TCP socket
    #define RSP_USOCR "+USOCR: "
    #define TCP_PROTOCOL "6"
    c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USOCR, TCP_PROTOCOL );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    socket_num_buf = strstr( app_buf, RSP_USOCR ) + strlen ( RSP_USOCR );
    tcp_socket_num[ 0 ] = *socket_num_buf;
    c3gsara_error_check( error_flag );

    // Create UDP socket
    #define UDP_PROTOCOL "17"
    c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USOCR, UDP_PROTOCOL );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    socket_num_buf = strstr( app_buf, RSP_USOCR ) + strlen ( RSP_USOCR );
    udp_socket_num[ 0 ] = *socket_num_buf;
    c3gsara_error_check( error_flag );

    // Connect TCP socket to remote IP and port
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_USOCO, cmd_buf );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );

    // Connect UDP socket to remote IP and port
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USOCO, cmd_buf );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );

    // Get message length
    uint8_t message_len_buf[ 5 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    // Write message to TCP socket
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, MESSAGE_CONTENT );
    strcat( cmd_buf, "\"" );
    c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USOWR, cmd_buf );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );

    // Read response message from TCP socket
    #define URC_READ_SOCKET_DATA_TCP "+UUSORD: "
    strcpy( urc_buf, URC_READ_SOCKET_DATA_TCP );
    strcat( urc_buf, tcp_socket_num );
    for ( ; ; )
    {
        c3gsara_process( );
        uint8_t * __generic_ptr start_response_buf = strstr( app_buf, urc_buf );
        if ( start_response_buf )
        {
            Delay_ms( 100 );
            c3gsara_process( );
            uint8_t response_len_buf[ 5 ] = { 0 };
            uint8_t * __generic_ptr start_response_len = strstr( start_response_buf, "," ) + 1;
            memcpy ( response_len_buf, start_response_len, app_buf_len - ( start_response_len - app_buf ) );
            strcpy( cmd_buf, tcp_socket_num );
            strcat( cmd_buf, "," );
            strcat( cmd_buf, response_len_buf );
            c3gsara_log_app_buf( );
            c3gsara_clear_app_buf( );
            c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USORD, cmd_buf );
            error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
            func_error |= error_flag;
            c3gsara_error_check( error_flag );
            break;
        }
        if ( timeout_cnt++ > timeout )
        {
            break;
        }
        Delay_ms( 1 );
    }
    timeout_cnt = 0;

    // Write message to UDP socket
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, MESSAGE_CONTENT );
    strcat( cmd_buf, "\"" );
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_USOWR, cmd_buf );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );

    // Read response message from UDP socket
    #define URC_READ_SOCKET_DATA_UDP "+UUSORD: "
    strcpy( urc_buf, URC_READ_SOCKET_DATA_UDP );
    strcat( urc_buf, udp_socket_num );
    for ( ; ; )
    {
        c3gsara_process( );
        uint8_t * __generic_ptr start_response_buf = strstr( app_buf, urc_buf );
        if ( start_response_buf )
        {
            Delay_ms( 100 );
            c3gsara_process( );
            uint8_t response_len_buf[ 5 ] = { 0 };
            uint8_t * __generic_ptr start_response_len = strstr( start_response_buf, "," ) + 1;
            memcpy ( response_len_buf, start_response_len, app_buf_len - ( start_response_len - app_buf ) );
            strcpy( cmd_buf, udp_socket_num );
            strcat( cmd_buf, "," );
            strcat( cmd_buf, response_len_buf );
            c3gsara_log_app_buf( );
            c3gsara_clear_app_buf( );
            c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USORF, cmd_buf );
            error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
            func_error |= error_flag;
            c3gsara_error_check( error_flag );
            break;
        }
        if ( timeout_cnt++ > timeout )
        {
            break;
        }
        Delay_ms( 1 );
    }
    
    // Close TCP socket
    c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USOCL, tcp_socket_num );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
    
    // Close UDP socket
    c3gsara_send_cmd_with_par ( &c3gsara, C3GSARA_CMD_USOCL, udp_socket_num );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
    Delay_ms( 5000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    c3gsara_send_cmd_check( &c3gsara, C3GSARA_CMD_CMGF );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    func_error |= error_flag;
    c3gsara_error_check( error_flag );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        c3gsara_send_sms_pdu( &c3gsara, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
        func_error |= error_flag;
        c3gsara_error_check( error_flag );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        c3gsara_send_sms_text ( &c3gsara, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
        func_error |= error_flag;
        c3gsara_error_check( error_flag );
    }
    Delay_ms( 10000 );
    Delay_ms( 10000 );
    Delay_ms( 10000 );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

// ------------------------------------------------------------------------ END
