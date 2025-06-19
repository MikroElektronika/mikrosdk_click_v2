/*!
 * @file main.c
 * @brief XPort ETH SE Click Example.
 *
 * # Description
 * This example demonstrates the use of the XPort ETH SE Click board for Ethernet communication. 
 * The application initializes the XPort ETH SE module, retrieves essential information such as 
 * firmware version, MAC address, and network status, and demonstrates sending a ping command. 
 * It also allows for bidirectional UART communication between the USB UART and the XPort ETH SE UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the UART communication, logs essential information, configures the XPort ETH SE module, 
 * and retrieves the firmware version, MAC address, and network status. It also demonstrates basic 
 * command operations such as pinging the specific IP address (8.8.8.8).
 *
 * ## Application Task
 * Continuously reads data from the USB UART and forwards it to the XPort ETH SE module, 
 * while also capturing responses from the module and forwarding them back to the USB UART.
 * This allows real-time interaction with the device through the UART Terminal for
 * configuration and diagnostics.
 *
 * ## Additional Function
 * - static void xportethse_clear_app_buf ( void )
 * - static err_t xportethse_process ( xportethse_t *ctx )
 * - static err_t xportethse_read_response ( xportethse_t *ctx )
 *
 * @note
 * Ensure the XPort ETH SE Click board is properly connected to the network.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "xportethse.h"

// Application buffer size
#define APP_BUFFER_SIZE             300
#define PROCESS_BUFFER_SIZE         100

static xportethse_t xportethse;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief XPort ETH SE clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void xportethse_clear_app_buf ( void );

/**
 * @brief XPort ETH SE data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xportethse_process ( xportethse_t *ctx );

/**
 * @brief XPort ETH SE read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xportethse_read_response ( xportethse_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xportethse_cfg_t xportethse_cfg;  /**< Click config object. */

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
    xportethse_cfg_setup( &xportethse_cfg );
    XPORTETHSE_MAP_MIKROBUS( xportethse_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xportethse_init( &xportethse, &xportethse_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Reset Device to Monitor Mode <<<\r\n" );
    xportethse_reset_device ( &xportethse );
    xportethse_send_enter ( &xportethse );
    xportethse_send_cmd ( &xportethse, XPORTETHSE_CMD_MODE_MONITOR_WITH_NET );
    xportethse_read_response ( &xportethse );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Query Firmware Version <<<\r\n" );
    xportethse_send_cmd ( &xportethse, XPORTETHSE_CMD_QUERY_FW_VERSION );
    xportethse_read_response ( &xportethse );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Get MAC Address <<<\r\n" );
    xportethse_send_cmd ( &xportethse, XPORTETHSE_CMD_GET_MAC_ADDRESS );
    xportethse_read_response ( &xportethse );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Get Network Status and IP Address <<<\r\n" );
    log_printf( &logger, ">>> Send QU Command to Exit Monitor Mode and Connect to Listed <<<\r\n" );
    log_printf( &logger, ">>> IP Address Through Web Browser to Access Web Interface <<<\r\n" );
    xportethse_send_cmd ( &xportethse, XPORTETHSE_CMD_NET_STAT );
    xportethse_read_response ( &xportethse );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Ping 8.8.8.8 and Switch to UART Terminal Commands Input <<<\r\n" );
    xportethse_send_cmd ( &xportethse, XPORTETHSE_CMD_PING( "8.8.8.8" ) );
    xportethse_send_enter ( &xportethse );
    xportethse_read_response ( &xportethse );
}

void application_task ( void ) 
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &xportethse.uart, app_buf, app_buf_len );
        xportethse_clear_app_buf ( );
    }
    app_buf_len = uart_read( &xportethse.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        xportethse_clear_app_buf ( );
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

static void xportethse_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void xportethse_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t xportethse_process ( xportethse_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = xportethse_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
                log_printf( &logger, "%c", rx_buf[ rx_cnt ] );
            }
        }
        return XPORTETHSE_OK;
    }
    return XPORTETHSE_ERROR;
}

static err_t xportethse_read_response ( xportethse_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 30000;
    xportethse_clear_app_buf ( );
    while ( ( 0 == strstr( app_buf, XPORTETHSE_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, XPORTETHSE_RSP_NO_ANSWER ) ) && 
            ( 0 == strstr( app_buf, XPORTETHSE_RSP_NO_REACH ) ) && 
            ( 0 == strstr( app_buf, XPORTETHSE_RSP_WRONG_PAR ) ) && 
            ( 0 == strstr( app_buf, XPORTETHSE_RSP_INVALID_CMD ) ) )
    {
        Delay_ms ( 1 );
        xportethse_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            return XPORTETHSE_ERROR_TIMEOUT;
        }
    }
    timeout_cnt = 0;
    timeout = 50;
    xportethse_clear_app_buf ( );
    while ( timeout_cnt++ < timeout )
    {
        if ( XPORTETHSE_OK == xportethse_process( ctx ) )
        {
            timeout_cnt = 0;
        }
        Delay_ms ( 1 );
    }
    xportethse_clear_app_buf ( );
    return XPORTETHSE_OK;
}

// ------------------------------------------------------------------------ END
