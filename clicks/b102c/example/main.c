/*!
 * @file main.c
 * @brief B102C Click Example.
 *
 * # Description
 * This example demonstrates the use of B102C click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, then performs a factory reset and sets the local device name.
 *
 * ## Application Task
 * Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void b102c_clear_app_buf ( void )
 * - static void b102c_log_app_buf ( void )
 * - static err_t b102c_process ( b102c_t *ctx )
 * - static err_t b102c_rsp_check ( b102c_t *ctx, uint8_t *response )
 * - static void b102c_error_check( err_t error_flag )
 *
 * @note
 * For communication with B102C click use the android application on the link:
 * https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner
 *   
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "b102c.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static b102c_t b102c;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t app_error_flag;

/**
 * @brief B102C clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void b102c_clear_app_buf ( void );

/**
 * @brief B102C log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void b102c_log_app_buf ( void );

/**
 * @brief B102C data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t b102c_process ( b102c_t *ctx );

/**
 * @brief B102C response read function.
 * @details This function reads the response of the sent command and writes it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #b102c_t object definition for detailed explanation.
 * @param[in] response : Expected response.
 * @return @li @c  0 - Response OK.
 *         @li @c -1 - Response ERROR.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t b102c_rsp_check ( b102c_t *ctx, uint8_t *response );

/**
 * @brief Check for errors.
 * @details This function checks for different types of 
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag : Response to be checked.
 * @note None.
 */
static void b102c_error_check( err_t error_flag );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    b102c_cfg_t b102c_cfg;  /**< Click config object. */

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
    b102c_cfg_setup( &b102c_cfg );
    B102C_MAP_MIKROBUS( b102c_cfg, MIKROBUS_1 );
    if ( UART_ERROR == b102c_init( &b102c, &b102c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_printf( &logger, " Software reset. \r\n" );
    b102c_send_cmd( &b102c, B102C_CMD_RESET );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_READY );
    
    log_printf( &logger, " Factory reset. \r\n" );
    b102c_send_cmd( &b102c, B102C_CMD_DEFAULT );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_READY );

    log_printf( &logger, " Set device name. \r\n" );
    #define DEVICE_NAME             "B102C Click"
    b102c_send_cmd_with_params( &b102c, B102C_CMD_NAME, DEVICE_NAME );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_OK );

    log_printf( &logger, " Set Auto broadcast mode. \r\n" );
    #define AUTO_BROADCAST          "1"
    b102c_send_cmd_with_params( &b102c, B102C_CMD_ADVMOD, AUTO_BROADCAST );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_OK );

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Connect to device. " );
}

void application_task ( void ) 
{
    if ( B102C_OK == b102c_process( &b102c ) ) 
    {
        b102c_log_app_buf( );
        b102c_clear_app_buf( );
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

static void b102c_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void b102c_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t b102c_process ( b102c_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = b102c_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return B102C_OK;
    }
    return B102C_ERROR;
}

static err_t b102c_rsp_check ( b102c_t *ctx, uint8_t *response ) 
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 50000;
    
    err_t error_flag = b102c_process( ctx );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) 
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, response ) == 0 ) && ( strstr( app_buf, B102C_RSP_ERROR ) == 0 ) ) 
    {
        error_flag = b102c_process( ctx );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) 
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout ) 
        {
            return B102C_TIMEOUT;
        }
        
        Delay_ms ( 1 );
    }
    
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ ) 
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n" );
    b102c_clear_app_buf( );
    Delay_ms ( 500 );
    
    log_printf( &logger, "-----------------------------------\r\n" );
}

static void b102c_error_check( err_t error_flag ) 
{
    if ( ( error_flag != 0 ) && ( error_flag != B102C_ERROR ) ) 
    {
        switch ( error_flag ) 
        {
            case B102C_OVERFLOW: 
            {
                log_error( &logger, " Overflow!" );
                break;
            }
            case B102C_TIMEOUT:
            {
                log_error( &logger, " Timeout!" );
                break;
            }
            default: 
            {
                break;
            }
        }
    }
}


// ------------------------------------------------------------------------ END
