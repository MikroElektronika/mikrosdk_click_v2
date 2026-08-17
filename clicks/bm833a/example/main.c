/*!
 * @file main.c
 * @brief BM833A Click Example.
 *
 * # Description
 * This example demonstrates the use of BM833A Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - BM833A_POWER_UP:
 * Powers up the device and reads the system information.
 *  - BM833A_CONFIG_EXAMPLE:
 * Sets the BT device name.
 *  - BM833A_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BT device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void bm833a_clear_app_buf ( void )
 * - static void bm833a_log_app_buf ( void )
 * - static err_t bm833a_process ( bm833a_t *ctx )
 * - static err_t bm833a_read_response ( bm833a_t *ctx, uint8_t *rsp )
 * - static err_t bm833a_power_up ( bm833a_t *ctx )
 * - static err_t bm833a_config_example ( bm833a_t *ctx )
 * - static err_t bm833a_example ( bm833a_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bm833a.h"
#include "generic_pointer.h"

#ifndef MIKROBUS_POSITION_BM833A
    #define MIKROBUS_POSITION_BM833A MIKROBUS_1
#endif

// Message content
#define MESSAGE_CONTENT     "BM833A Click board - demo example."

// Local device name.
#define DEVICE_NAME         "BM833A Click"

// Application buffer size
#define APP_BUFFER_SIZE     600
#define PROCESS_BUFFER_SIZE 200

static bm833a_t bm833a;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    BM833A_POWER_UP = 1,
    BM833A_CONFIG_EXAMPLE,
    BM833A_EXAMPLE

} bm833a_app_state_t;

static bm833a_app_state_t app_state = BM833A_POWER_UP;

/**
 * @brief BM833A clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void bm833a_clear_app_buf ( void );

/**
 * @brief BM833A log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void bm833a_log_app_buf ( void );

/**
 * @brief BM833A data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bm833a_process ( bm833a_t *ctx );

/**
 * @brief BM833A read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bm833a_read_response ( bm833a_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief BM833A power up function.
 * @details This function powers up the device, and reads the system information.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bm833a_power_up ( bm833a_t *ctx );

/**
 * @brief BM833A config example function.
 * @details This function sets the BT device name.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bm833a_config_example ( bm833a_t *ctx );

/**
 * @brief BM833A example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BT device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #bm833a_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bm833a_example ( bm833a_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bm833a_cfg_t bm833a_cfg;  /**< Click config object. */

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
    bm833a_cfg_setup( &bm833a_cfg );
    BM833A_MAP_MIKROBUS( bm833a_cfg, MIKROBUS_POSITION_BM833A );
    if ( UART_ERROR == bm833a_init( &bm833a, &bm833a_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = BM833A_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case BM833A_POWER_UP:
        {
            if ( BM833A_OK == bm833a_power_up( &bm833a ) )
            {
                app_state = BM833A_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BM833A_CONFIG_EXAMPLE:
        {
            if ( BM833A_OK == bm833a_config_example( &bm833a ) )
            {
                app_state = BM833A_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BM833A_EXAMPLE:
        {
            bm833a_example( &bm833a );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
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

static void bm833a_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void bm833a_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t bm833a_process ( bm833a_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = bm833a_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return BM833A_OK;
    }
    return BM833A_ERROR;
}

static err_t bm833a_read_response ( bm833a_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    bm833a_clear_app_buf ( );
    bm833a_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, BM833A_RSP_FAIL ) ) )
    {
        bm833a_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            bm833a_log_app_buf( );
            bm833a_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return BM833A_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    bm833a_process( ctx );
    bm833a_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return BM833A_OK;
    }
    return BM833A_ERROR_CMD;
}

static err_t bm833a_power_up ( bm833a_t *ctx )
{
    err_t error_flag = BM833A_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    bm833a_set_cmd_mode( &bm833a );
    bm833a_reset_device( &bm833a );
    bm833a_wakeup_device( &bm833a );
    while ( BM833A_OK == bm833a_process( ctx ) )
    {
        bm833a_log_app_buf( );
        bm833a_clear_app_buf ( );
    }
    log_printf( &logger, "--------------------------------\r\n" );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    bm833a_cmd_run( &bm833a, BM833A_CMD_DEFAULT_RESET );
    error_flag |= bm833a_read_response( &bm833a, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_RESET );

    log_printf( &logger, ">>> Check communication.\r\n" );
    bm833a_cmd_run( &bm833a, BM833A_CMD_AT );
    error_flag |= bm833a_read_response( &bm833a, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get software version.\r\n" );
    bm833a_cmd_get( ctx, BM833A_CMD_GET_SW_VERSION );
    error_flag |= bm833a_read_response( ctx, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Get MAC address.\r\n" );
    bm833a_cmd_get( ctx, BM833A_CMD_GET_MAC );
    error_flag |= bm833a_read_response( ctx, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t bm833a_config_example ( bm833a_t *ctx )
{
    err_t error_flag = BM833A_OK;

    log_printf( &logger, ">>> Set device name to \"%s\".\r\n", ( char * ) DEVICE_NAME );
    bm833a_cmd_set( ctx, BM833A_CMD_DEVICE_NAME, DEVICE_NAME );
    error_flag |= bm833a_read_response( ctx, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_DEFAULT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Save settings.\r\n" );
    bm833a_cmd_set( &bm833a, BM833A_CMD_SAVE_SETTINGS, "1" );
    error_flag |= bm833a_read_response( ctx, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Reboot.\r\n" );
    bm833a_cmd_run( ctx, BM833A_CMD_RESET );
    error_flag |= bm833a_read_response( ctx, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_RESET );
    
    return error_flag;
}

static err_t bm833a_example ( bm833a_t *ctx )
{
    err_t error_flag = BM833A_OK;
    uint32_t timeout_cnt = 0;
    uint8_t data_len = 0;
    uint8_t byte_cnt = 0;
    uint8_t * __generic_ptr start_ptr = NULL;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    #define TERMINATION_CMD             "END"
    #define TERMINATION_RESPONSE        "END command received, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT         "Timeout, closing the connection in a few seconds."
    #define NEW_LINE_STRING             "\r\n"
    
    log_printf( &logger, ">>> Waiting for a BT peer to establish connection with the Click board...\r\n" );
    while ( BM833A_OK != bm833a_read_response( ctx, BM833A_URC_CONNECTED, BM833A_MAX_RSP_TIME_BLE_CONNECT ) );

    bm833a_set_data_mode( &bm833a );

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        bm833a_clear_app_buf( );
        if ( BM833A_OK == bm833a_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            bm833a_process( ctx );
            bm833a_log_app_buf( );
            start_ptr = strstr( app_buf, BM833A_URC_RECEIVE );
            if ( start_ptr )
            {
                start_ptr += strlen ( BM833A_URC_RECEIVE );
                data_len = *start_ptr;
                log_printf( &logger, "<<< Received data (HEX): " );
                for ( byte_cnt = 0; byte_cnt < data_len; byte_cnt++ )
                {
                    log_printf( &logger, "0x%.2X ", *( start_ptr + byte_cnt + 1 ) );
                }
                log_printf( &logger, "\r\n" );
                log_printf( &logger, "<<< Received data (STR): %s", ( start_ptr + 1 ) );
                log_printf( &logger, "--------------------------------\r\n" );
            }
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminating connection on demand.\r\n" );
                data_len = strlen ( TERMINATION_RESPONSE ) + strlen ( NEW_LINE_STRING );
                bm833a_generic_write ( ctx, &data_len, 1 );
                bm833a_generic_write ( ctx, TERMINATION_RESPONSE, strlen ( TERMINATION_RESPONSE ) );
                bm833a_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
                Delay_ms ( 100 );
                error_flag |= bm833a_read_response( ctx, BM833A_RSP_SEND, BM833A_MAX_RSP_TIME_DEFAULT );

                log_printf( &logger, ">>> Disconnecting BT peer.\r\n" );
                bm833a_set_cmd_mode( &bm833a );
                bm833a_cmd_set( ctx, BM833A_CMD_DISCONNECT, "1" );
                error_flag |= bm833a_read_response( ctx, BM833A_URC_DISCONNECTED, BM833A_MAX_RSP_TIME_DEFAULT );
                break;
            }
            else if ( strstr( app_buf, BM833A_URC_DISCONNECTED ) )
            {
                log_printf( &logger, ">>> BT peer has disconnected.\r\n" );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            data_len = strlen ( MESSAGE_CONTENT ) + strlen ( NEW_LINE_STRING );
            bm833a_generic_write ( ctx, &data_len, 1 );
            bm833a_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            bm833a_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            Delay_ms ( 100 );
            error_flag |= bm833a_read_response( ctx, BM833A_RSP_SEND, BM833A_MAX_RSP_TIME_DEFAULT );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminating connection due to 60s timeout expiration.\r\n" );
            data_len = strlen ( TERMINATION_TIMEOUT ) + strlen ( NEW_LINE_STRING );
            bm833a_generic_write ( ctx, &data_len, 1 );
            bm833a_generic_write ( ctx, TERMINATION_TIMEOUT, strlen ( TERMINATION_TIMEOUT ) );
            bm833a_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            Delay_ms ( 100 );
            error_flag |= bm833a_read_response( ctx, BM833A_RSP_SEND, BM833A_MAX_RSP_TIME_DEFAULT );

            log_printf( &logger, ">>> Disconnecting BT peer.\r\n" );
            bm833a_set_cmd_mode( &bm833a );
            bm833a_cmd_set( ctx, BM833A_CMD_DISCONNECT, "1" );
            error_flag |= bm833a_read_response( ctx, BM833A_URC_DISCONNECTED, BM833A_MAX_RSP_TIME_DEFAULT );
            break;
        }
        Delay_ms ( 1 );
    }

    log_printf( &logger, ">>> Reboot.\r\n" );
    bm833a_cmd_run( ctx, BM833A_CMD_RESET );
    error_flag |= bm833a_read_response( ctx, BM833A_RSP_OK, BM833A_MAX_RSP_TIME_RESET );
    
    return error_flag;
}

// ------------------------------------------------------------------------ END
