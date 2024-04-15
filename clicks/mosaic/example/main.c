/*!
 * @file main.c
 * @brief Mosaic Click Example.
 *
 * # Description
 * This example demonstrates the use of Mosaic click by reading and displaying
 * the GNSS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, reads the NMEA version, and enables the NMEA output.
 *
 * ## Application Task
 * Reads the received data, parses the NMEA GGA info from it, and once it receives 
 * the position fix it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void mosaic_clear_app_buf ( void )
 * - static void mosaic_log_app_buf ( void )
 * - static err_t mosaic_process ( mosaic_t *ctx )
 * - static err_t mosaic_wait_prompt ( mosaic_t *ctx )
 * - static void mosaic_parser_application ( uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mosaic.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static mosaic_t mosaic;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Mosaic clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void mosaic_clear_app_buf ( void );

/**
 * @brief Mosaic log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void mosaic_log_app_buf ( void );

/**
 * @brief Mosaic data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mosaic_process ( mosaic_t *ctx );

/**
 * @brief Mosaic wait prompt function.
 * @details This function waits for a "COM1>" prompt string to appear on UART which indicates
 * the device is ready to receive commands.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @return @li @c  0 - Prompt (COM1>) read successfully.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mosaic_wait_prompt ( mosaic_t *ctx );

/**
 * @brief Mosaic parser application.
 * @param[in] rsp Response buffer.
 * @details This function logs GNSS data on the USB UART.
 * @return None.
 * @note None.
 */
static void mosaic_parser_application ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mosaic_cfg_t mosaic_cfg;  /**< Click config object. */

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
    mosaic_cfg_setup( &mosaic_cfg );
    MOSAIC_MAP_MIKROBUS( mosaic_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mosaic_init( &mosaic, &mosaic_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( MOSAIC_OK != mosaic_wait_prompt( &mosaic ) )
    {
        log_error( &logger, " No connection prompt detected." );
        for ( ; ; );
    }
    mosaic_log_app_buf( );
    mosaic_clear_app_buf( );
    Delay_ms ( 100 );

    mosaic_send_cmd( &mosaic, MOSAIC_CMD_GET_NMEA_VERSION );
    mosaic_wait_prompt( &mosaic );
    mosaic_log_app_buf( );
    mosaic_clear_app_buf( );
    Delay_ms ( 100 );

    mosaic_enable_nmea_output( &mosaic, MOSAIC_SNO_MESSAGES_GGA, MOSAIC_SNO_INTERVAL_SEC1 );
    mosaic_wait_prompt( &mosaic );
    mosaic_log_app_buf( );
    mosaic_clear_app_buf( );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    mosaic_process( &mosaic );
    if ( app_buf_len > ( sizeof ( MOSAIC_NMEA_GGA ) + MOSAIC_GGA_ELEMENT_SIZE ) ) 
    {
        mosaic_parser_application( app_buf );
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

static void mosaic_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void mosaic_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n" );
}

static err_t mosaic_process ( mosaic_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = mosaic_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return MOSAIC_OK;
    }
    return MOSAIC_ERROR;
}

static err_t mosaic_wait_prompt ( mosaic_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    mosaic_process( ctx );
    while ( 0 == strstr( app_buf, MOSAIC_PROMPT_CMD ) )
    {
        mosaic_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            mosaic_clear_app_buf( );
            return MOSAIC_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    return MOSAIC_OK;
}

static void mosaic_parser_application ( uint8_t *rsp )
{
    uint8_t element_buf[ 100 ] = { 0 };
    if ( MOSAIC_OK == mosaic_parse_gga( rsp, MOSAIC_GGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            mosaic_parse_gga( rsp, MOSAIC_GGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            mosaic_parse_gga( rsp, MOSAIC_GGA_ALTITUDE, element_buf );
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
        mosaic_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
