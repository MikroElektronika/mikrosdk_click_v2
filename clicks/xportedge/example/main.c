/*!
 * @file main.c
 * @brief XPort EDGE Click Example.
 *
 * # Description
 * This example demonstrates the functionality of the XPort EDGE Click board. It initializes the module, 
 * retrieves the device and interface information, performs diagnostic commands such as pinging a specific 
 * address, and allows the user to access the device via its web interface. Additionally, it provides a 
 * CLI (Command Line Interface) mode to UART terminal for further interaction with the device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the XPort EDGE Click driver, performs a device reset, retrieves device 
 * information, and pings the specific address in diagnostics. The application retrieves the device's IP address, 
 * enabling the user to connect via a web browser and access the web interface. Finally, it enters CLI mode 
 * for advanced command interactions.
 *
 * ## Application Task
 * Continuously monitors UART communication, relaying commands and responses between the XPort EDGE Click 
 * board and the logger. This allows real-time interaction with the device through the UART Terminal for
 * configuration and diagnostics.
 *
 * ## Additional Function
 * - static void xportedge_clear_app_buf ( void )
 * - static void xportedge_log_app_buf ( void )
 * - static err_t xportedge_process ( xportedge_t *ctx )
 * - static err_t xportedge_read_response ( xportedge_t *ctx )
 *
 * @note
 * Ensure the XPort EDGE Click board is properly connected to the network.
 * The application uses a predefined address to test connectivity via the ping diagnostic command.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "xportedge.h"

// Link or IP address for pinging
#define ADDRESS_TO_PING             "https://www.mikroe.com"

// Application buffer size
#define APP_BUFFER_SIZE             200
#define PROCESS_BUFFER_SIZE         100

static xportedge_t xportedge;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief XPort EDGE clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void xportedge_clear_app_buf ( void );

/**
 * @brief XPort EDGE log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void xportedge_log_app_buf ( void );

/**
 * @brief XPort EDGE data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xportedge_process ( xportedge_t *ctx );

/**
 * @brief XPort EDGE read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #xportedge_t object definition for detailed explanation.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xportedge_read_response ( xportedge_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xportedge_cfg_t xportedge_cfg;  /**< Click config object. */

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
    xportedge_cfg_setup( &xportedge_cfg );
    XPORTEDGE_MAP_MIKROBUS( xportedge_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xportedge_init( &xportedge, &xportedge_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, "*** Reset Device ***" );
    xportedge_reset_device ( &xportedge );
    xportedge_read_response ( &xportedge );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Get Device Info ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DEVICE );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_SHOW );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Go Back to Status Level ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Get Interface Status and IP Address ***\r\n" );
    log_printf( &logger, "*** Connect to Listed IP Address Through Web Browser to Access Web Interface ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_INTERFACE_ETH0 );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_SHOW );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Go Back to Status Level ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Ping %s ***", ( char * ) ADDRESS_TO_PING );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DIAGNOSTICS );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DIAGNOSTICS_PING );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_STATUS_DIAGNOSTICS_PING_HOST( ADDRESS_TO_PING ) );
    xportedge_read_response ( &xportedge );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** Go Back to ROOT Level ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    xportedge_send_cmd ( &xportedge, XPORTEDGE_CMD_EXIT );
    xportedge_read_response ( &xportedge );
    
    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, "*** List ROOT Level Commands and Switch to CLI Terminal ***\r\n" );
    log_printf( &logger, "*** Now CLI Commands are Input from the UART Terminal ***" );
    xportedge_send_enter ( &xportedge );
    xportedge_read_response ( &xportedge );
    xportedge_list_commands ( &xportedge );
    xportedge_read_response ( &xportedge );
}

void application_task ( void ) 
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &xportedge.uart, app_buf, app_buf_len );
        xportedge_clear_app_buf ( );
    }
    app_buf_len = uart_read( &xportedge.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        xportedge_clear_app_buf ( );
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

static void xportedge_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void xportedge_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t xportedge_process ( xportedge_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = xportedge_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            for ( int32_t buf_cnt = 0; buf_cnt < overflow_bytes; buf_cnt++ )
            {
                log_printf( &logger, "%c", app_buf[ buf_cnt ] );
            }
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
        return XPORTEDGE_OK;
    }
    return XPORTEDGE_ERROR;
}

static err_t xportedge_read_response ( xportedge_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 30000;
    while ( 0 == strstr( app_buf, XPORTEDGE_CMD_TERMINAL ) )
    {
        xportedge_clear_app_buf ( );
        xportedge_process( ctx );
        xportedge_log_app_buf ( );
        if ( timeout_cnt++ > timeout )
        {
            return XPORTEDGE_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    timeout_cnt = 0;
    timeout = 100;
    xportedge_clear_app_buf ( );
    while ( timeout_cnt++ < timeout )
    {
        if ( XPORTEDGE_OK == xportedge_process( ctx ) )
        {
            timeout_cnt = 0;
        }
        xportedge_log_app_buf ( );
        xportedge_clear_app_buf ( );
        Delay_ms ( 1 );
    }
    return XPORTEDGE_OK;
}

// ------------------------------------------------------------------------ END
