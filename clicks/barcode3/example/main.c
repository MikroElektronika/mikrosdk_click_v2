/*!
 * @file main.c
 * @brief Barcode 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Barcode 3 Click board by scanning
 * and displaying the content of a barcode or QR Code.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, stops scanning and resets the barcode device.
 *
 * ## Application Task
 * Triggers scanning and waits up to 3 seconds for the barcode to be detected.
 * If a barcode or QR Code is detected, it displays its content on the USB UART.
 *
 * ## Additional Function
 * - static void barcode3_clear_app_buf ( void )
 * - static void barcode3_log_app_buf ( void )
 * - static err_t barcode3_process ( barcode3_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barcode3.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static barcode3_t barcode3;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Barcode 3 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void barcode3_clear_app_buf ( void );

/**
 * @brief Barcode 3 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void barcode3_log_app_buf ( void );

/**
 * @brief Barcode 3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #barcode3_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t barcode3_process ( barcode3_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barcode3_cfg_t barcode3_cfg;  /**< Click config object. */

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
    barcode3_cfg_setup( &barcode3_cfg );
    BARCODE3_MAP_MIKROBUS( barcode3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == barcode3_init( &barcode3, &barcode3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    barcode3_stop_scanning ( &barcode3 );
    barcode3_reset_device ( &barcode3 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t timeout = 0;
    log_printf( &logger, "\r\n------- SCAN START ------\r\n" );
    barcode3_start_scanning ( &barcode3 );
    while ( ++timeout < 3000 )
    {
        if ( BARCODE3_OK == barcode3_process( &barcode3 ) )
        {
            barcode3_log_app_buf( );
            barcode3_clear_app_buf( );
            Delay_10ms ( );
            while ( BARCODE3_OK == barcode3_process( &barcode3 ) )
            {
                barcode3_log_app_buf( );
                barcode3_clear_app_buf( );
                Delay_10ms ( );
            }
            break;
        }
        Delay_1ms ( );
    }
    log_printf( &logger, "------- SCAN STOP -------\r\n" );
    barcode3_stop_scanning ( &barcode3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

static void barcode3_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void barcode3_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t barcode3_process ( barcode3_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = barcode3_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return BARCODE3_OK;
    }
    return BARCODE3_ERROR;
}

// ------------------------------------------------------------------------ END
