/*!
 * @file main.c
 * @brief BLE P Click example
 *
 * # Description
 * This example demonstrates the use of BLE P Click by exchanging text with a
 * connected Nordic UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split into three stages:
 *  - BLEP_POWER_UP:
 * Waits for the module startup event.
 *  - BLEP_CONFIG_EXAMPLE:
 * Loads the Nordic UART profile, displays device information, sets the name, and starts advertising.
 *  - BLEP_EXAMPLE:
 * Echoes received text, sends periodic messages, and restarts advertising after disconnection.
 * The connection closes on the "END" string or after 60 seconds without received terminal data.
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "blep.h"

#ifndef MIKROBUS_POSITION_BLEP
    #define MIKROBUS_POSITION_BLEP MIKROBUS_1
#endif

/** Local device name. Keep it short to fit the advertising data. */
#define DEVICE_NAME                 "BLE P Click"

/** Pending terminal output buffer size in bytes. */
#define APP_TX_BUFFER_SIZE          128

static blep_t blep;                 /**< Click context object. */
static log_t logger;                /**< Logger object. */
static blep_event_t app_event;      /**< Most recently processed ACI event. */

/**
 * @brief BLE P example states.
 * @details Sequences startup, profile configuration, and terminal use.
 */
typedef enum
{
    BLEP_POWER_UP = 1,
    BLEP_CONFIG_EXAMPLE,
    BLEP_EXAMPLE

} blep_app_state_t;

static blep_app_state_t app_state = BLEP_POWER_UP; /**< Current example stage. */
static char tx_buf[ APP_TX_BUFFER_SIZE ];   /**< Pending text, sent in 20-byte notifications. */
static uint16_t tx_len = 0;                 /**< Total buffered output bytes. */
static uint16_t tx_offset = 0;              /**< Bytes already submitted to the module. */
static uint32_t idle_ms = 0;                /**< Polling time since the last received terminal data. */
static uint32_t message_ms = 0;             /**< Polling time since the last periodic message. */
static uint16_t wait_ms = 0;                /**< Polling time since the last connection waiting log. */
static uint16_t close_ms = 0;               /**< Bounded wait to drain output before disconnecting. */
static uint8_t closing = 0;                 /**< One after END, two after inactivity timeout. */
static uint8_t end_match = 0;               /**< Matched characters of END across receive packets. */
static uint8_t notifications = 0;           /**< Last reported UART notification subscription. */
static uint8_t advertise_pending = 0;       /**< Restart advertising after a disconnection event. */

/**
 * @brief BLE P output queue function.
 * @details This function appends text to the BLE P example transmit buffer.
 * @param[in] text : Null-terminated text.
 * @return BLEP_OK, or BLEP_ERROR when the output buffer is full.
 * @note Queued text is split into credit-controlled notifications by blep_example.
 */
static err_t blep_queue_text ( char *text );

/**
 * @brief BLE P response processing function.
 * @details This function reads one BLE P Click event and handles terminal, connection, and error logs.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return BLEP_OK, BLEP_NO_EVENT, or a negative error.
 * @note Incoming text is echoed only while the connection is not closing.
 */
static err_t blep_process ( blep_t *ctx );

/**
 * @brief BLE P response reading function.
 * @details This function processes BLE P Click events until the requested command response arrives.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] command : Command opcode whose response is expected.
 * @return BLEP_OK, or a negative response, transport, or timeout error.
 * @note The response timeout is 2000 ms; asynchronous events continue to be processed.
 */
static err_t blep_read_response ( blep_t *ctx, uint8_t command );

/**
 * @brief BLE P power-up function.
 * @details This function waits for the BLE P Click setup-mode startup event after default configuration.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return BLEP_OK, or a negative error.
 * @note A board with an OTP-locked custom profile requires a matching application.
 */
static err_t blep_power_up ( blep_t *ctx );

/**
 * @brief BLE P example configuration function.
 * @details This function loads the BLE P Click UART profile, reads identification, and starts advertising.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return BLEP_OK, or a negative error.
 * @note The device name is selected with DEVICE_NAME.
 */
static err_t blep_config_example ( blep_t *ctx );

/**
 * @brief BLE P terminal example function.
 * @details This function processes BLE P Click terminal traffic, timed messages, and graceful disconnection.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return BLEP_OK, or a negative error.
 * @note Timeout counters advance with the 10 ms polling delay; SPI and logging add a small overhead.
 */
static err_t blep_example ( blep_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    blep_cfg_t blep_cfg;  /**< Click config object. */

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
    blep_cfg_setup( &blep_cfg );
    BLEP_MAP_MIKROBUS( blep_cfg, MIKROBUS_POSITION_BLEP );
    if ( SPI_MASTER_ERROR == blep_init( &blep, &blep_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\r\n" );
}

void application_task ( void )
{
    err_t error_flag = BLEP_OK;

    switch ( app_state )
    {
        case BLEP_POWER_UP:
        {
            error_flag = blep_power_up( &blep );
            if ( BLEP_OK == error_flag )
            {
                app_state = BLEP_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\r\n" );
            }
            break;
        }
        case BLEP_CONFIG_EXAMPLE:
        {
            error_flag = blep_config_example( &blep );
            if ( BLEP_OK == error_flag )
            {
                app_state = BLEP_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\r\n" );
            }
            break;
        }
        case BLEP_EXAMPLE:
        {
            error_flag = blep_example( &blep );
            break;
        }
        default:
        {
            error_flag = BLEP_ERROR;
            break;
        }
    }
    if ( error_flag < 0 )
    {
        log_error( &logger, " Communication error: %d. Restarting module.", ( int16_t ) error_flag );
        app_state = BLEP_POWER_UP;
        Delay_ms( 1000 );
        blep_reset( &blep );
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

static err_t blep_queue_text ( char *text )
{
    uint16_t len = strlen( text );
    uint16_t pending = tx_len - tx_offset;
    err_t error_flag = BLEP_ERROR;

    if ( len <= APP_TX_BUFFER_SIZE - pending )
    {
        if ( pending && tx_offset )
        {
            // Keep unsent bytes at the start of the buffer before appending new text.
            memmove( tx_buf, &tx_buf[ tx_offset ], pending );
        }
        memcpy( &tx_buf[ pending ], text, len );
        tx_offset = 0;
        tx_len = pending + len;
        error_flag = BLEP_OK;
    }
    else
    {
        log_error( &logger, " Terminal output buffer full." );
    }
    return error_flag;
}

static err_t blep_process ( blep_t *ctx )
{
    char received[ BLEP_UART_DATA_SIZE + 1 ];
    char end_command[ 4 ] = "END";
    uint8_t len;
    uint8_t idx;
    uint8_t pipe_open;
    err_t error_flag = blep_read_event( ctx, &app_event );

    if ( BLEP_OK == error_flag )
    {
        switch ( app_event.opcode )
        {
            case BLEP_EVT_COMMAND_RESPONSE:
            {
                if ( app_event.payload[ 1 ] >= 0x80 )
                {
                    log_error( &logger, " Command 0x%.2X: status 0x%.2X.",
                               ( uint16_t ) app_event.payload[ 0 ], ( uint16_t ) app_event.payload[ 1 ] );
                    error_flag = BLEP_ERROR_RESPONSE;
                }
                break;
            }
            case BLEP_EVT_CONNECTED:
            {
                idle_ms = 0;
                message_ms = 0;
                wait_ms = 0;
                close_ms = 0;
                closing = 0;
                end_match = 0;
                notifications = 0;
                tx_len = 0;
                tx_offset = 0;
                log_printf( &logger, ">>> Connection established.\r\n" );
                log_printf( &logger, ">>> Waiting for data (up to 60 seconds of inactivity).\r\n" );
                log_printf( &logger, ">>> Send \"END\" to close the connection.\r\n" );
                break;
            }
            case BLEP_EVT_DISCONNECTED:
            {
                tx_len = 0;
                tx_offset = 0;
                closing = 0;
                end_match = 0;
                notifications = 0;
                advertise_pending = 1;
                log_printf( &logger, ">>> Connection ended. Reason: 0x%.2X.\r\n\r\n", ( uint16_t ) app_event.payload[ 1 ] );
                break;
            }
            case BLEP_EVT_PIPE_STATUS:
            {
                pipe_open = blep_is_pipe_open( ctx, BLEP_PIPE_UART_TX );
                if ( pipe_open != notifications )
                {
                    notifications = pipe_open;
                    log_printf( &logger, ">>> Terminal notifications %s.\r\n", notifications ? "enabled" : "disabled" );
                }
                break;
            }
            case BLEP_EVT_DATA_RECEIVED:
            {
                len = app_event.len - 2;
                if ( ( BLEP_PIPE_UART_RX == app_event.payload[ 0 ] ) && ( len <= BLEP_UART_DATA_SIZE ) && len )
                {
                    idle_ms = 0;
                    memcpy( received, &app_event.payload[ 1 ], len );
                    received[ len ] = 0;
                    // Keep terminal line endings out of the log prefix, but preserve them in the echo.
                    log_printf( &logger, "<<< Received data: " );
                    // Preserve partial matches so END is recognized when split across BLE packets.
                    for ( idx = 0; idx < len; idx++ )
                    {
                        if ( ( '\r' != received[ idx ] ) && ( '\n' != received[ idx ] ) )
                        {
                            log_printf( &logger, "%c", received[ idx ] );
                        }
                        if ( !closing )
                        {
                            end_match = ( received[ idx ] == end_command[ end_match ] ) ?
                                        end_match + 1 : ( ( 'E' == received[ idx ] ) ? 1 : 0 );
                            if ( 3 == end_match )
                            {
                                closing = 1;
                                close_ms = 0;
                                end_match = 0;
                            }
                        }
                    }
                    log_printf( &logger, "\r\n" );
                    if ( 1 == closing )
                    {
                        // Queue the final reply only once, even if more input arrives while closing.
                        if ( 0 == close_ms )
                        {
                            error_flag = blep_queue_text( "END command received. Closing connection.\r\n" );
                            close_ms = 1;
                            log_printf( &logger, ">>> Terminating connection on demand.\r\n" );
                        }
                    }
                    else if ( !closing )
                    {
                        error_flag = blep_queue_text( received );
                        if ( ( BLEP_OK == error_flag ) && ( '\n' != received[ len - 1 ] ) )
                        {
                            error_flag = blep_queue_text( "\r\n" );
                        }
                    }
                }
                break;
            }
            case BLEP_EVT_PIPE_ERROR:
            {
                log_error( &logger, " Pipe %u: status 0x%.2X.", ( uint16_t ) app_event.payload[ 0 ], 
                                                                ( uint16_t ) app_event.payload[ 1 ] );
                error_flag = BLEP_ERROR_RESPONSE;
                break;
            }
            default: break;
        }
    }
    return error_flag;
}

static err_t blep_read_response ( blep_t *ctx, uint8_t command )
{
    /** Maximum command response wait in milliseconds. */
    #define APP_RESPONSE_TIMEOUT_MS         2000

    uint16_t elapsed;
    uint8_t received = 0;
    err_t error_flag = BLEP_OK;

    for ( elapsed = 0; ( elapsed < APP_RESPONSE_TIMEOUT_MS ) && !received && ( BLEP_OK == error_flag ); elapsed++ )
    {
        error_flag = blep_process( ctx );
        if ( BLEP_NO_EVENT == error_flag )
        {
            error_flag = BLEP_OK;
        }
        else if ( ( BLEP_OK == error_flag ) && ( BLEP_EVT_COMMAND_RESPONSE == app_event.opcode ) &&
                  ( command == app_event.payload[ 0 ] ) )
        {
            received = 1;
            if ( BLEP_STATUS_SUCCESS != app_event.payload[ 1 ] )
            {
                error_flag = BLEP_ERROR_RESPONSE;
            }
        }
        Delay_1ms( );
    }
    if ( ( BLEP_OK == error_flag ) && !received )
    {
        log_error( &logger, " Response timeout: command 0x%.2X.", ( uint16_t ) command );
        error_flag = BLEP_ERROR_TIMEOUT;
    }
    return error_flag;
}

static err_t blep_power_up ( blep_t *ctx )
{
    /** Maximum startup event wait in milliseconds, after the reset delay. */
    #define APP_STARTUP_TIMEOUT_MS          2000

    uint16_t elapsed;
    err_t error_flag = BLEP_OK;

    tx_len = 0;
    tx_offset = 0;
    advertise_pending = 0;
    closing = 0;
    notifications = 0;
    log_printf( &logger, ">>> Wake device.\r\n" );

    for ( elapsed = 0; ( elapsed < APP_STARTUP_TIMEOUT_MS ) && ( 0 == ctx->device_mode ) &&
          ( BLEP_OK == error_flag ); elapsed++ )
    {
        error_flag = blep_process( ctx );
        if ( BLEP_NO_EVENT == error_flag )
        {
            error_flag = BLEP_OK;
        }
        Delay_1ms( );
    }
    if ( BLEP_OK == error_flag )
    {
        if ( 0 == ctx->device_mode )
        {
            log_error( &logger, " Startup event timeout." );
            error_flag = BLEP_ERROR_TIMEOUT;
        }
        else if ( BLEP_MODE_SETUP != ctx->device_mode )
        {
            log_error( &logger, " Expected setup mode; check for an OTP-locked profile." );
            error_flag = BLEP_ERROR_RESPONSE;
        }
    }
    return error_flag;
}

static err_t blep_config_example ( blep_t *ctx )
{
    char device_name[ ] = DEVICE_NAME;
    uint16_t name_len = strlen( device_name );
    uint16_t configuration;
    int8_t idx;
    err_t error_flag;

    log_printf( &logger, ">>> Load Nordic UART profile.\r\n" );
    error_flag = blep_uart_cfg( ctx );
    if ( BLEP_OK == error_flag )
    {
        log_printf( &logger, ">>> Get device version.\r\n" );
        error_flag = blep_run_command( ctx, BLEP_CMD_GET_DEVICE_VERSION );
    }
    if ( BLEP_OK == error_flag )
    {
        error_flag = blep_read_response( ctx, BLEP_CMD_GET_DEVICE_VERSION );
        if ( ( BLEP_OK == error_flag ) && ( app_event.len >= 12 ) )
        {
            configuration = ( uint16_t ) app_event.payload[ 2 ] | ( ( uint16_t ) app_event.payload[ 3 ] << 8 );
            log_printf( &logger, "Configuration: 0x%.4X | ACI version: 0x%.2X | Setup format: %u\r\n",
                        configuration, ( uint16_t ) app_event.payload[ 4 ], ( uint16_t ) app_event.payload[ 5 ] );
        }
        else if ( BLEP_OK == error_flag )
        {
            error_flag = BLEP_ERROR_RESPONSE;
        }
    }
    if ( BLEP_OK == error_flag )
    {
        log_printf( &logger, ">>> Get Bluetooth address.\r\n" );
        error_flag = blep_run_command( ctx, BLEP_CMD_GET_DEVICE_ADDRESS );
    }
    if ( BLEP_OK == error_flag )
    {
        error_flag = blep_read_response( ctx, BLEP_CMD_GET_DEVICE_ADDRESS );
        if ( ( BLEP_OK == error_flag ) && ( app_event.len >= 10 ) )
        {
            for ( idx = 7; idx >= 2; idx-- )
            {
                log_printf( &logger, "%.2X%s", ( uint16_t ) app_event.payload[ idx ], ( idx > 2 ) ? ":" : "\r\n" );
            }
        }
        else if ( BLEP_OK == error_flag )
        {
            error_flag = BLEP_ERROR_RESPONSE;
        }
    }
    if ( BLEP_OK == error_flag )
    {
        log_printf( &logger, ">>> Set device name to \"%s\".\r\n", device_name );
        if ( ( name_len > 0 ) && ( name_len <= BLEP_DEVICE_NAME_SIZE ) )
        {
            error_flag = blep_set_local_data( ctx, BLEP_PIPE_DEVICE_NAME, ( uint8_t * ) device_name, name_len );
        }
        else
        {
            error_flag = BLEP_ERROR;
        }
    }
    if ( BLEP_OK == error_flag )
    {
        error_flag = blep_read_response( ctx, BLEP_CMD_SET_LOCAL_DATA );
    }
    if ( BLEP_OK == error_flag )
    {
        log_printf( &logger, ">>> Start advertising.\r\n" );
        error_flag = blep_start_advertising( ctx, BLEP_ADV_NO_TIMEOUT, BLEP_ADV_INTERVAL );
    }
    if ( BLEP_OK == error_flag )
    {
        error_flag = blep_read_response( ctx, BLEP_CMD_CONNECT );
        wait_ms = 0;
    }
    return error_flag;
}

static err_t blep_example ( blep_t *ctx )
{
    /** Application polling delay and timer increment in milliseconds. */
    #define APP_POLL_MS                     10
    /** Close the connection after this many milliseconds without terminal input. */
    #define APP_INACTIVITY_MS               60000ul
    /** Periodic message and connection waiting log interval in milliseconds. */
    #define APP_MESSAGE_INTERVAL_MS         5000
    /** Maximum final notification drain time before issuing Disconnect, in milliseconds. */
    #define APP_CLOSE_DRAIN_MS              2000
    /** Maximum wait for Disconnected after an accepted command, in milliseconds. */
    #define APP_DISCONNECT_TIMEOUT_MS       5000

    uint8_t chunk;
    uint16_t elapsed;
    err_t error_flag = blep_process( ctx );

    if ( BLEP_NO_EVENT == error_flag )
    {
        error_flag = BLEP_OK;
    }
    if ( ( BLEP_OK == error_flag ) && advertise_pending )
    {
        log_printf( &logger, ">>> Restart advertising.\r\n" );
        error_flag = blep_start_advertising( ctx, BLEP_ADV_NO_TIMEOUT, BLEP_ADV_INTERVAL );
        if ( BLEP_OK == error_flag )
        {
            error_flag = blep_read_response( ctx, BLEP_CMD_CONNECT );
            advertise_pending = 0;
            wait_ms = APP_MESSAGE_INTERVAL_MS;
        }
    }
    if ( ( BLEP_OK == error_flag ) && !ctx->connected )
    {
        if ( 0 == wait_ms )
        {
            log_printf( &logger, ">>> Waiting for a BLE peer to establish connection with the Click board...\r\n" );
        }
        wait_ms += APP_POLL_MS;
        if ( wait_ms >= APP_MESSAGE_INTERVAL_MS )
        {
            wait_ms = 0;
        }
    }
    else if ( ( BLEP_OK == error_flag ) && ctx->connected )
    {
        idle_ms += APP_POLL_MS;
        message_ms += APP_POLL_MS;
        if ( !closing && ( idle_ms >= APP_INACTIVITY_MS ) )
        {
            closing = 2;
            close_ms = 0;
            log_printf( &logger, ">>> Terminating connection due to 60s inactivity timeout.\r\n" );
            error_flag = blep_queue_text( "Timeout, closing the connection.\r\n" );
        }
        if ( !closing && notifications && ( message_ms >= APP_MESSAGE_INTERVAL_MS ) && ( tx_offset == tx_len ) )
        {
            message_ms = 0;
            log_printf( &logger, ">>> Sending \"BLE P Click\" message to connected device.\r\n" );
            error_flag = blep_queue_text( "BLE P Click\r\n" );
        }
        if ( ( BLEP_OK == error_flag ) && notifications && ( tx_offset < tx_len ) )
        {
            // Send one notification at a time; the module's returned credits gate further chunks.
            chunk = ( tx_len - tx_offset > BLEP_UART_DATA_SIZE ) ? BLEP_UART_DATA_SIZE : tx_len - tx_offset;
            error_flag = blep_send_data( ctx, BLEP_PIPE_UART_TX, ( uint8_t * ) &tx_buf[ tx_offset ], chunk );
            if ( BLEP_OK == error_flag )
            {
                tx_offset += chunk;
            }
            else if ( BLEP_BUSY == error_flag )
            {
                error_flag = BLEP_OK;
            }
        }
        if ( ( BLEP_OK == error_flag ) && closing )
        {
            close_ms += APP_POLL_MS;
            // Let submitted notifications drain, but cap the wait if the peer stops acknowledging.
            if ( ( ( tx_offset == tx_len ) && ( ctx->credits == ctx->total_credits ) ) ||
                 ( close_ms >= APP_CLOSE_DRAIN_MS ) )
            {
                if ( close_ms >= APP_CLOSE_DRAIN_MS )
                {
                    log_printf( &logger, ">>> Final notification not confirmed; closing connection.\r\n" );
                }
                error_flag = blep_disconnect( ctx );
                if ( BLEP_OK == error_flag )
                {
                    error_flag = blep_read_response( ctx, BLEP_CMD_DISCONNECT );
                }
                for ( elapsed = 0; ( elapsed < APP_DISCONNECT_TIMEOUT_MS ) && ctx->connected &&
                      ( BLEP_OK == error_flag ); elapsed++ )
                {
                    error_flag = blep_process( ctx );
                    if ( BLEP_NO_EVENT == error_flag )
                    {
                        error_flag = BLEP_OK;
                    }
                    Delay_1ms( );
                }
                if ( ( BLEP_OK == error_flag ) && ctx->connected )
                {
                    error_flag = BLEP_ERROR_TIMEOUT;
                }
            }
        }
    }
    Delay_10ms( );
    return error_flag;
}

// ------------------------------------------------------------------------ END
