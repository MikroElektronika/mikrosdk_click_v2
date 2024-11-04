/*!
 * @file main.c
 * @brief GNSS 14 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS 14 Click board by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the Click board.
 *
 * ## Application Task
 * Reads the received data, parses the GNGGA info from it, and once it receives the position fix
 * it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnss14_clear_app_buf ( void )
 * - static err_t gnss14_process ( gnss14_t *ctx )
 * - static void gnss14_parser_application ( char *rsp )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss14.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static gnss14_t gnss14;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS 14 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnss14_clear_app_buf ( void );

/**
 * @brief GNSS 14 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss14_process ( gnss14_t *ctx );

/**
 * @brief GNSS 14 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss14_parser_application ( char *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss14_cfg_t gnss14_cfg;  /**< Click config object. */

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
    gnss14_cfg_setup( &gnss14_cfg );
    GNSS14_MAP_MIKROBUS( gnss14_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss14_init( &gnss14, &gnss14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss14_reset_device( &gnss14 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( GNSS14_OK == gnss14_process( &gnss14 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSS14_RSP_GNGGA ) + GNSS14_GNGGA_ELEMENT_SIZE ) ) 
        {
            gnss14_parser_application( app_buf );
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

static void gnss14_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t gnss14_process ( gnss14_t *ctx ) 
{
    int32_t rx_size = 0;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    if ( GNSS14_DRV_SEL_UART == ctx->drv_sel )
    {
        rx_size = gnss14_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    }
    else if ( ( GNSS14_DRV_SEL_I2C == ctx->drv_sel ) )
    {
        if ( GNSS14_OK == gnss14_generic_read( ctx, rx_buf, 1 ) )
        {
            if ( GNSS14_DUMMY != rx_buf[ 0 ] )
            {
                rx_size = 1;
            }
        }
    }
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            gnss14_clear_app_buf(  );
            return GNSS14_ERROR;
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
        return GNSS14_OK;
    }
    return GNSS14_ERROR;
}

static void gnss14_parser_application ( char *rsp )
{
    char element_buf[ 100 ] = { 0 };
    if ( GNSS14_OK == gnss14_parse_gngga( rsp, GNSS14_GNGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            gnss14_parse_gngga( rsp, GNSS14_GNGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss14_parse_gngga( rsp, GNSS14_GNGGA_ALTITUDE, element_buf );
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
        gnss14_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
