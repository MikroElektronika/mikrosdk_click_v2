/*!
 * @file main.c
 * @brief RTK Base Click Example.
 *
 * # Description
 * This example demonstrates the use of RTK Base Click by reading and displaying the RTCM3 messages.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads and parses the RTCM3 messages received from the module, and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void rtkbase_clear_app_buf ( void )
 * - static err_t rtkbase_process_rtcm3 ( rtkbase_t *ctx )
 *
 * @note
 * The Click board comes with the default baud rate of 460800, but the baud rate is set to 115200
 * in the example due to code portability and speed limitations of some MCUs. So in order to run
 * the example you will need to adjust the baud rate using Quectel QGNSS evaluation software.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtkbase.h"

#define PROCESS_BUFFER_SIZE 300

static rtkbase_t rtkbase;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static uint16_t app_buf_len = 0;

/**
 * @brief RTK Base clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return None.
 * @note None.
 */
static void rtkbase_clear_app_buf ( void );

/**
 * @brief RTK Base process rtcm3 function.
 * @details This function reads and processes the RTCM3 messages and displays them on the USB UART.
 * @param[in] ctx : Click context object.
 * See #rtkbase_t object definition for detailed explanation.
 * @return @li @c  0 - Successfully read RTCM3 message.
 *         @li @c -1 - Read error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rtkbase_process_rtcm3 ( rtkbase_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtkbase_cfg_t rtkbase_cfg;  /**< Click config object. */

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
    rtkbase_cfg_setup( &rtkbase_cfg );
    RTKBASE_MAP_MIKROBUS( rtkbase_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rtkbase_init( &rtkbase, &rtkbase_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    rtkbase_process_rtcm3 ( &rtkbase );
    rtkbase_clear_app_buf( );
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

static void rtkbase_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t rtkbase_process_rtcm3 ( rtkbase_t *ctx ) 
{
    #define RTKBASE_HEADER_0    0xD3
    #define RTKBASE_HEADER_1    0x00
    for ( ; ; ) // loop until a header byte 0 is read
    {
        while ( rtkbase_rx_bytes_available ( ctx ) < 1 );
        
        if ( 1 == rtkbase_generic_read( ctx, app_buf, 1 ) )
        {
            if ( RTKBASE_HEADER_0 == app_buf[ 0 ] )
            {
                break;
            }
        }
    }
    // wait until a header byte 1 and packet size bytes are available for read
    while ( rtkbase_rx_bytes_available ( ctx ) < 2 );
    if ( 2 != rtkbase_generic_read( ctx, &app_buf[ 1 ], 2 ) )
    {
        return RTKBASE_ERROR;
    }
    if ( RTKBASE_HEADER_1 != ( app_buf[ 1 ] & 0xFC ) )
    {
        return RTKBASE_ERROR;
    }
    app_buf_len = ( ( uint16_t ) ( app_buf[ 1 ] & 0x03 ) << 8 ) + app_buf[ 2 ] + 6; // Header + size + payload bytes + CRC bytes
    
    // wait until payload and CRC bytes are available for read
    while ( rtkbase_rx_bytes_available ( ctx ) < ( app_buf_len - 3 ) );
    if ( ( app_buf_len - 3 ) != rtkbase_generic_read( ctx, &app_buf[ 3 ], ( app_buf_len - 3 ) ) )
    {
        return RTKBASE_ERROR;
    }
    
    // The CRC across the whole packet should sum to zero (remainder)
    if ( 0 == rtkbase_calculate_crc24( app_buf, app_buf_len ) )
    {
        uint16_t rtcm3_msg_type = ( ( uint16_t ) app_buf[ 3 ] << 4 ) | ( ( app_buf[ 4 ] >> 4 ) & 0x0F ); // 12-bit message type
        log_printf ( &logger, "\r\n\n RTCM3 -> Type: %u; Size: %u;\r\n", rtcm3_msg_type, app_buf_len );
        for ( int32_t cnt = 0; cnt < app_buf_len; cnt++ ) 
        {
            log_printf( &logger, " %.2X", ( uint16_t ) app_buf[ cnt ] );
            if ( ( cnt % 16 ) == 15 )
            {
                log_printf( &logger, "\r\n" );
            }
        }
        return RTKBASE_OK;
    }
    return RTKBASE_ERROR;
}

// ------------------------------------------------------------------------ END
