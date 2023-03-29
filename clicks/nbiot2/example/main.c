/*!
 * @file main.c
 * @brief NB IoT 2 Click Example.
 *
 * # Description
 * This example reads and processes data from NB IoT 2 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver, wake-up module and sets default configuration 
 * for connecting device to network.
 *
 * ## Application Task
 * This application is split into two examples:
 * - TCP/UDP example - connecting to echo server and writing and reading data.
 * - SMS example - Sending SMS message to desired number using TEXT or PDU mode. 
 *
 * ## Additional Function
 * - static void nbiot2_clear_app_buf ( void )
 * - static err_t nbiot2_process ( void )
 * - static void nbiot2_config_device_for_example ( void )
 * - static void nbiot2_check_connection ( void )
 * - static void nbiot2_log_response ( void )
 * - static void nbiot2_error_check( err_t error_flag );
 * - static err_t nbiot2_check_response ( void )
 * - static void nbiot2_config_device_for_network ( void )
 * - static void nbiot2_send_sms ( void )
 * - static void nbiot2_config_device_for_tcp_udp ( void )
 * - static void nbiot2_tcp_udp_example ( void )
 *
 * @note
 * In order for the examples to work, user needs to set the APN and SMSC (SMS PDU mode only) 
 * of entered SIM card as well as the phone number to which he wants to send an SMS.
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
#include "conversions.h"
#include "nbiot2.h"

// Example selection macros
#define NBIOT2_TCP_UDP_EXAMPLE
// #define NBIOT2_SMS_EXAMPLE

// SMS example selection macros
// #define SMS_PDU_MODE
#define SMS_TEXT_MODE

// SMS example parameters
#define PHONE_NUMBER_TO_MESSAGE             ""              // Set Phone number to message
#define SIM_SMSC                            ""              // Set SIM SMSC

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// SIM APN config
#define SIM_APN                             ""
#define MESSAGE_CONTENT                     "NB IoT 2 Click Example"   // Message content

#define PROCESS_BUFFER_SIZE                 200

#define CONFIGURATION_FOR_EXAMPLE           0
#define EXAMPLE                             1

static nbiot2_t nbiot2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

static err_t app_error_flag;

static uint8_t app_connection_status = CONFIGURATION_FOR_EXAMPLE;

/**
 * @brief NB IoT 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void nbiot2_clear_app_buf ( void );

/**
 * @brief NB IoT 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot2_process ( void );

/**
 * @brief Configure device for example.
 * @details Configure device for sending messages or sending messages to TCP/UDP Echo server.
 * @return Nothing.
 * @note None.
 */
static void nbiot2_config_device_for_example ( void );

/**
 * @brief Wait for connection signal.
 * @details Wait for connection signal from CREG URC.
 * @return Nothing.
 * @note None.
 */
static void nbiot2_check_connection ( void );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void nbiot2_log_response ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of 
 * errors and logs them on UART or logs the response if no errors occured.
 * @note None.
 */
static void nbiot2_error_check( err_t error_flag );

/**
 * @brief NB IoT 2 response read function.
 * @details This function reads the response of the sent command and writes it on the USB UART.
 * @return @li @c  0 - Response OK.
 *         @li @c -1 - Response ERROR.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot2_check_response ( void );

/**
 * @brief Configure device for connection to the network.
 * @details Sends commands to configure and enable connection to the specified network.
 * @return Nothing.
 * @note None.
 */
static void nbiot2_config_device_for_network ( void );

/**
 * @brief Check for connection to the network.
 * @details Sends commands to check connection to the specified network.
 * @return Nothing.
 * @note None.
 */
static void nbiot2_check_connection_to_network ( void );

/**
 * @brief Send SMS example.
 * @details Sends commands to send SMS messages in TEXT or PDU mode.
 * @return Nothing.
 * @note None.
 */
static void nbiot2_send_sms ( void );

/**
 * @brief Configure device for TCP/UDP example.
 * @details Sends commands to connect with TCP/UDP server.
 * @return Nothing.
 * @note None.
 */
static void nbiot2_config_device_for_tcp_udp ( void );

/**
 * @brief TCP/UDP example.
 * @details Sends message to TCP/UDP server and receives data from it.
 * @return Nothing.
 * @note None.
 */
static void nbiot2_tcp_udp_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot2_cfg_t nbiot2_cfg;  /**< Click config object. */

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
    nbiot2_cfg_setup( &nbiot2_cfg );
    NBIOT2_MAP_MIKROBUS( nbiot2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot2_init( &nbiot2, &nbiot2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " - Reseting device... \r\n" );
    nbiot2_hw_reset( &nbiot2 );
    Delay_ms( 4000 );
    app_error_flag = nbiot2_process( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd( &nbiot2, NBIOT2_CMD_AT );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd( &nbiot2, NBIOT2_CMD_ATI );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CFUN, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QSPCHSC, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CPSMS, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );
    
    nbiot2_set_apn( &nbiot2, SIM_APN );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );   
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QRST, "1" );
    Delay_ms( 2000 );
    app_error_flag = nbiot2_process( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QBAND, "1,20" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );      
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CEREG, "2" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );   
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CSCON, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QNBIOTEVENT, "1,1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_SM, "LOCK" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QSCLK, "0" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    log_info( &logger, " Application Task " );
    
    app_connection_status = CONFIGURATION_FOR_EXAMPLE;
    
    app_buf_len = 0;
    app_buf_cnt = 0;
}

void application_task ( void ) 
{   
    switch( app_connection_status )
    {
        case CONFIGURATION_FOR_EXAMPLE:
        {
            nbiot2_config_device_for_example( );
            break;
        }
        case EXAMPLE:
        {
            #if defined( NBIOT2_TCP_UDP_EXAMPLE )
                nbiot2_tcp_udp_example( );
            #endif   
            #if defined( NBIOT2_SMS_EXAMPLE )
                nbiot2_send_sms( );
                Delay_ms( 10000 );
            #endif
            break;
        }
        default:
        {
            log_error( &logger, "Application status error!" );
            app_connection_status = CONFIGURATION_FOR_EXAMPLE;
            Delay_ms( 1000 );
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

static void nbiot2_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t nbiot2_process ( void ) 
{
    int32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = nbiot2_generic_read( &nbiot2, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            nbiot2_clear_app_buf(  );
            return NBIOT2_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] != 0 ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buf[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return NBIOT2_OK;
    }
    return NBIOT2_ERROR;
}

static void nbiot2_config_device_for_example ( void )
{
#if defined( NBIOT2_TCP_UDP_EXAMPLE )
    nbiot2_config_device_for_tcp_udp( );
#endif
#if defined( NBIOT2_SMS_EXAMPLE )
    nbiot2_config_device_for_network( );
    for( ; ; )
    {
        nbiot2_check_connection_to_network( );
        if ( CONFIGURATION_FOR_EXAMPLE != app_connection_status )
        {
            break;
        }
    }
#endif 
}

static void nbiot2_check_connection( void )
{
    #define CONNECTED "+CGATT: 1"

    if ( strstr( app_buf, CONNECTED ) != 0 )
    {
        app_connection_status = EXAMPLE;
    }
}

static err_t nbiot2_check_response ( void )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 100000;
    err_t error_flag;
    while ( ( 0 == strstr( app_buf, NBIOT2_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, NBIOT2_RSP_ERROR ) ) )
    {
        error_flag = nbiot2_process( );
        if ( ( NBIOT2_OK != error_flag ) && ( NBIOT2_ERROR != error_flag ) )
        {
            return error_flag;
        }
        if ( timeout_cnt++ > timeout )
        {
            nbiot2_clear_app_buf( );
            return NBIOT2_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    if ( strstr( app_buf, NBIOT2_RSP_OK ) )
    {
        return NBIOT2_OK;
    }
    else if ( strstr( app_buf, NBIOT2_RSP_ERROR ) )
    {
        return NBIOT2_ERROR;
    }
    else
    {
        return NBIOT2_ERROR;
    }
}

static void nbiot2_log_response ( void )
{    
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        nbiot2_check_connection();
    }
    log_printf( &logger, "-----------------------------------\r\n" );
}

static void nbiot2_error_check( err_t error_flag )
{
    switch ( error_flag )
    {
        case NBIOT2_OK:
        {
            nbiot2_log_response( );
            break;
        }
        case NBIOT2_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case NBIOT2_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    nbiot2_clear_app_buf(  );
    Delay_ms( 500 );
}

static void nbiot2_config_device_for_network( void )
{
    nbiot2_send_cmd( &nbiot2, NBIOT2_CMD_CIMI );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  

    nbiot2_set_apn( &nbiot2, SIM_APN );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  

    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CREG, "2" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
}

static void nbiot2_check_connection_to_network( void )
{
    nbiot2_send_cmd_check( &nbiot2, NBIOT2_CMD_CGATT );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  

    nbiot2_send_cmd_check( &nbiot2, NBIOT2_CMD_CEREG );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  

    nbiot2_send_cmd_check( &nbiot2, NBIOT2_CMD_COPS );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  

    if ( CONFIGURATION_FOR_EXAMPLE != app_connection_status )
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
    }
}

static void nbiot2_send_sms ( void )
{
#if defined( SMS_TEXT_MODE )
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CMGF, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  

    log_printf( &logger, "> Sending message to phone number...\r\n" );
    nbiot2_send_sms_text_mode( &nbiot2, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    if ( NBIOT2_OK != app_error_flag )
    {
        log_printf( &logger, "> Message sent...\r\n" );
        Delay_ms( 10000 );
    }
#elif defined( SMS_PDU_MODE )
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CMGF, "0" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    nbiot2_send_sms_pdu ( &nbiot2, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    if ( NBIOT2_OK != app_error_flag )
    {
        log_printf( &logger, "> Message sent...\r\n" );
        Delay_ms( 10000 );
    }
#endif
}

static void nbiot2_config_device_for_tcp_udp ( void )
{
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_CGATT, "1" );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    
    if ( NBIOT2_OK == app_error_flag )
    {
        app_connection_status = EXAMPLE;
    }
}

static void nbiot2_tcp_udp_example ( void )
{
    #define CONTEXTID       "1"
    #define TCP_PROTOCOL    "0"
    #define UDP_PROTOCOL    "1"
    #define URC_READ_SOCKET_DATA "+QIURC: \"recv\""
    
    char cmd_buf[ 100 ] = { 0 };
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 30000;
    
    // Get message length
    uint8_t message_len_buf[ 5 ] = { 0 };
    uint16_t message_len = strlen( MESSAGE_CONTENT );
    uint16_to_str( message_len, message_len_buf );
    l_trim( message_len_buf );
    r_trim( message_len_buf );
    
    // Create TCP socket
    strcpy( cmd_buf, CONTEXTID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, TCP_PROTOCOL );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, "TCP" );
    strcat( cmd_buf, "\"" );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "," ); 
    strcat( cmd_buf, REMOTE_PORT ); 
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QIOPEN, cmd_buf );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    Delay_ms( 2000 );
    
    if ( NBIOT2_OK == app_error_flag )
    {
        log_info( &logger, "SENDING MESSAGES TO TCP" );
        // Write message to TCP socket
        strcpy( cmd_buf, TCP_PROTOCOL );
        strcat( cmd_buf, "," );
        strcat( cmd_buf, message_len_buf );
        strcat( cmd_buf, ",\"" );
        strcat( cmd_buf, MESSAGE_CONTENT );
        strcat( cmd_buf, "\"" );
        nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QISEND, cmd_buf );
    
        // Read response message from TCP socket
        for ( ; ; )
        {
            nbiot2_process( );
            uint8_t * __generic_ptr start_response_buf = strstr( app_buf, URC_READ_SOCKET_DATA );
            if ( start_response_buf )
            {
                log_info( &logger, "RECEIVED MESSAGE" );
                strcpy( cmd_buf, TCP_PROTOCOL );
                strcat( cmd_buf, "," );
                strcat( cmd_buf, "256" );
                nbiot2_clear_app_buf( );
                nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QIRD, cmd_buf );
                app_error_flag = nbiot2_check_response( );
                nbiot2_error_check( app_error_flag );  
            
                if ( NBIOT2_OK == app_error_flag )
                {
                    break;
                }
            }
            if ( timeout_cnt++ > timeout )
            {
                log_error( &logger, "TIMEOUT!!!" );
                break;
            }   
            Delay_ms( 1 );
        }
        timeout_cnt = 0;
        Delay_ms( 2000 );
        
        // Close TCP socket
        nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QICLOSE, TCP_PROTOCOL );
        app_error_flag = nbiot2_check_response( );
        nbiot2_error_check( app_error_flag );  
    }
    else
    {
        log_error( &logger, "Not connected to the TCP server" );
    }
    
    // Create UDP socket
    strcpy( cmd_buf, CONTEXTID );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, UDP_PROTOCOL );
    strcat( cmd_buf, ",\"" );
    strcat( cmd_buf, "UDP" );
    strcat( cmd_buf, "\"" );
    strcat( cmd_buf, "," );
    strcat( cmd_buf, REMOTE_IP );
    strcat( cmd_buf, "," ); 
    strcat( cmd_buf, REMOTE_PORT ); 
    
    nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QIOPEN, cmd_buf );
    app_error_flag = nbiot2_check_response( );
    nbiot2_error_check( app_error_flag );  
    Delay_ms( 2000 );
    
    if ( NBIOT2_OK == app_error_flag )
    {
        log_info( &logger, "SENDING MESSAGES TO UDP" );
        // Write message to UDP socket
        strcpy( cmd_buf, UDP_PROTOCOL );
        strcat( cmd_buf, "," );
        strcat( cmd_buf, message_len_buf );
        strcat( cmd_buf, ",\"" );
        strcat( cmd_buf, MESSAGE_CONTENT );
        strcat( cmd_buf, "\"" );
        nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QISEND, cmd_buf );
    
        // Read response message from UDP socket
        for ( ; ; )
        {
            nbiot2_process( );
            uint8_t * __generic_ptr start_response_buf = strstr( app_buf, URC_READ_SOCKET_DATA );
            if ( start_response_buf )
            {
                log_info( &logger, "RECEIVED MESSAGE" );
                strcpy( cmd_buf, UDP_PROTOCOL );
                strcat( cmd_buf, "," );
                strcat( cmd_buf, "256" );
                nbiot2_clear_app_buf( );
                nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QIRD, cmd_buf );
                app_error_flag = nbiot2_check_response( );
                nbiot2_error_check( app_error_flag );  
            
                if ( NBIOT2_OK == app_error_flag )
                {
                    break;
                }
            }
            if ( timeout_cnt++ > timeout )
            {
                log_error( &logger, "TIMEOUT!!!" );
                break;
            }   
            Delay_ms( 1 );
        }
        timeout_cnt = 0;
        Delay_ms( 2000 );
        
        // Close UDP socket
        nbiot2_send_cmd_with_parameter( &nbiot2, NBIOT2_CMD_QICLOSE, UDP_PROTOCOL );
        app_error_flag = nbiot2_check_response( );
        nbiot2_error_check( app_error_flag );  
    }
    else
    {
        log_error( &logger, "Not connected to the UDP server" );
    }
    
    Delay_ms( 5000 );
}




// ------------------------------------------------------------------------ END
