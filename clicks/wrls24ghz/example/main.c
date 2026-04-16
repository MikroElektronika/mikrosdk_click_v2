/*!
 * @file main.c
 * @brief WRLS 2.4GHz Click Example.
 *
 * # Description
 * This example demonstrates the use of WRLS 2.4GHz Click board by processing data
 * from a connected BLE device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - WRLS24GHZ_POWER_UP:
 * Powers up the device, reads software version, and restores factory settings.
 *  - WRLS24GHZ_CONFIG_EXAMPLE:
 * Sets sleep timeout and BT device name, and reads the BT address.
 *  - WRLS24GHZ_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BLE device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void wrls24ghz_clear_app_buf ( void )
 * - static void wrls24ghz_log_app_buf ( void )
 * - static err_t wrls24ghz_process ( wrls24ghz_t *ctx )
 * - static err_t wrls24ghz_read_response ( wrls24ghz_t *ctx, uint8_t *rsp )
 * - static err_t wrls24ghz_power_up ( wrls24ghz_t *ctx )
 * - static err_t wrls24ghz_config_example ( wrls24ghz_t *ctx )
 * - static err_t wrls24ghz_example ( wrls24ghz_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "wrls24ghz.h"

#ifndef MIKROBUS_POSITION_WRLS24GHZ
    #define MIKROBUS_POSITION_WRLS24GHZ MIKROBUS_1
#endif

// Device name
#define DEVICE_NAME             "WRLS 2.4GHz Click"

// Message content
#define MESSAGE_CONTENT         "WRLS 2.4GHz Click board - demo example."

// Application buffer size
#define APP_BUFFER_SIZE         600
#define PROCESS_BUFFER_SIZE     200

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    WRLS24GHZ_POWER_UP = 1,
    WRLS24GHZ_CONFIG_EXAMPLE,
    WRLS24GHZ_EXAMPLE

} wrls24ghz_app_state_t;

static wrls24ghz_t wrls24ghz;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static wrls24ghz_app_state_t app_state = WRLS24GHZ_POWER_UP;

/**
 * @brief WRLS 2.4GHz clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void wrls24ghz_clear_app_buf ( void );

/**
 * @brief WRLS 2.4GHz log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void wrls24ghz_log_app_buf ( void );

/**
 * @brief WRLS 2.4GHz data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wrls24ghz_process ( wrls24ghz_t *ctx );

/**
 * @brief WRLS 2.4GHz read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wrls24ghz_read_response ( wrls24ghz_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief WRLS 2.4GHz power up function.
 * @details This function powers up the device, reads software version, and restores factory settings.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wrls24ghz_power_up ( wrls24ghz_t *ctx );

/**
 * @brief WRLS 2.4GHz config connection function.
 * @details This function sets sleep timeout and BT device name, and reads the BT address.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wrls24ghz_config_example ( wrls24ghz_t *ctx );

/**
 * @brief WRLS 2.4GHz example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BLE device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #wrls24ghz_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t wrls24ghz_example ( wrls24ghz_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wrls24ghz_cfg_t wrls24ghz_cfg;  /**< Click config object. */

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
    wrls24ghz_cfg_setup( &wrls24ghz_cfg );
    WRLS24GHZ_MAP_MIKROBUS( wrls24ghz_cfg, MIKROBUS_POSITION_WRLS24GHZ );
    if ( UART_ERROR == wrls24ghz_init( &wrls24ghz, &wrls24ghz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = WRLS24GHZ_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case WRLS24GHZ_POWER_UP:
        {
            if ( WRLS24GHZ_OK == wrls24ghz_power_up( &wrls24ghz ) )
            {
                app_state = WRLS24GHZ_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WRLS24GHZ_CONFIG_EXAMPLE:
        {
            if ( WRLS24GHZ_OK == wrls24ghz_config_example( &wrls24ghz ) )
            {
                app_state = WRLS24GHZ_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WRLS24GHZ_EXAMPLE:
        {
            wrls24ghz_example( &wrls24ghz );
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

static void wrls24ghz_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void wrls24ghz_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t wrls24ghz_process ( wrls24ghz_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = wrls24ghz_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return WRLS24GHZ_OK;
    }
    return WRLS24GHZ_ERROR;
}

static err_t wrls24ghz_read_response ( wrls24ghz_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    wrls24ghz_clear_app_buf ( );
    wrls24ghz_process( ctx );
    while ( 0 == strstr( app_buf, rsp ) )
    {
        wrls24ghz_process( ctx );
        if ( WRLS24GHZ_WAIT_TIMEOUT_INFINITE != max_rsp_time )
        {
            if ( timeout_cnt++ > max_rsp_time )
            {
                wrls24ghz_log_app_buf( );
                wrls24ghz_clear_app_buf( );
                log_error( &logger, " Timeout!" );
                return WRLS24GHZ_ERROR;
            }
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    wrls24ghz_process( ctx );
    wrls24ghz_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "\r\n--------------------------------\r\n" );
        return WRLS24GHZ_OK;
    }
    return WRLS24GHZ_ERROR;
}

static err_t wrls24ghz_power_up ( wrls24ghz_t *ctx )
{
    err_t error_flag = WRLS24GHZ_OK;

    log_printf( &logger, ">>> Reset device.\r\n" );
    wrls24ghz_reset_device ( ctx );
    
    log_printf( &logger, ">>> Read software version.\r\n" );
    wrls24ghz_send_cmd ( ctx, WRLS24GHZ_CMD_READ_SOFT_VERSION );
    error_flag |= wrls24ghz_read_response( ctx, "rd_soft_version", WRLS24GHZ_WAIT_TIMEOUT_5000MS );

    log_printf( &logger, ">>> Reset to factory settings.\r\n" );
    wrls24ghz_send_cmd( ctx, WRLS24GHZ_CMD_FACTORY_RESET );
    error_flag |= wrls24ghz_read_response( ctx, "st_factory", WRLS24GHZ_WAIT_TIMEOUT_10000MS );

    return error_flag;
}

static err_t wrls24ghz_config_example ( wrls24ghz_t *ctx )
{
    err_t error_flag = WRLS24GHZ_OK;

    log_printf( &logger, ">>> Set sleep delay to 10s.\r\n" );
    #define SLEEP_DELAY "100" // 0.1 seconds step
    wrls24ghz_send_cmd ( ctx, WRLS24GHZ_CMD_SET_SLEEP_DELAY( SLEEP_DELAY ) );
    error_flag |= wrls24ghz_read_response( ctx, "st_sleep_delay", WRLS24GHZ_WAIT_TIMEOUT_5000MS );

    log_printf( &logger, ">>> Set BLE device name to \"%s\".\r\n", ( char * ) DEVICE_NAME );
    wrls24ghz_send_cmd ( ctx, WRLS24GHZ_CMD_SET_NAME( DEVICE_NAME ) );
    error_flag |= wrls24ghz_read_response( ctx, "st_name", WRLS24GHZ_WAIT_TIMEOUT_5000MS );

    log_printf( &logger, ">>> Read MAC address.\r\n" );
    wrls24ghz_send_cmd ( ctx, WRLS24GHZ_CMD_READ_MAC );
    error_flag |= wrls24ghz_read_response( ctx, "rd_ble_mac", WRLS24GHZ_WAIT_TIMEOUT_5000MS );

    return error_flag;
}

static err_t wrls24ghz_example ( wrls24ghz_t *ctx )
{
    err_t error_flag = WRLS24GHZ_OK;
    uint32_t timeout_cnt = 0;

    #define BLE_TERMINAL_TIMEOUT_MS         60000
    #define BLE_TERMINAL_MESSAGE_FREQ_MS    5000
    #define TERMINATION_CMD                 "END"
    #define TERMINATION_RESPONSE            "Acknowledged, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT             "Timeout, closing the connection in a few seconds."
    #define NEW_LINE_STRING                 "\r\n"

    log_printf( &logger, ">>> Read BLE device name.\r\n" );
    wrls24ghz_send_cmd( ctx, WRLS24GHZ_CMD_READ_NAME );
    error_flag |= wrls24ghz_read_response( ctx, "rd_name", WRLS24GHZ_WAIT_TIMEOUT_5000MS );

    log_printf( &logger, ">>> Waiting for a BLE peer to establish connection with the Click board...\r\n" );
    while ( !wrls24ghz_get_status_pin( ctx ) );

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    wrls24ghz_wake_uart ( ctx );
    for ( ; ; )
    {
        wrls24ghz_clear_app_buf( );
        if ( !wrls24ghz_get_status_pin( ctx ) )
        {
            log_printf( &logger, ">>> BLE client has terminated the connection.\r\n" );
            break;
        }
        if ( WRLS24GHZ_OK == wrls24ghz_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            wrls24ghz_process( ctx );
            wrls24ghz_log_app_buf( );
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminate connection on demand.\r\n" );
                wrls24ghz_generic_write ( ctx, TERMINATION_RESPONSE, strlen ( TERMINATION_RESPONSE ) );
                wrls24ghz_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
                Delay_ms ( 1000 );
                
                log_printf( &logger, ">>> Disconnect BLE device.\r\n" );
                wrls24ghz_send_cmd( ctx, WRLS24GHZ_CMD_DISCONNECT_LINK );
                error_flag |= wrls24ghz_read_response( ctx, "st_disconnect_link", WRLS24GHZ_WAIT_TIMEOUT_5000MS );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BLE_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            wrls24ghz_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            wrls24ghz_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
        }
        if ( BLE_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminate connection due to 60s timeout expiration.\r\n" );
            wrls24ghz_generic_write ( ctx, TERMINATION_TIMEOUT, strlen ( TERMINATION_TIMEOUT ) );
            wrls24ghz_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            Delay_ms ( 1000 );
            log_printf( &logger, ">>> Disconnect BLE device.\r\n" );
            wrls24ghz_send_cmd( ctx, WRLS24GHZ_CMD_DISCONNECT_LINK );
            error_flag |= wrls24ghz_read_response( ctx, "st_disconnect_link", WRLS24GHZ_WAIT_TIMEOUT_5000MS );
            break;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 1000 );
    return error_flag;
}

// ------------------------------------------------------------------------ END
