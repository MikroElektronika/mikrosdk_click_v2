/*!
 * @file main.c
 * @brief LTE Cat.1 3 NAX Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and 
 * sending SMS, TCP/UDP messages, calling the selected number, or getting GNSS location
 * using standard "AT" commands. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Sets the device configuration for sending SMS, TCP/UDP messages, calling the selected number
 * or GNSS location.
 *
 * ## Application Task
 * Depending on the selected demo example, it sends an SMS message 
 * (in PDU or TXT mode) or a TCP/UDP message, calls the selected number or
 * gets GNSS location.
 *
 * ## Additional Function
 * - static void ltecat13nax_clear_app_buf ( void )
 * - static void ltecat13nax_log_app_buf ( void )
 * - static err_t ltecat13nax_process ( ltecat13nax_t *ctx )
 * - static void ltecat13nax_error_check( err_t error_flag )
 * - static void ltecat13nax_log_app_buf ( void )
 * - static err_t ltecat13nax_rsp_check ( uint8_t *rsp )
 * - static err_t ltecat13nax_cfg_for_network ( void )
 * - static err_t ltecat13nax_check_connection ( void )
 * - static err_t ltecat13nax_cfg_for_example ( void )
 * - static err_t ltecat13nax_example( void )
 * - static void gnss_parser_application ( char *rsp )
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
#include "ltecat13nax.h"
#include "generic_pointer.h"
#include "conversions.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define EXAMPLE_CALL                        2               // Example of calling selected phone number
#define EXAMPLE_GNSS                        3               // Example of getting GNSS location
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM APN config
#define SIM_APN                             "internet"      // Set valid SIM APN

// SMS/CALL example parameters
#define SIM_SMSC                            ""              // Set valid SMS Service Center Address - only in SMS PDU mode
#define PHONE_NUMBER                        ""              // Set Phone number to message or call
#define SMS_MODE                            "0"             // SMS mode: "0" - PDU, "1" - TXT

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// Message content
#define MESSAGE_CONTENT                     "LTE Cat.1 3 NAX Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE                     500
#define PROCESS_BUFFER_SIZE                 200

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LTECAT13NAX_CONFIGURE_FOR_NETWORK = 1,
    LTECAT13NAX_WAIT_FOR_CONNECTION,
    LTECAT13NAX_CONFIGURE_FOR_EXAMPLE,
    LTECAT13NAX_EXAMPLE

} ltecat13nax_example_state_t;

static ltecat13nax_t ltecat13nax;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static uint8_t gnss_info_message[ 200 ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;
static ltecat13nax_example_state_t example_state;

/**
 * @brief LTE Cat.1 3 NAX clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ltecat13nax_clear_app_buf ( void );

/**
 * @brief LTE Cat.1 3 NAX log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void ltecat13nax_log_app_buf ( void );

/**
 * @brief LTE Cat.1 3 NAX data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ltecat13nax_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ltecat13nax_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void ltecat13nax_error_check( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void ltecat13nax_log_app_buf ( void );

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
static err_t ltecat13nax_rsp_check ( uint8_t *rsp );

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
static err_t ltecat13nax_cfg_for_network ( void );

/**
 * @brief Wait for connection signal.
 * @details Wait for connection signal from CREG URC.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat13nax_check_connection ( void );

/**
 * @brief Configure device for example.
 * @details Configure device for the specified example.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat13nax_cfg_for_example ( void );

/**
 * @brief Execute example.
 * @details This function executes SMS, TCP/UDP or CALL example depending on the DEMO_EXAMPLE macro.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t ltecat13nax_example( void );

/**
 * @brief GNSS parser application.
 * @details This function logs GNSS data on the USB UART and stores data in gnss_info_message buffer.
 * @param rsp Response buffer.
 * @note None.
 */
static void gnss_parser_application ( char *rsp ) ;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat13nax_cfg_t ltecat13nax_cfg;  /**< Click config object. */

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
    ltecat13nax_cfg_setup( &ltecat13nax_cfg );
    LTECAT13NAX_MAP_MIKROBUS( ltecat13nax_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat13nax_init( &ltecat13nax, &ltecat13nax_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ltecat13nax_process( );
    ltecat13nax_clear_app_buf( );
    Delay_ms ( 1000 );

    if ( 0 == ltecat13nax_get_ri_pin( &ltecat13nax ) )
    {
        ltecat13nax_start_up( &ltecat13nax );
        error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_RDY );
        ltecat13nax_error_check( error_flag );
    }

    // Restart device
    #define MIN_FUN_DEVICE "0"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CFUN, MIN_FUN_DEVICE );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    ltecat13nax_error_check( error_flag );

    #define FULL_FUN_DEVICE "1"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CFUN, FULL_FUN_DEVICE );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    ltecat13nax_error_check( error_flag );
    
    // Check communication
    ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_AT );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    ltecat13nax_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTECAT13NAX_CONFIGURE_FOR_NETWORK;
}

void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTECAT13NAX_CONFIGURE_FOR_NETWORK:
        {
            if ( LTECAT13NAX_OK == ltecat13nax_cfg_for_network( ) )
            {
                example_state = LTECAT13NAX_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTECAT13NAX_WAIT_FOR_CONNECTION:
        {
            if ( LTECAT13NAX_OK == ltecat13nax_check_connection( ) )
            {
                example_state = LTECAT13NAX_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTECAT13NAX_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTECAT13NAX_OK == ltecat13nax_cfg_for_example( ) )
            {
                example_state = LTECAT13NAX_EXAMPLE;
            }
            break;
        }
        case LTECAT13NAX_EXAMPLE:
        {
            ltecat13nax_example( );
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

static void ltecat13nax_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ltecat13nax_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "============================\r\n" );
}

static err_t ltecat13nax_process ( void ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ltecat13nax_generic_read( &ltecat13nax, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LTECAT13NAX_OK;
    }
    return LTECAT13NAX_ERROR;
}

static err_t ltecat13nax_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 10000;
    err_t error_flag = ltecat13nax_process( );
    if ( ( LTECAT13NAX_OK != error_flag ) && ( LTECAT13NAX_ERROR != error_flag ) )
    {
        return error_flag;
    }
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LTECAT13NAX_RSP_ERROR ) ) )
    {
        error_flag = ltecat13nax_process( );
        if ( ( LTECAT13NAX_OK != error_flag ) && ( LTECAT13NAX_ERROR != error_flag ) )
        {
            return error_flag;
        }
        if ( timeout_cnt++ > timeout )
        {
            ltecat13nax_clear_app_buf( );
            return LTECAT13NAX_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    if ( strstr( app_buf, rsp ) )
    {
        return LTECAT13NAX_OK;
    }
    else if ( strstr( app_buf, LTECAT13NAX_RSP_ERROR ) )
    {
        return LTECAT13NAX_ERROR_CMD;
    }
    else
    {
        return LTECAT13NAX_ERROR_UNKNOWN;
    }
}

static void ltecat13nax_error_check( err_t error_flag )
{
    switch ( error_flag )
    {
        case LTECAT13NAX_OK:
        {
            ltecat13nax_log_app_buf( );
            break;
        }
        case LTECAT13NAX_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case LTECAT13NAX_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case LTECAT13NAX_ERROR_CMD:
        {
            ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_QIGETERROR );
            ltecat13nax_log_app_buf( );
            break;
        }
        case LTECAT13NAX_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    ltecat13nax_clear_app_buf(  );
    Delay_ms ( 500 );
}

static err_t ltecat13nax_cfg_for_network( void )
{
    err_t func_error = LTECAT13NAX_OK;
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) || ( DEMO_EXAMPLE == EXAMPLE_GNSS ) )
    // Deregister from network
    #define DEREGISTER_FROM_NETWORK "2"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_COPS, DEREGISTER_FROM_NETWORK );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );
    
    // Set SIM APN
    ltecat13nax_set_sim_apn( &ltecat13nax, SIM_APN );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Enable network registartion
    #define ENABLE_REG "2"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CREG, ENABLE_REG );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );
    
    // Automatic registration
    #define AUTOMATIC_REGISTRATION "0"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_COPS, AUTOMATIC_REGISTRATION );

#endif

    return func_error;
}

static err_t ltecat13nax_check_connection( void )
{
#if ( ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP ) || ( DEMO_EXAMPLE == EXAMPLE_SMS ) || ( DEMO_EXAMPLE == EXAMPLE_CALL ) )
    #define CONNECTED_HOME      "+CREG: 2,1"
    #define CONNECTED_ROAMING   "+CREG: 2,5"
    ltecat13nax_send_cmd_check( &ltecat13nax, LTECAT13NAX_CMD_CREG );
    ltecat13nax_process( );
    if ( strstr( app_buf, CONNECTED_HOME ) || strstr( app_buf, CONNECTED_ROAMING ) )
    {
        Delay_ms ( 100 );
        ltecat13nax_process( );
        ltecat13nax_log_app_buf( );
        log_printf( &logger, "\r\n" );
        ltecat13nax_clear_app_buf( );
        // Check signal quality
        ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_CSQ );
        error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
        ltecat13nax_error_check( error_flag );
        return error_flag;
    }
    return LTECAT13NAX_ERROR;
    Delay_ms ( 500 );
#endif
    return LTECAT13NAX_OK;
}

static err_t ltecat13nax_cfg_for_example ( void )
{
    err_t func_error = LTECAT13NAX_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    #define ACTIVATE_CONTEXT "1"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QIACT, ACTIVATE_CONTEXT );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QICSGP, ACTIVATE_CONTEXT );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CMGF, SMS_MODE );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    #define DEFAULT_ALPHABET    "\"GSM\""
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CSCS, DEFAULT_ALPHABET );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );
#elif ( DEMO_EXAMPLE == EXAMPLE_CALL )
    if ( LTECAT13NAX_OK != ltecat13nax_max9860_cfg( &ltecat13nax ) )
    {
        log_error( &logger, " MAX9860 configuration." );
        for ( ; ; );
    }
    
#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    #define TURN_ON_GPS     "1"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QGPS, TURN_ON_GPS );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

#else
    #error "No demo example selected"
#endif
    return func_error;
}

static err_t ltecat13nax_example ( void )
{
    err_t func_error = LTECAT13NAX_OK;
#if ( DEMO_EXAMPLE == EXAMPLE_TCP_UDP )
    uint8_t txt_end[ ] = "\032";
    uint8_t cmd_buf[ 100 ] = { 0 };
    
    #define CONTEXT_ID      "1"
    #define CONNECT_ID_TCP  "1"
    #define SEVICE_TYPE_TCP "\"TCP\""
    #define LOCAL_PORT      "0"
    #define ACCESS_MODE     "0"
    #define MAX_READ_SIZE   "1500"

    // Open TCP socket
    strcpy( cmd_buf, CONTEXT_ID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, CONNECT_ID_TCP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, SEVICE_TYPE_TCP );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, LOCAL_PORT );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, ACCESS_MODE );
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QIOPEN, cmd_buf );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Send data to TCP socket
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QISEND, CONNECT_ID_TCP );
    strcpy( cmd_buf, MESSAGE_CONTENT );
    strcat( cmd_buf, txt_end );
    ltecat13nax_rsp_check( ">" );
    ltecat13nax_send_cmd( &ltecat13nax, cmd_buf );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_SEND_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Read TCP socket data
    strcpy( cmd_buf, CONNECT_ID_TCP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, MAX_READ_SIZE );
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QIRD, cmd_buf );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Close TCP socket
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QICLOSE, CONNECT_ID_TCP );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    #define CONNECT_ID_UDP  "2"
    #define SEVICE_TYPE_UDP "\"UDP\""

    // Open UDP socket
    strcpy( cmd_buf, CONTEXT_ID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, CONNECT_ID_UDP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, SEVICE_TYPE_UDP );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "\"," );
    strcat( cmd_buf, REMOTE_PORT );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, LOCAL_PORT );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, ACCESS_MODE );
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QIOPEN, cmd_buf );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Send data to UDP socket
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QISEND, CONNECT_ID_UDP );
    strcpy( cmd_buf, MESSAGE_CONTENT );
    strcat( cmd_buf, txt_end );
    ltecat13nax_rsp_check( ">" );
    ltecat13nax_send_cmd( &ltecat13nax, cmd_buf );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_SEND_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Read UDP socket data
    strcpy( cmd_buf, CONNECT_ID_UDP );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, MAX_READ_SIZE );
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QIRD, cmd_buf );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );

    // Close UDP socket
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QICLOSE, CONNECT_ID_UDP );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_EXAMPLE == EXAMPLE_SMS )

    // Check SMS mode
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    ltecat13nax_send_cmd_check( &ltecat13nax, LTECAT13NAX_CMD_CMGF );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    if ( strstr( app_buf, CMGF_PDU ) )
    {
        ltecat13nax_error_check( error_flag );
        // Send SMS in PDU mode
        ltecat13nax_send_sms_pdu( &ltecat13nax, SIM_SMSC, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
        func_error |= error_flag;
    }
    else if ( strstr( app_buf, CMGF_TXT ) )
    {
        ltecat13nax_error_check( error_flag );
        // Send SMS in TXT mode
        ltecat13nax_send_sms_text ( &ltecat13nax, PHONE_NUMBER, MESSAGE_CONTENT );
        error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
        func_error |= error_flag;
    }
    ltecat13nax_error_check( error_flag );
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
    
    strcpy( cmd_buf, LTECAT13NAX_CMD_ATD );
    ltecat13nax_clear_app_buf( );
    strcat( cmd_buf, PHONE_NUMBER );
    strcat( cmd_buf, ";" );
    
    log_printf( &logger, " Calling selected number \r\n" );
    ltecat13nax_send_cmd( &ltecat13nax, cmd_buf );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );
    
    ltecat13nax_clear_app_buf( );
    log_printf( &logger, "Dialing \r\n" );
    #define CHECK_DIALING "+CLCC: 1,0,2"  
    ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_CLCC );    
    error_flag = ltecat13nax_rsp_check( CHECK_DIALING );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    #define CHECK_ANSWERED "+CLCC: 1,0,0"  
    ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_CLCC ); 
    error_flag = ltecat13nax_rsp_check( CHECK_ANSWERED );   
    while ( LTECAT13NAX_OK != error_flag )
    {
        ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_CLCC ); 
        error_flag = ltecat13nax_rsp_check( CHECK_ANSWERED );    
    }
    log_printf( &logger, "Answered \r\n" );
    ltecat13nax_error_check( error_flag );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Hanging up \r\n" );
    ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_CHUP );
    ltecat13nax_clear_app_buf( );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    ltecat13nax_error_check( error_flag );
    ltecat13nax_clear_app_buf( );
    
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

#elif ( DEMO_EXAMPLE == EXAMPLE_GNSS )
    #define GPS_NEMA_GGA    "\"GGA\""
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_QGPSGNMEA, GPS_NEMA_GGA );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    func_error |= error_flag;
    gnss_parser_application( app_buf );
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

static void gnss_parser_application ( char *rsp ) 
{
    char element_buf[ 100 ] = { 0 };
    if ( LTECAT13NAX_OK == ltecat13nax_parse_gpgga( rsp, LTECAT13NAX_GPGGA_LATITUDE, element_buf ) )
    {        
        memset( gnss_info_message, 0, 200 ); 
        if ( strlen( element_buf ) > 0 )
        {
            strcpy( gnss_info_message, "GNSS info\n\r" );
            strcat( gnss_info_message, "Latitude: " );
            strncat( gnss_info_message, element_buf, 2 );
            strcat( gnss_info_message, " deg, " );
            strcat( gnss_info_message, &element_buf[ 2 ] );
            strcat( gnss_info_message, " min" );
            ltecat13nax_parse_gpgga( rsp, LTECAT13NAX_GPGGA_LONGITUDE, element_buf );
            strcat( gnss_info_message, "\n\rLongitude: " );
            strncat( gnss_info_message, element_buf, 3 );
            strcat( gnss_info_message, " deg, " );
            strcat( gnss_info_message, &element_buf[ 3 ] );
            strcat( gnss_info_message, " min" );
            memset( element_buf, 0, sizeof( element_buf ) );
            ltecat13nax_parse_gpgga( rsp, LTECAT13NAX_GPGGA_ALTITUDE, element_buf );
            strcat( gnss_info_message, "\n\rAltitude: " );
            strcat( gnss_info_message, element_buf );
            strcat( gnss_info_message, " m" );
            log_printf( &logger, "%s\r\n", gnss_info_message );
        }
        else
        {
            log_printf( &logger, " Waiting for the position fix...\r\n" );
        }
        log_printf( &logger, "\r\n-----------------------------------\r\n" );
        ltecat13nax_clear_app_buf();
    }
}

// ------------------------------------------------------------------------ END
