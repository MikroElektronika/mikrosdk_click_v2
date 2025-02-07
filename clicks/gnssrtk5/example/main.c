/*!
 * @file main.c
 * @brief GNSS RTK 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS RTK 5 Click by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets the Click board, reads the module version and config,
 * and enables the NMEA GNGGA message output.
 *
 * ## Application Task
 * Reads the received data, parses the NMEA GGA info from it, and once it receives 
 * the position fix it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnssrtk5_clear_app_buf ( void )
 * - static void gnssrtk5_log_app_buf ( void )
 * - static err_t gnssrtk5_process ( gnssrtk5_t *ctx )
 * - static err_t gnssrtk5_read_response ( gnssrtk5_t *ctx, uint8_t *rsp )
 * - static void gnssrtk5_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnssrtk5.h"

// Application buffer size
#define APP_BUFFER_SIZE             800
#define PROCESS_BUFFER_SIZE         100

static gnssrtk5_t gnssrtk5;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS RTK 5 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnssrtk5_clear_app_buf ( void );

/**
 * @brief GNSS RTK 5 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void gnssrtk5_log_app_buf ( void );

/**
 * @brief GNSS RTK 5 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnssrtk5_process ( gnssrtk5_t *ctx );

/**
 * @brief GNSS RTK 5 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnssrtk5_read_response ( gnssrtk5_t *ctx, uint8_t *rsp );

/**
 * @brief GNSS RTK 5 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnssrtk5_parser_application ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk5_cfg_t gnssrtk5_cfg;  /**< Click config object. */

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
    gnssrtk5_cfg_setup( &gnssrtk5_cfg );
    GNSSRTK5_MAP_MIKROBUS( gnssrtk5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnssrtk5_init( &gnssrtk5, &gnssrtk5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Reset device.\r\n" );
    gnssrtk5_reset_device ( &gnssrtk5 );
    gnssrtk5_read_response ( &gnssrtk5, GNSSRTK5_RSP_RESET );
    
    log_printf( &logger, ">>> Get module version.\r\n" );
    gnssrtk5_cmd_run ( &gnssrtk5, GNSSRTK5_CMD_GET_VERSION );
    gnssrtk5_read_response ( &gnssrtk5, GNSSRTK5_RSP_COMMAND );

    log_printf( &logger, ">>> Get module config.\r\n" );
    gnssrtk5_cmd_run ( &gnssrtk5, GNSSRTK5_CMD_GET_CONFIG );
    gnssrtk5_read_response ( &gnssrtk5, GNSSRTK5_RSP_COMMAND );

    log_printf( &logger, ">>> Enable GNGGA output.\r\n" );
    gnssrtk5_cmd_run ( &gnssrtk5, GNSSRTK5_CMD_ENABLE_GGA );
    gnssrtk5_read_response ( &gnssrtk5, GNSSRTK5_RSP_COMMAND );
    gnssrtk5_clear_app_buf( );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( GNSSRTK5_OK == gnssrtk5_process( &gnssrtk5 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSSRTK5_RSP_GGA ) + GNSSRTK5_GGA_ELEMENT_SIZE ) ) 
        {
            gnssrtk5_parser_application( app_buf );
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

static void gnssrtk5_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void gnssrtk5_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t gnssrtk5_process ( gnssrtk5_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = gnssrtk5_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return GNSSRTK5_OK;
    }
    return GNSSRTK5_ERROR;
}

static err_t gnssrtk5_read_response ( gnssrtk5_t *ctx, uint8_t *rsp )
{
    #define READ_RESPONSE_TIMEOUT_MS 5000
    uint32_t timeout_cnt = 0;
    gnssrtk5_clear_app_buf ( );
    while ( ( GNSSRTK5_OK == gnssrtk5_process( ctx ) ) || ( 0 == strstr( app_buf, rsp ) ) )
    {
        if ( timeout_cnt > READ_RESPONSE_TIMEOUT_MS )
        {
            gnssrtk5_log_app_buf( );
            gnssrtk5_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return GNSSRTK5_ERROR_TIMEOUT;
        }
        timeout_cnt += 10;
        Delay_ms( 10 );
    }
    gnssrtk5_log_app_buf( );
    log_printf( &logger, "--------------------------------\r\n" );
    return GNSSRTK5_OK;
}

static void gnssrtk5_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    if ( GNSSRTK5_OK == gnssrtk5_parse_gga( rsp, GNSSRTK5_GGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnssrtk5_parse_gga( rsp, GNSSRTK5_GGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnssrtk5_parse_gga( rsp, GNSSRTK5_GGA_ALTITUDE, element_buf );
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
        gnssrtk5_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
