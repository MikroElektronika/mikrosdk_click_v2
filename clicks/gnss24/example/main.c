/*!
 * @file main.c
 * @brief GNSS 24 Click Example.
 *
 * # Description
 * This example demonstrates the use of GNSS 24 Click by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets the Click board, reads the module version,
 * enables 1PPS output, and starts positioning.
 *
 * ## Application Task
 * Reads the received data, parses the NMEA GGA info from it, and once it receives 
 * the position fix it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void gnss24_clear_app_buf ( void )
 * - static void gnss24_log_app_buf ( void )
 * - static err_t gnss24_process ( gnss24_t *ctx )
 * - static err_t gnss24_read_response ( gnss24_t *ctx, uint8_t *rsp )
 * - static void gnss24_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss24.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static gnss24_t gnss24;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief GNSS 24 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void gnss24_clear_app_buf ( void );

/**
 * @brief GNSS 24 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void gnss24_log_app_buf ( void );

/**
 * @brief GNSS 24 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss24_process ( gnss24_t *ctx );

/**
 * @brief GNSS 24 read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gnss24_read_response ( gnss24_t *ctx, uint8_t *rsp );

/**
 * @brief GNSS 24 parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void gnss24_parser_application ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss24_cfg_t gnss24_cfg;  /**< Click config object. */

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
    gnss24_cfg_setup( &gnss24_cfg );
    GNSS24_MAP_MIKROBUS( gnss24_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss24_init( &gnss24, &gnss24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    gnss24_reset_device ( &gnss24 );
    
    log_printf( &logger, ">>> Get module version.\r\n" );
    gnss24_cmd_run ( &gnss24, GNSS24_CMD_FW_REV_NUM_ACQ );
    gnss24_read_response ( &gnss24, GNSS24_RSP_DONE );

    log_printf( &logger, ">>> Enable 1PPS output.\r\n" );
    gnss24_cmd_set ( &gnss24, GNSS24_CMD_1PPS_OUT_SET, "1" );
    gnss24_read_response ( &gnss24, GNSS24_RSP_DONE );

    log_printf( &logger, ">>> Start positioning.\r\n" );
    gnss24_cmd_run ( &gnss24, GNSS24_CMD_HOT_START_TTFF );
    gnss24_read_response ( &gnss24, GNSS24_RSP_DONE );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( GNSS24_OK == gnss24_process( &gnss24 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSS24_RSP_GGA ) + GNSS24_GGA_ELEMENT_SIZE ) ) 
        {
            gnss24_parser_application( app_buf );
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

static void gnss24_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void gnss24_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t gnss24_process ( gnss24_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = gnss24_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return GNSS24_OK;
    }
    return GNSS24_ERROR;
}

static err_t gnss24_read_response ( gnss24_t *ctx, uint8_t *rsp )
{
    #define READ_RESPONSE_TIMEOUT_MS 5000
    uint32_t timeout_cnt = 0;
    gnss24_clear_app_buf ( );
    while ( ( GNSS24_OK == gnss24_process( ctx ) ) || ( 0 == strstr( app_buf, rsp ) ) )
    {
        if ( timeout_cnt > READ_RESPONSE_TIMEOUT_MS )
        {
            gnss24_log_app_buf( );
            gnss24_clear_app_buf( );
            log_error( &logger, " Timeout!" );
            return GNSS24_ERROR_TIMEOUT;
        }
        timeout_cnt += 10;
        Delay_ms( 10 );
    }
    gnss24_log_app_buf( );
    log_printf( &logger, "--------------------------------\r\n" );
    return GNSS24_OK;
}

static void gnss24_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 200 ] = { 0 };
    if ( GNSS24_OK == gnss24_parse_gga( rsp, GNSS24_GGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss24_parse_gga( rsp, GNSS24_GGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            gnss24_parse_gga( rsp, GNSS24_GGA_ALTITUDE, element_buf );
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
        gnss24_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
