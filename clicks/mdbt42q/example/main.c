/*!
 * @file main.c
 * @brief MDBT42Q Click Example.
 *
 * # Description
 * This example demonstrates the use of MDBT42Q Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - MDBT42Q_POWER_UP:
 * Powers up the device, performs a factory reset and reads system information.
 *  - MDBT42Q_CONFIG_EXAMPLE:
 * Sets the BT device name.
 *  - MDBT42Q_EXAMPLE:
 * Performs a BT terminal example by processing all data from a connected BT device 
 * and sending back an adequate response messages.
 *
 * ## Additional Function
 * - static void mdbt42q_clear_app_buf ( void )
 * - static void mdbt42q_log_app_buf ( void )
 * - static err_t mdbt42q_process ( mdbt42q_t *ctx )
 * - static err_t mdbt42q_read_response ( mdbt42q_t *ctx )
 * - static err_t mdbt42q_power_up ( mdbt42q_t *ctx )
 * - static err_t mdbt42q_config_example ( mdbt42q_t *ctx )
 * - static err_t mdbt42q_example ( mdbt42q_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mdbt42q.h"

// Message content
#define MESSAGE_CONTENT         "MDBT42Q Click board - demo example."

// Device name.
#define DEVICE_NAME             "MDBT42Q Click"

static mdbt42q_t mdbt42q;
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
    MDBT42Q_POWER_UP = 1,
    MDBT42Q_CONFIG_EXAMPLE,
    MDBT42Q_EXAMPLE

} mdbt42q_app_state_t;

static mdbt42q_app_state_t app_state = MDBT42Q_POWER_UP;

/**
 * @brief MDBT42Q clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void mdbt42q_clear_app_buf ( void );

/**
 * @brief MDBT42Q log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void mdbt42q_log_app_buf ( void );

/**
 * @brief MDBT42Q data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mdbt42q_process ( mdbt42q_t *ctx );

/**
 * @brief MDBT42Q read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mdbt42q_read_response ( mdbt42q_t *ctx );

/**
 * @brief MDBT42Q power up function.
 * @details This function powers up the device, performs a factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mdbt42q_power_up ( mdbt42q_t *ctx );

/**
 * @brief MDBT42Q config example function.
 * @details This function sets the BT device name.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mdbt42q_config_example ( mdbt42q_t *ctx );

/**
 * @brief MDBT42Q example function.
 * @details This function performs a BT terminal example by processing all data from
 * a connected BT device and sending back an adequate response messages.
 * @param[in] ctx : Click context object.
 * See #mdbt42q_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mdbt42q_example ( mdbt42q_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mdbt42q_cfg_t mdbt42q_cfg;  /**< Click config object. */

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
    mdbt42q_cfg_setup( &mdbt42q_cfg );
    MDBT42Q_MAP_MIKROBUS( mdbt42q_cfg, MIKROBUS_1 );
    if ( MDBT42Q_OK != mdbt42q_init( &mdbt42q, &mdbt42q_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = MDBT42Q_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case MDBT42Q_POWER_UP:
        {
            if ( MDBT42Q_OK == mdbt42q_power_up( &mdbt42q ) )
            {
                app_state = MDBT42Q_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case MDBT42Q_CONFIG_EXAMPLE:
        {
            if ( MDBT42Q_OK == mdbt42q_config_example( &mdbt42q ) )
            {
                app_state = MDBT42Q_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case MDBT42Q_EXAMPLE:
        {
            mdbt42q_example( &mdbt42q );
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

static void mdbt42q_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void mdbt42q_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t mdbt42q_process ( mdbt42q_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = mdbt42q_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return MDBT42Q_OK;
    }
    return MDBT42Q_ERROR;
}

static err_t mdbt42q_read_response ( mdbt42q_t *ctx ) 
{
    #define READ_RESPONSE_TIMEOUT_MS 60000
    uint32_t timeout_cnt = 0;
    mdbt42q_clear_app_buf ( );
    while ( MDBT42Q_ERROR == mdbt42q_process( ctx ) )
    {
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            log_error( &logger, " Timeout!" );
            return MDBT42Q_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 500 );
    mdbt42q_process( ctx );
    mdbt42q_log_app_buf( );
    log_printf( &logger, "\r\n--------------------------------\r\n" );
    return MDBT42Q_OK;
}

static err_t mdbt42q_power_up ( mdbt42q_t *ctx )
{
    err_t error_flag = MDBT42Q_OK;

    log_printf( &logger, ">>> Hardware reset.\r\n" );
    mdbt42q_reset_device ( ctx );
    
    log_printf( &logger, ">>> Restore default settings.\r\n" );
    mdbt42q_cmd_run( ctx, MDBT42Q_CMD_RESTORE_DEFAULT );
    error_flag |= mdbt42q_read_response( ctx );

    log_printf( &logger, ">>> Get version.\r\n" );
    mdbt42q_cmd_run( ctx, MDBT42Q_CMD_GET_VERSION );
    error_flag |= mdbt42q_read_response( ctx );

    return error_flag;
}

static err_t mdbt42q_config_example ( mdbt42q_t *ctx )
{
    err_t error_flag = MDBT42Q_OK;

    log_printf( &logger, ">>> Set device name.\r\n" );
    mdbt42q_cmd_set( ctx, MDBT42Q_CMD_SET_PARAM_DEVICE_NAME, DEVICE_NAME );
    error_flag |= mdbt42q_read_response( ctx );

    log_printf( &logger, ">>> Save settings.\r\n" );
    mdbt42q_cmd_run( ctx, MDBT42Q_CMD_RESET );
    error_flag |= mdbt42q_read_response( ctx );
    
    return error_flag;
}

static err_t mdbt42q_example ( mdbt42q_t *ctx )
{
    err_t error_flag = MDBT42Q_OK;
    uint32_t timeout_cnt = 0;

    #define BT_TERMINAL_TIMEOUT_MS      60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS 5000
    #define TERMINATION_CMD             "END"
    #define TERMINATION_RESPONSE        "Acknowledged, the connection will be terminated in a few seconds."
    #define TERMINATION_TIMEOUT         "Timeout, closing the connection in a few seconds."
    #define NEW_LINE_STRING             "\r\n"

    log_printf( &logger, ">>> Waiting for a BT peer to establish connection with the Click board...\r\n" );
    while ( mdbt42q_get_ind_pin ( ctx ) );

    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, ">>> BT peer has connected.\r\n" );

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; ; )
    {
        mdbt42q_clear_app_buf( );
        if ( MDBT42Q_OK == mdbt42q_process( ctx ) )
        {
            Delay_ms ( 100 );
            timeout_cnt = 0;
            mdbt42q_process( ctx );
            mdbt42q_log_app_buf( );
            if ( strstr( app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminate connection on demand.\r\n" );
                mdbt42q_generic_write ( ctx, TERMINATION_RESPONSE, strlen ( TERMINATION_RESPONSE ) );
                mdbt42q_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
                break;
            }
        }
        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) MESSAGE_CONTENT );
            mdbt42q_generic_write ( ctx, MESSAGE_CONTENT, strlen ( MESSAGE_CONTENT ) );
            mdbt42q_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
        }
        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminate connection due to 60s timeout expiration.\r\n" );
            mdbt42q_generic_write ( ctx, TERMINATION_TIMEOUT, strlen ( TERMINATION_TIMEOUT ) );
            mdbt42q_generic_write ( ctx, NEW_LINE_STRING, strlen ( NEW_LINE_STRING ) );
            break;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 1000 );
    log_printf( &logger, ">>> Closing BT peer connection.\r\n" );
    mdbt42q_cmd_run( ctx, MDBT42Q_CMD_DISCONNECT );
    error_flag |= mdbt42q_read_response( ctx );
    return error_flag;
}

// ------------------------------------------------------------------------ END
