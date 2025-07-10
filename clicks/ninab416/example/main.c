/*!
 * @file main.c
 * @brief NINA-B416 Click Example.
 *
 * # Description
 * This example demonstrates the use of NINA-B416 Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - NINAB416_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *  - NINAB416_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BT device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void ninab416_clear_app_buf ( void )
 * - static void ninab416_log_app_buf ( void )
 * - static err_t ninab416_process ( ninab416_t *ctx )
 * - static err_t ninab416_read_response ( ninab416_t *ctx, uint8_t *rsp )
 * - static err_t ninab416_power_up ( ninab416_t *ctx )
 * - static err_t ninab416_example ( ninab416_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the Click board must be paired to exchange messages.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ninab416.h"

// Message content
#define MESSAGE_CONTENT         "NINA-B416 Click board - demo example."

static ninab416_t ninab416;
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
    NINAB416_POWER_UP = 1,
    NINAB416_EXAMPLE

} ninab416_app_state_t;

static ninab416_app_state_t app_state = NINAB416_POWER_UP;

/**
 * @brief NINA-B416 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ninab416_clear_app_buf ( void );

/**
 * @brief NINA-B416 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void ninab416_log_app_buf ( void );

/**
 * @brief NINA-B416 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ninab416_process ( ninab416_t *ctx );

/**
 * @brief NINA-B416 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ninab416_read_response ( ninab416_t *ctx, uint8_t *rsp );

/**
 * @brief NINA-B416 power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ninab416_power_up ( ninab416_t *ctx );

/**
 * @brief NINA-B416 example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BT device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ninab416_example ( ninab416_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ninab416_cfg_t ninab416_cfg;  /**< Click config object. */

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
    ninab416_cfg_setup( &ninab416_cfg );
    NINAB416_MAP_MIKROBUS( ninab416_cfg, MIKROBUS_1 );
    if ( NINAB416_OK != ninab416_init( &ninab416, &ninab416_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = NINAB416_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case NINAB416_POWER_UP:
        {
            if ( NINAB416_OK == ninab416_power_up( &ninab416 ) )
            {
                app_state = NINAB416_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NINAB416_EXAMPLE:
        {
            ninab416_example( &ninab416 );
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

static void ninab416_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ninab416_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ninab416_process ( ninab416_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ninab416_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return NINAB416_OK;
    }
    return NINAB416_ERROR;
}

static err_t ninab416_read_response ( ninab416_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS 120000
    uint32_t timeout_cnt = 0;
    ninab416_clear_app_buf ( );
    ninab416_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, NINAB416_RSP_ERROR ) ) )
    {
        ninab416_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            ninab416_log_app_buf( );
            ninab416_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return NINAB416_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 200 );
    ninab416_process( ctx );
    ninab416_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return NINAB416_OK;
    }
    return NINAB416_ERROR_CMD;
}

static err_t ninab416_power_up ( ninab416_t *ctx )
{
    err_t error_flag = NINAB416_OK;

    log_printf( &logger, ">>> Perform device hardware reset.\r\n" );
    ninab416_reset_device ( ctx );
    error_flag |= ninab416_read_response( ctx, NINAB416_URC_GREETING );
    
    log_printf( &logger, ">>> Check communication.\r\n" );
    ninab416_cmd_run( ctx, NINAB416_CMD_AT );
    error_flag |= ninab416_read_response( ctx, NINAB416_RSP_OK );

    log_printf( &logger, ">>> Reset to factory settings.\r\n" );
    ninab416_cmd_run( ctx, NINAB416_CMD_FACTORY_RESET );
    error_flag |= ninab416_read_response( ctx, NINAB416_RSP_OK );
    
    log_printf( &logger, ">>> Reboot device.\r\n" );
    ninab416_cmd_run( ctx, NINAB416_CMD_REBOOT_DEVICE );
    error_flag |= ninab416_read_response( ctx, NINAB416_URC_GREETING );

    log_printf( &logger, ">>> Get device software version ID.\r\n" );
    ninab416_cmd_run( ctx, NINAB416_CMD_GET_SW_VERSION );
    error_flag |= ninab416_read_response( ctx, NINAB416_RSP_OK );

    log_printf( &logger, ">>> Get BT local name.\r\n" );
    ninab416_cmd_get( ctx, NINAB416_CMD_BT_LOCAL_NAME );
    error_flag |= ninab416_read_response( ctx, NINAB416_RSP_OK );

    return error_flag;
}

static err_t ninab416_example ( ninab416_t *ctx )
{
    err_t error_flag = NINAB416_OK;
    uint8_t * __generic_ptr urc_buf_ptr = 0;
    uint8_t bt_peer_handle[ 2 ] = { 0 };
    uint32_t timeout_cnt = 0;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    #define TERMINATION_CMD             "END"
    #define TERMINATION_RESPONSE        "Acknowledged, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT         "Timeout, closing the connection in a few seconds."
    #define NEW_LINE_STRING             "\r\n"

    log_printf( &logger, ">>> Waiting for a BT peer to establish connection with the Click board...\r\n" );
    for ( ; ; )
    {
        ninab416_clear_app_buf( );
        if ( NINAB416_OK == ninab416_process( ctx ) )
        {
            Delay_ms ( 200 );
            ninab416_process( ctx );
            ninab416_log_app_buf( );
            if ( strstr( app_buf, NINAB416_URC_PEER_CONNECTED ) )
            {
                log_printf( &logger, "--------------------------------\r\n" );
                log_printf( &logger, ">>> BT peer has connected.\r\n" );
                break;
            }
        }
    }

    urc_buf_ptr = strstr( app_buf, NINAB416_URC_PEER_CONNECTED ) + strlen ( NINAB416_URC_PEER_CONNECTED );
    bt_peer_handle[ 0 ] = *urc_buf_ptr;

    log_printf( &logger, ">>> Entering data mode. URC and AT commands are not accepted in this mode.\r\n" );
    ninab416_cmd_run( ctx, NINAB416_CMD_ENTER_DATA_MODE );
    error_flag |= ninab416_read_response( ctx, NINAB416_RSP_OK );

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        ninab416_clear_app_buf( );
        if ( NINAB416_OK == ninab416_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            ninab416_process( ctx );
            ninab416_log_app_buf( );
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminate connection on demand.\r\n" );
                ninab416_generic_write ( ctx, TERMINATION_RESPONSE, strlen ( TERMINATION_RESPONSE ) );
                ninab416_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            ninab416_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            ninab416_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminate connection due to 60s timeout expiration.\r\n" );
            ninab416_generic_write ( ctx, TERMINATION_TIMEOUT, strlen ( TERMINATION_TIMEOUT ) );
            ninab416_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            break;
        }
        Delay_ms ( 1 );
    }
    log_printf( &logger, ">>> Switching back to command mode.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    ninab416_generic_write ( ctx, NINAB416_CMD_ENTER_CMD_MODE, strlen ( NINAB416_CMD_ENTER_CMD_MODE ) );
    error_flag |= ninab416_read_response( ctx, NINAB416_RSP_OK );
    
    log_printf( &logger, ">>> Closing BT peer connection.\r\n" );
    ninab416_cmd_set( ctx, NINAB416_CMD_CLOSE_PEER, bt_peer_handle );
    error_flag |= ninab416_read_response( ctx, NINAB416_RSP_OK );
    return error_flag;
}

// ------------------------------------------------------------------------ END
