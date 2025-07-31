/*!
 * @file main.c
 * @brief WIZFI360 Click Example.
 *
 * # Description
 * This example demonstrates the use of the WIZFI360 Click board 
 * by processing the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, connects to the desired WiFi network, 
 * and then connects to the TCP/UDP server and configures SNTP parameter.
 *
 * ## Application Task
 * The demo app displays current time data, sends data messages to the TCP/UDP server, 
 * reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void wizfi360_clear_app_buf ( void )
 * - static void wizfi360_log_app_buf ( void )
 * - static err_t wizfi360_process ( wizfi360_t *ctx )
 * - static void wizfi360_check_response ( uint8_t *rsp )
 *
 * @note
 * In order for the examples to work without using Planet Debug, 
 * the user needs to set the SSID and password of the target AP.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "wizfi360.h"

// Application buffer size
#define APP_BUFFER_SIZE             200
#define PROCESS_BUFFER_SIZE         200

// Response timeout
#define RESPONSE_TIMEOUT            100000

// Demo data for sending
#define DEMO_SEND_DATA              "MikroE WIZFI360 Click"

// Send data length in normal transmission mode
#define DEMO_SEND_DATA_LENGTH       "22"

// SSID and password of the target AP
#define DEMO_SSID                   "MIKROE GUEST"
#define DEMO_PASSWORD               "!guest.mikroe!"

// Example of sending messages to a TCP/UDP echo server
#define DEMO_EXAMPLE_TCP            "TCP"
#define DEMO_EXAMPLE_UDP            "UDP"

// TCP/UDP echo server IP address and port
#define DEMO_REMOTE_ID              "54.187.244.144"
#define DEMO_REMOTE_PORT            "51111"

static wizfi360_t wizfi360;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static uint8_t cmd_buf[ 100 ] = { 0 };

/**
 * @brief WIZFI360 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void wizfi360_clear_app_buf ( void );

/**
 * @brief WIZFI360 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void wizfi360_log_app_buf ( void );

/**
 * @brief WIZFI360 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wizfi360_process ( wizfi360_t *ctx );

/**
 * @brief WIZFI360 response check.
 * @details This function checks for response and displays the status of response.
 * @param[in] rsp  Expected response.
 * @return Nothing.
 */
static void wizfi360_check_response ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wizfi360_cfg_t wizfi360_cfg;  /**< Click config object. */

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
    wizfi360_cfg_setup( &wizfi360_cfg );
    WIZFI360_MAP_MIKROBUS( wizfi360_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wizfi360_init( &wizfi360, &wizfi360_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    wizfi360_write_command( &wizfi360, WIZFI360_CMD_AT );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_command( &wizfi360, WIZFI360_CMD_RESTORE );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_command( &wizfi360, WIZFI360_CMD_GMR );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CWMODE_CUR, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         WIZFI360_CWMODE_STATION );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CIPMUX, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         WIZFI360_CIPMUX_SINGLE_CONN );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CWDHCP_CUR, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         WIZFI360_CWDHCP_STATION_DHCP );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    memset( cmd_buf, 0, 100 );
    strcpy( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_SSID );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_SEPARATOR );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_PASSWORD );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CWJAP_CUR, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         cmd_buf );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_inquire_command( &wizfi360, WIZFI360_CMD_CIPSTA_CUR );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    memset( cmd_buf, 0, 100 );
    strcpy( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_EXAMPLE_TCP );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_SEPARATOR );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, DEMO_REMOTE_ID );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_QUOTE );
    strcat( cmd_buf, WIZFI360_PREFIX_SYMB_SEPARATOR );
    strcat( cmd_buf, DEMO_REMOTE_PORT );
    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CIPSTART, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         cmd_buf );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    wizfi360_write_cmd_param ( &wizfi360, WIZFI360_CMD_CIPSNTPCFG, 
                                          WIZFI360_PREFIX_SYMB_SET_VAL, 
                                          WIZFI360_ENABLE_TIMEZONE_1 );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 500 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    wizfi360_inquire_command( &wizfi360, WIZFI360_CMD_CIPSNTPTIME );
    wizfi360_check_response( WIZFI360_RSP_OK );
    Delay_ms ( 1000 );

    wizfi360_write_cmd_param( &wizfi360, WIZFI360_CMD_CIPSEND, 
                                         WIZFI360_PREFIX_SYMB_SET_VAL, 
                                         DEMO_SEND_DATA_LENGTH );
    wizfi360_check_response( WIZFI360_RSP_READY_FOR_SEND );
    
    wizfi360_send_message( &wizfi360, DEMO_SEND_DATA );
    wizfi360_check_response( WIZFI360_RECEIVE );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

static void wizfi360_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void wizfi360_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t wizfi360_process ( wizfi360_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = wizfi360_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return WIZFI360_OK;
    }
    return WIZFI360_ERROR;
}

static void wizfi360_check_response ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    wizfi360_clear_app_buf( );
    wizfi360_process( &wizfi360 );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, WIZFI360_RSP_ERROR ) ) )
    {
        wizfi360_process( &wizfi360 );
        if ( timeout_cnt++ > RESPONSE_TIMEOUT )
        {
            wizfi360_clear_app_buf( );
            log_error( &logger, " Timeout!" );
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 1 );
    
    wizfi360_process( &wizfi360 );
    if ( strstr( app_buf, rsp ) )
    {
        wizfi360_log_app_buf( );
        log_printf( &logger, "\r\n" );
    }
    else if ( strstr( app_buf, WIZFI360_RSP_ERROR ) )
    {
        log_error( &logger, " Command!" );
    }
    else
    {
        log_error( &logger, " Unknown!" );
    }
}

// ------------------------------------------------------------------------ END
