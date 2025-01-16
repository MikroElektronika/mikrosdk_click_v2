/*!
 * @file main.c
 * @brief NINA-B222 Click Example.
 *
 * # Description
 * This example demonstrates the use of NINA-B222 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void ninab222_clear_app_buf ( void )
 * - static void ninab222_log_app_buf ( void )
 * - static err_t ninab222_process ( ninab222_t *ctx )
 *
 * @note
 * - Recommended Android application at the link:
 *   https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal
 * - Before using this Click, it must be paired with your devices.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ninab222.h"

// Demo device name
#define DEVICE_NAME                 "NINA-B222 Click"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static ninab222_t ninab222;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief NINA-B222 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ninab222_clear_app_buf ( void );

/**
 * @brief NINA-B222 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void ninab222_log_app_buf ( void );

/**
 * @brief NINA-B222 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ninab222_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ninab222_process ( ninab222_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ninab222_cfg_t ninab222_cfg;  /**< Click config object. */

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
    ninab222_cfg_setup( &ninab222_cfg );
    NINAB222_MAP_MIKROBUS( ninab222_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ninab222_init( &ninab222, &ninab222_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ninab222_hw_reset( &ninab222 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Configuring the module " );
    Delay_ms ( 1000 );
    
    ninab222_set_sry_pin( &ninab222, NINAB222_PIN_STATE_HIGH );
    Delay_ms ( 100 );

    do 
    {
        ninab222_set_echo( &ninab222, NINAB222_ECHO_ON );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );

    do 
    {
        ninab222_get_info( &ninab222 );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_device_name( &ninab222, DEVICE_NAME );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_connectability( &ninab222, NINAB222_GAP_MODE_CONN );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_discoverability( &ninab222, NINAB222_GAP_MODE_GEN_DISC );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    Delay_ms ( 500 );
    
    do 
    {
        ninab222_set_enter_mode( &ninab222, NINAB222_MODE_DATA );
        Delay_ms ( 100 );
    }
    while ( NINAB222_OK != ninab222_process( &ninab222 ) );
    ninab222_clear_app_buf( );
    Delay_ms ( 500 );
    
    ninab222_set_sry_pin( &ninab222, NINAB222_PIN_STATE_LOW );
    log_info( &logger, " Configuration is complete " );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    if ( NINAB222_OK == ninab222_process( &ninab222 ) ) 
    {
        ninab222_log_app_buf( );
        ninab222_clear_app_buf( );
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

static void ninab222_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ninab222_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ninab222_process ( ninab222_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ninab222_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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

        if ( strstr( rx_buf, NINAB222_RSP_OK ) ) 
        {
            log_printf( &logger, "%s", rx_buf );
            Delay_ms ( 100 );
            return NINAB222_OK;
        }

        if ( strstr( rx_buf, NINAB222_RSP_ERROR ) ) 
        {
            return NINAB222_ERROR;
        }

        return NINAB222_OK;
    }
    return NINAB222_ERROR;
}

// ------------------------------------------------------------------------ END
