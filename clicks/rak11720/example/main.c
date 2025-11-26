/*!
 * @file main.c
 * @brief RAK11720 Click Example.
 *
 * # Description
 * This example demonstrates the use of RAK11720 Click board by showing
 * the communication between two Click boards configured in P2P network mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - RAK11720_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *  - RAK11720_CONFIG_EXAMPLE:
 * Configures device for the LoRa P2P network mode.
 *  - RAK11720_EXAMPLE:
 * Performs a LoRa P2P example by exchanging messages with another RAK11720 Click board.
 *
 * ## Additional Function
 * - static void rak11720_clear_app_buf ( void )
 * - static void rak11720_log_app_buf ( void )
 * - static err_t rak11720_process ( rak11720_t *ctx )
 * - static err_t rak11720_read_response ( rak11720_t *ctx, uint8_t *rsp )
 * - static err_t rak11720_power_up ( rak11720_t *ctx )
 * - static err_t rak11720_config_example ( rak11720_t *ctx )
 * - static err_t rak11720_example ( rak11720_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rak11720.h"
#include "conversions.h"
#include "generic_pointer.h"

#define DEMO_TEXT_MESSAGE   "MIKROE - RAK11720 Click board"

static rak11720_t rak11720;
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
    RAK11720_POWER_UP = 1,
    RAK11720_CONFIG_EXAMPLE,
    RAK11720_EXAMPLE

} rak11720_app_state_t;

static rak11720_app_state_t app_state = RAK11720_POWER_UP;

/**
 * @brief RAK11720 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void rak11720_clear_app_buf ( void );

/**
 * @brief RAK11720 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void rak11720_log_app_buf ( void );

/**
 * @brief RAK11720 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak11720_process ( rak11720_t *ctx );

/**
 * @brief RAK11720 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak11720_read_response ( rak11720_t *ctx, uint8_t *rsp );

/**
 * @brief RAK11720 power up function.
 * @details This function powers up the device, performs device factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak11720_power_up ( rak11720_t *ctx );

/**
 * @brief RAK11720 config example function.
 * @details This function configures device for LoRa P2P example.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak11720_config_example ( rak11720_t *ctx );

/**
 * @brief RAK11720 example function.
 * @details This function performs a LoRa P2P example by exchanging messages with another RAK11720 Click board.
 * @param[in] ctx : Click context object.
 * See #rak11720_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak11720_example ( rak11720_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rak11720_cfg_t rak11720_cfg;  /**< Click config object. */

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
    rak11720_cfg_setup( &rak11720_cfg );
    RAK11720_MAP_MIKROBUS( rak11720_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rak11720_init( &rak11720, &rak11720_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = RAK11720_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case RAK11720_POWER_UP:
        {
            if ( RAK11720_OK == rak11720_power_up( &rak11720 ) )
            {
                app_state = RAK11720_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RAK11720_CONFIG_EXAMPLE:
        {
            if ( RAK11720_OK == rak11720_config_example( &rak11720 ) )
            {
                app_state = RAK11720_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RAK11720_EXAMPLE:
        {
            rak11720_example( &rak11720 );
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

static void rak11720_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void rak11720_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t rak11720_process ( rak11720_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = rak11720_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return RAK11720_OK;
    }
    return RAK11720_ERROR;
}

static err_t rak11720_read_response ( rak11720_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS    120000
    uint32_t timeout_cnt = 0;
    rak11720_clear_app_buf ( );
    rak11720_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, RAK11720_RSP_ERROR ) ) &&
            ( 0 == strstr( app_buf, RAK11720_RSP_PARAM_ERROR ) ) &&
            ( 0 == strstr( app_buf, RAK11720_RSP_BUSY_ERROR ) ) &&
            ( 0 == strstr( app_buf, RAK11720_RSP_TEST_PARAM_OVERFLOW ) ) &&
            ( 0 == strstr( app_buf, RAK11720_RSP_NO_CLASSB_ENABLE ) ) &&
            ( 0 == strstr( app_buf, RAK11720_RSP_NO_NETWORK_JOINED ) ) &&
            ( 0 == strstr( app_buf, RAK11720_RSP_RX_ERROR ) ) )
    {
        rak11720_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            rak11720_log_app_buf( );
            rak11720_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return RAK11720_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    rak11720_process( ctx );
    rak11720_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return RAK11720_OK;
    }
    return RAK11720_ERROR_CMD;
}

static err_t rak11720_power_up ( rak11720_t *ctx )
{
    err_t error_flag = RAK11720_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    rak11720_reset_device( &rak11720 );
    error_flag |= rak11720_read_response( &rak11720, RAK11720_RSP_INITIAL );

    log_printf( &logger, ">>> Check communication.\r\n" );
    rak11720_cmd_run( &rak11720, RAK11720_CMD_AT );
    error_flag |= rak11720_read_response( &rak11720, RAK11720_RSP_OK );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    rak11720_cmd_run( &rak11720, RAK11720_CMD_FACTORY_RESET );
    error_flag |= rak11720_read_response( &rak11720, RAK11720_RSP_INITIAL );

    log_printf( &logger, ">>> Toggle command echo.\r\n" );
    rak11720_cmd_run( &rak11720, RAK11720_CMD_TOGGLE_ECHO );
    error_flag |= rak11720_read_response( &rak11720, RAK11720_RSP_OK );
    
    log_printf( &logger, ">>> Get device model ID.\r\n" );
    rak11720_cmd_get( ctx, RAK11720_CMD_GET_MODEL_ID );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    log_printf( &logger, ">>> Get device firmware version.\r\n" );
    rak11720_cmd_get( ctx, RAK11720_CMD_GET_FW_VERSION );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    rak11720_cmd_get( ctx, RAK11720_CMD_GET_SERIAL_NUMBER );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    log_printf( &logger, ">>> Get BLE MAC address.\r\n" );
    rak11720_cmd_get( ctx, RAK11720_CMD_GET_BLE_MAC_ADDRESS );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    return error_flag;
}

static err_t rak11720_config_example ( rak11720_t *ctx )
{
    err_t error_flag = RAK11720_OK;
    #define NETWORK_WORK_MODE_P2P_LORA "0"
    log_printf( &logger, ">>> Get network work mode.\r\n" );
    rak11720_cmd_get( ctx, RAK11720_CMD_NETWORK_WORK_MODE );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );
    if ( !strstr( app_buf, NETWORK_WORK_MODE_P2P_LORA ) )
    {
        log_printf( &logger, ">>> Set LoRa P2P network work mode.\r\n" );
        rak11720_cmd_set( ctx, RAK11720_CMD_NETWORK_WORK_MODE, NETWORK_WORK_MODE_P2P_LORA );
        error_flag |= rak11720_read_response( ctx, RAK11720_RSP_INITIAL );
    }
    #define P2P_MODE_FREQUENCY "868000000"
    log_printf( &logger, ">>> Set P2P mode frequency to 868 MHz.\r\n" );
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_MODE_FREQUENCY, P2P_MODE_FREQUENCY );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    #define P2P_MODE_SPREADING_FACTOR "12"
    log_printf( &logger, ">>> Set P2P mode spreading factor to 12.\r\n" );
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_MODE_SPREADING_FACTOR, P2P_MODE_SPREADING_FACTOR );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    #define P2P_MODE_BANDWIDTH "0"
    log_printf( &logger, ">>> Set P2P mode bandwidth to 125 kHz.\r\n" );
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_MODE_BANDWIDTH, P2P_MODE_BANDWIDTH );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    #define P2P_MODE_CODE_RATE "0"
    log_printf( &logger, ">>> Set P2P mode code rate to 4/5.\r\n" );
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_MODE_CODE_RATE, P2P_MODE_CODE_RATE );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    #define P2P_MODE_PREAMBLE_LENGTH "8"
    log_printf( &logger, ">>> Set P2P mode preamble length to 8.\r\n" );
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_MODE_PREAMBLE_LENGTH, P2P_MODE_PREAMBLE_LENGTH );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    #define P2P_MODE_TX_POWER "22"
    log_printf( &logger, ">>> Set P2P mode TX power to 22 dBm.\r\n" );
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_MODE_TX_POWER, P2P_MODE_TX_POWER );
    error_flag |= rak11720_read_response( ctx, RAK11720_RSP_OK );

    return error_flag;
}

static err_t rak11720_example ( rak11720_t *ctx )
{
    err_t error_flag = RAK11720_OK;
    uint8_t msg_hex[ 201 ] = { 0 };
    uint8_t byte_hex[ 3 ] = { 0 };
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
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_TX_MODE, msg_hex );
    error_flag |= rak11720_read_response( ctx, RAK11720_EVT_TX_P2P );
    
    memset( msg_hex, 0, sizeof ( msg_hex ) );
    #define P2P_RX_MODE_TIMEOUT "30000"
    log_printf( &logger, ">>> Go to P2P RX mode with a 30s timeout.\r\n" );
    rak11720_cmd_set( ctx, RAK11720_CMD_P2P_RX_MODE, P2P_RX_MODE_TIMEOUT );
    error_flag |= rak11720_read_response( ctx, RAK11720_EVT_RX_P2P );
    
    if ( !strstr( app_buf, RAK11720_EVT_RX_P2P_ERROR ) && 
         !strstr( app_buf, RAK11720_EVT_RX_P2P_TIMEOUT ) )
    {
        uint8_t * __generic_ptr start_ptr = strstr( app_buf, RAK11720_EVT_RX_P2P );
        uint8_t * __generic_ptr end_ptr = NULL;
        if ( start_ptr )
        {
            start_ptr = start_ptr + strlen ( RAK11720_EVT_RX_P2P ) + 1;
            end_ptr = strstr ( start_ptr, ":" );
            memcpy ( rssi, start_ptr, end_ptr - start_ptr );
            
            start_ptr = end_ptr + 1;
            end_ptr = strstr ( start_ptr, ":" );
            memcpy ( snr, start_ptr, end_ptr - start_ptr );

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
            log_printf ( &logger, " RSSI: %s\r\n", rssi );
            log_printf ( &logger, " SNR: %s\r\n", snr );
            log_printf( &logger, "--------------------------------\r\n" );
        }
    }
    Delay_ms ( 1000 );
    
    return error_flag;
}

// ------------------------------------------------------------------------ END
