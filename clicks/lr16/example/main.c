/*!
 * @file main.c
 * @brief LR 16 Click Example.
 *
 * # Description
 * This example demonstrates the use of LR 16 Click board by showing
 * the communication between two Click boards configured in P2P network mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LR16_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *  - LR16_CONFIG_EXAMPLE:
 * Configures device for the LoRa P2P network mode.
 *  - LR16_EXAMPLE:
 * Performs a LoRa P2P example by exchanging messages with another LR 16 Click board.
 *
 * ## Additional Function
 * - static void lr16_clear_app_buf ( void )
 * - static void lr16_log_app_buf ( void )
 * - static err_t lr16_process ( lr16_t *ctx )
 * - static err_t lr16_read_response ( lr16_t *ctx, uint8_t *rsp )
 * - static err_t lr16_power_up ( lr16_t *ctx )
 * - static err_t lr16_config_example ( lr16_t *ctx )
 * - static err_t lr16_example ( lr16_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lr16.h"
#include "conversions.h"
#include "generic_pointer.h"

#define DEMO_TEXT_MESSAGE   "MIKROE - LR 16 Click board"

// Application buffer size
#define APP_BUFFER_SIZE     600
#define PROCESS_BUFFER_SIZE 200

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LR16_POWER_UP = 1,
    LR16_CONFIG_EXAMPLE,
    LR16_EXAMPLE

} lr16_app_state_t;

static lr16_t lr16;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static lr16_app_state_t app_state = LR16_POWER_UP;

/**
 * @brief LR 16 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lr16_clear_app_buf ( void );

/**
 * @brief LR 16 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lr16_log_app_buf ( void );

/**
 * @brief LR 16 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr16_process ( lr16_t *ctx );

/**
 * @brief LR 16 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr16_read_response ( lr16_t *ctx, uint8_t *rsp );

/**
 * @brief LR 16 power up function.
 * @details This function powers up the device, performs device factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr16_power_up ( lr16_t *ctx );

/**
 * @brief LR 16 config example function.
 * @details This function configures device for LoRa P2P example.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr16_config_example ( lr16_t *ctx );

/**
 * @brief LR 16 example function.
 * @details This function performs a LoRa P2P example by exchanging messages with another LR 16 Click board.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr16_example ( lr16_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr16_cfg_t lr16_cfg;  /**< Click config object. */

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
    lr16_cfg_setup( &lr16_cfg );
    LR16_MAP_MIKROBUS( lr16_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr16_init( &lr16, &lr16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = LR16_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LR16_POWER_UP:
        {
            if ( LR16_OK == lr16_power_up( &lr16 ) )
            {
                app_state = LR16_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR16_CONFIG_EXAMPLE:
        {
            if ( LR16_OK == lr16_config_example( &lr16 ) )
            {
                app_state = LR16_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR16_EXAMPLE:
        {
            lr16_example( &lr16 );
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

static void lr16_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lr16_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lr16_process ( lr16_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lr16_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LR16_OK;
    }
    return LR16_ERROR;
}

static err_t lr16_read_response ( lr16_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS 60000
    uint32_t timeout_cnt = 0;
    lr16_clear_app_buf ( );
    lr16_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_ERROR ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_PARAM_ERROR ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_BUSY_ERROR ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_TEST_PARAM_OVERFLOW ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_NO_NETWORK_JOINED ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_RX_ERROR ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_DUTYCYCLE_RESTRICTED ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_CRYPTO_ERROR ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_INVALID_MODE ) ) &&
            ( 0 == strstr( app_buf, LR16_RSP_INVALID_ROLE ) ) )
    {
        lr16_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            lr16_log_app_buf( );
            lr16_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LR16_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lr16_process( ctx );
    lr16_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return LR16_OK;
    }
    return LR16_ERROR_CMD;
}

static err_t lr16_power_up ( lr16_t *ctx )
{
    err_t error_flag = LR16_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    lr16_reset_device( &lr16 );    
    while ( LR16_OK == lr16_process( ctx ) )
    {
        lr16_log_app_buf( );
        lr16_clear_app_buf ( );
    }
    log_printf( &logger, "--------------------------------\r\n" );

    log_printf( &logger, ">>> Check communication.\r\n" );
    lr16_cmd_run( &lr16, LR16_CMD_AT );
    error_flag |= lr16_read_response( &lr16, LR16_RSP_OK );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    lr16_cmd_run( &lr16, LR16_CMD_FACTORY_RESET );
    error_flag |= lr16_read_response( &lr16, LR16_RSP_OK );

    log_printf( &logger, ">>> SW reset.\r\n" );
    lr16_cmd_run( &lr16, LR16_CMD_RESET );
    error_flag |= lr16_read_response( &lr16, LR16_EVT_READY );

    log_printf( &logger, ">>> Get device firmware version.\r\n" );
    lr16_cmd_get( ctx, LR16_CMD_GET_FW_VERSION );
    error_flag |= lr16_read_response( ctx, LR16_RSP_OK );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    lr16_cmd_get( ctx, LR16_CMD_GET_SERIAL_NUMBER );
    error_flag |= lr16_read_response( ctx, LR16_RSP_OK );

    return error_flag;
}

static err_t lr16_config_example ( lr16_t *ctx )
{
    err_t error_flag = LR16_OK;
    
    #define OPERATING_MODE_P2P "1"
    log_printf( &logger, ">>> Set LoRa P2P operating mode.\r\n" );
    lr16_cmd_set( ctx, LR16_CMD_SET_OPERATING_MODE_USER, OPERATING_MODE_P2P );
    error_flag |= lr16_read_response( ctx, LR16_RSP_OK );

    log_printf( &logger, ">>> SW reset.\r\n" );
    lr16_cmd_run( &lr16, LR16_CMD_RESET );
    error_flag |= lr16_read_response( &lr16, LR16_EVT_READY );

    #define P2P_RX_ENABLE "1"
    log_printf( &logger, ">>> Enable P2P RX.\r\n" );
    lr16_cmd_set( ctx, LR16_CMD_P2P_RX, P2P_RX_ENABLE );
    error_flag |= lr16_read_response( ctx, LR16_RSP_OK );

    return error_flag;
}

static err_t lr16_example ( lr16_t *ctx )
{
    err_t error_flag = LR16_OK;
    uint8_t msg_hex[ 201 ] = { 0 };
    uint8_t byte_hex[ 3 ] = { 0 };
    uint8_t mac_addr[ 20 ] = { 0 };
    uint8_t rssi[ 10 ] = { 0 };
    uint8_t cnt = 0;

    memset( msg_hex, 0, sizeof ( msg_hex ) );
    for ( cnt = 0; ( cnt < strlen ( DEMO_TEXT_MESSAGE ) ) && ( cnt < 100 ); cnt++ ) 
    {
        uint8_to_hex ( DEMO_TEXT_MESSAGE[ cnt ], byte_hex );
        strcat ( msg_hex, byte_hex );
    }
    log_printf( &logger, ">>> Send message: \"%s\".\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    lr16_cmd_set( ctx, LR16_CMD_P2P_BROADCAST_TX, msg_hex );
    error_flag |= lr16_read_response( ctx, LR16_EVT_P2P_TX_RESP );
    
    memset( msg_hex, 0, sizeof ( msg_hex ) );
    log_printf( &logger, ">>> Waiting for a P2P response [60s timeout].\r\n" );
    error_flag |= lr16_read_response( ctx, LR16_EVT_P2P_RX_DATA );
    
    if ( LR16_OK == error_flag )
    {
        uint8_t * __generic_ptr start_ptr = strstr( app_buf, LR16_EVT_P2P_RX_DATA );
        uint8_t * __generic_ptr end_ptr = NULL;
        if ( start_ptr )
        {
            start_ptr = start_ptr + strlen ( LR16_EVT_P2P_RX_DATA );
            end_ptr = strstr ( start_ptr, "," );
            memcpy ( mac_addr, start_ptr, end_ptr - start_ptr );
            
            start_ptr = end_ptr + 1;
            end_ptr = strstr ( start_ptr, "," );
            memcpy ( rssi, start_ptr, end_ptr - start_ptr );

            start_ptr = end_ptr + 1;
            end_ptr = strstr ( start_ptr, "," );

            start_ptr = end_ptr + 1;
            end_ptr = strstr ( start_ptr, "\r\n" );
            memcpy ( msg_hex, start_ptr, end_ptr - start_ptr );

            for ( cnt = 0; cnt < strlen ( msg_hex ); cnt += 2 )
            {
                msg_hex[ cnt / 2 ] = hex_to_uint8 ( &msg_hex [ cnt ] );
            }
            msg_hex[ cnt / 2 ] = 0;

            log_printf( &logger, ">>> Parse received message.\r\n" );
            log_printf ( &logger, " Message: %s\r\n", msg_hex );
            log_printf ( &logger, " MAC address: %s\r\n", mac_addr );
            log_printf ( &logger, " RSSI: %s\r\n", rssi );
            log_printf( &logger, "--------------------------------\r\n" );
        }
    }
    Delay_ms ( 1000 );
    
    return error_flag;
}

// ------------------------------------------------------------------------ END
