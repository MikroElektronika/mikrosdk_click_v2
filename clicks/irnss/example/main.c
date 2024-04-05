/*!
 * @file main.c
 * @brief IRNSS Click Example.
 *
 * # Description
 * This example demonstrates the use of IRNSS click by reading and displaying
 * the GPS coordinates.
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
 * - static void irnss_clear_app_buf ( void )
 * - static err_t irnss_process ( irnss_t *ctx )
 * - static void irnss_parser_application ( char *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irnss.h"

#define PROCESS_BUFFER_SIZE 200

static irnss_t irnss;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief IRNSS clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @return None.
 * @note None.
 */
static void irnss_clear_app_buf ( void );

/**
 * @brief IRNSS data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #irnss_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read or Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irnss_process ( irnss_t *ctx );

/**
 * @brief IRNSS parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void irnss_parser_application ( char *rsp );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irnss_cfg_t irnss_cfg;  /**< Click config object. */

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
    irnss_cfg_setup( &irnss_cfg );
    IRNSS_MAP_MIKROBUS( irnss_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irnss_init( &irnss, &irnss_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    irnss_process( &irnss );
    if ( app_buf_len > ( sizeof ( ( char * ) IRNSS_RSP_GNGGA ) + IRNSS_GNGGA_ELEMENT_SIZE ) ) 
    {
        irnss_parser_application( app_buf );
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

static void irnss_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t irnss_process ( irnss_t *ctx ) 
{
    int32_t rx_size = 0;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = irnss_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            irnss_clear_app_buf(  );
            return IRNSS_ERROR;
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
        return IRNSS_OK;
    }
    return IRNSS_ERROR;
}

static void irnss_parser_application ( char *rsp )
{
    char element_buf[ 100 ] = { 0 };
    if ( IRNSS_OK == irnss_parse_gngga( rsp, IRNSS_GNGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            irnss_parse_gngga( rsp, IRNSS_GNGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            irnss_parse_gngga( rsp, IRNSS_GNGGA_ALTITUDE, element_buf );
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
        irnss_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
