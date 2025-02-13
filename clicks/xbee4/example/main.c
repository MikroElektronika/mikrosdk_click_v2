/*!
 * @file main.c
 * @brief XBEE 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of an XBEE 4 Click board by showing
 * the communication between the two Click boards configured in transparent mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Click board by performing a factory reset, 
 * and setting the device name, destination address, api mode to transparent, 
 * and a device role to join or form network depending on the application mode.
 *
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired message every 3 seconds.
 *
 * ## Additional Function
 * - static void xbee4_clear_app_buf ( void )
 * - static void xbee4_log_app_buf ( void )
 * - static err_t xbee4_process ( xbee4_t *ctx )
 * - static err_t xbee4_read_response ( xbee4_t *ctx, uint8_t *rsp, uint32_t timeout )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "xbee4.h"

// Device name (Node identifier).
#define DEVICE_NAME                 "XBEE 4 Click"

// Enter here the specific serial number high and low bytes of the remote device as a hex string or 
// leave it set to broadcast addresses for forwarding messages to all devices
#define DESTINATION_ADDRESS_HIGH    XBEE4_BROADCAST_DEST_ADDRESS_HIGH
#define DESTINATION_ADDRESS_LOW     XBEE4_BROADCAST_DEST_ADDRESS_LOW

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - XBEE 4 Click board\r\n"

// Application buffer size
#define APP_BUFFER_SIZE             400
#define PROCESS_BUFFER_SIZE         200

static xbee4_t xbee4;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief XBEE 4 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void xbee4_clear_app_buf ( void );

/**
 * @brief XBEE 4 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void xbee4_log_app_buf ( void );

/**
 * @brief XBEE 4 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xbee4_process ( xbee4_t *ctx );

/**
 * @brief XBEE 4 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] timeout : Response timeout in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Command error.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xbee4_read_response ( xbee4_t *ctx, uint8_t *rsp, uint32_t timeout );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xbee4_cfg_t xbee4_cfg;  /**< Click config object. */

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
    xbee4_cfg_setup( &xbee4_cfg );
    XBEE4_MAP_MIKROBUS( xbee4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xbee4_init( &xbee4, &xbee4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    xbee4_hw_reset ( &xbee4 );
    xbee4_process ( &xbee4 );
    xbee4_clear_app_buf( );
    
    log_printf( &logger, " - Enter command mode -\r\n" );
    xbee4_enter_command_mode ( &xbee4 );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S );
    
    log_printf( &logger, " - Factory Reset -\r\n" );
    xbee4_factory_reset ( &xbee4 );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S );
    
    log_printf( &logger, " - Get serial number -\r\n" );
    xbee4_get_serial_number ( &xbee4 );
    xbee4_read_response ( &xbee4, XBEE4_RSP_NEW_LINE, XBEE4_TIMEOUT_3S );
    
    log_printf( &logger, " - Set Device Name -\r\n" );
    xbee4_set_device_name ( &xbee4, DEVICE_NAME );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S );
    
    log_printf( &logger, " - Set Destination Address -\r\n" );
    xbee4_set_destination_address ( &xbee4, DESTINATION_ADDRESS_HIGH, DESTINATION_ADDRESS_LOW );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S );
    
    log_printf( &logger, " - Set API mode -\r\n" );
    xbee4_set_api_mode ( &xbee4, XBEE4_MODE_TRANSPARENT );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S );

    log_printf( &logger, " - Set Device Role -\r\n" );
#ifdef DEMO_APP_TRANSMITTER
    xbee4_set_device_role ( &xbee4, XBEE4_DEVICE_ROLE_JOIN_NETWORK );
#else
    xbee4_set_device_role ( &xbee4, XBEE4_DEVICE_ROLE_FORM_NETWORK );
#endif
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S );
    
    log_printf( &logger, " - Apply changes -\r\n" );
    xbee4_apply_changes ( &xbee4 );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S ); 
    
    log_printf( &logger, " - Save changes -\r\n" );
    xbee4_save_changes ( &xbee4 );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S );
    
    log_printf( &logger, " - Exit command mode -\r\n" );
    xbee4_exit_command_mode ( &xbee4 );
    xbee4_read_response ( &xbee4, XBEE4_RSP_OK, XBEE4_TIMEOUT_3S ); 
    
    xbee4_clear_app_buf ( );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    xbee4_generic_write( &xbee4, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    if ( XBEE4_OK == xbee4_process( &xbee4 ) ) 
    {
        xbee4_log_app_buf ( );
        xbee4_clear_app_buf ( );
    }
#endif
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

static void xbee4_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void xbee4_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t xbee4_process ( xbee4_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = xbee4_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return XBEE4_OK;
    }
    return XBEE4_ERROR;
}

static err_t xbee4_read_response ( xbee4_t *ctx, uint8_t *rsp, uint32_t timeout )
{
    uint32_t timeout_cnt = 0;
    xbee4_clear_app_buf ( );
    xbee4_process ( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) && 
            ( 0 == strstr( app_buf, XBEE4_RSP_ERROR ) ) )
    {
        xbee4_process ( ctx );
        if ( timeout_cnt++ > timeout )
        {
            xbee4_log_app_buf( );
            log_error( &logger, " Timeout!" );
            return XBEE4_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    xbee4_process( ctx );
    xbee4_log_app_buf( );
    if ( strstr( app_buf, XBEE4_RSP_ERROR ) )
    {
        log_error( &logger, " CMD!" );
        return XBEE4_ERROR;
    }
    log_printf( &logger, "--------------------------------\r\n" );
    return XBEE4_OK;
}

// ------------------------------------------------------------------------ END
