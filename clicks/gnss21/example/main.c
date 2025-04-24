/*!
 * @file main.c
 * @brief GNSS 21 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS 21 Click by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the received data, parses the NMEA GGA info from it, and once it receives 
 * the position fix it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnss21_clear_app_buf ( void )
 * - static void gnss21_log_app_buf ( void )
 * - static err_t gnss21_process ( gnss21_t *ctx )
 * - static void gnss21_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss21.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static gnss21_t gnss21;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static uint8_t i2c_data_ready = 0;

/**
 * @brief GNSS 21 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnss21_clear_app_buf ( void );

/**
 * @brief GNSS 21 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void gnss21_log_app_buf ( void );

/**
 * @brief GNSS 21 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnss21_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss21_process ( gnss21_t *ctx );

/**
 * @brief GNSS 21 parser application.
 * @details This function logs GNSS data on the USB UART.
 * @param[in] rsp Response buffer.
 * @return None.
 * @note None.
 */
static void gnss21_parser_application ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss21_cfg_t gnss21_cfg;  /**< Click config object. */

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
    gnss21_cfg_setup( &gnss21_cfg );
    GNSS21_MAP_MIKROBUS( gnss21_cfg, MIKROBUS_1 );
    if ( GNSS21_OK != gnss21_init( &gnss21, &gnss21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( GNSS21_OK == gnss21_process( &gnss21 ) ) 
    {
        gnss21_parser_application( app_buf );
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

static void gnss21_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void gnss21_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t gnss21_process ( gnss21_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = 0;
    
    if ( ( GNSS21_DRV_SEL_I2C == ctx->drv_sel ) && ( !i2c_data_ready ) )
    {
        uint16_t pps_wait_log_cnt = 0;
        while ( !gnss21_get_pps_pin ( ctx ) )
        {
            if ( ++pps_wait_log_cnt > 5000 )
            {
                log_printf( &logger, " Waiting for the position fix (PPS signal)...\r\n\n" );
                pps_wait_log_cnt = 0;
            }
            Delay_ms ( 1 );
        }
        i2c_data_ready = 1;
        Delay_ms ( 200 );
    }
    rx_size = gnss21_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
            if ( rx_buf[ rx_cnt ] && ( GNSS21_DUMMY != rx_buf[ rx_cnt ] ) ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return GNSS21_OK;
    }
    return GNSS21_ERROR;
}

static void gnss21_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 200 ] = { 0 };
    if ( GNSS21_OK == gnss21_parse_gga( rsp, GNSS21_GGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( ( strlen( element_buf ) > 0 ) && ( !strstr ( element_buf, GNSS21_RSP_NO_FIX ) ) )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes\r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss21_parse_gga( rsp, GNSS21_GGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes\r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss21_parse_gga( rsp, GNSS21_GGA_ALTITUDE, element_buf );
            log_printf( &logger, " Altitude: %s m\r\n", element_buf );
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
        gnss21_clear_app_buf(  );
        i2c_data_ready = 0;
    }
}

// ------------------------------------------------------------------------ END
