/*!
 * @file main.c
 * @brief GNSS 16 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS 16 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the Click board.
 *
 * ## Application Task
 * Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void gnss16_clear_app_buf ( void )
 * - static err_t gnss16_process ( gnss16_t *ctx )
 * - static void gnss16_parser_application ( char *rsp )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss16.h"

// Application buffer size
#define PROCESS_BUFFER_SIZE         200

static gnss16_t gnss16;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS 16 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnss16_clear_app_buf ( void );

/**
 * @brief GNSS 16 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnss16_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss16_process ( gnss16_t *ctx );

/**
 * @brief GNSS 16 parser application.
 * @details This function reads and parse data from device.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss16_parser_application ( char *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss16_cfg_t gnss16_cfg;  /**< Click config object. */

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
    gnss16_cfg_setup( &gnss16_cfg );
    GNSS16_MAP_MIKROBUS( gnss16_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss16_init( &gnss16, &gnss16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss16_reset_device( &gnss16 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    gnss16_process( &gnss16 );
    if ( app_buf_len > ( sizeof ( GNSS16_RSP_GNGGA ) + GNSS16_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnss16_parser_application( app_buf );
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

static void gnss16_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t gnss16_process ( gnss16_t *ctx ) 
{
    int32_t rx_size = 0;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = gnss16_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            gnss16_clear_app_buf(  );
            return GNSS16_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buf[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return GNSS16_OK;
    }
    return GNSS16_ERROR;
}

static void gnss16_parser_application ( char *rsp )
{
    char element_buf[ 100 ] = { 0 };
    if ( GNSS16_OK == gnss16_parse_gngga( rsp, GNSS16_GNGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            gnss16_parse_gngga( rsp, GNSS16_GNGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss16_parse_gngga( rsp, GNSS16_GNGGA_ALTITUDE, element_buf );
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
        gnss16_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
