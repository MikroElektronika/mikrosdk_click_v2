/*!
 * @file main.c
 * @brief LR 9 Click Example.
 *
 * # Description
 * This example demonstrates the use of LR 9 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs a hardware reset of the device.
 *
 * ## Application Task
 * Depending on the selected mode, the application demo 
 * receives and processes all incoming data or sends the LoRa packet demo string.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static void lr9_clear_app_buf ( void )
 * - static void lr9_log_app_buf ( void )
 * - static void lr9_log_receiver ( void )
 * - static void lr9_log_response ( void )
 * - static err_t lr9_process ( lr9_t *ctx )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lr9.h"
#include "conversions.h"

// Comment the line below to switch application mode to receiver
#define DEMO_APP_TRANSMITTER

// Default RF configuration
#define LR9_RF_CFG_DEFAULT_TX       "433000000,1,1,1,22,1"
#define LR9_RF_CFG_DEFAULT_RX       "433000000,1,1,1,1"
#define LR9_DEMO_STRING             "MikroE"

// Receiver string sequences
#define PROCESS_START_RECEIVE       "Recv:"
#define PROCESS_ATDTRX              "AT"

// Response timeout
#define RESPONSE_TIMEOUT            100000

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static lr9_t lr9;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief LR 9 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lr9_clear_app_buf ( void );

/**
 * @brief LR 9 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lr9_log_app_buf ( void );

/**
 * @brief LR 9 log receiver data.
 * @details This function logs data from receiver application buffer to USB UART.
 * @note None.
 */
static void lr9_log_receiver ( void );

/**
 * @brief LR 9 log response.
 * @details This function reads data from device and 
 * concatenates and logs data to application buffer to USB UART.
 * @note None.
 */
static void lr9_log_response ( void );

/**
 * @brief LR 9 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr9_process ( lr9_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr9_cfg_t lr9_cfg;  /**< Click config object. */

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
    lr9_cfg_setup( &lr9_cfg );
    LR9_MAP_MIKROBUS( lr9_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr9_init( &lr9, &lr9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lr9_hw_reset( &lr9 );
    Delay_ms ( 500 );

    lr9_inquire_command( &lr9, LR9_CMD_CTXADDRSET, LR9_EQUAL_ENABLE );
    lr9_log_response( );
    Delay_ms ( 500 );

    lr9_inquire_command( &lr9, LR9_CMD_CADDRSET, LR9_EQUAL_ENABLE );
    lr9_log_response( );
    Delay_ms ( 500 );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " > Transmitter < \r\n" );
    lr9_write_command( &lr9, LR9_CMD_CTX , LR9_RF_CFG_DEFAULT_TX );
    lr9_log_response( );
    Delay_ms ( 500 );
#else
    log_printf( &logger, " > Receiver < \r\n" );
    lr9_write_command( &lr9, LR9_CMD_CRXS , LR9_RF_CFG_DEFAULT_RX );
    lr9_log_response( );
    Delay_ms ( 500 );
#endif

    lr9_log_response( );
    Delay_ms ( 500 );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    lr9_send_data_frame( &lr9, LR9_DTRX_CONFIG_DATA, LR9_NB_TRIALS_2, LR9_DEMO_STRING );
    lr9_log_response( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    lr9_log_receiver( );
#endif
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

static void lr9_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lr9_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static void lr9_log_receiver ( void )
{
    uint32_t timeout_cnt = 0;
    lr9_clear_app_buf( );
    lr9_process( &lr9 );
    while ( 0 == strstr( app_buf, PROCESS_START_RECEIVE ) )
    {
        lr9_process( &lr9 );
        if ( timeout_cnt++ > RESPONSE_TIMEOUT )
        {
            lr9_clear_app_buf( );
            log_printf( &logger, " Timeout\r\n" );
            break;
        }
        Delay_ms ( 1 );
    }
    lr9_process( &lr9 );
    if ( strstr( app_buf, PROCESS_ATDTRX ) )
    {
        log_printf( &logger, " Receive: " );
        for ( int32_t buf_cnt = 15; buf_cnt < 15 + strlen( LR9_DEMO_STRING ); buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        log_printf( &logger, "\r\n" );
    }
    lr9_clear_app_buf( );
}

static void lr9_log_response ( void )
{
    if ( LR9_OK == lr9_process( &lr9 ) ) 
    {
        lr9_log_app_buf( );
        lr9_clear_app_buf( );
    }
}

static err_t lr9_process ( lr9_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lr9_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return LR9_OK;
    }
    return LR9_ERROR;
}

// ------------------------------------------------------------------------ END
