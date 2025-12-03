/*!
 * @file main.c
 * @brief RAK4630 Click Example.
 *
 * # Description
 * This example demonstrates the use of RAK4630 Click board by showing
 * the communication between two Click boards configured in P2P network mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - RAK4630_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *  - RAK4630_CONFIG_EXAMPLE:
 * Configures device for the LoRa P2P network mode.
 *  - RAK4630_EXAMPLE:
 * Performs a LoRa P2P example by exchanging messages with another RAK4630 Click board.
 *
 * ## Additional Function
 * - static void rak4630_clear_app_buf ( void )
 * - static void rak4630_log_app_buf ( void )
 * - static err_t rak4630_process ( rak4630_t *ctx )
 * - static err_t rak4630_read_response ( rak4630_t *ctx, uint8_t *rsp )
 * - static err_t rak4630_power_up ( rak4630_t *ctx )
 * - static err_t rak4630_config_example ( rak4630_t *ctx )
 * - static err_t rak4630_example ( rak4630_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rak4630.h"
#include "conversions.h"
#include "generic_pointer.h"

#define DEMO_TEXT_MESSAGE   "MIKROE - RAK4630 Click board"

static rak4630_t rak4630;
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
    RAK4630_POWER_UP = 1,
    RAK4630_CONFIG_EXAMPLE,
    RAK4630_EXAMPLE

} rak4630_app_state_t;

static rak4630_app_state_t app_state = RAK4630_POWER_UP;

/**
 * @brief RAK4630 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void rak4630_clear_app_buf ( void );

/**
 * @brief RAK4630 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void rak4630_log_app_buf ( void );

/**
 * @brief RAK4630 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak4630_process ( rak4630_t *ctx );

/**
 * @brief RAK4630 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak4630_read_response ( rak4630_t *ctx, uint8_t *rsp );

/**
 * @brief RAK4630 power up function.
 * @details This function powers up the device, performs device factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak4630_power_up ( rak4630_t *ctx );

/**
 * @brief RAK4630 config example function.
 * @details This function configures device for LoRa P2P example.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak4630_config_example ( rak4630_t *ctx );

/**
 * @brief RAK4630 example function.
 * @details This function performs a LoRa P2P example by exchanging messages with another RAK4630 Click board.
 * @param[in] ctx : Click context object.
 * See #rak4630_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rak4630_example ( rak4630_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rak4630_cfg_t rak4630_cfg;  /**< Click config object. */

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
    rak4630_cfg_setup( &rak4630_cfg );
    RAK4630_MAP_MIKROBUS( rak4630_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rak4630_init( &rak4630, &rak4630_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = RAK4630_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case RAK4630_POWER_UP:
        {
            if ( RAK4630_OK == rak4630_power_up( &rak4630 ) )
            {
                app_state = RAK4630_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RAK4630_CONFIG_EXAMPLE:
        {
            if ( RAK4630_OK == rak4630_config_example( &rak4630 ) )
            {
                app_state = RAK4630_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case RAK4630_EXAMPLE:
        {
            rak4630_example( &rak4630 );
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

static void rak4630_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void rak4630_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t rak4630_process ( rak4630_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = rak4630_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return RAK4630_OK;
    }
    return RAK4630_ERROR;
}

static err_t rak4630_read_response ( rak4630_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS    120000
    uint32_t timeout_cnt = 0;
    rak4630_clear_app_buf ( );
    rak4630_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, RAK4630_RSP_ERROR ) ) &&
            ( 0 == strstr( app_buf, RAK4630_RSP_PARAM_ERROR ) ) &&
            ( 0 == strstr( app_buf, RAK4630_RSP_BUSY_ERROR ) ) &&
            ( 0 == strstr( app_buf, RAK4630_RSP_TEST_PARAM_OVERFLOW ) ) &&
            ( 0 == strstr( app_buf, RAK4630_RSP_NO_CLASSB_ENABLE ) ) &&
            ( 0 == strstr( app_buf, RAK4630_RSP_NO_NETWORK_JOINED ) ) &&
            ( 0 == strstr( app_buf, RAK4630_RSP_RX_ERROR ) ) )
    {
        rak4630_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            rak4630_log_app_buf( );
            rak4630_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return RAK4630_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    rak4630_process( ctx );
    rak4630_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return RAK4630_OK;
    }
    return RAK4630_ERROR_CMD;
}

static err_t rak4630_power_up ( rak4630_t *ctx )
{
    err_t error_flag = RAK4630_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    rak4630_reset_device( &rak4630 );
    error_flag |= rak4630_read_response( &rak4630, RAK4630_RSP_INITIAL );

    log_printf( &logger, ">>> Check communication.\r\n" );
    rak4630_cmd_run( &rak4630, RAK4630_CMD_AT );
    error_flag |= rak4630_read_response( &rak4630, RAK4630_RSP_OK );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    rak4630_cmd_run( &rak4630, RAK4630_CMD_FACTORY_RESET );
    error_flag |= rak4630_read_response( &rak4630, RAK4630_RSP_INITIAL );

    log_printf( &logger, ">>> Toggle command echo.\r\n" );
    rak4630_cmd_run( &rak4630, RAK4630_CMD_TOGGLE_ECHO );
    error_flag |= rak4630_read_response( &rak4630, RAK4630_RSP_OK );
    
    log_printf( &logger, ">>> Get device model ID.\r\n" );
    rak4630_cmd_get( ctx, RAK4630_CMD_GET_MODEL_ID );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    log_printf( &logger, ">>> Get device firmware version.\r\n" );
    rak4630_cmd_get( ctx, RAK4630_CMD_GET_FW_VERSION );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    log_printf( &logger, ">>> Get device serial number.\r\n" );
    rak4630_cmd_get( ctx, RAK4630_CMD_GET_SERIAL_NUMBER );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    log_printf( &logger, ">>> Get BLE MAC address.\r\n" );
    rak4630_cmd_get( ctx, RAK4630_CMD_GET_BLE_MAC_ADDRESS );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    return error_flag;
}

static err_t rak4630_config_example ( rak4630_t *ctx )
{
    err_t error_flag = RAK4630_OK;
    #define NETWORK_WORK_MODE_P2P_LORA "0"
    log_printf( &logger, ">>> Get network work mode.\r\n" );
    rak4630_cmd_get( ctx, RAK4630_CMD_NETWORK_WORK_MODE );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );
    if ( !strstr( app_buf, NETWORK_WORK_MODE_P2P_LORA ) )
    {
        log_printf( &logger, ">>> Set LoRa P2P network work mode.\r\n" );
        rak4630_cmd_set( ctx, RAK4630_CMD_NETWORK_WORK_MODE, NETWORK_WORK_MODE_P2P_LORA );
        error_flag |= rak4630_read_response( ctx, RAK4630_RSP_INITIAL );
    }
    #define P2P_MODE_FREQUENCY "868000000"
    log_printf( &logger, ">>> Set P2P mode frequency to 868 MHz.\r\n" );
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_MODE_FREQUENCY, P2P_MODE_FREQUENCY );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    #define P2P_MODE_SPREADING_FACTOR "12"
    log_printf( &logger, ">>> Set P2P mode spreading factor to 12.\r\n" );
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_MODE_SPREADING_FACTOR, P2P_MODE_SPREADING_FACTOR );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    #define P2P_MODE_BANDWIDTH "0"
    log_printf( &logger, ">>> Set P2P mode bandwidth to 125 kHz.\r\n" );
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_MODE_BANDWIDTH, P2P_MODE_BANDWIDTH );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    #define P2P_MODE_CODE_RATE "0"
    log_printf( &logger, ">>> Set P2P mode code rate to 4/5.\r\n" );
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_MODE_CODE_RATE, P2P_MODE_CODE_RATE );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    #define P2P_MODE_PREAMBLE_LENGTH "8"
    log_printf( &logger, ">>> Set P2P mode preamble length to 8.\r\n" );
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_MODE_PREAMBLE_LENGTH, P2P_MODE_PREAMBLE_LENGTH );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    #define P2P_MODE_TX_POWER "22"
    log_printf( &logger, ">>> Set P2P mode TX power to 22 dBm.\r\n" );
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_MODE_TX_POWER, P2P_MODE_TX_POWER );
    error_flag |= rak4630_read_response( ctx, RAK4630_RSP_OK );

    return error_flag;
}

static err_t rak4630_example ( rak4630_t *ctx )
{
    err_t error_flag = RAK4630_OK;
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
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_TX_MODE, msg_hex );
    error_flag |= rak4630_read_response( ctx, RAK4630_EVT_TX_P2P );
    
    memset( msg_hex, 0, sizeof ( msg_hex ) );
    #define P2P_RX_MODE_TIMEOUT "30000"
    log_printf( &logger, ">>> Go to P2P RX mode with a 30s timeout.\r\n" );
    rak4630_cmd_set( ctx, RAK4630_CMD_P2P_RX_MODE, P2P_RX_MODE_TIMEOUT );
    error_flag |= rak4630_read_response( ctx, RAK4630_EVT_RX_P2P );
    
    if ( !strstr( app_buf, RAK4630_EVT_RX_P2P_ERROR ) && 
         !strstr( app_buf, RAK4630_EVT_RX_P2P_TIMEOUT ) )
    {
        uint8_t * __generic_ptr start_ptr = strstr( app_buf, RAK4630_EVT_RX_P2P );
        uint8_t * __generic_ptr end_ptr = NULL;
        if ( start_ptr )
        {
            start_ptr = start_ptr + strlen ( RAK4630_EVT_RX_P2P ) + 1;
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
