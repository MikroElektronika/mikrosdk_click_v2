/*!
 * @file main.c
 * @brief LTE IoT 11 Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and
 * sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, tests the communication by sending "AT" command, and after that restarts the device.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LTEIOT11_CONFIGURE_FOR_NETWORK:
 * Sets configuration to device to be able to connect to the network. (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT11_WAIT_FOR_CONNECTION:
 * Waits for the network registration indicated via CREG URC event and then checks
 * the connection status (used only for SMS or TCP/UDP demo examples).
 *
 *  - LTEIOT11_CONFIGURE_FOR_EXAMPLE:
 * Sets the device configuration for sending SMS or TCP/UDP messages or for retrieving data from GNSS 
 * depending on the selected demo example.
 *
 *  - LTEIOT11_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or 
 * waits for the GPS fix to retrieve location info from GNSS.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void lteiot11_clear_app_buf ( void )
 * - static err_t lteiot11_process ( void )
 * - static void lteiot11_error_check( err_t error_flag )
 * - static void lteiot11_log_app_buf ( void )
 * - static err_t lteiot11_rsp_check ( uint8_t *rsp )
 * - static err_t lteiot11_configure_for_connection( void )
 * - static err_t lteiot11_check_connection( void )
 * - static err_t lteiot11_configure_for_messages( void )
 * - static err_t lteiot11_send_message( void )
 *
 * @note
 * In order for the examples to work (except GNSS example), user needs to set the APN and SMSC (SMS PDU mode only)
 * of entered SIM card as well as the phone number (SMS mode only) to which he wants to send an SMS.
 * Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
 * Example:
    SIM_APN "internet"
    SIM_SMSC "+381610401"
    PHONE_NUMBER_TO_MESSAGE "+381659999999"
 * In order to establish communication with the module, some of the supported MCUs may require the UART RX line
 * to be pulled up additionally either with the external or internal weak pull-up resistor.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lteiot11.h"
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
#define PHONE_NUMBER_TO_MESSAGE             ""              // Set Phone number to message
#define SMS_MODE                            "1"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "LTE IoT 11 Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTEIOT11_CONFIGURE_FOR_NETWORK = 1,
    LTEIOT11_WAIT_FOR_CONNECTION,
    LTEIOT11_CONFIGURE_FOR_EXAMPLE,
    LTEIOT11_EXAMPLE

} lteiot11_example_state_t;

static lteiot11_t lteiot11;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;
static lteiot11_example_state_t example_state;

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application
 * buffer and reset its length and counter.
 */
static void lteiot11_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and
 * appends it to the application buffer.
 * @return @li @c  0 - Some data is read.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot11_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void lteiot11_error_check ( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void lteiot11_log_app_buf ( void );

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
static err_t lteiot11_rsp_check ( uint8_t *rsp );

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
static err_t lteiot11_configure_for_network ( void );

/**
 * @brief Wait for connection signal.
 * @details Wait for connection signal from CREG URC.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot11_check_connection ( void );

/**
 * @brief Configure device for example.
 * @details Configure device for the specified example.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot11_configure_for_example ( void );

/**
 * @brief Execute example.
 * @details This function executes SMS, TCP/UDP or GNSS example depending on the DEMO_EXAMPLE macro.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot11_example ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot11_cfg_t lteiot11_cfg;  /**< Click config object. */

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
    lteiot11_cfg_setup( &lteiot11_cfg );
    LTEIOT11_MAP_MIKROBUS( lteiot11_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot11_init( &lteiot11, &lteiot11_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    lteiot11_process( );
    lteiot11_clear_app_buf( );

    // Check communication
    lteiot11_send_cmd( &lteiot11, LTEIOT11_CMD_AT );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    lteiot11_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_CFUN, RESTART_DEVICE );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_SYSSTART );
    lteiot11_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = LTEIOT11_CONFIGURE_FOR_NETWORK;
}

void application_task ( void )
{
    switch ( example_state )
    {
        case LTEIOT11_CONFIGURE_FOR_NETWORK:
        {
            if ( LTEIOT11_OK == lteiot11_configure_for_network( ) )
            {
                example_state = LTEIOT11_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT11_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT11_OK == lteiot11_check_connection( ) )
            {
                example_state = LTEIOT11_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTEIOT11_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTEIOT11_OK == lteiot11_configure_for_example( ) )
            {
                example_state = LTEIOT11_EXAMPLE;
            }
            break;
        }
        case LTEIOT11_EXAMPLE:
        {
            lteiot11_example( );
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

static void lteiot11_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t lteiot11_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = lteiot11_generic_read( &lteiot11, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTEIOT11_OK;
    }
    return LTEIOT11_ERROR;
}

static err_t lteiot11_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    lteiot11_clear_app_buf( );
    lteiot11_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTEIOT11_RSP_ERROR ) ) )
    {
        lteiot11_process( );
        if ( timeout_cnt++ > timeout )
        {
            lteiot11_clear_app_buf( );
            return LTEIOT11_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    lteiot11_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return LTEIOT11_OK;
    }
    else if ( strstr( app_buf, LTEIOT11_RSP_ERROR ) )
    {
        return LTEIOT11_ERROR_CMD;
    }
    else
    {
        return LTEIOT11_ERROR_UNKNOWN;
    }
}

static void lteiot11_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case LTEIOT11_OK:
        {
            lteiot11_log_app_buf( );
            break;
        }
        case LTEIOT11_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case LTEIOT11_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case LTEIOT11_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case LTEIOT11_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    Delay_ms ( 500 );
}

static void lteiot11_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot11_configure_for_network ( void )
{
    err_t func_error = LTEIOT11_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    // Deregister from network
    #define DEREGISTER_FROM_NETWORK "2"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_COPS, DEREGISTER_FROM_NETWORK );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Set SIM APN
    lteiot11_set_sim_apn( &lteiot11, SIM_APN );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );

    // Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );

    // Enable network registartion
    #define ENABLE_REG "2"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_CREG, ENABLE_REG );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Automatic registration
    #define AUTOMATIC_REGISTRATION "0"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_COPS, AUTOMATIC_REGISTRATION );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
#endif
    return func_error;
}

static err_t lteiot11_check_connection ( void )
{
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    #define CONNECTED "+CREG: 1"
    lteiot11_process( );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms ( 100 );
        lteiot11_process( );
        lteiot11_log_app_buf( );
        log_printf( &logger, "\r\n" );
        lteiot11_clear_app_buf( );
        // Check signal quality
        lteiot11_send_cmd( &lteiot11, LTEIOT11_CMD_CESQ );
        error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
        lteiot11_error_check( error_flag );
        return error_flag;
    }
    return LTEIOT11_ERROR;
#endif
    return LTEIOT11_OK;
}

static err_t lteiot11_configure_for_example ( void )
{
    err_t func_error = LTEIOT11_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    #define ACTIVATE_PDP_CONTEXT "1,1"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SICA, ACTIVATE_PDP_CONTEXT );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    #define REQ_DYNAMIC_IP "1"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_CGPADDR, REQ_DYNAMIC_IP );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_CMGF, SMS_MODE );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    #define GNNS_START_MODE_EN "\"Engine/StartMode\",0"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SGPSC, GNNS_START_MODE_EN );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    #define GNNS_START_GPS "\"Nmea/GPS\",\"on\""
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SGPSC, GNNS_START_GPS );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    #define GNSS_POWER_UP "\"Engine\",3"
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SGPSC, GNSS_POWER_UP );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

static err_t lteiot11_example ( void )
{
    err_t func_error = LTEIOT11_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };
    uint8_t tcp_socket_num[ 2 ] = { '0', 0 };
    uint8_t udp_socket_num[ 2 ] = { '1', 0 };

    // Select service type Socket.
    #define SRVTYPE_SOCKET ",srvtype,\"socket\""
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, SRVTYPE_SOCKET );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );

    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, SRVTYPE_SOCKET );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );

    // Select connection profile.
    #define CONN_PROFILE ",conid,\"1\""
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, CONN_PROFILE );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, CONN_PROFILE );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Choose ASCII alphabet.
    #define ASCII_ALPHABET ",alphabet,1"
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, ASCII_ALPHABET );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, ASCII_ALPHABET );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );

    // Specify the TCP remote IP and port
    #define ADDRESS_TCP ",address,\"socktcp://"
    strcpy( cmd_buf, tcp_socket_num );
    strcat( cmd_buf, ADDRESS_TCP );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, ":" );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, "\"" );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Specify the UDP remote IP and port
    #define ADDRESS_UDP ",address,\"sockudp://"
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, ADDRESS_UDP );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, ":" );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, "\"" );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISS, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Open TCP socket
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISO, tcp_socket_num );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Open UDP socket
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISO, udp_socket_num );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );

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
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISW, cmd_buf );
    Delay_ms ( 100 );
    lteiot11_generic_write ( &lteiot11, MESSAGE_CONTENT, message_len );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    Delay_ms ( 1000 );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISR, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );

    // Write message to UDP socket and read response
    strcpy( cmd_buf, udp_socket_num );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, message_len_buf );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISW, cmd_buf );
    Delay_ms ( 100 );
    lteiot11_generic_write ( &lteiot11, MESSAGE_CONTENT, message_len );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    Delay_ms ( 1000 );
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISR, cmd_buf );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Close TCP socket
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISC, tcp_socket_num );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    
    // Close UDP socket
    lteiot11_send_cmd_with_par( &lteiot11, LTEIOT11_CMD_SISC, udp_socket_num );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    lteiot11_send_cmd_check( &lteiot11, LTEIOT11_CMD_CMGF );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    func_error |= error_flag;
    lteiot11_error_check( error_flag );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        lteiot11_send_sms_pdu( &lteiot11, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
        func_error |= error_flag;
        lteiot11_error_check( error_flag );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        lteiot11_send_sms_text ( &lteiot11, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
        func_error |= error_flag;
        lteiot11_error_check( error_flag );
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
    lteiot11_process ( );
    if ( app_buf_len > ( sizeof ( LTEIOT11_RSP_GGA ) + LTEIOT11_GGA_ELEMENT_SIZE ) ) 
    {
        uint8_t element_buf[ 100 ] = { 0 };
        if ( LTEIOT11_OK == lteiot11_parse_gga( app_buf, LTEIOT11_GGA_LATITUDE, element_buf ) )
        {
            static uint8_t wait_for_fix_cnt = 0;
            if ( strlen( element_buf ) > 0 )
            {
                log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
                lteiot11_parse_gga( app_buf, LTEIOT11_GGA_LONGITUDE, element_buf );
                log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
                memset( element_buf, 0, sizeof( element_buf ) );
                lteiot11_parse_gga( app_buf, LTEIOT11_GGA_ALTITUDE, element_buf );
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
            lteiot11_clear_app_buf(  );
        }
    }
#else
    #error "No demo example selected"
#endif
    return func_error;
}

// ------------------------------------------------------------------------ END
