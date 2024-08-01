/*!
 * @file main.c
 * @brief GNSS 18 Click example
 *
 * # Description
 * This example demonstrates the use of GNSS 18 click by reading and displaying
 * the GNSS coordinates.
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
 * - static void gnss18_clear_app_buf ( void )
 * - static err_t gnss18_process ( gnss18_t *ctx )
 * - static void gnss18_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss18.h"

#define PROCESS_BUFFER_SIZE 300

static gnss18_t gnss18;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS 18 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @return None.
 * @note None.
 */
static void gnss18_clear_app_buf ( void );

/**
 * @brief GNSS 18 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read or Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss18_process ( gnss18_t *ctx );

/**
 * @brief GNSS 18 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss18_parser_application ( uint8_t *rsp );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss18_cfg_t gnss18_cfg;  /**< Click config object. */

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
    gnss18_cfg_setup( &gnss18_cfg );
    GNSS18_MAP_MIKROBUS( gnss18_cfg, MIKROBUS_1 );
    err_t init_flag = gnss18_init( &gnss18, &gnss18_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( GNSS18_OK == gnss18_process( &gnss18 ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gnss18_parser_application( app_buf );
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

static void gnss18_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t gnss18_process ( gnss18_t *ctx ) 
{
    int32_t rx_size = 0;
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    if ( GNSS18_DRV_SEL_UART == ctx->drv_sel )
    {
        rx_size = gnss18_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    }
    else
    {
        if ( GNSS18_OK == gnss18_generic_read( ctx, rx_buf, 1 ) )
        {
            if ( GNSS18_DUMMY != rx_buf[ 0 ] )
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
        return GNSS18_OK;
    }
    return GNSS18_ERROR;
}

static void gnss18_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 100 ] = { 0 };
    if ( GNSS18_OK == gnss18_parse_gpgga( rsp, GNSS18_GPGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( ( strlen( element_buf ) > 0 ) )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            gnss18_parse_gpgga( rsp, GNSS18_GPGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss18_parse_gpgga( rsp, GNSS18_GPGGA_ALTITUDE, element_buf );
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
        gnss18_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
