/*!
 * @file main.c
 * @brief BT Audio 4 Click Example.
 *
 * # Description
 * This example demonstrates how to communicate with the BT Audio 4 Click board over UART.
 * It initializes the device, resets it, retrieves the device name, and then continuously
 * processes and logs any incoming UART messages from the device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the BT Audio 4 Click driver, performs a device reset,
 * and reads the device name.
 *
 * ## Application Task
 * Continuously processes UART data received from the Click board and logs it to the terminal.
 * Acts as a passive receiver of incoming messages, useful for monitoring notifications.
 *
 * ## Additional Function
 * - static void btaudio4_clear_app_buf ( void )
 * - static void btaudio4_log_app_buf ( void )
 * - static err_t btaudio4_process ( btaudio4_t *ctx )
 * - static err_t btaudio4_read_response ( btaudio4_t *ctx, uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "btaudio4.h"

// Application buffer size
#define APP_BUFFER_SIZE      200
#define PROCESS_BUFFER_SIZE  100

static btaudio4_t btaudio4;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief BT Audio 4 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void btaudio4_clear_app_buf ( void );

/**
 * @brief BT Audio 4 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void btaudio4_log_app_buf ( void );

/**
 * @brief BT Audio 4 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btaudio4_process ( btaudio4_t *ctx );

/**
 * @brief BT Audio 4 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #btaudio4_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t btaudio4_read_response ( btaudio4_t *ctx, uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btaudio4_cfg_t btaudio4_cfg;  /**< Click config object. */

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
    btaudio4_cfg_setup( &btaudio4_cfg );
    BTAUDIO4_MAP_MIKROBUS( btaudio4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btaudio4_init( &btaudio4, &btaudio4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Reset Device\r\n" );
    btaudio4_reset_device ( &btaudio4 );
    btaudio4_read_response ( &btaudio4, BTAUDIO4_RSP_READY );

    log_printf( &logger, ">>> Get Device Name\r\n" );
    btaudio4_cmd_get ( &btaudio4, BTAUDIO4_PARAM_NAME );
    btaudio4_read_response ( &btaudio4, BTAUDIO4_RSP_OK );
    btaudio4_clear_app_buf ( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( BTAUDIO4_OK == btaudio4_process ( &btaudio4 ) )
    {
        btaudio4_log_app_buf ( );
        btaudio4_clear_app_buf ( );
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

static void btaudio4_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void btaudio4_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t btaudio4_process ( btaudio4_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = btaudio4_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return BTAUDIO4_OK;
    }
    return BTAUDIO4_ERROR;
}

static err_t btaudio4_read_response ( btaudio4_t *ctx, uint8_t *rsp )
{
    #define READ_RESPONSE_TIMEOUT_MS 120000
    uint32_t timeout_cnt = 0;
    btaudio4_clear_app_buf ( );
    btaudio4_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, BTAUDIO4_RSP_ERROR ) ) )
    {
        btaudio4_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            btaudio4_log_app_buf( );
            btaudio4_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return BTAUDIO4_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 200 );
    btaudio4_process( ctx );
    btaudio4_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return BTAUDIO4_OK;
    }
    return BTAUDIO4_ERROR_CMD;
}

// ------------------------------------------------------------------------ END
