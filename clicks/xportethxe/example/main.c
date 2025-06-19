/*!
 * @file main.c
 * @brief XPort ETH XE Click Example.
 *
 * # Description
 * This example demonstrates the use of the XPort ETH XE Click board for Ethernet communication. 
 * The application initializes the XPort ETH XE module, retrieves essential information such as 
 * firmware version, MAC address, and network status, and demonstrates sending a ping command. 
 * It also allows for bidirectional UART communication between the USB UART and the XPort ETH XE UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the UART communication, logs essential information, configures the XPort ETH XE module, 
 * and retrieves the firmware version, MAC address, and network status. It also demonstrates basic 
 * command operations such as pinging the specific IP address (8.8.8.8).
 *
 * ## Application Task
 * Continuously reads data from the USB UART and forwards it to the XPort ETH XE module, 
 * while also capturing responses from the module and forwarding them back to the USB UART.
 * This allows real-time interaction with the device through the UART Terminal for
 * configuration and diagnostics.
 *
 * ## Additional Function
 * - static void xportethxe_clear_app_buf ( void )
 * - static err_t xportethxe_process ( xportethxe_t *ctx )
 * - static err_t xportethxe_read_response ( xportethxe_t *ctx )
 *
 * @note
 * Ensure the XPort ETH XE Click board is properly connected to the network.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "xportethxe.h"

// Application buffer size
#define APP_BUFFER_SIZE             300
#define PROCESS_BUFFER_SIZE         100

static xportethxe_t xportethxe;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief XPort ETH XE clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void xportethxe_clear_app_buf ( void );

/**
 * @brief XPort ETH XE data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #xportethxe_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xportethxe_process ( xportethxe_t *ctx );

/**
 * @brief XPort ETH XE read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #xportethxe_t object definition for detailed explanation.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t xportethxe_read_response ( xportethxe_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xportethxe_cfg_t xportethxe_cfg;  /**< Click config object. */

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
    xportethxe_cfg_setup( &xportethxe_cfg );
    XPORTETHXE_MAP_MIKROBUS( xportethxe_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xportethxe_init( &xportethxe, &xportethxe_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Reset Device to Monitor Mode <<<\r\n" );
    xportethxe_reset_device ( &xportethxe );
    xportethxe_send_enter ( &xportethxe );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_MODE_MONITOR_WITH_NET );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Query Firmware Version <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_QUERY_FW_VERSION );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Get MAC Address <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_GET_MAC_ADDRESS );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Get Network Status and IP Address <<<\r\n" );
    log_printf( &logger, ">>> Send QU Command to Exit Monitor Mode and Connect to Listed <<<\r\n" );
    log_printf( &logger, ">>> IP Address Through Web Browser to Access Web Interface <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_NET_STAT );
    xportethxe_read_response ( &xportethxe );

    log_printf( &logger, "\r\n-----------------------------\r\n" );
    log_printf( &logger, ">>> Ping 8.8.8.8 and Switch to UART Terminal Commands Input <<<\r\n" );
    xportethxe_send_cmd ( &xportethxe, XPORTETHXE_CMD_PING( "8.8.8.8" ) );
    xportethxe_send_enter ( &xportethxe );
    xportethxe_read_response ( &xportethxe );
}

void application_task ( void ) 
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &xportethxe.uart, app_buf, app_buf_len );
        xportethxe_clear_app_buf ( );
    }
    app_buf_len = uart_read( &xportethxe.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        xportethxe_clear_app_buf ( );
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

static void xportethxe_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void xportethxe_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t xportethxe_process ( xportethxe_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = xportethxe_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return XPORTETHXE_OK;
    }
    return XPORTETHXE_ERROR;
}

static err_t xportethxe_read_response ( xportethxe_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 30000;
    xportethxe_clear_app_buf ( );
    while ( ( 0 == strstr( app_buf, XPORTETHXE_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, XPORTETHXE_RSP_NO_ANSWER ) ) && 
            ( 0 == strstr( app_buf, XPORTETHXE_RSP_NO_REACH ) ) && 
            ( 0 == strstr( app_buf, XPORTETHXE_RSP_WRONG_PAR ) ) && 
            ( 0 == strstr( app_buf, XPORTETHXE_RSP_INVALID_CMD ) ) )
    {
        Delay_ms ( 1 );
        xportethxe_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            return XPORTETHXE_ERROR_TIMEOUT;
        }
    }
    timeout_cnt = 0;
    timeout = 50;
    xportethxe_clear_app_buf ( );
    while ( timeout_cnt++ < timeout )
    {
        if ( XPORTETHXE_OK == xportethxe_process( ctx ) )
        {
            timeout_cnt = 0;
        }
        Delay_ms ( 1 );
    }
    xportethxe_clear_app_buf ( );
    return XPORTETHXE_OK;
}

// ------------------------------------------------------------------------ END
