/*!
 * @file main.c
 * @brief GNSS 15 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS 15 click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the click board.
 *
 * ## Application Task
 * Reads the received data, parses the GPGGA info from it, and once it receives the position fix
 * it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnss15_clear_app_buf ( void )
 * - static err_t gnss15_process ( gnss15_t *ctx )
 * - static void gnss15_parser_application ( uint8_t *rsp )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss15.h"

// Application buffer size
#define PROCESS_BUFFER_SIZE         200

static gnss15_t gnss15;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS 15 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnss15_clear_app_buf ( void );

/**
 * @brief GNSS 15 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss15_process ( gnss15_t *ctx );

/**
 * @brief GNSS 15 parser application.
 * @details This function reads and parse data from device.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss15_parser_application ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss15_cfg_t gnss15_cfg;  /**< Click config object. */

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
    gnss15_cfg_setup( &gnss15_cfg );
    GNSS15_MAP_MIKROBUS( gnss15_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss15_init( &gnss15, &gnss15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( GNSS15_OK == gnss15_process( &gnss15 ) )
    {
        if ( app_buf_len > ( sizeof ( GNSS15_RSP_GPGGA ) + GNSS15_GPGGA_ELEMENT_SIZE ) ) 
        {
            gnss15_parser_application( app_buf );
        }
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

static void gnss15_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t gnss15_process ( gnss15_t *ctx ) 
{
    int32_t rx_size = 0;
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    if ( GNSS15_DRV_SEL_UART == ctx->drv_sel )
    {
        rx_size = gnss15_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    }
    else
    {
        if ( GNSS15_OK == gnss15_generic_read( ctx, rx_buf, 1 ) )
        {
            if ( GNSS15_DUMMY != rx_buf[ 0 ] )
            {
                rx_size = 1;
            }
        }
    }
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
        return GNSS15_OK;
    }
    return GNSS15_ERROR;
}

static void gnss15_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 100 ] = { 0 };
    if ( GNSS15_OK == gnss15_parse_gpgga( rsp, GNSS15_GPGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( ( strlen( element_buf ) > 0 ) && ( !strstr ( element_buf, GNSS15_RSP_NO_FIX ) ) )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            gnss15_parse_gpgga( rsp, GNSS15_GPGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss15_parse_gpgga( rsp, GNSS15_GPGGA_ALTITUDE, element_buf );
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
        gnss15_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
