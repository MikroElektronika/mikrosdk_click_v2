/*!
 * @file main.c
 * @brief GNSS 11 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS 11 Click by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the Click board.
 *
 * ## Application Task
 * Reads the received data, parses the NMEA GGA info from it, and once it receives 
 * the position fix it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnss11_clear_app_buf ( void )
 * - static void gnss11_log_app_buf ( void )
 * - static err_t gnss11_process ( gnss11_t *ctx )
 * - static void gnss11_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss11.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static gnss11_t gnss11;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS 11 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnss11_clear_app_buf ( void );

/**
 * @brief GNSS 11 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void gnss11_log_app_buf ( void );

/**
 * @brief GNSS 11 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnss11_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss11_process ( gnss11_t *ctx );

/**
 * @brief GNSS 11 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss11_parser_application ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss11_cfg_t gnss11_cfg;  /**< Click config object. */

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
    gnss11_cfg_setup( &gnss11_cfg );
    GNSS11_MAP_MIKROBUS( gnss11_cfg, MIKROBUS_1 );
    if ( GNSS11_OK != gnss11_init( &gnss11, &gnss11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss11_reset_device ( &gnss11 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    gnss11_process( &gnss11 );
    if ( app_buf_len > ( sizeof ( GNSS11_RSP_GGA ) + GNSS11_GGA_ELEMENT_SIZE ) ) 
    {
        gnss11_parser_application( app_buf );
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

static void gnss11_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void gnss11_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t gnss11_process ( gnss11_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = 0;
    if ( GNSS11_DRV_SEL_UART == ctx->drv_sel )
    {
        rx_size = gnss11_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    }
    else if ( ( GNSS11_DRV_SEL_I2C == ctx->drv_sel ) || ( GNSS11_DRV_SEL_SPI == ctx->drv_sel ) )
    {
        if ( GNSS11_OK == gnss11_generic_read( ctx, rx_buf, 1 ) )
        {
            if ( GNSS11_DUMMY != rx_buf[ 0 ] )
            {
                rx_size = 1;
            }
        }
    }
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
        return GNSS11_OK;
    }
    return GNSS11_ERROR;
}

static void gnss11_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 100 ] = { 0 };
    if ( GNSS11_OK == gnss11_parse_gga( rsp, GNSS11_GGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss11_parse_gga( rsp, GNSS11_GGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss11_parse_gga( rsp, GNSS11_GGA_ALTITUDE, element_buf );
            log_printf( &logger, " Altitude: %s m \r\n", element_buf );
            wait_for_fix_cnt = 0;
        }
        else
        {
            if ( wait_for_fix_cnt % 5 == 0 )
            {
                log_printf( &logger, " Waiting for the position fix...\r\n\n" );
                wait_for_fix_cnt = 0;
            }
            wait_for_fix_cnt++;
        }
        gnss11_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
