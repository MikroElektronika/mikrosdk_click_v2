/*!
 * @file main.c
 * @brief RTK Rover Click Example.
 *
 * # Description
 * This example demonstrates the use of RTK Rover click by reading and displaying
 * the GPS coordinates.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the received data, parses the GNGGA info from it, and once it receives the position fix
 * it will start displaying the coordinates on the USB UART.
 *
 * ## Additional Function
 * - static void rtkrover_clear_app_buf ( void )
 * - static err_t rtkrover_process ( rtkrover_t *ctx )
 * - static void rtkrover_parser_application ( char *rsp )
 *
 * @note
 * The click board comes with the default baud rate of 460800, but the baud rate is set to 115200
 * in the example due to code portability and speed limitations of some MCUs. So in order to run
 * the example you will need to adjust the baud rate using Quectel QGNSS evaluation software.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtkrover.h"
#include "string.h"

#define PROCESS_BUFFER_SIZE 200

static rtkrover_t rtkrover;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief RTK Rover clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void rtkrover_clear_app_buf ( void );

/**
 * @brief RTK Rover data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtkrover_process ( rtkrover_t *ctx );

/**
 * @brief RTK Rover parser application function.
 * @details This function parses GNSS data and logs it on the USB UART. It clears app and ring buffers
 * after successfully parsing data.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[in] rsp Response buffer.
 * @return None.
 * @note None.
 */
static void rtkrover_parser_application ( rtkrover_t *ctx, char *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtkrover_cfg_t rtkrover_cfg;  /**< Click config object. */

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
    rtkrover_cfg_setup( &rtkrover_cfg );
    RTKROVER_MAP_MIKROBUS( rtkrover_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rtkrover_init( &rtkrover, &rtkrover_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( RTKROVER_OK == rtkrover_process( &rtkrover ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            rtkrover_parser_application( &rtkrover, app_buf );
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

static void rtkrover_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t rtkrover_process ( rtkrover_t *ctx ) 
{
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = rtkrover_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return RTKROVER_OK;
    }
    return RTKROVER_ERROR;
}

static void rtkrover_parser_application ( rtkrover_t *ctx, char *rsp )
{
    char element_buf[ 100 ] = { 0 };
    if ( RTKROVER_OK == rtkrover_parse_gngga( rsp, RTKROVER_GNGGA_LATITUDE, element_buf ) )
    {
        static uint8_t wait_for_fix_cnt = 0;
        if ( strlen( element_buf ) > 0 )
        {
            log_printf( &logger, "\r\n Latitude: %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
            rtkrover_parse_gngga( rsp, RTKROVER_GNGGA_LONGITUDE, element_buf );
            log_printf( &logger, " Longitude: %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
            memset( element_buf, 0, sizeof( element_buf ) );
            rtkrover_parse_gngga( rsp, RTKROVER_GNGGA_ALTITUDE, element_buf );
            log_printf( &logger, " Altitude: %s m \r\n", element_buf );
            wait_for_fix_cnt = 0;
            Delay_ms ( 1000 );
        }
        else
        {
            if ( wait_for_fix_cnt % 20 == 0 )
            {
                log_printf( &logger, " Waiting for the position fix...\r\n\n" );
                wait_for_fix_cnt = 0;
            }
            wait_for_fix_cnt++;
        }
        rtkrover_clear_ring_buffers( ctx );
        rtkrover_clear_app_buf( );
    }
}

// ------------------------------------------------------------------------ END
