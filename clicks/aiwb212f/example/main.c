/*!
 * @file main.c
 * @brief Ai-WB2-12F Click Example.
 *
 * # Description
 * This example demonstrates the use of Ai-WB2-12F Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, tests the communication, and after that restarts the device, and performs example configuration.
 *
 * ## Application Task
 * Depending on the selected demo example, it sends a TCP/UDP echo server message and receives it or 
 * creates BLE Client which receives the messages from the connected device.
 *
 * ## Additional Function
 * - static void aiwb212f_clear_app_buf ( void )
 * - static void aiwb212f_log_app_buf ( void )
 * - static err_t aiwb212f_process ( aiwb212f_t *ctx )
 * - static void aiwb212f_rsp_check ( void )
 * - static void aiwb212f_error_check ( void )
 * - static void aiwb212f_configure_for_example ( void )
 * - static void aiwb212f_example ( void )
 *
 * @note
 * We have used the BLE Scanner Android application for the BLE Example test
 * and you can find it at the link:
 * https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "aiwb212f.h"

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_BLE                         1               // BLE Example
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// Message content
#define MESSAGE_CONTENT                     "Ai-WB2-12F Click board - demo example."
#define MESSAGE_LEN                         "40"

// TCP/UDP example parameters
#define REMOTE_IP                           "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port

// WiFi parameters
#define WIFI_SSID                           "MIKROE GUEST"
#define WIFI_PWD                            "!guest.mikroe!"

// GPIO parameters
#define LED_RED_GPIO                        "5"
#define LED_GREEN_GPIO                      "6"
#define LED_BLUE_GPIO                       "7"

// Application buffer size
#define APP_BUFFER_SIZE                     200
#define PROCESS_BUFFER_SIZE                 200

static aiwb212f_t aiwb212f;
static log_t logger;
static err_t error_flag;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Ai-WB2-12F clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void aiwb212f_clear_app_buf ( void );

/**
 * @brief Ai-WB2-12F log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void aiwb212f_log_app_buf ( void );

/**
 * @brief Ai-WB2-12F data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t aiwb212f_process ( void );

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
static err_t aiwb212f_rsp_check ( uint8_t *rsp );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void aiwb212f_error_check ( err_t error_flag );

/**
 * @brief Ai-WB2-12F configure for example function.
 * @details This function is used to configure device for example.
 */
static void aiwb212f_configure_for_example ( void );

/**
 * @brief Ai-WB2-12F execute example function.
 * @details This function executes TCP/UDP or BLE example depending on the DEMO_EXAMPLE macro.
 */
static void aiwb212f_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    aiwb212f_cfg_t aiwb212f_cfg;  /**< Click config object. */

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
    aiwb212f_cfg_setup( &aiwb212f_cfg );
    AIWB212F_MAP_MIKROBUS( aiwb212f_cfg, MIKROBUS_1 );
    if ( UART_ERROR == aiwb212f_init( &aiwb212f, &aiwb212f_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    aiwb212f_process( );
    aiwb212f_clear_app_buf( );

    aiwb212f_hw_reset( &aiwb212f );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_READY );
    aiwb212f_error_check( error_flag );

    // Check communication
    aiwb212f_send_cmd( &aiwb212f, AIWB212F_CMD_AT );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    // Restart device
    aiwb212f_send_cmd( &aiwb212f, AIWB212F_CMD_AT_SW_RESET );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_READY );
    aiwb212f_error_check( error_flag );

    aiwb212f_configure_for_example( );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    aiwb212f_example( );
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

static void aiwb212f_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void aiwb212f_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t aiwb212f_process ( void ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = aiwb212f_generic_read( &aiwb212f, rx_buf, PROCESS_BUFFER_SIZE );
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
        return AIWB212F_OK;
    }
    return AIWB212F_ERROR;
}

static err_t aiwb212f_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    aiwb212f_clear_app_buf( );
    aiwb212f_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, AIWB212F_RSP_ERROR ) ) )
    {
        aiwb212f_process( );
        if ( timeout_cnt++ > timeout )
        {
            aiwb212f_clear_app_buf( );
            return AIWB212F_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    aiwb212f_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return AIWB212F_OK;
    }
    else if ( strstr( app_buf, AIWB212F_RSP_ERROR ) )
    {
        return AIWB212F_ERROR_CMD;
    }
    else
    {
        return AIWB212F_ERROR_UNKNOWN;
    }
}

static void aiwb212f_error_check ( err_t error_flag )
{
    #define LED_STATE_ON        "1"
    #define LED_STATE_OFF       "0"
    uint8_t command_data[ 10 ] = { 0 };
    
    switch ( error_flag )
    {
        case AIWB212F_OK:
        {
            aiwb212f_log_app_buf( );
            break;
        }
        case AIWB212F_ERROR:
        {
            log_error( &logger, " Overflow!" );

            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_ON );
            Delay_ms ( 500 );
            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_OFF );
            break;
        }
        case AIWB212F_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );

            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_ON );
            Delay_ms ( 500 );
            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_OFF );
            break;
        }
        case AIWB212F_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );

            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_ON );
            Delay_ms ( 500 );
            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_OFF );
            break;
        }
        case AIWB212F_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );

            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_ON );
            Delay_ms ( 500 );
            aiwb212f_set_gpio( &aiwb212f, LED_RED_GPIO, LED_STATE_OFF );
            break;
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 500 );
}

static void aiwb212f_configure_for_example ( void )
{
#if ( EXAMPLE_TCP_UDP == DEMO_EXAMPLE )

    #define WIFI_MODE           "1,0"
    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_WMODE, WIFI_MODE );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    // Connect to WiFi
    #define WIFI_CONNECTED      "+EVENT:WIFI_GOT_IP"
    uint8_t wifi_data[ 50 ] = { 0 };
    strcpy( wifi_data, WIFI_SSID );
    strcat( wifi_data, "," );
    strcat( wifi_data, WIFI_PWD );
    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_WJAP, wifi_data );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    error_flag = aiwb212f_rsp_check( WIFI_CONNECTED );
    aiwb212f_error_check( error_flag );

#elif ( EXAMPLE_BLE == DEMO_EXAMPLE )

    #define DEVICE_NAME         "Ai-WB2-12F Click"
    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_BLENAME, DEVICE_NAME );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_BLEMODE, "0" );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag ); 

    #define DEVICE_CONNECT      "+EVENT:BLE_CONNECT"
    log_printf( &logger, "  Please connect your device\r\n" );
    do
    {
        aiwb212f_process(); 
        aiwb212f_set_gpio( &aiwb212f, LED_BLUE_GPIO, LED_STATE_ON );
        Delay_ms ( 500 );
        aiwb212f_set_gpio( &aiwb212f, LED_BLUE_GPIO, LED_STATE_OFF );
    }
    while ( !strstr( app_buf, DEVICE_CONNECT ) );
    Delay_ms ( 100 );
    aiwb212f_clear_app_buf( );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );

#else
    #error "No demo example selected"
#endif
}

static void aiwb212f_example ( void )
{
#if ( EXAMPLE_TCP_UDP == DEMO_EXAMPLE )
    uint8_t command_data[ APP_BUFFER_SIZE ] = { 0 };
    #define TCP_CLIENT          "4"
    #define UDP_CLIENT          "2"
    #define CON_ID              "1"
    #define KEEP_ALIVE          "1"

    aiwb212f_set_gpio( &aiwb212f, LED_BLUE_GPIO, LED_STATE_ON );
    Delay_ms ( 500 );
    aiwb212f_set_gpio( &aiwb212f, LED_BLUE_GPIO, LED_STATE_OFF );

    log_printf( &logger, " TCP Example \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );

    strcpy( command_data, TCP_CLIENT );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_IP );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_PORT );
    strcat( command_data, "," );
    strcat( command_data, KEEP_ALIVE );
    strcat( command_data, "," );
    strcat( command_data, CON_ID );
    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_SOCKET, command_data );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    aiwb212f_send_cmd_check( &aiwb212f, AIWB212F_CMD_AT_SOCKET );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    strcpy( command_data, CON_ID );
    strcat( command_data, "," );
    strcat( command_data, MESSAGE_LEN );
    strcat( command_data, "," );
    strcat( command_data, MESSAGE_CONTENT );
    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_SOCKETSENDLINE, command_data );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_SOCKETREAD, CON_ID );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_SOCKETDEL, CON_ID );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    aiwb212f_set_gpio( &aiwb212f, LED_BLUE_GPIO, LED_STATE_ON );
    Delay_ms ( 500 );
    aiwb212f_set_gpio( &aiwb212f, LED_BLUE_GPIO, LED_STATE_OFF );

    // UDP mode doesn't support read function
    log_printf( &logger, " UDP Example \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );

    strcpy( command_data, UDP_CLIENT );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_IP );
    strcat( command_data, "," );
    strcat( command_data, REMOTE_PORT );
    strcat( command_data, "," );
    strcat( command_data, KEEP_ALIVE );
    strcat( command_data, "," );
    strcat( command_data, CON_ID );
    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_SOCKET, command_data );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    aiwb212f_send_cmd_check( &aiwb212f, AIWB212F_CMD_AT_SOCKET );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    strcpy( command_data, CON_ID );
    strcat( command_data, "," );
    strcat( command_data, MESSAGE_LEN );
    strcat( command_data, "," );
    strcat( command_data, MESSAGE_CONTENT );
    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_SOCKETSENDLINE, command_data );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    aiwb212f_send_cmd_with_par( &aiwb212f, AIWB212F_CMD_AT_SOCKETDEL, CON_ID );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );
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

#elif ( EXAMPLE_BLE == DEMO_EXAMPLE )
    aiwb212f_process();
    
    if ( app_buf_len > 0 ) 
    { 
        log_printf( &logger, "%s", app_buf );
        aiwb212f_clear_app_buf(  );    
    }

#else
    #error "No demo example selected"
#endif
}

// ------------------------------------------------------------------------ END
