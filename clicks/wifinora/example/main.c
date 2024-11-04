/*!
 * @file main.c
 * @brief WiFi NORA Click Example.
 *
 * # Description
 * This example demonstrates the use of WiFi NORA Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, tests the communication, and after that restarts the device, and performs example configuration.
 *
 * ## Application Task
 * It creates a connection to the TCP-UDP echo server, sends a message to it reads it back, displaces it on the UART terminal, and then closes the connection.
 *
 * ## Additional Function
 * - static void wifinora_clear_app_buf ( void )
 * - static void wifinora_log_app_buf ( void )
 * - static err_t wifinora_process ( wifinora_t *ctx )
 * - static err_t wifinora_rsp_check ( uint8_t *rsp )
 * - static void wifinora_configure_for_example ( void )
 * - static void wifinora_configure_for_example ( void )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "wifinora.h"

// Message content
#define MESSAGE_CONTENT                     "WiFi NORA Click board - demo example."

// TCP/UDP example parameters
#define REMOTE_IP                           "77.46.162.162" // TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// WiFi parameters
#define WIFI_SSID                           "MikroE Public"
#define WIFI_PWD                            "mikroe.guest"

// Application buffer size
#define APP_BUFFER_SIZE                     200
#define PROCESS_BUFFER_SIZE                 200

static wifinora_t wifinora;
static log_t logger;
static err_t error_flag;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief WiFi NORA clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void wifinora_clear_app_buf ( void );

/**
 * @brief WiFi NORA log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void wifinora_log_app_buf ( void );

/**
 * @brief WiFi NORA data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wifinora_process ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Error response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t wifinora_rsp_check ( uint8_t *rsp );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void wifinora_error_check ( err_t error_flag );

/**
 * @brief WiFi NORA configure for example function.
 * @details This function is used to configure device for example.
 */
static void wifinora_configure_for_example ( void );

/**
 * @brief WiFi NORA execute example function.
 * @details This function executes TCP/UDP Example.
 */
static void wifinora_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifinora_cfg_t wifinora_cfg;  /**< Click config object. */

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
    wifinora_cfg_setup( &wifinora_cfg );
    WIFINORA_MAP_MIKROBUS( wifinora_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wifinora_init( &wifinora, &wifinora_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    wifinora_process( );
    wifinora_clear_app_buf( );

    // Hardware reset
    wifinora_hw_reset( &wifinora );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_READY );
    wifinora_error_check( error_flag );

    // Communication check
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    // Factory reset
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_USYFR );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    // Software reset
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_SW_RESET );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_READY );
    wifinora_error_check( error_flag );

    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_GMM );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    wifinora_configure_for_example( );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    wifinora_example( );
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

static void wifinora_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void wifinora_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t wifinora_process ( void ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = wifinora_generic_read( &wifinora, rx_buf, PROCESS_BUFFER_SIZE );
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
        return WIFINORA_OK;
    }
    return WIFINORA_ERROR;
}

static err_t wifinora_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    wifinora_clear_app_buf( );
    wifinora_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, WIFINORA_RSP_ERROR ) ) )
    {
        wifinora_process( );
        if ( timeout_cnt++ > timeout )
        {
            wifinora_clear_app_buf( );
            return WIFINORA_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    wifinora_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return WIFINORA_OK;
    }
    else if ( strstr( app_buf, WIFINORA_RSP_ERROR ) )
    {
        return WIFINORA_ERROR_CMD;
    }
    else
    {
        return WIFINORA_ERROR_UNKNOWN;
    }
}

static void wifinora_error_check ( err_t error_flag )
{    
    switch ( error_flag )
    {
        case WIFINORA_OK:
        {
            wifinora_log_app_buf( );
            break;
        }
        case WIFINORA_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case WIFINORA_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case WIFINORA_ERROR_CMD:
        {
            log_error( &logger, " ERROR Response!" );
            break;
        }
        case WIFINORA_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 500 );
}

static void wifinora_configure_for_example ( void )
{
    uint8_t command_data[ APP_BUFFER_SIZE ] = { 0 };

    #define WLAN_HANDLE         "0"
    strcpy( command_data, WLAN_HANDLE );
    strcat( command_data, ",\"" );
    strcat( command_data, WIFI_SSID );
    strcat( command_data, "\"" );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_UWSCP, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_UWSIPD, "0" );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    #define WPA_THRESHILD       "0"
    strcpy( command_data, WLAN_HANDLE );
    strcat( command_data, ",\"" );
    strcat( command_data, WIFI_PWD );
    strcat( command_data, "\"," );
    strcat( command_data, WPA_THRESHILD );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_UWSSW, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_UWSC, "0" );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    #define CONNECTED           "+UENEU"
    error_flag = wifinora_rsp_check( CONNECTED );
}

static void wifinora_example ( void )
{
    uint8_t command_data[ APP_BUFFER_SIZE ] = { 0 };
    #define TCP_CLIENT          "0"
    #define UDP_CLIENT          "1"
    #define READ_LEN            "255"

    log_printf( &logger, " TCP Example \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );

    #define TCP_PROTOCOL        "6"
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOCR, TCP_PROTOCOL );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    strcpy( command_data, TCP_CLIENT );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_IP );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_PORT );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOC, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    log_printf( &logger, " Send data \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    strcpy( command_data, TCP_CLIENT );
    strcat( command_data, ",\"" );
    strcat( command_data, MESSAGE_CONTENT );
    strcat( command_data, "\"" );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOWS, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    log_printf( &logger, " Read data \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    strcpy( command_data, TCP_CLIENT );
    strcat( command_data, "," );
    strcat( command_data, READ_LEN );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USORS, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

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

    log_printf( &logger, " UDP Example \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );

    #define UDP_PROTOCOL        "17"
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOCR, UDP_PROTOCOL );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    strcpy( command_data, UDP_CLIENT );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_IP );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_PORT );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOC, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    log_printf( &logger, " Send data \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    strcpy( command_data, UDP_CLIENT );
    strcat( command_data, ",\"" );
    strcat( command_data, MESSAGE_CONTENT );
    strcat( command_data, "\"" );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOWS, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    log_printf( &logger, " Read data \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    strcpy( command_data, UDP_CLIENT );
    strcat( command_data, "," );
    strcat( command_data, READ_LEN );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USORS, command_data );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    log_printf( &logger, " Close sockets \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOCL, UDP_CLIENT );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    wifinora_send_cmd_with_par( &wifinora, WIFINORA_CMD_AT_USOCL, TCP_CLIENT );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

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
}

// ------------------------------------------------------------------------ END
