/*!
 * @file main.c
 * @brief BLE2 Click Example.
 *
 * # Description
 * This example demonstrates the use of BLE2 Click by processing data from a
 * connected BLE terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split into three stages:
 *  - BLE2_POWER_UP:
 * Wakes the module and checks UART communication.
 *  - BLE2_CONFIG_EXAMPLE:
 * Restores factory settings, enables MLDP, sets the device name, and starts advertising.
 *  - BLE2_EXAMPLE:
 * Exchanges text with a connected BLE terminal and restarts advertising after disconnection.
 *
 * ## Additional Function
 * - static void ble2_clear_app_buf ( void )
 * - static void ble2_log_app_buf ( void )
 * - static err_t ble2_process ( ble2_t *ctx )
 * - static err_t ble2_read_response ( ble2_t *ctx, char *rsp, uint32_t max_rsp_time )
 * - static err_t ble2_power_up ( ble2_t *ctx )
 * - static err_t ble2_config_example ( ble2_t *ctx )
 * - static err_t ble2_example ( ble2_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * The short device name leaves room for the MLDP UUID in the advertising packet.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ble2.h"

#ifndef MIKROBUS_POSITION_BLE2
    #define MIKROBUS_POSITION_BLE2              MIKROBUS_1
#endif

// Local device name. MLDP advertising leaves room for up to eight characters.
#define DEVICE_NAME                             "BLE2"

/** Application receive buffer size in bytes. */
#define APP_BUFFER_SIZE                         600

/** Temporary UART receive buffer size in bytes. */
#define PROCESS_BUFFER_SIZE                     200

static ble2_t ble2;                             /**< Click context object. */
static log_t logger;                            /**< Logger object. */
static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 }; /**< Application receive buffer. */
static int32_t app_buf_len = 0;                 /**< Number of bytes in the application buffer. */

/**
 * @brief BLE2 example states.
 * @details States used to sequence power-up, configuration, and terminal use.
 */
typedef enum
{
    BLE2_POWER_UP = 1,
    BLE2_CONFIG_EXAMPLE,
    BLE2_EXAMPLE

} ble2_app_state_t;

static ble2_app_state_t app_state = BLE2_POWER_UP; /**< Current example state. */

/**
 * @brief BLE2 application buffer clearing function.
 * @details This function clears the application buffer and resets its length.
 * @return None.
 * @note None.
 */
static void ble2_clear_app_buf ( void );

/**
 * @brief BLE2 application buffer logging function.
 * @details This function writes the application buffer to the USB UART logger.
 * @return None.
 * @note None.
 */
static void ble2_log_app_buf ( void );

/**
 * @brief BLE2 response processing function.
 * @details This function reads available module data into the application
 * buffer.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @return @li @c  0 - Data read,
 *         @li @c -1 - No data available.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ble2_process ( ble2_t *ctx );

/**
 * @brief BLE2 response reading function.
 * @details This function waits for an expected response, then reads and
 * displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - Expected response received,
 *         @li @c -2 - Response timeout,
 *         @li @c -3 - Command error response received.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ble2_read_response ( ble2_t *ctx, char *rsp, uint32_t max_rsp_time );

/**
 * @brief BLE2 power-up function.
 * @details This function waits for Command mode and displays the firmware
 * version.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @return @li @c    0 - Success,
 *         @li @c != 0 - Response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ble2_power_up ( ble2_t *ctx );

/**
 * @brief BLE2 example configuration function.
 * @details This function restores factory settings, configures MLDP and the
 * device name, reboots the module, and starts advertising.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @return @li @c    0 - Success,
 *         @li @c != 0 - Command or response error.
 * See #err_t definition for detailed explanation.
 * @note The settings are stored in the module nonvolatile memory.
 */
static err_t ble2_config_example ( ble2_t *ctx );

/**
 * @brief BLE2 terminal example function.
 * @details This function exchanges text with a connected MLDP terminal and
 * restarts advertising after the connection closes.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @return @li @c    0 - Success,
 *         @li @c != 0 - Command or response error.
 * See #err_t definition for detailed explanation.
 * @note Send "END" from the peer to close the connection before the timeout.
 */
static err_t ble2_example ( ble2_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ble2_cfg_t ble2_cfg;  /**< Click config object. */

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
    ble2_cfg_setup( &ble2_cfg );
    BLE2_MAP_MIKROBUS( ble2_cfg, MIKROBUS_POSITION_BLE2 );
    if ( UART_ERROR == ble2_init( &ble2, &ble2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BLE2_ERROR == ble2_default_cfg( &ble2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = BLE2_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case BLE2_POWER_UP:
        {
            if ( BLE2_OK == ble2_power_up( &ble2 ) )
            {
                app_state = BLE2_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE2_CONFIG_EXAMPLE:
        {
            if ( BLE2_OK == ble2_config_example( &ble2 ) )
            {
                app_state = BLE2_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case BLE2_EXAMPLE:
        {
            ble2_example( &ble2 );
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

static void ble2_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ble2_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ble2_process ( ble2_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ble2_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
            memmove( app_buf, &app_buf[ overflow_bytes ], app_buf_len );
            memset( &app_buf[ app_buf_len ], 0, overflow_bytes );
        }
        for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ )
        {
            if ( rx_buf[ rx_cnt ] )
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return BLE2_OK;
    }
    return BLE2_ERROR;
}

static err_t ble2_read_response ( ble2_t *ctx, char *rsp, uint32_t max_rsp_time )
{
    uint32_t timeout_cnt = 0;
    ble2_clear_app_buf( );
    ble2_process( ctx );
    while ( ( NULL == strstr( ( char * ) app_buf, rsp ) ) &&
            ( NULL == strstr( ( char * ) app_buf, BLE2_RSP_ERROR ) ) )
    {
        ble2_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            ble2_log_app_buf( );
            ble2_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return BLE2_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 200 );
    ble2_process( ctx );
    ble2_log_app_buf( );
    if ( NULL != strstr( ( char * ) app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return BLE2_OK;
    }
    return BLE2_ERROR_CMD;
}

static err_t ble2_power_up ( ble2_t *ctx )
{
    err_t error_flag = BLE2_OK;
    uint8_t firmware_cmd[] = BLE2_CMD_GET_FIRMWARE_VERSION;

    #define BLE2_POWER_UP_RSP_TIME_MS            1000
    #define BLE2_POWER_UP_RESET_TIME_MS          3000

    log_printf( &logger, ">>> Wake device.\r\n" );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_COMMAND_MODE, BLE2_POWER_UP_RESET_TIME_MS );

    log_printf( &logger, ">>> Get firmware version.\r\n" );
    error_flag |= ble2_cmd_run( ctx, firmware_cmd );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_FIRMWARE_VERSION, BLE2_POWER_UP_RSP_TIME_MS );

    return error_flag;
}

static err_t ble2_config_example ( ble2_t *ctx )
{
    err_t error_flag = BLE2_OK;
    uint8_t factory_default_cmd[] = BLE2_CMD_FACTORY_DEFAULT;
    uint8_t factory_reset[] = BLE2_FACTORY_RESET;
    uint8_t device_name_cmd[] = BLE2_CMD_DEVICE_NAME;
    uint8_t features_cmd[] = BLE2_CMD_SUPPORTED_FEATURES;
    uint8_t mldp_feature[] = BLE2_FEATURE_MLDP;
    uint8_t reboot_cmd[] = BLE2_CMD_REBOOT "," BLE2_REBOOT;
    uint8_t display_info_cmd[] = BLE2_CMD_DISPLAY_CRITICAL_INFO;
    uint8_t advertise_cmd[] = BLE2_CMD_START_ADVERTISING;

    #define BLE2_CONFIG_RSP_TIME_MS              1000
    #define BLE2_CONFIG_RESET_TIME_MS            3000

    uint8_t device_name[] = DEVICE_NAME;

    log_printf( &logger, ">>> Restore factory settings.\r\n" );
    error_flag |= ble2_cmd_set( ctx, factory_default_cmd, factory_reset );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_OK, BLE2_CONFIG_RSP_TIME_MS );

    log_printf( &logger, ">>> Set device name to \"%s\".\r\n", ( char * ) device_name );
    error_flag |= ble2_cmd_set( ctx, device_name_cmd, device_name );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_OK, BLE2_CONFIG_RSP_TIME_MS );

    log_printf( &logger, ">>> Enable MLDP service.\r\n" );
    error_flag |= ble2_cmd_set( ctx, features_cmd, mldp_feature );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_OK, BLE2_CONFIG_RSP_TIME_MS );

    log_printf( &logger, ">>> Reboot device.\r\n" );
    error_flag |= ble2_cmd_run( ctx, reboot_cmd );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_COMMAND_MODE, BLE2_CONFIG_RESET_TIME_MS );

    log_printf( &logger, ">>> Display device information.\r\n" );
    error_flag |= ble2_cmd_run( ctx, display_info_cmd );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_SERVER_SERVICE, BLE2_CONFIG_RSP_TIME_MS );

    log_printf( &logger, ">>> Start advertising.\r\n" );
    error_flag |= ble2_cmd_run( ctx, advertise_cmd );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_OK, BLE2_CONFIG_RSP_TIME_MS );

    return error_flag;
}

static err_t ble2_example ( ble2_t *ctx )
{
    err_t error_flag = BLE2_OK;
    uint32_t timeout_cnt = 0;
    uint8_t disconnect_cmd[] = BLE2_CMD_DISCONNECT;
    uint8_t advertise_cmd[] = BLE2_CMD_START_ADVERTISING;

    #define MESSAGE_CONTENT                      "BLE2 Click board - demo example."
    #define BT_TERMINAL_TIMEOUT_MS               60000
    #define BT_TERMINAL_MESSAGE_FREQ_MS          5000
    #define BT_TERMINAL_RX_DELAY_MS              100
    #define BLE2_TERMINAL_RSP_TIME_MS            1000
    #define BLE2_CONNECTION_WAIT_LOG_MS          60000
    #define TERMINATION_CMD                      "END"
    #define TERMINATION_RESPONSE                 "END command received, closing the connection."
    #define TERMINATION_TIMEOUT                  "Timeout, closing the connection."
    #define NEW_LINE_STRING                      "\r\n"

    uint8_t message[] = MESSAGE_CONTENT;
    uint8_t new_line[] = NEW_LINE_STRING;
    uint8_t termination_response[] = TERMINATION_RESPONSE;
    uint8_t termination_timeout[] = TERMINATION_TIMEOUT;

    log_printf( &logger, ">>> Waiting for a BLE peer to establish connection with the Click board...\r\n" );
    ble2_clear_app_buf( );
    while ( BLE2_CONNECTION_DISCONNECTED == ble2_get_connection_pin( ctx ) )
    {
        ble2_process( ctx );
        if ( timeout_cnt++ >= BLE2_CONNECTION_WAIT_LOG_MS )
        {
            log_printf( &logger, ">>> Waiting for a BLE peer to establish connection with the Click board...\r\n" );
            timeout_cnt = 0;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 200 );
    ble2_process( ctx );
    ble2_log_app_buf( );
    log_printf( &logger, "--------------------------------\r\n" );
    timeout_cnt = 0;

    ble2_set_mode_pin( ctx, BLE2_MODE_MLDP );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_MLDP_MODE, BLE2_TERMINAL_RSP_TIME_MS );

    log_printf( &logger, ">>> Waiting for data (up to 60 seconds)...\r\n" );
    log_printf( &logger, ">>> Connection will be terminated if the Click receives an \"END\" string.\r\n" );
    for ( ; BLE2_CONNECTION_CONNECTED == ble2_get_connection_pin( ctx ); )
    {
        ble2_clear_app_buf( );
        if ( BLE2_OK == ble2_process( ctx ) )
        {
            Delay_ms( BT_TERMINAL_RX_DELAY_MS );
            timeout_cnt = 0;
            ble2_process( ctx );
            log_printf( &logger, "<<< Received data: " );
            ble2_log_app_buf( );
            log_printf( &logger, "\r\n" );

            if ( NULL != strstr( ( char * ) app_buf, TERMINATION_CMD ) )
            {
                log_printf( &logger, ">>> Terminating connection on demand.\r\n" );
                ble2_generic_write( ctx, termination_response, ( uint16_t ) strlen( ( char * ) termination_response ) );
                ble2_generic_write( ctx, new_line, ( uint16_t ) strlen( ( char * ) new_line ) );
                Delay_ms( BT_TERMINAL_RX_DELAY_MS );
                break;
            }
        }

        timeout_cnt++;
        if ( 0 == ( timeout_cnt % BT_TERMINAL_MESSAGE_FREQ_MS ) )
        {
            log_printf( &logger, ">>> Sending \"%s\" message to connected device.\r\n", ( char * ) message );
            ble2_generic_write( ctx, message, ( uint16_t ) strlen( ( char * ) message ) );
            ble2_generic_write( ctx, new_line, ( uint16_t ) strlen( ( char * ) new_line ) );
            Delay_ms( BT_TERMINAL_RX_DELAY_MS );
        }

        if ( BT_TERMINAL_TIMEOUT_MS < timeout_cnt )
        {
            log_printf( &logger, ">>> Terminating connection due to 60s timeout expiration.\r\n" );
            ble2_generic_write( ctx, termination_timeout, ( uint16_t ) strlen( ( char * ) termination_timeout ) );
            ble2_generic_write( ctx, new_line, ( uint16_t ) strlen( ( char * ) new_line ) );
            Delay_ms( BT_TERMINAL_RX_DELAY_MS );
            break;
        }
        Delay_ms( 1 );
    }

    Delay_ms( BT_TERMINAL_RX_DELAY_MS );
    ble2_set_mode_pin( ctx, BLE2_MODE_COMMAND );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_COMMAND_MODE, BLE2_TERMINAL_RSP_TIME_MS );

    if ( BLE2_CONNECTION_CONNECTED == ble2_get_connection_pin( ctx ) )
    {
        log_printf( &logger, ">>> Disconnecting BLE peer.\r\n" );
        error_flag |= ble2_cmd_run( ctx, disconnect_cmd );
        error_flag |= ble2_read_response( ctx, BLE2_RSP_DISCONNECTED, BLE2_TERMINAL_RSP_TIME_MS );
    }
    else
    {
        log_printf( &logger, ">>> BLE peer disconnected.\r\n" );
    }

    log_printf( &logger, ">>> Restart advertising.\r\n" );
    error_flag |= ble2_cmd_run( ctx, advertise_cmd );
    error_flag |= ble2_read_response( ctx, BLE2_RSP_OK, BLE2_TERMINAL_RSP_TIME_MS );

    return error_flag;
}

// ------------------------------------------------------------------------ END
