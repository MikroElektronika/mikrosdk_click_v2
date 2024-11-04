/*!
 * @file main.c
 * @brief GNSS MAX 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS MAX 2 Click by reading and displaying
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
 * - static void gnssmax2_clear_app_buf ( void )
 * - static void gnssmax2_log_app_buf ( void )
 * - static err_t gnssmax2_process ( gnssmax2_t *ctx )
 * - static void gnssmax2_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnssmax2.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static gnssmax2_t gnssmax2;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static uint8_t i2c_data_ready = 0;

/**
 * @brief GNSS MAX 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnssmax2_clear_app_buf ( void );

/**
 * @brief GNSS MAX 2 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void gnssmax2_log_app_buf ( void );

/**
 * @brief GNSS MAX 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnssmax2_process ( gnssmax2_t *ctx );

/**
 * @brief GNSS MAX 2 parser application.
 * @details This function logs GNSS data on the USB UART.
 * @param[in] rsp Response buffer.
 * @return None.
 * @note None.
 */
static void gnssmax2_parser_application ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssmax2_cfg_t gnssmax2_cfg;  /**< Click config object. */

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
    gnssmax2_cfg_setup( &gnssmax2_cfg );
    GNSSMAX2_MAP_MIKROBUS( gnssmax2_cfg, MIKROBUS_1 );
    if ( GNSSMAX2_OK != gnssmax2_init( &gnssmax2, &gnssmax2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( GNSSMAX2_OK == gnssmax2_process( &gnssmax2 ) ) 
    {
        gnssmax2_parser_application( app_buf );
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

static void gnssmax2_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void gnssmax2_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t gnssmax2_process ( gnssmax2_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = 0;
    
    if ( ( GNSSMAX2_DRV_SEL_I2C == ctx->drv_sel ) && ( !i2c_data_ready ) )
    {
        uint16_t pps_wait_log_cnt = 0;
        while ( !gnssmax2_get_pps_pin ( ctx ) )
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
    rx_size = gnssmax2_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
            if ( rx_buf[ rx_cnt ] && ( GNSSMAX2_DUMMY != rx_buf[ rx_cnt ] ) ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return GNSSMAX2_OK;
    }
    return GNSSMAX2_ERROR;
}

static void gnssmax2_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 200 ] = { 0 };
    if ( GNSSMAX2_OK == gnssmax2_parse_gga( rsp, GNSSMAX2_GGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes\r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnssmax2_parse_gga( rsp, GNSSMAX2_GGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes\r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnssmax2_parse_gga( rsp, GNSSMAX2_GGA_ALTITUDE, element_buf );
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
        gnssmax2_clear_app_buf(  );
        i2c_data_ready = 0;
    }
}

// ------------------------------------------------------------------------ END
