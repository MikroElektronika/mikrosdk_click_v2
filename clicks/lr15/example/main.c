/*!
 * @file main.c
 * @brief LR 15 Click Example.
 *
 * # Description
 * This example demonstrates the use of LR 15 Click board by showing
 * the communication between two Click boards configured in TEST mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LR15_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *  - LR15_CONFIG_EXAMPLE:
 * Configures device for the LoRa P2P network mode.
 *  - LR15_EXAMPLE:
 * Performs a LoRa P2P test example by exchanging messages with another LR 15 Click board.
 *
 * ## Additional Function
 * - static void lr15_clear_app_buf ( void )
 * - static void lr15_log_app_buf ( void )
 * - static err_t lr15_process ( lr15_t *ctx )
 * - static err_t lr15_read_response ( lr15_t *ctx, uint8_t *rsp, uint32_t timeout )
 * - static err_t lr15_power_up ( lr15_t *ctx )
 * - static err_t lr15_config_example ( lr15_t *ctx )
 * - static err_t lr15_example ( lr15_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lr15.h"
#include "conversions.h"
#include "generic_pointer.h"

#define DEMO_TEXT_MESSAGE   "MIKROE - LR 15 Click board"

static lr15_t lr15;
static log_t logger;

// Application buffer size
#define APP_BUFFER_SIZE     600
#define PROCESS_BUFFER_SIZE 200

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LR15_POWER_UP = 1,
    LR15_CONFIG_EXAMPLE,
    LR15_EXAMPLE

} lr15_app_state_t;

static lr15_app_state_t app_state = LR15_POWER_UP;

/**
 * @brief LR 15 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lr15_clear_app_buf ( void );

/**
 * @brief LR 15 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lr15_log_app_buf ( void );

/**
 * @brief LR 15 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr15_process ( lr15_t *ctx );

/**
 * @brief LR 15 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] timeout : Response timeout in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr15_read_response ( lr15_t *ctx, uint8_t *rsp, uint32_t timeout );

/**
 * @brief LR 15 power up function.
 * @details This function powers up the device, performs device factory reset and
 * reads system information.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr15_power_up ( lr15_t *ctx );

/**
 * @brief LR 15 config example function.
 * @details This function configures device for LoRa P2P example.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr15_config_example ( lr15_t *ctx );

/**
 * @brief LR 15 example function.
 * @details This function performs a LoRa P2P test example by exchanging messages
 * with another LR 15 Click board.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr15_example ( lr15_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr15_cfg_t lr15_cfg;  /**< Click config object. */

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
    lr15_cfg_setup( &lr15_cfg );
    LR15_MAP_MIKROBUS( lr15_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr15_init( &lr15, &lr15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = LR15_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LR15_POWER_UP:
        {
            if ( LR15_OK == lr15_power_up( &lr15 ) )
            {
                app_state = LR15_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR15_CONFIG_EXAMPLE:
        {
            if ( LR15_OK == lr15_config_example( &lr15 ) )
            {
                app_state = LR15_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR15_EXAMPLE:
        {
            lr15_example( &lr15 );
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

static void lr15_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lr15_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lr15_process ( lr15_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lr15_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LR15_OK;
    }
    return LR15_ERROR;
}

static err_t lr15_read_response ( lr15_t *ctx, uint8_t *rsp, uint32_t timeout ) 
{
    uint32_t timeout_cnt = 0;
    lr15_clear_app_buf ( );
    lr15_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LR15_RSP_ERROR ) ) )
    {
        lr15_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            lr15_log_app_buf( );
            log_error( &logger, " Timeout!" );
            return LR15_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lr15_process( ctx );
    lr15_log_app_buf( );
    if ( strstr( app_buf, LR15_RSP_ERROR ) )
    {
        log_error( &logger, " CMD!" );
        return LR15_ERROR_CMD;
    }
    log_printf( &logger, "--------------------------------\r\n" );
    return LR15_OK;
}

static err_t lr15_power_up ( lr15_t *ctx )
{
    err_t error_flag = LR15_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    lr15_reset_device( &lr15 );
    while ( LR15_OK == lr15_process( ctx ) )
    {
        lr15_log_app_buf( );
        lr15_clear_app_buf ( );
    }
    log_printf( &logger, "--------------------------------\r\n" );

    log_printf( &logger, ">>> Check communication.\r\n" );
    lr15_cmd_run( &lr15, LR15_CMD_AT );
    error_flag |= lr15_read_response( &lr15, LR15_RSP_AT, LR15_RSP_TIMEOUT_DEFAULT );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    lr15_cmd_run( &lr15, LR15_CMD_FDEFAULT );
    error_flag |= lr15_read_response( &lr15, LR15_RSP_FDEFAULT, LR15_RSP_TIMEOUT_DEFAULT );

    log_printf( &logger, ">>> Get device firmware version.\r\n" );
    lr15_cmd_get( ctx, LR15_CMD_VER );
    error_flag |= lr15_read_response( ctx, LR15_RSP_VER, LR15_RSP_TIMEOUT_DEFAULT );

    log_printf( &logger, ">>> Get module ID.\r\n" );
    lr15_cmd_get( ctx, LR15_CMD_ID );
    error_flag |= lr15_read_response( ctx, LR15_RSP_ID, LR15_RSP_TIMEOUT_DEFAULT );

    return error_flag;
}

static err_t lr15_config_example ( lr15_t *ctx )
{
    err_t error_flag = LR15_OK;

    log_printf( &logger, ">>> Enter TEST mode.\r\n" );
    lr15_cmd_set( ctx, LR15_CMD_MODE, LR15_PARAM_MODE_TEST );
    error_flag |= lr15_read_response( ctx, LR15_RSP_MODE, LR15_RSP_TIMEOUT_DEFAULT );

    log_printf( &logger, ">>> Check test mode and RF configuration.\r\n" );
    lr15_cmd_get( ctx, LR15_CMD_TEST );
    error_flag |= lr15_read_response( ctx, LR15_RSP_TEST_RFCFG, LR15_RSP_TIMEOUT_DEFAULT );
    
    // Default RF configuration: FREQUENCY, SF, BANDWIDTH, TX PR, RX PR, TX POWER, CRC, IQ, NET
    #define RF_CFG_DEFAULT "868, SF7, 125, 8, 8, 14, ON, OFF, OFF"
    log_printf( &logger, ">>> Set RF configuration.\r\n" );
    lr15_cmd_param_set( ctx, LR15_CMD_TEST, LR15_PARAM_TEST_RFCFG, RF_CFG_DEFAULT );
    error_flag |= lr15_read_response( ctx, LR15_RSP_TEST_RFCFG, LR15_RSP_TIMEOUT_DEFAULT );

    return error_flag;
}

static err_t lr15_example ( lr15_t *ctx )
{
    err_t error_flag = LR15_OK;
    uint8_t msg_hex[ 201 ] = { 0 };
    uint8_t byte_hex[ 3 ] = { 0 };
    uint8_t len[ 10 ] = { 0 };
    uint8_t rssi[ 10 ] = { 0 };
    uint8_t snr[ 10 ] = { 0 };
    uint8_t cnt = 0;

    memset( msg_hex, 0, sizeof ( msg_hex ) );
    for ( cnt = 0; ( cnt < strlen ( DEMO_TEXT_MESSAGE ) ) && ( cnt < 100 ); cnt++ ) 
    {
        uint8_to_hex ( DEMO_TEXT_MESSAGE[ cnt ], byte_hex );
        strcat ( msg_hex, byte_hex );
    }
    log_printf( &logger, ">>> Send message: \"%s\".\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    lr15_cmd_param_set( ctx, LR15_CMD_TEST, LR15_PARAM_TEST_TXLRPKT, msg_hex );
    error_flag |= lr15_read_response( ctx, LR15_RSP_TEST_TX_DONE, LR15_RSP_TIMEOUT_DEFAULT );
    
    if ( LR15_OK == error_flag )
    {
        memset( msg_hex, 0, sizeof ( msg_hex ) );
        #define RX_MODE_TIMEOUT 30000
        log_printf( &logger, ">>> Go to RX mode (timeout: 30s).\r\n" );
        lr15_cmd_param_get( ctx, LR15_CMD_TEST, LR15_PARAM_TEST_RXLRPKT );
        error_flag |= lr15_read_response( ctx, LR15_RSP_TEST_RX, RX_MODE_TIMEOUT );
    }
    
    if ( LR15_OK == error_flag )
    {
        uint8_t * __generic_ptr start_ptr = strstr( app_buf, LR15_RSP_TEST_RXLEN );
        uint8_t * __generic_ptr end_ptr = NULL;
        if ( start_ptr )
        {
            start_ptr = start_ptr + strlen ( LR15_RSP_TEST_RXLEN );
            end_ptr = strstr ( start_ptr, "," );
            memcpy ( len, start_ptr, end_ptr - start_ptr );

            start_ptr = strstr ( end_ptr, ":" ) + 1;
            end_ptr = strstr ( start_ptr, "," );
            memcpy ( rssi, start_ptr, end_ptr - start_ptr );
            
            start_ptr = strstr ( end_ptr, ":" ) + 1;
            end_ptr = strstr ( start_ptr, "\r\n" );
            memcpy ( snr, start_ptr, end_ptr - start_ptr );

            start_ptr = strstr ( end_ptr, "\"" ) + 1;
            end_ptr = strstr ( start_ptr, "\"" );
            memcpy ( msg_hex, start_ptr, end_ptr - start_ptr );

            for ( cnt = 0; cnt < strlen ( msg_hex ); cnt += 2 )
            {
                msg_hex[ cnt / 2 ] = hex_to_uint8 ( &msg_hex [ cnt ] );
            }
            msg_hex[ cnt / 2 ] = 0;
            log_printf( &logger, ">>> Parse received message.\r\n" );
            log_printf ( &logger, " Message: %s\r\n", msg_hex );
            log_printf ( &logger, " LEN: %s\r\n", len );
            log_printf ( &logger, " RSSI: %s\r\n", rssi );
            log_printf ( &logger, " SNR: %s\r\n", snr );
            log_printf( &logger, "--------------------------------\r\n" );
        }
    }

    Delay_ms ( 1000 );

    return error_flag;
}

// ------------------------------------------------------------------------ END
