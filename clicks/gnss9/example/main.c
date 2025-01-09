/*!
 * @file main.c
 * @brief GNSS 9 Click example
 *
 * # Description
 * This example demonstrates the use of GNSS 9 Click by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the Click board.
 *
 * ## Application Task
 * Reads the received data, parses the GPGGA info from it, and once it receives the position fix
 * it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnss9_clear_app_buf ( void )
 * - static err_t gnss9_process ( gnss9_t *ctx )
 * - static void gnss9_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss9.h"

#define PROCESS_BUFFER_SIZE 300

static gnss9_t gnss9;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS 9 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @return None.
 * @note None.
 */
static void gnss9_clear_app_buf ( void );

/**
 * @brief GNSS 9 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read or Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss9_process ( gnss9_t *ctx );

/**
 * @brief GNSS 9 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss9_parser_application ( uint8_t *rsp );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss9_cfg_t gnss9_cfg;  /**< Click config object. */

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
    gnss9_cfg_setup( &gnss9_cfg );
    GNSS9_MAP_MIKROBUS( gnss9_cfg, MIKROBUS_1 );
    err_t init_flag = gnss9_init( &gnss9, &gnss9_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( GNSS9_OK == gnss9_process( &gnss9 ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gnss9_parser_application( app_buf );
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

static void gnss9_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t gnss9_process ( gnss9_t *ctx ) 
{
    int32_t rx_size = 0;
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    if ( GNSS9_DRV_SEL_UART == ctx->drv_sel )
    {
        rx_size = gnss9_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    }
    else
    {
        if ( GNSS9_OK == gnss9_generic_read( ctx, rx_buf, 1 ) )
        {
            if ( GNSS9_DUMMY != rx_buf[ 0 ] )
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
        return GNSS9_OK;
    }
    return GNSS9_ERROR;
}

static void gnss9_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 100 ] = { 0 };
    if ( GNSS9_OK == gnss9_parse_gpgga( rsp, GNSS9_GPGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( ( strlen( element_buf ) > 0 ) )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            gnss9_parse_gpgga( rsp, GNSS9_GPGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss9_parse_gpgga( rsp, GNSS9_GPGGA_ALTITUDE, element_buf );
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
        gnss9_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END