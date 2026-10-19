/*!
 * @file main.c
 * @brief LR 12 Click Example.
 *
 * # Description
 * This example demonstrates the use of the LR 12 Click board as a LoRaWAN
 * end device. The device initializes, performs a factory reset, configures
 * OTAA parameters (AppEUI and AppKey), joins the LoRaWAN network, and then
 * periodically sends confirmed uplink messages containing sample data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and LR 12 Click driver, then sets the application
 * state machine to power-up state.
 *
 * ## Application Task
 * Implements a state machine that performs device reset, communication check,
 * network configuration, OTAA join procedure, and periodically sends confirmed
 * LoRaWAN messages with incrementing counters and example sensor data.
 *
 * @note
 * Replace LR12_APP_EUI and LR12_APP_KEY with values generated on your LoRaWAN server.
 * Ensure the device is within network coverage and properly registered on the network
 * server using the printed DevEUI and configured AppEUI and AppKey.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lr12.h"
#include "conversions.h"

#ifndef MIKROBUS_POSITION_LR12
    #define MIKROBUS_POSITION_LR12 MIKROBUS_1
#endif

// Replace these values with values configured/generated on server.
#define LR12_APP_EUI                "0101010101010101"
#define LR12_APP_KEY                "000102030405060708090A0B0C0D0E0F"

// Text message for transmittion
#define TEXT_MESSAGE_1              "MIKROE, #"
#define TEXT_MESSAGE_2              "LR 12 Click board, #"
#define TEXT_MESSAGE_3              "press=1013.5, temp=25.3, #"
#define TEXT_MESSAGE_4              "press=984.2, temp=-3.7, #"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    LR12_POWER_UP = 1,
    LR12_CONFIG_EXAMPLE,
    LR12_EXAMPLE

} lr12_app_state_t;

static lr12_t lr12;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static lr12_app_state_t app_state = LR12_POWER_UP;

/**
 * @brief LR 12 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void lr12_clear_app_buf ( void );

/**
 * @brief LR 12 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return None.
 * @note None.
 */
static void lr12_log_app_buf ( void );

/**
 * @brief LR 12 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr12_process ( lr12_t *ctx );

/**
 * @brief LR 12 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr12_read_response ( lr12_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief LR 12 power up function.
 * @details This function powers up the device, performs device factory reset and reads system information.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr12_power_up ( lr12_t *ctx );

/**
 * @brief LR 12 config example function.
 * @details This function configures the AppEUI/AppKey placeholders and joins the LoRaWAN network in OTAA mode.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr12_config_example ( lr12_t *ctx );

/**
 * @brief LR 12 example function.
 * @details This function sends a sample message with a message counter appended every 2 seconds using
 * the confirmed uplink frames.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @return @li @c    0 - OK.
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr12_example ( lr12_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr12_cfg_t lr12_cfg;  /**< Click config object. */

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
    lr12_cfg_setup( &lr12_cfg );
    LR12_MAP_MIKROBUS( lr12_cfg, MIKROBUS_POSITION_LR12 );
    if ( UART_ERROR == lr12_init( &lr12, &lr12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LR12_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case LR12_POWER_UP:
        {
            if ( LR12_OK == lr12_power_up( &lr12 ) )
            {
                app_state = LR12_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR12_CONFIG_EXAMPLE:
        {
            if ( LR12_OK == lr12_config_example( &lr12 ) )
            {
                app_state = LR12_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LR12_EXAMPLE:
        {
            lr12_example( &lr12 );
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

static void lr12_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lr12_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lr12_process ( lr12_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lr12_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LR12_OK;
    }
    return LR12_ERROR;
}

static err_t lr12_read_response ( lr12_t *ctx, uint8_t *rsp, uint32_t max_rsp_time ) 
{
    uint32_t timeout_cnt = 0;
    lr12_clear_app_buf ( );
    lr12_process( ctx );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LR12_RSP_ERR ) ) &&
            ( 0 == strstr( app_buf, LR12_MSG_EVENT_JOIN_FAIL ) ) )
    {
        lr12_process( ctx );
        if ( timeout_cnt++ > max_rsp_time )
        {
            lr12_log_app_buf( );
            lr12_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return LR12_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms ( 200 );
    lr12_process( ctx );
    lr12_log_app_buf( );
    if ( strstr( app_buf, rsp ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return LR12_OK;
    }
    return LR12_ERROR_CMD;
}

static err_t lr12_power_up ( lr12_t *ctx )
{
    err_t error_flag = LR12_OK;
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    lr12_reset_device( &lr12 );
    error_flag = lr12_read_response( ctx, LR12_MSG_EVENT_REBOOT_SUCCESS, LR12_MAX_RSP_TIME_RESET );

    log_printf( &logger, ">>> Check communication.\r\n" );
    lr12_cmd_run( &lr12, LR12_CMD_AT, NULL );
    error_flag |= lr12_read_response( &lr12, LR12_RSP_OK, LR12_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Factory reset.\r\n" );
    lr12_cmd_run( &lr12, LR12_CMD_FACTORY_RESET, NULL );
    error_flag |= lr12_read_response( &lr12, LR12_MSG_EVENT_REBOOT_SUCCESS, LR12_MAX_RSP_TIME_FACTORY_RESET );

    log_printf( &logger, ">>> Get device firmware version.\r\n" );
    lr12_cmd_get( ctx, LR12_CMD_GET_FW_VERSION );
    error_flag |= lr12_read_response( ctx, LR12_RSP_OK, LR12_MAX_RSP_TIME_DEFAULT );

    return error_flag;
}

static err_t lr12_config_example ( lr12_t *ctx )
{
    err_t error_flag = LR12_OK;

    log_printf( &logger, ">>> Get device EUI.\r\n" );
    lr12_cmd_get( ctx, LR12_CMD_DEVICE_EUI );
    error_flag |= lr12_read_response( ctx, LR12_RSP_OK, LR12_MAX_RSP_TIME_DEFAULT );
    
    log_printf( &logger, ">>> Set application EUI: %s\r\n", ( char * ) LR12_APP_EUI );
    lr12_cmd_set( ctx, LR12_CMD_APPLICATION_EUI, LR12_APP_EUI, NULL );
    error_flag |= lr12_read_response( ctx, LR12_RSP_OK, LR12_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Set application key: %s\r\n", ( char * ) LR12_APP_KEY );
    lr12_cmd_set( ctx, LR12_CMD_APPLICATION_KEY, LR12_APP_KEY, NULL );
    error_flag |= lr12_read_response( ctx, LR12_RSP_OK, LR12_MAX_RSP_TIME_DEFAULT );

    log_printf( &logger, ">>> Join network in OTAA mode.\r\n" );
    lr12_cmd_run( ctx, LR12_CMD_JOIN, NULL );
    error_flag |= lr12_read_response( ctx, LR12_MSG_EVENT_JOIN_OK, LR12_MAX_RSP_TIME_JOIN );

    return error_flag;
}

static err_t lr12_example ( lr12_t *ctx )
{
    err_t error_flag = LR12_OK;
    static uint16_t msg_cnt = 0;
    uint8_t msg_cnt_buf[ 10 ] = { 0 };
    uint8_t msg_len_buf[ 10 ] = { 0 };
    uint8_t msg_buf[ 100 ] = { 0 };
    
    uint16_to_str( msg_cnt++, msg_cnt_buf );
    l_trim( msg_cnt_buf );
    r_trim( msg_cnt_buf );
    strcpy( msg_buf, TEXT_MESSAGE_1 );
    strcat( msg_buf, msg_cnt_buf );
    uint16_to_str( strlen( msg_buf ), msg_len_buf );
    l_trim( msg_len_buf );
    r_trim( msg_len_buf );
    log_printf( &logger, ">>> Send confirmed message: \"%s\".\r\n", ( char * ) msg_buf );
    lr12_cmd_set( ctx, LR12_CMD_CONFIRMED_SEND, msg_len_buf, msg_buf );
    error_flag |= lr12_read_response( ctx, LR12_MSG_ACK, LR12_MAX_RSP_TIME_CONFIRMATION );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    uint16_to_str( msg_cnt++, msg_cnt_buf );
    l_trim( msg_cnt_buf );
    r_trim( msg_cnt_buf );
    strcpy( msg_buf, TEXT_MESSAGE_3 );
    strcat( msg_buf, msg_cnt_buf );
    uint16_to_str( strlen( msg_buf ), msg_len_buf );
    l_trim( msg_len_buf );
    r_trim( msg_len_buf );
    log_printf( &logger, ">>> Send confirmed message: \"%s\".\r\n", ( char * ) msg_buf );
    lr12_cmd_set( ctx, LR12_CMD_CONFIRMED_SEND, msg_len_buf, msg_buf );
    error_flag |= lr12_read_response( ctx, LR12_MSG_ACK, LR12_MAX_RSP_TIME_CONFIRMATION );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    uint16_to_str( msg_cnt++, msg_cnt_buf );
    l_trim( msg_cnt_buf );
    r_trim( msg_cnt_buf );
    strcpy( msg_buf, TEXT_MESSAGE_2 );
    strcat( msg_buf, msg_cnt_buf );
    uint16_to_str( strlen( msg_buf ), msg_len_buf );
    l_trim( msg_len_buf );
    r_trim( msg_len_buf );
    log_printf( &logger, ">>> Send confirmed message: \"%s\".\r\n", ( char * ) msg_buf );
    lr12_cmd_set( ctx, LR12_CMD_CONFIRMED_SEND, msg_len_buf, msg_buf );
    error_flag |= lr12_read_response( ctx, LR12_MSG_ACK, LR12_MAX_RSP_TIME_CONFIRMATION );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    uint16_to_str( msg_cnt++, msg_cnt_buf );
    l_trim( msg_cnt_buf );
    r_trim( msg_cnt_buf );
    strcpy( msg_buf, TEXT_MESSAGE_4 );
    strcat( msg_buf, msg_cnt_buf );
    uint16_to_str( strlen( msg_buf ), msg_len_buf );
    l_trim( msg_len_buf );
    r_trim( msg_len_buf );
    log_printf( &logger, ">>> Send confirmed message: \"%s\".\r\n", ( char * ) msg_buf );
    lr12_cmd_set( ctx, LR12_CMD_CONFIRMED_SEND, msg_len_buf, msg_buf );
    error_flag |= lr12_read_response( ctx, LR12_MSG_ACK, LR12_MAX_RSP_TIME_CONFIRMATION );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    return error_flag;
}

// ------------------------------------------------------------------------ END
