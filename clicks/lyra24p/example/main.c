/*!
 * @file main.c
 * @brief LYRA 24P Click Example.
 *
 * # Description
 * This example demonstrates the use of LYRA 24P Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs a factory reset. 
 * In the next step, the demo app requests the LYRA module name, software version, 
 * and MAC address and sets the local device name, 
 * sets the module into VSP mode and start advertising.
 * 
 *
 * ## Application Task
 * Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void lyra24p_clear_app_buf ( void )
 * - static void lyra24p_log_app_buf ( void )
 * - static err_t lyra24p_process ( lyra24p_t *ctx )
 * - static void lyra24p_check_response ( uint8_t *rsp )
 *
 * @note
 * We have used the BLE Scanner smartphone application for the test.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lyra24p.h"

// Demo device name
#define DEVICE_NAME                "LYRA 24P Click"

// Application buffer size
#define APP_BUFFER_SIZE             200
#define PROCESS_BUFFER_SIZE         200

// Response timeout
#define RESPONSE_TIMEOUT            100000

static lyra24p_t lyra24p;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief LYRA 24P clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lyra24p_clear_app_buf ( void );

/**
 * @brief LYRA 24P log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lyra24p_log_app_buf ( void );

/**
 * @brief LYRA 24P data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lyra24p_process ( lyra24p_t *ctx );

/**
 * @brief LYRA 24P response check.
 * @details This function checks for response and displays the status of response.
 * @param[in] rsp  Expected response.
 * @return Nothing.
 */
static void lyra24p_check_response ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lyra24p_cfg_t lyra24p_cfg;  /**< Click config object. */

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
    lyra24p_cfg_setup( &lyra24p_cfg );
    LYRA24P_MAP_MIKROBUS( lyra24p_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lyra24p_init( &lyra24p, &lyra24p_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    lyra24p_hw_reset( &lyra24p );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_AT );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_AT );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_DEV_NAME, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_FW_VER, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_BT_ADDR, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_cmd_param( &lyra24p, LYRA24P_CMD_ATS, 
                                       LYRA24P_ATS_ARG_DEVNAME_FORMAT, 
                                       LYRA24P_PREFIX_SYMBOL_SET_VAL, 
                                       LYRA24P_ATS_VAL_DEVNAME );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );
    
    lyra24p_set_device_name( &lyra24p, DEVICE_NAME );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATPS, 
                                       LYRA24P_PREFIX_SYMBOL_ZERO, 
                                       LYRA24P_QUERY_EN );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_ATLADV );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_ATLVSP );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );
}

void application_task ( void ) 
{
    if ( LYRA24P_OK == lyra24p_process( &lyra24p ) ) 
    {
        lyra24p_log_app_buf( );
        lyra24p_clear_app_buf( );
        Delay_ms ( 100 );
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

static void lyra24p_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lyra24p_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lyra24p_process ( lyra24p_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lyra24p_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LYRA24P_OK;
    }
    return LYRA24P_ERROR;
}

static void lyra24p_check_response ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    lyra24p_clear_app_buf( );
    lyra24p_process( &lyra24p );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, LYRA24P_RSP_ERROR ) ) )
    {
        lyra24p_process( &lyra24p );
        if ( timeout_cnt++ > RESPONSE_TIMEOUT )
        {
            lyra24p_clear_app_buf( );
            log_error( &logger, " Timeout!" );
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    
    lyra24p_process( &lyra24p );
    if ( strstr( app_buf, rsp ) )
    {
        lyra24p_log_app_buf( );
    }
    else if ( strstr( app_buf, LYRA24P_RSP_ERROR ) )
    {
        log_error( &logger, " Command!" );
    }
    else
    {
        log_error( &logger, " Unknown!" );
    }
}

// ------------------------------------------------------------------------ END
