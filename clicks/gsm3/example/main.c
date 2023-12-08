/*!
 * @file main.c
 * @brief GSM 3 Click Example.
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
 *  - GSM3_CONFIGURE_FOR_NETWORK:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - GSM3_WAIT_FOR_CONNECTION:
 * Waits for the network registration indicated via CREG URC event and then checks
 * the connection status.
 *
 *  - GSM3_CONFIGURE_FOR_EXAMPLE:
 * Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 *
 *  - GSM3_EXAMPLE:
 * Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void gsm3_clear_app_buf ( void )
 * - static err_t gsm3_process ( void )
 * - static void gsm3_error_check( err_t error_flag )
 * - static void gsm3_log_app_buf ( void )
 * - static err_t gsm3_rsp_check ( uint8_t *rsp )
 * - static err_t gsm3_configure_for_connection( void )
 * - static err_t gsm3_check_connection( void )
 * - static err_t gsm3_configure_for_messages( void )
 * - static err_t gsm3_send_message( void )
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
#include "gsm3.h"
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
#define MESSAGE_CONTENT                     "GSM 3 click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    GSM3_CONFIGURE_FOR_NETWORK = 1,
    GSM3_WAIT_FOR_CONNECTION,
    GSM3_CONFIGURE_FOR_EXAMPLE,
    GSM3_EXAMPLE

} gsm3_example_state_t;

static gsm3_t gsm3;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;
static gsm3_example_state_t example_state;

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application
 * buffer and reset its length and counter.
 */
static void gsm3_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and
 * appends it to the application buffer.
 * @return @li @c  0 - Some data is read.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 */
static err_t gsm3_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void gsm3_error_check ( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void gsm3_log_app_buf ( void );

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
static err_t gsm3_rsp_check ( uint8_t *rsp );

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
static err_t gsm3_configure_for_network ( void );

/**
 * @brief Wait for connection signal.
 * @details Wait for connection signal from CREG URC.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t gsm3_check_connection ( void );

/**
 * @brief Configure device for example.
 * @details Configure device for the specified example.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t gsm3_configure_for_example ( void );

/**
 * @brief Execute example.
 * @details This function executes SMS or TCP/UDP example depending on the DEMO_EXAMPLE macro.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t gsm3_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gsm3_cfg_t gsm3_cfg;  /**< Click config object. */

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
    gsm3_cfg_setup( &gsm3_cfg );
    GSM3_MAP_MIKROBUS( gsm3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gsm3_init( &gsm3, &gsm3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    gsm3_process( );
    gsm3_clear_app_buf( );

    // Check communication
    gsm3_send_cmd( &gsm3, GSM3_CMD_AT );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    gsm3_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CFUN, RESTART_DEVICE );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    gsm3_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = GSM3_CONFIGURE_FOR_NETWORK;
}

void application_task ( void )
{
    switch ( example_state )
    {
        case GSM3_CONFIGURE_FOR_NETWORK:
        {
            if ( GSM3_OK == gsm3_configure_for_network( ) )
            {
                example_state = GSM3_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case GSM3_WAIT_FOR_CONNECTION:
        {
            if ( GSM3_OK == gsm3_check_connection( ) )
            {
                example_state = GSM3_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case GSM3_CONFIGURE_FOR_EXAMPLE:
        {
            if ( GSM3_OK == gsm3_configure_for_example( ) )
            {
                example_state = GSM3_EXAMPLE;
            }
            break;
        }
        case GSM3_EXAMPLE:
        {
            gsm3_example( );
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
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void gsm3_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t gsm3_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = gsm3_generic_read( &gsm3, rx_buf, PROCESS_BUFFER_SIZE );
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
        return GSM3_OK;
    }
    return GSM3_ERROR;
}

static err_t gsm3_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    gsm3_clear_app_buf( );
    gsm3_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, GSM3_RSP_ERROR ) ) )
    {
        gsm3_process( );
        if ( timeout_cnt++ > timeout )
        {
            gsm3_clear_app_buf( );
            return GSM3_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 100 );
    gsm3_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return GSM3_OK;
    }
    else if ( strstr( app_buf, GSM3_RSP_ERROR ) )
    {
        return GSM3_ERROR_CMD;
    }
    else
    {
        return GSM3_ERROR_UNKNOWN;
    }
}

static void gsm3_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case GSM3_OK:
        {
            gsm3_log_app_buf( );
            break;
        }
        case GSM3_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case GSM3_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case GSM3_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case GSM3_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    Delay_ms( 500 );
}

static void gsm3_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t gsm3_configure_for_network ( void )
{
    err_t func_error = GSM3_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    Delay_ms ( 5000 );
    // Deregister from network
    #define DEREGISTER_FROM_NETWORK "2"
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_COPS, DEREGISTER_FROM_NETWORK );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    
    // Set SIM APN
    gsm3_set_sim_apn( &gsm3, SIM_APN );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );

    // Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );

    // Enable network registartion
    #define ENABLE_REG "2"
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CREG, ENABLE_REG );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    
    // Automatic registration
    #define AUTOMATIC_REGISTRATION "0"
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_COPS, AUTOMATIC_REGISTRATION );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
#endif
    return func_error;
}

static err_t gsm3_check_connection ( void )
{
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) )
    #define CONNECTED "+CREG: 2,1"
    gsm3_send_cmd_check ( &gsm3, GSM3_CMD_CREG );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    gsm3_error_check( error_flag );
    if ( strstr( app_buf, CONNECTED ) )
    {
        Delay_ms( 100 );
        // Check signal quality
        gsm3_send_cmd( &gsm3, GSM3_CMD_CSQ );
        error_flag = gsm3_rsp_check( GSM3_RSP_OK );
        gsm3_error_check( error_flag );
        #define NO_SIGNAL "99,99"
        if ( !strstr( app_buf, NO_SIGNAL ) )
        {
            Delay_ms ( 1000 );
            return error_flag;
        }
    }
    Delay_ms ( 1000 );
    return GSM3_ERROR;
#endif
    return GSM3_OK;
}

static err_t gsm3_configure_for_example ( void )
{
    err_t func_error = GSM3_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    #define ENABLE_RESPONSE_HEADER "1"
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CIPHEAD, ENABLE_RESPONSE_HEADER );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CMGF, SMS_MODE );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
#else
    #error "No demo example selected"
#endif
    return func_error;
}

static err_t gsm3_example ( void )
{
    err_t func_error = GSM3_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t cmd_buf[ 100 ] = { 0 };

    // Open TCP socket.
    #define RESPONSE_CONNECT "CONNECT OK"
    #define TCP_SERVICE_TYPE "\"TCP\","
    strcpy( cmd_buf, TCP_SERVICE_TYPE );
    strcat( cmd_buf, "\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"" );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_PORT );
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CIPSTART, cmd_buf );
    error_flag = gsm3_rsp_check( RESPONSE_CONNECT );
    func_error |= error_flag;
    gsm3_error_check( error_flag );

    // Get message length
    uint8_t message_len_buf[ 10 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );

    // Write message to TCP socket
    uint8_t ctrl_z = 0x1A;
    strcpy( cmd_buf, message_len_buf );
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CIPSEND, cmd_buf );
    error_flag = gsm3_rsp_check( ">" );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    gsm3_generic_write ( &gsm3, MESSAGE_CONTENT, message_len );
    gsm3_generic_write ( &gsm3, &ctrl_z, 1 );
    
    // Read response
    #define RESPONSE_URC "+IPD"
    error_flag = gsm3_rsp_check( RESPONSE_URC );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    log_printf( &logger, "\r\n" );
    
    // Close TCP socket
    gsm3_send_cmd( &gsm3, GSM3_CMD_CIPCLOSE );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    
    // Open UDP socket.
    #define UDP_SERVICE_TYPE "\"UDP\","
    strcpy( cmd_buf, UDP_SERVICE_TYPE );
    strcat( cmd_buf, "\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"" );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_PORT );
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CIPSTART, cmd_buf );
    error_flag = gsm3_rsp_check( RESPONSE_CONNECT );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    
    // Write message to UDP socket
    strcpy( cmd_buf, message_len_buf );
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CIPSEND, cmd_buf );
    error_flag = gsm3_rsp_check( ">" );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    gsm3_generic_write ( &gsm3, MESSAGE_CONTENT, message_len );
    gsm3_generic_write ( &gsm3, &ctrl_z, 1 );
    
    // Read response
    error_flag = gsm3_rsp_check( RESPONSE_URC );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    log_printf( &logger, "\r\n" );
    
    // Close UDP socket
    gsm3_send_cmd( &gsm3, GSM3_CMD_CIPCLOSE );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    Delay_ms( 5000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    // Check SMS mode
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    gsm3_send_cmd_check( &gsm3, GSM3_CMD_CMGF );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    func_error |= error_flag;
    gsm3_error_check( error_flag );
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        // Send SMS in PDU mode
        gsm3_send_sms_pdu( &gsm3, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = gsm3_rsp_check( GSM3_RSP_OK );
        func_error |= error_flag;
        gsm3_error_check( error_flag );
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        // Send SMS in TXT mode
        gsm3_send_sms_text ( &gsm3, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = gsm3_rsp_check( GSM3_RSP_OK );
        func_error |= error_flag;
        gsm3_error_check( error_flag );
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
