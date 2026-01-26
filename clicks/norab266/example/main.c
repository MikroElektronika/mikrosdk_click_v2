/*!
 * @file main.c
 * @brief NORA-B266 Click Example.
 *
 * # Description
 * This example demonstrates the use of NORA-B266 Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - NORAB266_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *  - NORAB266_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BT device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void norab266_clear_app_buf ( void )
 * - static void norab266_log_app_buf ( void )
 * - static err_t norab266_process ( norab266_t *ctx )
 * - static err_t norab266_read_response ( norab266_t *ctx, uint8_t *rsp )
 * - static err_t norab266_power_up ( norab266_t *ctx )
 * - static err_t norab266_example ( norab266_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "norab266.h"

// Message content
#define MESSAGE_CONTENT         "NORA-B266 Click board - demo example."

static norab266_t norab266;
static log_t logger;

// Application buffer size
#define APP_BUFFER_SIZE         600
#define PROCESS_BUFFER_SIZE     200

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    NORAB266_POWER_UP = 1,
    NORAB266_EXAMPLE

} norab266_app_state_t;

static norab266_app_state_t app_state = NORAB266_POWER_UP;

/**
 * @brief NORA-B266 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void norab266_clear_app_buf ( void );

/**
 * @brief NORA-B266 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void norab266_log_app_buf ( void );

/**
 * @brief NORA-B266 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t norab266_process ( norab266_t *ctx );

/**
 * @brief NORA-B266 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t norab266_read_response ( norab266_t *ctx, uint8_t *rsp );

/**
 * @brief NORA-B266 power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t norab266_power_up ( norab266_t *ctx );

/**
 * @brief NORA-B266 example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BT device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t norab266_example ( norab266_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    norab266_cfg_t norab266_cfg;  /**< Click config object. */

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
    norab266_cfg_setup( &norab266_cfg );
    NORAB266_MAP_MIKROBUS( norab266_cfg, MIKROBUS_1 );
    if ( NORAB266_OK != norab266_init( &norab266, &norab266_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = NORAB266_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case NORAB266_POWER_UP:
        {
            if ( NORAB266_OK == norab266_power_up( &norab266 ) )
            {
                app_state = NORAB266_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NORAB266_EXAMPLE:
        {
            norab266_example( &norab266 );
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

static void norab266_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void norab266_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t norab266_process ( norab266_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = norab266_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return NORAB266_OK;
    }
    return NORAB266_ERROR;
}

static err_t norab266_read_response ( norab266_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS 120000
    uint32_t timeout_cnt = 0;
    norab266_clear_app_buf ( );
    norab266_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, NORAB266_RSP_ERROR ) ) )
    {
        norab266_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            norab266_log_app_buf( );
            norab266_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return NORAB266_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 200 );
    norab266_process( ctx );
    norab266_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return NORAB266_OK;
    }
    return NORAB266_ERROR_CMD;
}

static err_t norab266_power_up ( norab266_t *ctx )
{
    err_t error_flag = NORAB266_OK;

    log_printf( &logger, ">> Perform device hardware reset.\r\n" );
    norab266_reset_device ( ctx );
    error_flag |= norab266_read_response( ctx, NORAB266_URC_GREETING );
    
    log_printf( &logger, ">> Check communication.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_AT );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

    log_printf( &logger, ">> Get device software version ID.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_GET_SW_VERSION );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

    log_printf( &logger, ">> Reset to factory settings.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_FACTORY_RESET );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

    log_printf( &logger, ">> Save settings.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_SAVE_CONFIG );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );
    
    log_printf( &logger, ">> Reboot device.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_REBOOT_DEVICE );
    error_flag |= norab266_read_response( ctx, NORAB266_URC_GREETING );

    log_printf( &logger, ">> Enable SPS service.\r\n" );
    norab266_cmd_set( ctx, NORAB266_CMD_SET_SPS_SERVICE_STATE, "1" );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

    log_printf( &logger, ">> Set SPS direct string receive mode.\r\n" );
    norab266_cmd_set( ctx, NORAB266_CMD_SET_SPS_RECEIVE_MODE, "1" );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

    log_printf( &logger, ">> Save settings.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_SAVE_CONFIG );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );
    
    log_printf( &logger, ">> Reboot device.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_REBOOT_DEVICE );
    error_flag |= norab266_read_response( ctx, NORAB266_URC_GREETING );

    log_printf( &logger, ">> Start legacy advertisements.\r\n" );
    norab266_cmd_run( ctx, NORAB266_CMD_START_LEGACY_ADV );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

    return error_flag;
}

static err_t norab266_example ( norab266_t *ctx )
{
    err_t error_flag = NORAB266_OK;
    uint8_t * __generic_ptr urc_buf_ptr = 0;
    uint8_t bt_peer_handle[ 2 ] = { 0 };
    uint8_t sps_string[ 100 ] = { 0 };
    uint32_t timeout_cnt = 0;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    #define TERMINATION_CMD             "END"
    #define TERMINATION_RESPONSE        "Acknowledged, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT         "Timeout, closing the connection in a few seconds."
    #define NEW_LINE_STRING             "\\r\\n"

    log_printf( &logger, ">> Get BT local name.\r\n" );
    norab266_cmd_get( ctx, NORAB266_CMD_BT_LOCAL_NAME );
    error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

    log_printf( &logger, ">> Waiting for a BT SPS to establish connection with the Click board...\r\n" );
    for ( ; ; )
    {
        norab266_clear_app_buf( );
        if ( NORAB266_OK == norab266_process( ctx ) )
        {
            Delay_ms ( 200 );
            norab266_process( ctx );
            norab266_log_app_buf( );
            if ( strstr( app_buf, NORAB266_URC_SPS_CONNECTED ) )
            {
                log_printf( &logger, "--------------------------------\r\n" );
                log_printf( &logger, ">> BT SPS has connected.\r\n" );
                break;
            }
        }
    }

    urc_buf_ptr = strstr( app_buf, NORAB266_URC_SPS_CONNECTED ) + strlen ( NORAB266_URC_SPS_CONNECTED );
    bt_peer_handle[ 0 ] = *urc_buf_ptr;

    log_printf( &logger, ">> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        norab266_clear_app_buf( );
        if ( NORAB266_OK == norab266_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            norab266_process( ctx );
            norab266_log_app_buf( );
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">> Terminate connection on demand.\r\n" );
                strcpy ( sps_string, bt_peer_handle );
                strcat ( sps_string, ",\"" );
                strcat ( sps_string, TERMINATION_RESPONSE );
                strcat ( sps_string, NEW_LINE_STRING );
                strcat ( sps_string, "\"" );
                norab266_cmd_set( ctx, NORAB266_CMD_SPS_WRITE_STRING, sps_string );
                error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

                log_printf( &logger, ">> Closing BT peer connection.\r\n" );
                norab266_cmd_set( ctx, NORAB266_CMD_CLOSE_CONNECTION, bt_peer_handle );
                error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );
                break;
            }
            else if ( strstr( app_buf, NORAB266_URC_SPS_DISCONNECTED ) )
            {
                log_printf( &logger, ">> BT SPS has disconnected.\r\n" );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            strcpy ( sps_string, bt_peer_handle );
            strcat ( sps_string, ",\"" );
            strcat ( sps_string, MESSAGE_CONTENT );
            strcat ( sps_string, NEW_LINE_STRING );
            strcat ( sps_string, "\"" );
            norab266_cmd_set( ctx, NORAB266_CMD_SPS_WRITE_STRING, sps_string );
            error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">> Terminate connection due to 60s timeout expiration.\r\n" );
            strcpy ( sps_string, bt_peer_handle );
            strcat ( sps_string, ",\"" );
            strcat ( sps_string, TERMINATION_TIMEOUT );
            strcat ( sps_string, NEW_LINE_STRING );
            strcat ( sps_string, "\"" );
            norab266_cmd_set( ctx, NORAB266_CMD_SPS_WRITE_STRING, sps_string );
            error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );

            log_printf( &logger, ">> Closing BT peer connection.\r\n" );
            norab266_cmd_set( ctx, NORAB266_CMD_CLOSE_CONNECTION, bt_peer_handle );
            error_flag |= norab266_read_response( ctx, NORAB266_RSP_OK );
            break;
        }
        Delay_ms ( 1 );
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
