/*!
 * @file main.c
 * @brief GNSS10 Click example
 *
 * # Description
 * This example demonstrates the use of GNSS 10 click by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the click board.
 *
 * ## Application Task
 * Reads the received data, parses the GNGGA info from it, and once it receives the position fix
 * it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnss10_clear_app_buf ( void )
 * - static err_t gnss10_process ( gnss10_t *ctx )
 * - static void gnss10_parser_application ( char *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss10.h"

#define PROCESS_BUFFER_SIZE 200

static gnss10_t gnss10;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief GNSS 10 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @return None.
 * @note None.
 */
static void gnss10_clear_app_buf ( void );

/**
 * @brief GNSS 10 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read or Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss10_process ( gnss10_t *ctx );

/**
 * @brief GNSS 10 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss10_parser_application ( char *rsp );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss10_cfg_t gnss10_cfg;  /**< Click config object. */

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
    gnss10_cfg_setup( &gnss10_cfg );
    GNSS10_MAP_MIKROBUS( gnss10_cfg, MIKROBUS_1 );
    err_t init_flag = gnss10_init( &gnss10, &gnss10_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss10_reset_device ( &gnss10 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    gnss10_process( &gnss10 );
    if ( app_buf_len > ( sizeof ( GNSS10_RSP_GNGGA ) + GNSS10_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnss10_parser_application( app_buf );
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

static void gnss10_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t gnss10_process ( gnss10_t *ctx ) 
{
    int32_t rx_size = 0;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    if ( GNSS10_DRV_SEL_UART == ctx->drv_sel )
    {
        rx_size = gnss10_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    }
    else if ( ( GNSS10_DRV_SEL_I2C == ctx->drv_sel ) || ( GNSS10_DRV_SEL_SPI == ctx->drv_sel ) )
    {
        if ( GNSS10_OK == gnss10_generic_read( ctx, rx_buf, 1 ) )
        {
            if ( GNSS10_DUMMY != rx_buf[ 0 ] )
            {
                rx_size = 1;
            }
        }
    }
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) 
        {
            gnss10_clear_app_buf(  );
            return GNSS10_ERROR;
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
        return GNSS10_OK;
    }
    return GNSS10_ERROR;
}

static void gnss10_parser_application ( char *rsp )
{
    char element_buf[ 100 ] = { 0 };
    if ( GNSS10_OK == gnss10_parse_gngga( rsp, GNSS10_GNGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            gnss10_parse_gngga( rsp, GNSS10_GNGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss10_parse_gngga( rsp, GNSS10_GNGGA_ALTITUDE, element_buf );
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
        gnss10_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
