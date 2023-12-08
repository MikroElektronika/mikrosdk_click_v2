/*!
 * @file main.c
 * @brief ANNA-B412 Click Example.
 *
 * # Description
 * This example demonstrates the use of ANNA-B412 click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void annab412_clear_app_buf ( void )
 * - static err_t annab412_process ( annab412_t *ctx )
 * - static err_t annab412_display_rsp ( char *rsp_end )
 *
 * @note
 * We have used the BLE Scanner smartphone application for the test.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "annab412.h"

#define PROCESS_BUFFER_SIZE    200
#define DEVICE_NAME            "ANNA-B412 Click"
#define RSP_TIMEOUT            20000
#define RSP_OK                 "OK"

static annab412_t annab412;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief ANNA-B412 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void annab412_clear_app_buf ( void );

/**
 * @brief ANNA-B412 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t annab412_process ( annab412_t *ctx );

/**
 * @brief ANNA-B412 display response function.
 * @details This function reads data from device until sends @a rsp_end or ERROR message or until
 * it exceeds the timeout value.
 * @param[in] rsp_end : Response/Event ending string
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t annab412_display_rsp ( char *rsp_end );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    annab412_cfg_t annab412_cfg;  /**< Click config object. */

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
    annab412_cfg_setup( &annab412_cfg );
    ANNAB412_MAP_MIKROBUS( annab412_cfg, MIKROBUS_1 );
    if ( UART_ERROR == annab412_init( &annab412, &annab412_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANNAB412_ERROR == annab412_default_cfg ( &annab412 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 1000 );
    
    annab412_set_cmd_echo_on( &annab412 );
    annab412_display_rsp( RSP_OK );
    Delay_ms( 100 );
    
    annab412_set_cmd_device_name( &annab412, DEVICE_NAME );
    annab412_display_rsp( RSP_OK );
    Delay_ms( 100 );

    annab412_set_cmd_discover_mode( &annab412, ANNAB412_DISCOVERABLE_MODE_ON );
    annab412_display_rsp( RSP_OK );
    Delay_ms( 100 );

    annab412_set_cmd_enter_mode( &annab412, ANNAB412_ENTER_MODE_DATA );
    annab412_display_rsp( RSP_OK );
    Delay_ms( 100 );
    
    annab412_set_dsr_pin( &annab412, ANNAB412_PIN_STATE_LOW );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    annab412_process( &annab412 );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        annab412_clear_app_buf( );
    }
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

static void annab412_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t annab412_process ( annab412_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = annab412_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = PROCESS_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - PROCESS_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ PROCESS_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < PROCESS_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return ANNAB412_OK;
    }
    return ANNAB412_ERROR;
}

static err_t annab412_display_rsp ( char *rsp_end )
{
    uint32_t timeout = RSP_TIMEOUT;
    annab412_clear_app_buf( );
    while ( timeout-- )
    {
        annab412_process( &annab412 );
        if ( app_buf_len > 0 )
        {
            for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
            {
                log_printf( &logger, "%c", app_buf[ buf_cnt ] );
            }
            if ( strstr( app_buf, rsp_end ) )
            {
                annab412_clear_app_buf( );
                Delay_ms( 100 );
                annab412_process( &annab412 );
                for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
                {
                    log_printf( &logger, "%c", app_buf[ buf_cnt ] );
                }
                annab412_clear_app_buf( );
                log_printf( &logger, "--------------------------------\r\n" );
                return ANNAB412_OK;
            }
        }
        Delay_ms( 1 );
    }
    return ANNAB412_ERROR;
}

// ------------------------------------------------------------------------ END
