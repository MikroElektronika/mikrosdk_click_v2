/*!
 * @file main.c
 * @brief 4G LTE GNSS Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, restarts the device, and after that tests the communication by sending "AT" command.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - C4GLTEGNSS_CONFIGURE_FOR_NETWORK:
 * Sets configuration to device to be able to connect to the network (used only for SMS or TCP/UDP demo examples).
 *
 *  - C4GLTEGNSS_WAIT_FOR_CONNECTION:
 * Waits for the network registration indicated via CREG URC event and then checks
 * the connection status (used only for SMS or TCP/UDP demo examples).
 *
 *  - C4GLTEGNSS_CONFIGURE_FOR_EXAMPLE:
 * Sets the device configuration for sending SMS or TCP/UDP messages or for retrieving data from GNSS 
 * depending on the selected demo example.
 *
 *  - C4GLTEGNSS_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or 
 * waits for the GPS fix to retrieve location info from GNSS.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void c4gltegnss_clear_app_buf ( void )
 * - static void c4gltegnss_log_app_buf ( void )
 * - static err_t c4gltegnss_process ( void )
 * - static void c4gltegnss_error_check ( err_t error_flag )
 * - static err_t c4gltegnss_rsp_check ( uint8_t *rsp )
 * - static err_t c4gltegnss_config_for_network ( void )
 * - static err_t c4gltegnss_check_connection ( void )
 * - static err_t c4gltegnss_config_for_example ( void )
 * - static err_t c4gltegnss_example ( void )
 *
 * @note
 * In order for the examples to work (except GNSS example), user needs to set the APN and SMSC (SMS PDU mode only)
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
#include "c4gltegnss.h"
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
#define PHONE_NUMBER_TO_MESSAGE             ""              // Set Phone number to message
#define SMS_MODE                            "1"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "4G LTE GNSS Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    C4GLTEGNSS_CONFIGURE_FOR_NETWORK = 1,
    C4GLTEGNSS_WAIT_FOR_CONNECTION,
    C4GLTEGNSS_CONFIGURE_FOR_EXAMPLE,
    C4GLTEGNSS_EXAMPLE

} c4gltegnss_example_state_t;

static c4gltegnss_t c4gltegnss;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag = C4GLTEGNSS_OK;
static c4gltegnss_example_state_t example_state;

/**
 * @brief 4G LTE GNSS clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void c4gltegnss_clear_app_buf ( void );

/**
 * @brief 4G LTE GNSS log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void c4gltegnss_log_app_buf ( void );

/**
 * @brief 4G LTE GNSS data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c4gltegnss_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void c4gltegnss_error_check ( err_t error_flag );

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
static err_t c4gltegnss_rsp_check ( uint8_t *rsp );

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
static err_t c4gltegnss_config_for_network ( void );

/**
 * @brief Wait for connection signal.
 * @details Wait for connection signal from CREG URC.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t c4gltegnss_check_connection ( void );

/**
 * @brief Configure device for example.
 * @details Configure device for the specified example.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t c4gltegnss_config_for_example ( void );

/**
 * @brief Execute example.
 * @details This function executes SMS, TCP/UDP or GNSS example depending on the DEMO_EXAMPLE macro.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t c4gltegnss_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4gltegnss_cfg_t c4gltegnss_cfg;  /**< Click config object. */

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
    c4gltegnss_cfg_setup( &c4gltegnss_cfg );
    C4GLTEGNSS_MAP_MIKROBUS( c4gltegnss_cfg, MIKROBUS_1 );
    if ( UART_ERROR == c4gltegnss_init( &c4gltegnss, &c4gltegnss_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    // Power cycle device
    c4gltegnss_set_power_state ( &c4gltegnss, C4GLTEGNSS_POWER_STATE_OFF );
    c4gltegnss_set_power_state ( &c4gltegnss, C4GLTEGNSS_POWER_STATE_ON );
    
    // Dummy write to activate AT commands interface
    c4gltegnss_send_cmd( &c4gltegnss, C4GLTEGNSS_CMD_AT );
    c4gltegnss_process( );
    c4gltegnss_clear_app_buf( );
    
    // Check communication
    c4gltegnss_send_cmd( &c4gltegnss, C4GLTEGNSS_CMD_AT );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    c4gltegnss_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = C4GLTEGNSS_CONFIGURE_FOR_NETWORK;
}

void application_task ( void ) 
{
    switch ( example_state )
    {
        case C4GLTEGNSS_CONFIGURE_FOR_NETWORK:
        {
            if ( C4GLTEGNSS_OK == c4gltegnss_config_for_network( ) )
            {
                example_state = C4GLTEGNSS_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case C4GLTEGNSS_WAIT_FOR_CONNECTION:
        {
            if ( C4GLTEGNSS_OK == c4gltegnss_check_connection( ) )
            {
                example_state = C4GLTEGNSS_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case C4GLTEGNSS_CONFIGURE_FOR_EXAMPLE:
        {
            if ( C4GLTEGNSS_OK == c4gltegnss_config_for_example( ) )
            {
                example_state = C4GLTEGNSS_EXAMPLE;
            }
            break;
        }
        case C4GLTEGNSS_EXAMPLE:
        {
            c4gltegnss_example( );
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

static void c4gltegnss_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void c4gltegnss_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t c4gltegnss_process ( void ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = c4gltegnss_generic_read( &c4gltegnss, rx_buf, PROCESS_BUFFER_SIZE );
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
        return C4GLTEGNSS_OK;
    }
    return C4GLTEGNSS_ERROR;
}

static err_t c4gltegnss_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    c4gltegnss_clear_app_buf( );
    c4gltegnss_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, C4GLTEGNSS_RSP_ERROR ) ) )
    {
        c4gltegnss_process( );
        if ( timeout_cnt++ > timeout )
        {
            c4gltegnss_clear_app_buf( );
            return C4GLTEGNSS_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    c4gltegnss_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return C4GLTEGNSS_OK;
    }
    else if ( strstr( app_buf, C4GLTEGNSS_RSP_ERROR ) )
    {
        return C4GLTEGNSS_ERROR_CMD;
    }
    else
    {
        return C4GLTEGNSS_ERROR_UNKNOWN;
    }
}

static void c4gltegnss_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case C4GLTEGNSS_OK:
        {
            c4gltegnss_log_app_buf( );
            break;
        }
        case C4GLTEGNSS_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case C4GLTEGNSS_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case C4GLTEGNSS_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case C4GLTEGNSS_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    Delay_ms ( 500 );
}

static err_t c4gltegnss_config_for_network ( void )
{
    err_t func_error = C4GLTEGNSS_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    // Set SIM APN
    c4gltegnss_set_sim_apn( &c4gltegnss, SIM_APN );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );

    // Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );

    // Enable network registartion
    #define ENABLE_REG "2"
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_CREG, ENABLE_REG );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );
    
    // Automatic registration
    #define AUTOMATIC_REGISTRATION "0"
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_COPS, AUTOMATIC_REGISTRATION );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
#endif
    return func_error;
}

static err_t c4gltegnss_check_connection ( void )
{
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    #define CONNECTED "+CREG: 1"
    c4gltegnss_process( );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms ( 100 );
        c4gltegnss_process( );
        c4gltegnss_log_app_buf( );
        log_printf( &logger, "\r\n" );
        c4gltegnss_clear_app_buf( );
        // Check signal quality
        c4gltegnss_send_cmd( &c4gltegnss, C4GLTEGNSS_CMD_CSQ );
        error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
        c4gltegnss_error_check( error_flag );
        return error_flag;
    }
    return C4GLTEGNSS_ERROR;
#endif
    return C4GLTEGNSS_OK;
}

static err_t c4gltegnss_config_for_example( void )
{
    err_t func_error = C4GLTEGNSS_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    #define ACTIVATE_PDP_CONTEXT "1,1"
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_CGACT, ACTIVATE_PDP_CONTEXT );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_CMGF, SMS_MODE );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    c4gltegnss_send_cmd_check( &c4gltegnss, C4GLTEGNSS_CMD_UGPS );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    #define GPS_POWERED_OFF "+UGPS: 0"
    if ( strstr( app_buf, GPS_POWERED_OFF ) )
    {
        c4gltegnss_error_check( error_flag );
        #define ENABLE_GPS "1,0,1"
        c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_UGPS, ENABLE_GPS );
        error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
        func_error |= error_flag;
        c4gltegnss_error_check( error_flag );
        Delay_ms ( 1000 );
    }
    #define ENABLE_NMEA_GGA "1"
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_UGGGA, ENABLE_NMEA_GGA );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

static err_t c4gltegnss_example( void )
{
    err_t func_error = C4GLTEGNSS_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t urc_buf[ 20 ] = { 0 };
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 30000;
    uint8_t * __generic_ptr socket_num_buf = 0;
    uint8_t tcp_socket_num[ 2 ] = { 0 };
    uint8_t udp_socket_num[ 2 ] = { 0 };

    // Create TCP socket
    #define RSP_USOCR "+USOCR:"
    #define TCP_PROTOCOL "6"
    c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USOCR, TCP_PROTOCOL );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    socket_num_buf = strstr( app_buf, RSP_USOCR ) + strlen ( RSP_USOCR );
    tcp_socket_num[ 0 ] = *socket_num_buf;
    c4gltegnss_error_check( error_flag );

    // Create UDP socket
    #define UDP_PROTOCOL "17"
    c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USOCR, UDP_PROTOCOL );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    socket_num_buf = strstr( app_buf, RSP_USOCR ) + strlen ( RSP_USOCR );
    udp_socket_num[ 0 ] = *socket_num_buf;
    c4gltegnss_error_check( error_flag );

    // Connect TCP socket to remote IP and port
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_USOCO, cmd_buf );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );

    // Connect UDP socket to remote IP and port
    #define ASYNC_CONNECT "1"
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, ASYNC_CONNECT );
    c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USOCO, cmd_buf );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );

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
    c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USOWR, cmd_buf );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );

    // Read response message from TCP socket
    #define URC_READ_SOCKET_DATA_TCP "+UUSORD:"
    strcpy( urc_buf, URC_READ_SOCKET_DATA_TCP );
    strcat( urc_buf, tcp_socket_num );
    for ( ; ; )
    {
        c4gltegnss_process( );
        uint8_t * __generic_ptr start_response_buf = strstr( app_buf, urc_buf );
        if ( start_response_buf )
        {
            Delay_ms ( 100 );
            c4gltegnss_process( );
            uint8_t response_len_buf[ 5 ] = { 0 };
            uint8_t * __generic_ptr start_response_len = strstr( start_response_buf, "," ) + 1;
            memcpy ( response_len_buf, start_response_len, app_buf_len - ( start_response_len - app_buf ) );
            strcpy( cmd_buf, tcp_socket_num );
            strcat( cmd_buf, "," );
            strcat( cmd_buf, response_len_buf );
            c4gltegnss_log_app_buf( );
            c4gltegnss_clear_app_buf( );
            c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USORD, cmd_buf );
            error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
            func_error |= error_flag;
            c4gltegnss_error_check( error_flag );
            break;
        }
        if ( timeout_cnt++ > timeout )
        {
            break;
        }
        Delay_ms ( 1 );
    }
    timeout_cnt = 0;

    // Write message to UDP socket
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, MESSAGE_CONTENT );
    strcat( cmd_buf, "\"" );
    c4gltegnss_send_cmd_with_par( &c4gltegnss, C4GLTEGNSS_CMD_USOWR, cmd_buf );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );

    // Read response message from UDP socket
    #define URC_READ_SOCKET_DATA_UDP "+UUSORF:"
    strcpy( urc_buf, URC_READ_SOCKET_DATA_UDP );
    strcat( urc_buf, udp_socket_num );
    for ( ; ; )
    {
        c4gltegnss_process( );
        uint8_t * __generic_ptr start_response_buf = strstr( app_buf, urc_buf );
        if ( start_response_buf )
        {
            Delay_ms ( 100 );
            c4gltegnss_process( );
            uint8_t response_len_buf[ 5 ] = { 0 };
            uint8_t * __generic_ptr start_response_len = strstr( start_response_buf, "," ) + 1;
            memcpy ( response_len_buf, start_response_len, app_buf_len - ( start_response_len - app_buf ) );
            strcpy( cmd_buf, udp_socket_num );
            strcat( cmd_buf, "," );
            strcat( cmd_buf, response_len_buf );
            c4gltegnss_log_app_buf( );
            c4gltegnss_clear_app_buf( );
            c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USORF, cmd_buf );
            error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
            func_error |= error_flag;
            c4gltegnss_error_check( error_flag );
            break;
        }
        if ( timeout_cnt++ > timeout )
        {
            break;
        }
        Delay_ms ( 1 );
    }
    
    // Close TCP socket
    c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USOCL, tcp_socket_num );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );
    
    // Close UDP socket
    c4gltegnss_send_cmd_with_par ( &c4gltegnss, C4GLTEGNSS_CMD_USOCL, udp_socket_num );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    c4gltegnss_send_cmd_check( &c4gltegnss, C4GLTEGNSS_CMD_CMGF );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    c4gltegnss_error_check( error_flag );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        c4gltegnss_send_sms_pdu( &c4gltegnss, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
        func_error |= error_flag;
        c4gltegnss_error_check( error_flag );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        c4gltegnss_send_sms_text ( &c4gltegnss, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
        func_error |= error_flag;
        c4gltegnss_error_check( error_flag );
    }
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
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    c4gltegnss_send_cmd_check( &c4gltegnss, C4GLTEGNSS_CMD_UGGGA );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    func_error |= error_flag;
    if ( app_buf_len > ( sizeof ( C4GLTEGNSS_RSP_GGA ) + C4GLTEGNSS_GGA_ELEMENT_SIZE ) ) 
    {
        uint8_t element_buf[ 100 ] = { 0 };
        if ( C4GLTEGNSS_OK == c4gltegnss_parse_gga( app_buf, C4GLTEGNSS_GGA_LATITUDE, element_buf ) )
        {
            static uint8_t wait_for_fix_cnt = 0;
            if ( strlen( element_buf ) > 0 )
            {
                log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
                c4gltegnss_parse_gga( app_buf, C4GLTEGNSS_GGA_LONGITUDE, element_buf );
                log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
                memset( element_buf, 0, sizeof( element_buf ) );
                c4gltegnss_parse_gga( app_buf, C4GLTEGNSS_GGA_ALTITUDE, element_buf );
                log_printf( &logger, " Altitude: %s m \r\n", element_buf );
                wait_for_fix_cnt = 0;
            }
            else
            {
                if ( wait_for_fix_cnt % 5 == 0 )
                {
                    log_printf( &logger, " Waiting for the position fix...\r\n\n" );
                    wait_for_fix_cnt = 0;
                }
                wait_for_fix_cnt++;
            }
            c4gltegnss_clear_app_buf(  );
        }
    }
    Delay_ms ( 1000 );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

// ------------------------------------------------------------------------ END
