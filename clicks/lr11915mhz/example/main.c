/*!
 * @file main.c
 * @brief LR 11 915MHz Click Example.
 *
 * # Description
 * This example demonstrates the use of LR 11 915MHz Click board by showing
 * the communication between two Click boards configured in P2P network mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - LR11915MHZ_POWER_UP:
 * Powers up the device, performs a device factory reset and reads system information.
 *  - LR11915MHZ_CONFIG_EXAMPLE:
 * Configures device for the LoRa P2P network mode.
 *  - LR11915MHZ_EXAMPLE:
 * Performs a LoRa P2P example by exchanging messages with another LR 11 915MHz Click board.
 * One device should be set to NODE_0_ADDRESS, and the other to NODE_1_ADDRESS.
 *
 * ## Additional Function
 * - static void lr11915mhz_clear_app_buf ( void )
 * - static void lr11915mhz_log_app_buf ( void )
 * - static err_t lr11915mhz_process ( lr11915mhz_t *ctx )
 * - static err_t lr11915mhz_read_response ( lr11915mhz_t *ctx, uint8_t *rsp )
 * - static err_t lr11915mhz_power_up ( lr11915mhz_t *ctx )
 * - static err_t lr11915mhz_config_example ( lr11915mhz_t *ctx )
 * - static err_t lr11915mhz_example ( lr11915mhz_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lr11915mhz.h"
#include "conversions.h"
#include "generic_pointer.h"

// Node address selection macros
#define NODE_0_ADDRESS      0
#define NODE_1_ADDRESS      1
#define NODE_ADDRESS        NODE_0_ADDRESS

// Text message for transmittion
#define DEMO_TEXT_MESSAGE   "MIKROE - LR 11 915MHz Click board"

static lr11915mhz_t lr11915mhz;
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
    LR11915MHZ_POWER_UP = 1,
    LR11915MHZ_CONFIG_EXAMPLE,
    LR11915MHZ_EXAMPLE

} lr11915mhz_app_state_t;

static lr11915mhz_app_state_t app_state = LR11915MHZ_POWER_UP;

/**
 * @brief LR 11 915MHz clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lr11915mhz_clear_app_buf ( void );

/**
 * @brief LR 11 915MHz log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lr11915mhz_log_app_buf ( void );

/**
 * @brief LR 11 915MHz data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lr11915mhz_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr11915mhz_process ( lr11915mhz_t *ctx );

/**
 * @brief LR 11 915MHz read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lr11915mhz_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr11915mhz_read_response ( lr11915mhz_t *ctx, uint8_t *rsp );

/**
 * @brief LR 11 915MHz power up function.
 * @details This function powers up the device, performs device factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lr11915mhz_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr11915mhz_power_up ( lr11915mhz_t *ctx );

/**
 * @brief LR 11 915MHz config example function.
 * @details This function configures device for LoRa P2P example.
 * @param[in] ctx : Click context object.
 * See #lr11915mhz_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr11915mhz_config_example ( lr11915mhz_t *ctx );

/**
 * @brief LR 11 915MHz example function.
 * @details This function performs a LoRa P2P example by exchanging messages with another LR 11 915MHz Click board.
 * @param[in] ctx : Click context object.
 * See #lr11915mhz_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr11915mhz_example ( lr11915mhz_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr11915mhz_cfg_t lr11915mhz_cfg;  /**< Click config object. */

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
    lr11915mhz_cfg_setup( &lr11915mhz_cfg );
    LR11915MHZ_MAP_MIKROBUS( lr11915mhz_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr11915mhz_init( &lr11915mhz, &lr11915mhz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LR11915MHZ_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LR11915MHZ_POWER_UP:
        {
            if ( LR11915MHZ_OK == lr11915mhz_power_up( &lr11915mhz ) )
            {
                app_state = LR11915MHZ_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR11915MHZ_CONFIG_EXAMPLE:
        {
            if ( LR11915MHZ_OK == lr11915mhz_config_example( &lr11915mhz ) )
            {
                app_state = LR11915MHZ_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR11915MHZ_EXAMPLE:
        {
            lr11915mhz_example( &lr11915mhz );
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

static void lr11915mhz_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lr11915mhz_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lr11915mhz_process ( lr11915mhz_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lr11915mhz_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LR11915MHZ_OK;
    }
    return LR11915MHZ_ERROR;
}

static err_t lr11915mhz_read_response ( lr11915mhz_t *ctx, uint8_t *rsp ) 
{
    #define READ_RESPONSE_TIMEOUT_MS 30000
    uint32_t timeout_cnt = 0;
    lr11915mhz_clear_app_buf ( );
    lr11915mhz_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LR11915MHZ_RSP_ERROR ) ) )
    {
        lr11915mhz_process( ctx );
        if ( timeout_cnt++ > READ_RESPONSE_TIMEOUT_MS )
        {
            lr11915mhz_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LR11915MHZ_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lr11915mhz_process( ctx );
    if ( strstr( app_buf, rsp ) )
    {
        lr11915mhz_log_app_buf( );
        log_printf( &logger, "--------------------------------\r\n" );
        return LR11915MHZ_OK;
    }
    lr11915mhz_log_app_buf( );
    return LR11915MHZ_ERROR_CMD;
}

static err_t lr11915mhz_power_up ( lr11915mhz_t *ctx )
{
    err_t error_flag = LR11915MHZ_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    lr11915mhz_reset_device( &lr11915mhz );
    while ( LR11915MHZ_OK == lr11915mhz_process( ctx ) )
    {
        lr11915mhz_log_app_buf( );
        lr11915mhz_clear_app_buf ( );
    }
    log_printf( &logger, "--------------------------------\r\n" );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_FACTORY_RESET, NULL );
    error_flag |= lr11915mhz_read_response( &lr11915mhz, LR11915MHZ_RSP_OK );

    log_printf( &logger, ">>> Check communication.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_AT, NULL );
    error_flag |= lr11915mhz_read_response( &lr11915mhz, LR11915MHZ_RSP_OK );

    log_printf( &logger, ">>> Get device type.\r\n" );
    lr11915mhz_cmd_run( ctx, LR11915MHZ_CMD_GET_INFO, LR11915MHZ_PARAM_DEVICE_TYPE );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );

    log_printf( &logger, ">>> Get firmware version.\r\n" );
    lr11915mhz_cmd_run( ctx, LR11915MHZ_CMD_GET_INFO, LR11915MHZ_PARAM_APP_FW_VERSION );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );

    return error_flag;
}

static err_t lr11915mhz_config_example ( lr11915mhz_t *ctx )
{
    uint8_t data_buf[ 10 ] = { 0 };
    err_t error_flag = LR11915MHZ_OK;
    #define DEVICE_CLASS_P2P "3"
    log_printf( &logger, ">>> Set LoRa operation to P2P.\r\n" );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_DEVICE_CLASS, DEVICE_CLASS_P2P );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );

    #define REGION_US902_928 "3"
    log_printf( &logger, ">>> Set operation region to US902_928.\r\n" );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_REGION, REGION_US902_928 );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );

    int16_to_str ( NODE_ADDRESS, data_buf );
    l_trim ( data_buf );
    r_trim ( data_buf );
    log_printf( &logger, ">>> Set P2P node address to %s.\r\n", data_buf );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_DEVICE_ADDRESS, data_buf );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );

    #define P2P_NETWORK_SIZE "2"
    log_printf( &logger, ">>> Set P2P network size to %s nodes.\r\n", ( char * ) P2P_NETWORK_SIZE );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_NET_SIZE, P2P_NETWORK_SIZE );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    #define P2P_DATA_RATE_DR2 "2"
    log_printf( &logger, ">>> Set P2P data rate to DR2.\r\n" );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_DATA_RATE, P2P_DATA_RATE_DR2 );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    #define P2P_LISTEN_DURATION "0"
    log_printf( &logger, ">>> Set P2P listen duration to 0.\r\n" );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_LISTEN_DURATION, P2P_LISTEN_DURATION );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    #define P2P_LISTEN_INTERVAL "0"
    log_printf( &logger, ">>> Set P2P listen interval to 0.\r\n" );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_LISTEN_INTERVAL, P2P_LISTEN_INTERVAL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    #define P2P_BEACON_DATA_RATE_DR2 "2"
    log_printf( &logger, ">>> Set P2P beacon data rate to DR2.\r\n" );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_BEACON_DATA_RATE, P2P_BEACON_DATA_RATE_DR2 );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    #define P2P_TX_POWER "1"
    log_printf( &logger, ">>> Set P2P TX power to %s dBm.\r\n", ( char * ) P2P_TX_POWER );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_TX_POWER, P2P_TX_POWER );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Save settings.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_SAVE_SETTINGS, NULL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Reboot.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_WARM_RESET, NULL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Get P2P maximum packet size.\r\n" );
    lr11915mhz_cmd_run( ctx, LR11915MHZ_CMD_GET_INFO, LR11915MHZ_PARAM_P2P_SLOT_PACKET_SIZE );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    int16_t packet_size = atoi( &app_buf[ 1 ] ) - 1;
    if ( packet_size < strlen ( DEMO_TEXT_MESSAGE ) )
    {
        log_error( &logger, " DEMO_TEXT_MESSAGE length [%d] exceeds the packet size limit [%d].\r\n", 
                   ( int16_t ) strlen ( DEMO_TEXT_MESSAGE ), packet_size );
        for ( ; ; );
    }
    
    int16_to_str ( strlen ( DEMO_TEXT_MESSAGE ), data_buf );
    l_trim ( data_buf );
    r_trim ( data_buf );
    log_printf( &logger, ">>> Set P2P packet size to %s.\r\n", data_buf );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_PACKET_SIZE, data_buf );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Save settings.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_SAVE_SETTINGS, NULL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Reboot.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_WARM_RESET, NULL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Get P2P minimum window length.\r\n" );
    lr11915mhz_cmd_run( ctx, LR11915MHZ_CMD_GET_INFO, LR11915MHZ_PARAM_P2P_MIN_WINDOW_LENGTH );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    int16_t window_len = atoi( &app_buf[ 1 ] ) + 1;
    int16_to_str ( window_len, data_buf );
    l_trim ( data_buf );
    r_trim ( data_buf );
    log_printf( &logger, ">>> Set P2P window length to %s.\r\n", data_buf );
    lr11915mhz_cmd_set( ctx, LR11915MHZ_CMD_PARAM_ACCESS_NUM, LR11915MHZ_PARAM_ID_P2P_WINDOW_LENGTH, data_buf );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Save settings.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_SAVE_SETTINGS, NULL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Reboot.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_WARM_RESET, NULL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    log_printf( &logger, ">>> Start a P2P session.\r\n" );
    lr11915mhz_cmd_run( &lr11915mhz, LR11915MHZ_CMD_P2P_START_SESSION, NULL );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    return error_flag;
}

static err_t lr11915mhz_example ( lr11915mhz_t *ctx )
{
    err_t error_flag = LR11915MHZ_OK;
    uint8_t param_buf[ 120 ] = { 0 };
    uint8_t msg_hex[ 101 ] = { 0 };
    uint8_t byte_hex[ 3 ] = { 0 };
    uint8_t src_addr[ 10 ] = { 0 };
    uint8_t source[ 10 ] = { 0 };
    uint8_t rssi[ 10 ] = { 0 };
    uint8_t snr[ 10 ] = { 0 };
    uint8_t cnt = 0;

    memset( msg_hex, 0, sizeof ( msg_hex ) );
    for ( cnt = 0; ( cnt < strlen ( DEMO_TEXT_MESSAGE ) ) && ( cnt < 50 ); cnt++ ) 
    {
        uint8_to_hex ( DEMO_TEXT_MESSAGE[ cnt ], byte_hex );
        strcat ( msg_hex, byte_hex );
    }
#if ( NODE_ADDRESS == NODE_0_ADDRESS )
    int16_to_str ( NODE_1_ADDRESS, param_buf );
    l_trim ( param_buf );
    r_trim ( param_buf );
#else
    int16_to_str ( NODE_0_ADDRESS, param_buf );
    l_trim ( param_buf );
    r_trim ( param_buf );
#endif
    log_printf( &logger, ">>> Send message \"%s\" to node address %s.\r\n", ( char * ) DEMO_TEXT_MESSAGE, param_buf );
    strcat ( param_buf, ", \"" );
    strcat ( param_buf, msg_hex );
    strcat ( param_buf, "\"" );
    lr11915mhz_cmd_run( ctx, LR11915MHZ_CMD_P2P_SEND_DATA, param_buf );
    error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_RSP_OK );
    
    if ( LR11915MHZ_OK == error_flag )
    {
        memset( msg_hex, 0, sizeof ( msg_hex ) );
        log_printf( &logger, ">>> Waiting for a P2P RX message.\r\n" );
        error_flag |= lr11915mhz_read_response( ctx, LR11915MHZ_EVT_RX_P2P );
    }
    else
    {
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    if ( LR11915MHZ_OK == error_flag )
    {
        uint8_t * __generic_ptr start_ptr = strstr( app_buf, LR11915MHZ_EVT_RX_P2P );
        uint8_t * __generic_ptr end_ptr = NULL;
        if ( start_ptr )
        {
            start_ptr = start_ptr + strlen ( LR11915MHZ_EVT_RX_P2P );
            end_ptr = strstr ( start_ptr, "," );
            memcpy ( source, start_ptr, end_ptr - start_ptr );
            
            start_ptr = strstr ( end_ptr, ":" ) + 1;
            end_ptr = strstr ( start_ptr, "," );
            memcpy ( rssi, start_ptr, end_ptr - start_ptr );

            start_ptr = strstr ( end_ptr, ":" ) + 1;
            end_ptr = strstr ( start_ptr, "," );
            memcpy ( snr, start_ptr, end_ptr - start_ptr );
            
            start_ptr = end_ptr + 2;
            end_ptr = strstr ( start_ptr, "\n" );
            memcpy ( msg_hex, start_ptr, end_ptr - start_ptr );

            for ( cnt = 0; cnt < strlen ( msg_hex ); cnt += 2 )
            {
                msg_hex[ cnt / 2 ] = hex_to_uint8 ( &msg_hex [ cnt ] );
            }
            msg_hex[ cnt / 2 ] = 0;
            log_printf( &logger, ">>> Parse received message.\r\n" );
            log_printf ( &logger, " Source address: %s\r\n", source );
            log_printf ( &logger, " Message: %s\r\n", msg_hex );
            log_printf ( &logger, " RSSI: %s\r\n", rssi );
            log_printf ( &logger, " SNR: %s\r\n", snr );
            log_printf( &logger, "--------------------------------\r\n" );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
