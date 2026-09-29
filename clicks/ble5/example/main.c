/*!
 * @file main.c
 * @brief BLE 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of BLE 5 Click board as a Nordic UART
 * terminal for sending and receiving data with a connected BLE peer.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and resets the module.
 *
 * ## Application Task
 * Application task is split into three stages:
 *  - BLE5_POWER_UP:
 * Waits for the module and displays the firmware version and Bluetooth address.
 *  - BLE5_CONFIG_EXAMPLE:
 * Configures the device name and Nordic UART service and starts advertising.
 *  - BLE5_EXAMPLE:
 * Echoes received text, periodically sends a message, and restarts advertising
 * after disconnection.
 *
 * @note
 * Set MODE to Standalone and use the preprogrammed AT firmware with mikroBUS UART.
 * We have used the Serial Bluetooth Terminal smartphone application for the test.
 * This example does not require bonding.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ble5.h"

#ifndef MIKROBUS_POSITION_BLE5
    #define MIKROBUS_POSITION_BLE5 MIKROBUS_1
#endif

/** Message sent periodically to the connected terminal. */
#define MESSAGE_CONTENT                         "BLE 5 Click board - demo example."

/** Local device name; the advertising packet supports up to eight characters. */
#define DEVICE_NAME                             "BLE 5"

/** Maximum received AT packet size, including its header and terminator. */
#define APP_BUFFER_SIZE                         256

/** Events retained while waiting for a command reply. */
#define APP_EVENT_QUEUE_SIZE                    4

static ble5_t ble5;                             /**< Click context object. */
static log_t logger;                            /**< Logger object. */
static uint8_t app_buf[ APP_BUFFER_SIZE ];      /**< Complete response or event. */
static uint16_t app_buf_len = 0;                /**< Payload bytes in app_buf. */
static uint16_t rx_len = 0;                     /**< Bytes assembled for the current packet. */
static uint16_t packet_len = BLE5_PACKET_HEADER_SIZE; /**< Current receive target. */

/** Events must survive commands issued while handling an earlier event. */
static uint8_t event_buf[ APP_EVENT_QUEUE_SIZE ][ APP_BUFFER_SIZE ];
static uint16_t event_len[ APP_EVENT_QUEUE_SIZE ]; /**< Queued payload lengths. */
static uint8_t event_head = 0;                  /**< Oldest queued event. */
static uint8_t event_count = 0;                 /**< Number of queued events. */
static uint16_t connection_id = 0;              /**< Handle supplied by the module. */
static uint8_t connected = 0;                   /**< Active BLE connection. */
static uint8_t notifications_enabled = 0;       /**< Peer enabled the TX descriptor. */
static uint8_t end_requested = 0;               /**< Peer requested local termination. */
static uint8_t data_received = 0;               /**< Valid RX data arrived during the current task call. */

/**
 * @brief BLE 5 example states.
 * @details States used to sequence power-up, configuration, and terminal use.
 */
typedef enum
{
    BLE5_POWER_UP = 1,
    BLE5_CONFIG_EXAMPLE,
    BLE5_EXAMPLE

} ble5_app_state_t;

static ble5_app_state_t app_state = BLE5_POWER_UP; /**< Current example state. */

/**
 * @brief BLE 5 application buffer clearing function.
 * @details This function resets packet assembly, queued events, and connection state.
 * @return None.
 * @note Call after a module reset or communication failure.
 */
static void ble5_clear_app_buf ( void );

/**
 * @brief BLE 5 application buffer logging function.
 * @details This function logs printable bytes and displays binary bytes in hexadecimal.
 * @return None.
 * @note None.
 */
static void ble5_log_app_buf ( void );

/**
 * @brief BLE 5 response processing function.
 * @details This function assembles one length-prefixed packet without discarding zero bytes.
 * @param[in] ctx : Click context object.
 * @return @li @c 0 - Complete payload available,
 *         @li @c -1 - Packet incomplete,
 *         @li @c -3 - Invalid packet.
 * @note Additional packets remain in the UART receive buffer.
 */
static err_t ble5_process ( ble5_t *ctx );

/**
 * @brief BLE 5 response reading function.
 * @details This function waits for an expected reply and queues asynchronous events.
 * @param[in] ctx : Click context object.
 * @param[in] rsp : Expected response prefix.
 * @param[in] max_rsp_time : Maximum response wait in milliseconds.
 * @return @li @c 0 - Expected reply received,
 *         @li @c -2 - Timeout,
 *         @li @c -3 - Invalid packet or command error,
 *         @li @c -4 - Event queue full.
 * @note Complete response packets are logged except routine +OK acknowledgements and
 * formatted Bluetooth address replies; asynchronous events remain queued.
 */
static err_t ble5_read_response ( ble5_t *ctx, char *rsp, uint32_t max_rsp_time );

/**
 * @brief BLE 5 command execution function.
 * @details This function sends a command and waits for its acknowledgement.
 * @param[in] ctx : Click context object.
 * @param[in] cmd : Command identifier.
 * @param[in] params : Binary parameters, or NULL for a command without parameters.
 * @param[in] len : Parameter length in bytes.
 * @return Zero on success, or a negative communication error.
 * @note None.
 */
static err_t ble5_execute ( ble5_t *ctx, uint8_t *cmd, uint8_t *params, uint16_t len );

/**
 * @brief BLE 5 notification sending function.
 * @details This function sends data through the Nordic UART TX characteristic.
 * @param[in] ctx : Click context object.
 * @param[in] conn : Connection handle.
 * @param[in] payload : Notification payload.
 * @param[in] len : Notification payload length in bytes.
 * @return Zero on success, or a negative communication error.
 * @note Payloads longer than 20 bytes are split into multiple ATT notifications.
 */
static err_t ble5_send_notification ( ble5_t *ctx, uint16_t conn, uint8_t *payload, uint16_t len );

/**
 * @brief BLE 5 advertising start function.
 * @details This function advertises the complete device name and Nordic UART service UUID.
 * @param[in] ctx : Click context object.
 * @return Zero on success, or a negative communication error.
 * @note None.
 */
static err_t ble5_start_advertising ( ble5_t *ctx );

/**
 * @brief BLE 5 power-up function.
 * @details This function waits for readiness and displays firmware and address information.
 * @param[in] ctx : Click context object.
 * @return Zero on success, or a negative communication error.
 * @note None.
 */
static err_t ble5_power_up ( ble5_t *ctx );

/**
 * @brief BLE 5 example configuration function.
 * @details This function creates the Generic Access and Nordic UART services.
 * @param[in] ctx : Click context object.
 * @return Zero on success, or a negative communication error.
 * @note The profile is recreated after reset and is not written to flash.
 */
static err_t ble5_config_example ( ble5_t *ctx );

/**
 * @brief BLE 5 connection termination function.
 * @details This function resets the BLE module after the example receives the END command.
 * @param[in] ctx : Click context object.
 * @return Zero on success, or a negative communication error.
 * @note Reset closes the link because the installed firmware requires a peer address for direct
 * disconnect.
 */
static err_t ble5_terminate_connection ( ble5_t *ctx );

/**
 * @brief BLE 5 event handling function.
 * @details This function handles connection, MTU, read, and write events and echoes terminal data.
 * @param[in] ctx : Click context object.
 * @return Zero on success, or a negative communication error.
 * @note Event parameters are copied before a command can replace app_buf.
 */
static err_t ble5_handle_event ( ble5_t *ctx );

/**
 * @brief BLE 5 terminal example function.
 * @details This function services events, sends terminal text, and terminates an inactive link.
 * @param[in] ctx : Click context object.
 * @return Zero on success, or a negative communication error.
 * @note The link is terminated after 60 seconds without received terminal data.
 */
static err_t ble5_example ( ble5_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ble5_cfg_t ble5_cfg;  /**< Click config object. */

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
    ble5_cfg_setup( &ble5_cfg );
    BLE5_MAP_MIKROBUS( ble5_cfg, MIKROBUS_POSITION_BLE5 );
    if ( UART_ERROR == ble5_init( &ble5, &ble5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BLE5_ERROR == ble5_default_cfg( &ble5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    err_t error_flag = BLE5_OK;

    switch ( app_state )
    {
        case BLE5_POWER_UP:
        {
            error_flag = ble5_power_up( &ble5 );
            if ( BLE5_OK == error_flag )
            {
                app_state = BLE5_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE5_CONFIG_EXAMPLE:
        {
            error_flag = ble5_config_example( &ble5 );
            if ( BLE5_OK == error_flag )
            {
                app_state = BLE5_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE5_EXAMPLE:
        {
            error_flag = ble5_example( &ble5 );
            break;
        }
        default:
        {
            error_flag = BLE5_ERROR;
            break;
        }
    }

    if ( BLE5_OK != error_flag )
    {
        log_error( &logger, " Communication error: %d. Restarting module.", error_flag );
        // A failed profile build must restart from an empty module database.
        Delay_1sec( );
        ble5_clear_app_buf( );
        ble5_default_cfg( &ble5 );
        app_state = BLE5_POWER_UP;
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

static void ble5_clear_app_buf ( void )
{
    app_buf_len = 0;
    rx_len = 0;
    packet_len = BLE5_PACKET_HEADER_SIZE;
    event_head = 0;
    event_count = 0;
    connection_id = 0;
    connected = 0;
    notifications_enabled = 0;
    end_requested = 0;
    data_received = 0;
}

static void ble5_log_app_buf ( void )
{
    for ( uint16_t index = 0; index < app_buf_len; index++ )
    {
        if ( ( app_buf[ index ] >= 32 ) && ( app_buf[ index ] <= 126 ) )
        {
            log_printf( &logger, "%c", app_buf[ index ] );
        }
        else
        {
            log_printf( &logger, "[%.2X]", app_buf[ index ] );
        }
    }
    log_printf( &logger, "\r\n" );
}

static err_t ble5_process ( ble5_t *ctx )
{
    err_t result = BLE5_ERROR;
    err_t received;
    uint32_t total_len = 0;
    uint8_t read_more = 1;

    // Read only the current packet so a following response stays in the UART buffer.
    for ( uint8_t pass = 0; ( pass < 2 ) && ( 0 != read_more ); pass++ )
    {
        received = ble5_generic_read( ctx, &app_buf[ rx_len ], packet_len - rx_len );
        if ( received <= 0 )
        {
            read_more = 0;
        }
        else if ( received > packet_len - rx_len )
        {
            rx_len = 0;
            packet_len = BLE5_PACKET_HEADER_SIZE;
            result = BLE5_ERROR_CMD;
            read_more = 0;
        }
        else
        {
            rx_len += received;
            if ( rx_len == packet_len )
            {
                if ( BLE5_PACKET_HEADER_SIZE == packet_len )
                {
                    total_len = ( uint32_t ) app_buf[ 0 ] | ( ( uint32_t ) app_buf[ 1 ] << 8 ) |
                                ( ( uint32_t ) app_buf[ 2 ] << 16 );
                    if ( ( total_len <= BLE5_PACKET_HEADER_SIZE + BLE5_PACKET_END_SIZE ) ||
                         ( total_len > APP_BUFFER_SIZE ) )
                    {
                        rx_len = 0;
                        packet_len = BLE5_PACKET_HEADER_SIZE;
                        result = BLE5_ERROR_CMD;
                        read_more = 0;
                    }
                    else
                    {
                        packet_len = ( uint16_t ) total_len;
                    }
                }
                else if ( ( '\r' != app_buf[ packet_len - 2 ] ) || ( '\n' != app_buf[ packet_len - 1 ] ) )
                {
                    rx_len = 0;
                    packet_len = BLE5_PACKET_HEADER_SIZE;
                    result = BLE5_ERROR_CMD;
                    read_more = 0;
                }
                else
                {
                    app_buf_len = packet_len - BLE5_PACKET_HEADER_SIZE - BLE5_PACKET_END_SIZE;
                    memmove( app_buf, &app_buf[ BLE5_PACKET_HEADER_SIZE ], app_buf_len );

                    // Events also carry an initial CR/LF pair in the packet payload.
                    if ( ( app_buf_len >= 2 ) && ( '\r' == app_buf[ 0 ] ) && ( '\n' == app_buf[ 1 ] ) )
                    {
                        app_buf_len -= 2;
                        memmove( app_buf, &app_buf[ 2 ], app_buf_len );
                    }

                    rx_len = 0;
                    packet_len = BLE5_PACKET_HEADER_SIZE;
                    result = BLE5_OK;
                    read_more = 0;
                }
            }
        }
    }

    return result;
}

static err_t ble5_read_response ( ble5_t *ctx, char *rsp, uint32_t max_rsp_time )
{
    uint16_t rsp_len = strlen( rsp );
    uint8_t tail;
    uint8_t wait_for_response = 1;
    err_t packet_result;
    err_t result = BLE5_ERROR_TIMEOUT;
    uint32_t elapsed = 0;

    for ( elapsed = 0; ( elapsed < max_rsp_time ) && ( 0 != wait_for_response ); elapsed++ )
    {
        packet_result = ble5_process( ctx );
        if ( BLE5_ERROR_CMD == packet_result )
        {
            result = packet_result;
            wait_for_response = 0;
        }
        else if ( BLE5_OK == packet_result )
        {
            if ( ( ( app_buf_len < strlen( BLE5_RSP_OK ) ) ||
                  ( 0 != memcmp( app_buf, BLE5_RSP_OK, strlen( BLE5_RSP_OK ) ) ) ) &&
                 ( ( app_buf_len < strlen( BLE5_RSP_ADDRESS ) ) ||
                  ( 0 != memcmp( app_buf, BLE5_RSP_ADDRESS, strlen( BLE5_RSP_ADDRESS ) ) ) ) )
            {
                ble5_log_app_buf( );
            }
            if ( ( app_buf_len >= strlen( BLE5_EVT_PREFIX ) ) &&
                 ( 0 == memcmp( app_buf, BLE5_EVT_PREFIX, strlen( BLE5_EVT_PREFIX ) ) ) )
            {
                if ( APP_EVENT_QUEUE_SIZE == event_count )
                {
                    result = BLE5_ERROR_OVERFLOW;
                    wait_for_response = 0;
                }
                else
                {
                    tail = ( event_head + event_count ) % APP_EVENT_QUEUE_SIZE;
                    memcpy( event_buf[ tail ], app_buf, app_buf_len );
                    event_len[ tail ] = app_buf_len;
                    event_count++;
                }
            }
            else if ( ( app_buf_len >= strlen( BLE5_RSP_ERROR ) ) &&
                      ( 0 == memcmp( app_buf, BLE5_RSP_ERROR, strlen( BLE5_RSP_ERROR ) ) ) )
            {
                result = BLE5_ERROR_CMD;
                wait_for_response = 0;
            }
            else if ( ( app_buf_len >= rsp_len ) && ( 0 == memcmp( app_buf, rsp, rsp_len ) ) )
            {
                result = BLE5_OK;
                wait_for_response = 0;
            }
        }

        if ( 0 != wait_for_response )
        {
            Delay_1ms( );
        }
    }

    if ( BLE5_ERROR_TIMEOUT == result )
    {
        ble5_log_app_buf( );
        log_error( &logger, " Response timeout: %s.", rsp );
    }

    return result;
}

static err_t ble5_execute ( ble5_t *ctx, uint8_t *cmd, uint8_t *params, uint16_t len )
{
    #define BLE5_COMMAND_RSP_TIME_MS             2000

    err_t result = ble5_cmd_set( ctx, cmd, params, len );
    if ( BLE5_OK == result )
    {
        result = ble5_read_response( ctx, BLE5_RSP_OK, BLE5_COMMAND_RSP_TIME_MS );
    }
    if ( BLE5_OK != result )
    {
        log_error( &logger, " Command: %s.", ( char * ) cmd );
    }

    return result;
}

static err_t ble5_start_advertising ( ble5_t *ctx )
{
    uint8_t name[] = DEVICE_NAME;
    uint8_t uuid[] = { 0x6E, 0x40, 0x00, 0x01, 0xB5, 0xA3, 0xF3, 0x93,
                       0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E };
    uint8_t params[ 96 ] = {
        0x01, ',', 0x00, 0xA0, ',', 0x00, 0xA0, ',', 0x00, ',', 0x00, ',', 0x00, ',',
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, ',', 0x07, ',', 0x00, ','
    };
    uint16_t offset = 25;
    uint8_t name_len = sizeof( name ) - 1;
    err_t result = BLE5_OK;

    if ( ( 0 == name_len ) || ( name_len > 8 ) )
    {
        result = BLE5_ERROR;
    }
    else
    {
        // Flags, complete service UUID, and complete name fit the 31-byte advertising limit.
        params[ offset++ ] = 23 + name_len;
        params[ offset++ ] = ',';
        params[ offset++ ] = 2;
        params[ offset++ ] = 0x01;
        params[ offset++ ] = 0x06;
        params[ offset++ ] = 17;
        params[ offset++ ] = 0x07;
        for ( uint8_t index = 0; index < sizeof( uuid ); index++ )
        {
            // Advertising UUIDs use little-endian order, unlike AT UUID parameters.
            params[ offset++ ] = uuid[ sizeof( uuid ) - 1 - index ];
        }
        params[ offset++ ] = name_len + 1;
        params[ offset++ ] = 0x09;
        memcpy( &params[ offset ], name, name_len );
        offset += name_len;

        params[ offset++ ] = ',';
        params[ offset++ ] = name_len + 2;
        params[ offset++ ] = ',';
        params[ offset++ ] = name_len + 1;
        params[ offset++ ] = 0x09;
        memcpy( &params[ offset ], name, name_len );
        offset += name_len;
        log_printf( &logger, ">>> Start advertising.\r\n" );
        result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_LEADV, params, offset );
    }

    return result;
}

static err_t ble5_power_up ( ble5_t *ctx )
{
    #define BLE5_POWER_UP_RSP_TIME_MS            3000

    err_t result = BLE5_OK;
    uint16_t ready_len = strlen( BLE5_RSP_READY );
    uint16_t address_len = strlen( BLE5_RSP_ADDRESS );

    log_printf( &logger, ">>> Wake device.\r\n" );
    result = ble5_read_response( ctx, BLE5_RSP_READY, BLE5_POWER_UP_RSP_TIME_MS );
    if ( BLE5_OK == result )
    {
        if ( ( app_buf_len <= ready_len ) ||
             ( BLE5_STATUS_SUCCESS != app_buf[ ready_len ] ) )
        {
            result = BLE5_ERROR_CMD;
        }
    }

    if ( BLE5_OK == result )
    {
        log_printf( &logger, ">>> Get firmware version.\r\n" );
        result = ble5_cmd_run( ctx, ( uint8_t * ) BLE5_CMD_SYSRDSWVERSION );
        if ( BLE5_OK == result )
        {
            result = ble5_read_response( ctx, BLE5_RSP_VERSION, BLE5_POWER_UP_RSP_TIME_MS );
        }
    }

    if ( BLE5_OK == result )
    {
        log_printf( &logger, ">>> Get Bluetooth address.\r\n" );
        result = ble5_cmd_run( ctx, ( uint8_t * ) BLE5_CMD_SYSGBDADDR );
        if ( BLE5_OK == result )
        {
            // This command returns +OK followed by a separate address packet.
            result = ble5_read_response( ctx, BLE5_RSP_ADDRESS, BLE5_POWER_UP_RSP_TIME_MS );
        }
        if ( BLE5_OK == result )
        {
            if ( app_buf_len < address_len + 6 )
            {
                result = BLE5_ERROR_CMD;
            }
            else
            {
                for ( uint8_t index = 0; index < 6; index++ )
                {
                    log_printf( &logger, "%.2X%s", app_buf[ address_len + index ],
                                ( index < 5 ) ? ":" : "\r\n" );
                }
            }
        }
    }

    return result;
}

static err_t ble5_config_example ( ble5_t *ctx )
{
    uint8_t name[] = DEVICE_NAME;
    // GAP service and standard device-name and appearance characteristics.
    uint8_t gap_service[] = { BLE5_UUID_16_BIT, ',', 0x18, 0x00 };
    uint8_t name_char[] = {
        BLE5_UUID_16_BIT, ',', 0x2A, 0x00, ',', 0x00, sizeof( name ) - 1, ',',
        BLE5_CHAR_READ, ',', 0x00, 0x00
    };
    uint8_t appearance_char[] = {
        BLE5_UUID_16_BIT, ',', 0x2A, 0x01, ',', 0x00, 0x02, ',', BLE5_CHAR_READ, ',', 0x00, 0x00
    };
    // Nordic UART service and RX/TX characteristics.
    uint8_t uart_service[] = {
        BLE5_UUID_128_BIT, ',', 0x6E, 0x40, 0x00, 0x01, 0xB5, 0xA3, 0xF3, 0x93,
        0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E
    };
    uint8_t rx_char[] = {
        BLE5_UUID_128_BIT, ',', 0x6E, 0x40, 0x00, 0x02, 0xB5, 0xA3, 0xF3, 0x93,
        0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E, ',', 0x00, BLE5_ATT_VALUE_SIZE,
        ',', 0x00, BLE5_ATT_VALUE_SIZE, ',', BLE5_CHAR_WRITE | BLE5_CHAR_WRITE_COMMAND, ',', 0x00, 0x00
    };
    uint8_t tx_char[] = {
        BLE5_UUID_128_BIT, ',', 0x6E, 0x40, 0x00, 0x03, 0xB5, 0xA3, 0xF3, 0x93,
        0xE0, 0xA9, 0xE5, 0x0E, 0x24, 0xDC, 0xCA, 0x9E, ',', 0x00, BLE5_ATT_VALUE_SIZE,
        ',', 0x00, BLE5_ATT_VALUE_SIZE, ',', BLE5_CHAR_NOTIFY, ',', 0x00, 0x00
    };
    // A read/write CCCD is required by terminal applications before notifications are enabled.
    // CCCD used by terminal applications to enable TX notifications.
    uint8_t cccd[] = { BLE5_UUID_16_BIT, ',', 0x29, 0x02, ',', 0x00, 0x02, ',', 0x00, 0x03 };
    // Initial values for the device name and notification descriptor.
    uint8_t name_value[ 9 + sizeof( name ) - 1 ] = { 'P', 1, '+', 'C', 1, '+', 'E', 1, ',' };
    uint8_t appearance_value[] = { 'P', 1, '+', 'C', 2, '+', 'E', 1, ',', 0x00, 0x00 };
    uint8_t cccd_value[] = { 'P', 2, '+', 'C', 2, '+', 'E', 2, ',', 0x00, 0x00 };
    err_t result = BLE5_OK;

    if ( ( sizeof( name ) < 2 ) || ( sizeof( name ) > 9 ) )
    {
        log_error( &logger, " Device name must contain 1-8 characters." );
        result = BLE5_ERROR;
    }
    else
    {
        memcpy( &name_value[ 9 ], name, sizeof( name ) - 1 );

        log_printf( &logger, ">>> Create GATT profile.\r\n" );
        log_printf( &logger, ">>> Set device name to \"%s\".\r\n", ( char * ) name );
        result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDPROF, NULL, 0 );

        if ( BLE5_OK == result )
        {
            log_printf( &logger, ">>> Add Generic Access service.\r\n" );
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDSVC, 
                                   gap_service, sizeof( gap_service ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDCHAR, 
                                   name_char, sizeof( name_char ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDCHAR, 
                                   appearance_char, sizeof( appearance_char ) );
        }

        if ( BLE5_OK == result )
        {
            log_printf( &logger, ">>> Add Nordic UART service.\r\n" );
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDSVC,
                                   uart_service, sizeof( uart_service ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDCHAR, rx_char, sizeof( rx_char ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDCHAR, tx_char, sizeof( tx_char ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSADDDESC, cccd, sizeof( cccd ) );
        }

        if ( BLE5_OK == result )
        {
            log_printf( &logger, ">>> Register GATT profile.\r\n" );
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSREGPROF, NULL, 0 );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSUPDVAL,
                                   name_value, sizeof( name_value ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSUPDVAL,
                                   appearance_value, sizeof( appearance_value ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSUPDVAL,
                                   cccd_value, sizeof( cccd_value ) );
        }
        if ( BLE5_OK == result )
        {
            result = ble5_start_advertising( ctx );
        }
    }

    return result;
}

static err_t ble5_terminate_connection ( ble5_t *ctx )
{
    log_printf( &logger, ">>> Restarting BLE module.\r\n" );

    // The installed AT firmware exposes the disconnect command by peer address,
    // while this server example receives only a connection handle. Resetting the
    // module closes the link without sending an invalid address to the firmware.
    ble5_clear_app_buf( );
    ble5_default_cfg( ctx );
    app_state = BLE5_POWER_UP;

    return BLE5_OK;
}

static err_t ble5_send_notification ( ble5_t *ctx, uint16_t conn, uint8_t *payload, uint16_t len )
{
    uint8_t params[ BLE5_CMD_BUFFER_SIZE ];
    uint16_t offset = 0;
    uint16_t chunk_len;
    err_t result = BLE5_OK;

    if ( len > ( sizeof( params ) - BLE5_NOTIFICATION_PREFIX_SIZE ) )
    {
        result = BLE5_ERROR_OVERFLOW;
    }
    else
    {
        do
        {
            chunk_len = len - offset;
            if ( chunk_len > BLE5_ATT_VALUE_SIZE )
            {
                chunk_len = BLE5_ATT_VALUE_SIZE;
            }

            params[ 0 ] = 'P';
            params[ 1 ] = BLE5_UART_PROFILE_ID;
            params[ 2 ] = '+';
            params[ 3 ] = 'C';
            params[ 4 ] = BLE5_UART_TX_CHARACTERISTIC_ID;
            params[ 5 ] = ',';
            params[ BLE5_NOTIFICATION_CONNECTION_HIGH_OFFSET ] = ( uint8_t ) ( conn >> 8 );
            params[ BLE5_NOTIFICATION_CONNECTION_LOW_OFFSET ] = ( uint8_t ) conn;
            params[ BLE5_NOTIFICATION_SEPARATOR_OFFSET ] = ',';
            memcpy( &params[ BLE5_NOTIFICATION_VALUE_OFFSET ], &payload[ offset ], chunk_len );
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSSRVNOT, params,
                                   BLE5_NOTIFICATION_PREFIX_SIZE + chunk_len );
            offset += chunk_len;
        } while ( ( offset < len ) && ( BLE5_OK == result ) );
    }

    return result;
}

static err_t ble5_handle_event ( ble5_t *ctx )
{
    #define BLE5_MATCH_EVENT( text ) \
        ( ( app_buf_len >= strlen( text ) ) && ( 0 == memcmp( app_buf, text, strlen( text ) ) ) )

    enum
    {
        BLE5_EVENT_NONE = 0,
        BLE5_EVENT_CONNECTED,
        BLE5_EVENT_DISCONNECTED,
        BLE5_EVENT_MTU_REQUEST,
        BLE5_EVENT_READ,
        BLE5_EVENT_WRITE,
        BLE5_EVENT_WRITE_COMMAND
    };

    uint8_t params[ 16 + BLE5_ATT_VALUE_SIZE ];
    uint8_t value[ BLE5_ATT_VALUE_SIZE ];
    uint8_t *event_data = NULL;
    uint16_t data_len = 0;
    uint16_t conn = 0;
    uint8_t profile = 0;
    uint8_t characteristic = 0;
    uint8_t element = 0;
    uint8_t value_len = 0;
    uint8_t accept = BLE5_STATUS_SUCCESS;
    uint8_t write_request = 0;
    uint8_t event_type = BLE5_EVENT_NONE;
    err_t result = BLE5_OK;

    if ( BLE5_MATCH_EVENT( BLE5_EVT_CONNECTED ) )
    {
        event_type = BLE5_EVENT_CONNECTED;
    }
    else if ( BLE5_MATCH_EVENT( BLE5_EVT_DISCONNECTED ) )
    {
        event_type = BLE5_EVENT_DISCONNECTED;
    }
    else if ( BLE5_MATCH_EVENT( BLE5_EVT_MTU_REQUEST ) )
    {
        event_type = BLE5_EVENT_MTU_REQUEST;
    }
    else if ( BLE5_MATCH_EVENT( BLE5_EVT_READ ) )
    {
        event_type = BLE5_EVENT_READ;
    }
    else if ( BLE5_MATCH_EVENT( BLE5_EVT_WRITE ) )
    {
        event_type = BLE5_EVENT_WRITE;
        write_request = 1;
    }
    else if ( BLE5_MATCH_EVENT( BLE5_EVT_WRITE_COMMAND ) )
    {
        event_type = BLE5_EVENT_WRITE_COMMAND;
    }
    else if ( BLE5_MATCH_EVENT( BLE5_RSP_ERROR ) )
    {
        ble5_log_app_buf( );
        result = BLE5_ERROR_CMD;
    }

    if ( BLE5_EVENT_CONNECTED == event_type )
    {
        event_data = &app_buf[ strlen( BLE5_EVT_CONNECTED ) ];
        data_len = app_buf_len - ( strlen( BLE5_EVT_CONNECTED ) );
        if ( ( data_len < 7 ) || ( ',' != event_data[ 1 ] ) || ( ',' != event_data[ 4 ] ) )
        {
            result = BLE5_ERROR_CMD;
        }
        else if ( BLE5_STATUS_SUCCESS == event_data[ 0 ] )
        {
            connection_id = ( ( uint16_t ) event_data[ 2 ] << 8 ) | event_data[ 3 ];
            connected = 1;
            notifications_enabled = 0;
        }
    }
    else if ( BLE5_EVENT_DISCONNECTED == event_type )
    {
        event_data = &app_buf[ strlen( BLE5_EVT_DISCONNECTED ) ];
        data_len = app_buf_len - ( strlen( BLE5_EVT_DISCONNECTED ) );
        if ( ( data_len < 4 ) || ( ',' != event_data[ 1 ] ) )
        {
            result = BLE5_ERROR_CMD;
        }
        else
        {
            conn = ( ( uint16_t ) event_data[ 2 ] << 8 ) | event_data[ 3 ];
            if ( ( 0 == connected ) || ( conn == connection_id ) )
            {
                connected = 0;
                notifications_enabled = 0;
                log_printf( &logger, ">>> BLE peer disconnected.\r\n" );
                result = ble5_start_advertising( ctx );
            }
        }
    }
    else if ( BLE5_EVENT_MTU_REQUEST == event_type )
    {
        event_data = &app_buf[ strlen( BLE5_EVT_MTU_REQUEST ) ];
        data_len = app_buf_len - ( strlen( BLE5_EVT_MTU_REQUEST ) );
        if ( ( data_len < 5 ) || ( ',' != event_data[ 2 ] ) )
        {
            result = BLE5_ERROR_CMD;
        }
        else
        {
            params[ 0 ] = event_data[ 0 ];
            params[ 1 ] = event_data[ 1 ];
            params[ 2 ] = ',';
            params[ 3 ] = 0;
            params[ 4 ] = BLE5_ATT_MTU_DEFAULT;
            result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSSRVMTU, params, 5 );
        }
    }
    else if ( ( BLE5_EVENT_READ == event_type ) ||
              ( BLE5_EVENT_WRITE == event_type ) ||
              ( BLE5_EVENT_WRITE_COMMAND == event_type ) )
    {
        if ( BLE5_EVENT_READ == event_type )
        {
            event_data = &app_buf[ strlen( BLE5_EVT_READ ) ];
            data_len = app_buf_len - ( strlen( BLE5_EVT_READ ) );
        }
        else if ( BLE5_EVENT_WRITE == event_type )
        {
            event_data = &app_buf[ strlen( BLE5_EVT_WRITE ) ];
            data_len = app_buf_len - ( strlen( BLE5_EVT_WRITE ) );
        }
        else
        {
            event_data = &app_buf[ strlen( BLE5_EVT_WRITE_COMMAND ) ];
            data_len = app_buf_len - ( strlen( BLE5_EVT_WRITE_COMMAND ) );
        }

        // Event attributes are encoded as: connection_id,P<id>+C<id>+E<id>.
        if ( ( data_len < BLE5_ATTRIBUTE_HEADER_SIZE ) || ( ',' != event_data[ 2 ] ) ||
            ( 'P' != event_data[ 3 ] ) || ( '+' != event_data[ 5 ] ) || ( 'C' != event_data[ 6 ] ) ||
            ( '+' != event_data[ 8 ] ) || ( 'E' != event_data[ 9 ] ) )
        {
            result = BLE5_ERROR_CMD;
        }
        else
        {
            conn = ( ( uint16_t ) event_data[ 0 ] << 8 ) | event_data[ 1 ];
            profile = event_data[ 4 ];
            characteristic = event_data[ 7 ];
            element = event_data[ 10 ];

            if ( BLE5_EVENT_READ == event_type )
            {
                uint8_t name[] = DEVICE_NAME;

                memcpy( params, &event_data[ 3 ], 8 );
                if ( ( BLE5_GAP_PROFILE_ID == profile ) &&
                     ( BLE5_DEVICE_NAME_CHARACTERISTIC_ID == characteristic ) &&
                     ( BLE5_VALUE_ELEMENT_ID == element ) )
                {
                    value_len = sizeof( name ) - 1;
                    memcpy( value, name, value_len );
                }
                else if ( ( BLE5_UART_PROFILE_ID == profile ) &&
                          ( BLE5_UART_TX_CHARACTERISTIC_ID == characteristic ) &&
                          ( BLE5_CCCD_ELEMENT_ID == element ) )
                {
                    value[ 0 ] = notifications_enabled;
                    value[ 1 ] = 0;
                    value_len = BLE5_CCCD_VALUE_SIZE;
                }
                else if ( ( BLE5_GAP_PROFILE_ID == profile ) &&
                          ( BLE5_APPEARANCE_CHARACTERISTIC_ID == characteristic ) &&
                          ( BLE5_VALUE_ELEMENT_ID == element ) )
                {
                    value[ 0 ] = 0;
                    value[ 1 ] = 0;
                    value_len = BLE5_CCCD_VALUE_SIZE;
                }
                else
                {
                    accept = 0x0A;
                }

                params[ 8 ] = ',';
                params[ 9 ] = ( uint8_t ) ( conn >> 8 );
                params[ 10 ] = ( uint8_t ) conn;
                params[ 11 ] = ',';
                params[ 12 ] = ( 0 != value_len );
                params[ 13 ] = ',';
                params[ 14 ] = accept;
                if ( 0 != value_len )
                {
                    params[ 15 ] = ',';
                    memcpy( &params[ 16 ], value, value_len );
                }
                result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSRDUPD, params,
                                       ( 0 != value_len ) ? 16 + value_len : 15 );
            }
            else if ( BLE5_OK == result )
            {
                if ( ( data_len < BLE5_ATTRIBUTE_VALUE_OFFSET ) || ( ',' != event_data[ 11 ] ) )
                {
                    result = BLE5_ERROR_CMD;
                }
                else
                {
                    data_len -= BLE5_ATTRIBUTE_VALUE_OFFSET;
                    if ( ( 0 == connected ) || ( conn != connection_id ) )
                    {
                        result = BLE5_ERROR_CMD;
                    }
                    else if ( ( BLE5_UART_PROFILE_ID == profile ) &&
                              ( BLE5_UART_RX_CHARACTERISTIC_ID == characteristic ) &&
                              ( BLE5_VALUE_ELEMENT_ID == element ) &&
                              ( data_len <= BLE5_ATT_VALUE_SIZE ) )
                    {
                        value_len = ( uint8_t ) data_len;
                        memcpy( value, &event_data[ BLE5_ATTRIBUTE_VALUE_OFFSET ], value_len );
                    }
                    else if ( ( BLE5_UART_PROFILE_ID == profile ) &&
                              ( BLE5_UART_TX_CHARACTERISTIC_ID == characteristic ) &&
                              ( BLE5_CCCD_ELEMENT_ID == element ) &&
                              ( BLE5_CCCD_VALUE_SIZE == data_len ) &&
                              ( event_data[ BLE5_ATTRIBUTE_VALUE_OFFSET ] <= 1 ) &&
                              ( 0 == event_data[ BLE5_ATTRIBUTE_VALUE_OFFSET + 1 ] ) )
                    {
                        value_len = BLE5_CCCD_VALUE_SIZE;
                        memcpy( value, &event_data[ BLE5_ATTRIBUTE_VALUE_OFFSET ], value_len );
                    }
                    else
                    {
                        accept = 0x0D;
                    }

                    if ( ( BLE5_OK == result ) && ( 0 != write_request ) )
                    {
                        params[ 0 ] = ( uint8_t ) ( conn >> 8 );
                        params[ 1 ] = ( uint8_t ) conn;
                        params[ 2 ] = ',';
                        params[ 3 ] = accept;
                        result = ble5_execute( ctx, ( uint8_t * ) BLE5_CMD_GSWRUPD, params, 4 );
                    }

                    if ( ( BLE5_OK == result ) && ( BLE5_STATUS_SUCCESS == accept ) )
                    {
                        if ( ( BLE5_UART_TX_CHARACTERISTIC_ID == characteristic ) && ( BLE5_CCCD_ELEMENT_ID == element ) )
                        {
                            notifications_enabled = value[ 0 ];
                            log_printf( &logger, ">>> Terminal notifications %s.\r\n",
                                        notifications_enabled ? "enabled" : "disabled" );
                        }
                        else
                        {
                            if ( ( ( 3 == value_len ) && ( 0 == memcmp( value, "END", 3 ) ) ) ||
                                 ( ( 5 == value_len ) && ( 0 == memcmp( value, "END\r\n", 5 ) ) ) )
                            {
                                end_requested = 1;
                            }
                            else
                            {
                                data_received = 1;
                                log_printf( &logger, "<<< Received data: " );
                                for ( uint8_t index = 0; index < value_len; index++ )
                                {
                                    log_printf( &logger, "%c", value[ index ] );
                                }
                                log_printf( &logger, "\r\n" );

                                if ( ( 0 != notifications_enabled ) && ( 0 != value_len ) )
                                {
                                    result = ble5_send_notification( ctx, conn, value, value_len );
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

static err_t ble5_example ( ble5_t *ctx )
{
    #define BLE5_CONNECTION_WAIT_LOG_MS       60000
    #define BLE5_CONNECTION_TIMEOUT_MS        60000
    #define BLE5_TERMINAL_MESSAGE_PERIOD_MS   5000
    #define BLE5_PACKET_ASSEMBLY_TIMEOUT_MS   2000
    
    static uint32_t elapsed = 0;
    static uint32_t timeout_cnt = 0;
    static uint16_t partial_wait = 0;
    static uint8_t previous_connected = 0;
    uint8_t message[] = MESSAGE_CONTENT;
    uint8_t message_data[] = MESSAGE_CONTENT "\r\n";
    uint8_t end_response[] = "END command received, closing the connection.\r\n";
    uint8_t timeout_response[] = "Timeout, closing the connection.\r\n";
    uint8_t disconnect_requested = 0;
    err_t packet_result;
    err_t result = BLE5_OK;

    if ( 0 != event_count )
    {
        app_buf_len = event_len[ event_head ];
        memcpy( app_buf, event_buf[ event_head ], app_buf_len );
        event_head = ( event_head + 1 ) % APP_EVENT_QUEUE_SIZE;
        event_count--;
        packet_result = BLE5_OK;
    }
    else
    {
        packet_result = ble5_process( ctx );
    }

    if ( BLE5_ERROR_CMD == packet_result )
    {
        result = packet_result;
    }
    else
    {
        if ( BLE5_OK == packet_result )
        {
            result = ble5_handle_event( ctx );
            if ( 0 != data_received )
            {
                timeout_cnt = 0;
                data_received = 0;
            }
        }

        if ( ( BLE5_OK == result ) && ( 0 != end_requested ) )
        {
            disconnect_requested = 1;
            if ( 0 != notifications_enabled )
            {
                result = ble5_send_notification( ctx, connection_id, end_response, sizeof( end_response ) - 1 );
            }
            if ( BLE5_OK == result )
            {
                log_printf( &logger, ">>> Terminating connection on demand.\r\n" );
                Delay_100ms( );
                result = ble5_terminate_connection( ctx );
            }
            if ( BLE5_OK == result )
            {
                end_requested = 0;
            }
        }

        if ( ( BLE5_OK == result ) && ( 0 == disconnect_requested ) )
        {
            // Detect an interrupted serial packet instead of waiting on its tail indefinitely.
            if ( 0 != rx_len )
            {
                if ( ++partial_wait >= BLE5_PACKET_ASSEMBLY_TIMEOUT_MS )
                {
                    result = BLE5_ERROR_TIMEOUT;
                }
            }
            else
            {
                partial_wait = 0;
            }
        }

        if ( ( BLE5_OK == result ) && ( 0 == disconnect_requested ) )
        {
            if ( previous_connected != connected )
            {
                previous_connected = connected;
                elapsed = 0;
                timeout_cnt = 0;
                if ( 0 != connected )
                {
                    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
                    log_printf( &logger,
                                ">>> Connection will be terminated if the Click "
                                "receives \"END\" string.\r\n" );
                }
            }

            if ( 0 == connected )
            {
                if ( ( 0 == elapsed ) || ( elapsed >= BLE5_CONNECTION_WAIT_LOG_MS ) )
                {
                    log_printf( &logger,
                                ">>> Waiting for a BLE peer to establish connection "
                                "with the Click board...\r\n" );
                    elapsed = 0;
                }
            }
            else if ( ( 0 != notifications_enabled ) &&
                      ( elapsed >= BLE5_TERMINAL_MESSAGE_PERIOD_MS ) )
            {
                result = ble5_send_notification( ctx, connection_id, message_data,
                                                 sizeof( message_data ) - 1 );
                if ( BLE5_OK == result )
                {
                    log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n",
                                ( char * ) message );
                    elapsed = 0;
                }
            }
        }

        if ( ( BLE5_OK == result ) && ( 0 != connected ) && ( 0 == disconnect_requested ) )
        {
            timeout_cnt++;
            if ( timeout_cnt >= BLE5_CONNECTION_TIMEOUT_MS )
            {
                log_printf( &logger, ">>> Terminating connection due to 60s timeout expiration.\r\n" );
                disconnect_requested = 1;
                if ( 0 != notifications_enabled )
                {
                    result = ble5_send_notification( ctx, connection_id, timeout_response,
                                                     sizeof( timeout_response ) - 1 );
                }
                if ( BLE5_OK == result )
                {
                    Delay_100ms( );
                    result = ble5_terminate_connection( ctx );
                }
            }
        }

        if ( BLE5_OK == result )
        {
            elapsed++;
            Delay_1ms( );
        }
    }

    return result;
}

// ------------------------------------------------------------------------ END