/*!
 * @file main.c
 * @brief LR 10 Click Example.
 *
 * # Description
 * This example demonstrates the use of LR 10 click board by processing
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
 * - static void lr10_clear_app_buf ( void )
 * - static void lr10_log_app_buf ( void )
 * - static void lr10_log_receiver ( void )
 * - static err_t lr10_process ( lr10_t *ctx )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lr10.h"
#include "conversions.h"

// Comment the line below to switch application mode to receiver
#define DEMO_APP_TRANSMITTER

// Application buffer size
#define PROCESS_BUFFER_SIZE       200

// Default RF configuration
#define PROCESS_RF_CFG_DEFAULT    "868,SF7,125,8,8,14,ON,OFF,OFF"

// Application demo string
#define LR10_DEMO_STRING          "MikroE - LR 10 Click"

static lr10_t lr10;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief LR 10 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lr10_clear_app_buf ( void );

/**
 * @brief LR 10 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void lr10_log_app_buf ( void );

/**
 * @brief LR 10 log receiver data.
 * @details This function logs data from receiver application buffer to USB UART.
 * @note None.
 */
static void lr10_log_receiver ( void );

/**
 * @brief LR 10 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lr10_process ( lr10_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr10_cfg_t lr10_cfg;  /**< Click config object. */

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
    lr10_cfg_setup( &lr10_cfg );
    LR10_MAP_MIKROBUS( lr10_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr10_init( &lr10, &lr10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    lr10_hw_reset( &lr10 );
    Delay_ms( 500 );

    lr10_generic_write( &lr10, LR10_CMD_AT, strlen(LR10_CMD_AT) );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_VER );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_ID );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms( 500 );
    
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_MODE, LR10_SUB_CMD_MODE_TEST, 
                                     LR10_SYMBOL_NULL, LR10_QUOTE_DISABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_TEST );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms( 500 );

    lr10_inquire_cmd( &lr10, LR10_CMD_MODE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms( 500 );

#ifdef DEMO_APP_TRANSMITTER
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_RFCFG, 
                                     PROCESS_RF_CFG_DEFAULT, LR10_QUOTE_DISABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms( 500 );
#endif
    
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_TX_STR, 
                                     LR10_DEMO_STRING, LR10_QUOTE_ENABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
#else
    lr10_write_cmd_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_RX );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_receiver( );
        lr10_clear_app_buf( );
    }
#endif
    Delay_ms( 1000 );   
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void lr10_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void lr10_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static void lr10_log_receiver ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        if ( ( app_buf[ buf_cnt ] == LR10_ASCII_SPACE ) && 
             ( app_buf[ buf_cnt + 1 ] == LR10_ASCII_QUOTE ) )
        {
            buf_cnt += 2;
            log_printf( &logger, "  Receive: " );
            for ( ; buf_cnt < app_buf_len - 3; buf_cnt += 2 )
            {
                uint8_t hex_in[ 3 ] = { 0 };
                hex_in[ 0 ] = app_buf[ buf_cnt ];
                hex_in[ 1 ] = app_buf[ buf_cnt + 1 ];
                log_printf( &logger, "%c", hex_to_uint8( hex_in ) );
            }
            log_printf( &logger, "\r\n" );
            break;
        }
    }
}

static err_t lr10_process ( lr10_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = lr10_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= PROCESS_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - PROCESS_BUFFER_SIZE;
            app_buf_len = PROCESS_BUFFER_SIZE - rx_size;
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
        return LR10_OK;
    }
    return LR10_ERROR;
}

// ------------------------------------------------------------------------ END
