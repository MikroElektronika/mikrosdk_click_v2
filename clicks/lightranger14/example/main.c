/*!
 * @file main.c
 * @brief LightRanger 14 Click example
 *
 * # Description
 * This example demonstrates the use of the LightRanger 14 Click board by
 * initializing the device, loading the firmware and configuration, and then 
 * reading and displaying distance measurement results. Each measurement frame 
 * contains distance data (in millimeters) and a confidence value. Data is displayed
 * only if confidence exceeds a threshold, otherwise it is marked as invalid. 
 * The example also logs the device information such as firmware version, chip version, 
 * and serial number.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the log interface, sets up the LightRanger 14 Click driver,
 * loads the default configuration for 8x8 measurement map, and prints device information.
 *
 * ## Application Task
 * Waits for a data ready interrupt, clears the interrupt flags, and then 
 * reads and logs the distance frame results with confidence filtering. 
 * The chip temperature and status flags are also displayed.
 *
 * @note
 * Measurement data updates approximately every 500 ms.
 * Refer to LIGHTRANGER14_DEFAULT_LOAD_CONFIG and LIGHTRANGER14_MAP_x macros
 * to set the measurement zone map to 8x8 (default), 16x16, 32x32, or 48x32.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lightranger14.h"
#include "math.h"

static lightranger14_t lightranger14;
static log_t logger;

/**
 * @brief LightRanger 14 rotate buf 90 ccw function.
 * @brief This functions rotates by 90 degrees counter-clockwise the buffer of 3-byte pixels.
 * @param[in,out] buf : Pixel buffer.
 * @param[in] height : Height (rows).
 * @param[in] width : Width (columns).
 * @return None.
 * @note None.
 */
static void lightranger14_rotate_buf_90_ccw ( uint8_t *buf, uint16_t height, uint16_t width );

/**
 * @brief LightRanger 14 log results function.
 * @details This function logs the measurement results to the USB UART.
 * @param[in] ctx : Click context object.
 * See #lightranger14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void lightranger14_log_results ( lightranger14_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger14_cfg_t lightranger14_cfg;  /**< Click config object. */

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
    lightranger14_cfg_setup( &lightranger14_cfg );
    LIGHTRANGER14_MAP_MIKROBUS( lightranger14_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger14_init( &lightranger14, &lightranger14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER14_OK != lightranger14_default_cfg ( &lightranger14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " Firmware Application Version: %u.%u.%u.%u\r\n", 
                 ( uint16_t ) lightranger14.info.app_ver[ 0 ],
                 ( uint16_t ) lightranger14.info.app_ver[ 1 ],
                 ( uint16_t ) lightranger14.info.app_ver[ 2 ],
                 ( uint16_t ) lightranger14.info.app_ver[ 3 ] );
    log_printf ( &logger, " Chip Version: %u.%u\r\n", 
                 ( uint16_t ) lightranger14.info.chip_ver[ 0 ],
                 ( uint16_t ) lightranger14.info.chip_ver[ 1 ] );
    log_printf ( &logger, " Serial Number: 0x%.8LX\r\n", lightranger14.info.serial_num );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t frame_data[ LIGHTRANGER14_FRAME_PAYLOAD_SIZE ] = { 0 };

    // Wait for data ready interrupt
    while ( lightranger14_get_int_pin ( &lightranger14 ) );
    
    if ( LIGHTRANGER14_OK == lightranger14_clear_interrupts ( &lightranger14 ) )
    {
        if ( LIGHTRANGER14_OK == lightranger14_read_results ( &lightranger14, frame_data, sizeof ( frame_data ) ) )
        {
            lightranger14_log_results ( &lightranger14 );
        }
        else
        {
            log_error( &logger, " Read results." );
        }
    }
    else
    {
        log_error( &logger, " Clear interrupts." );
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
 
static void lightranger14_rotate_buf_90_ccw ( uint8_t *buf, uint16_t height, uint16_t width )
{
    uint8_t tmp[ LIGHTRANGER14_PIXEL_SIZE ] = { 0 };
    uint32_t min_idx = 0;
    uint32_t idx = 0;
    uint32_t start = 0;
    uint32_t cur = 0;
    uint32_t nxt = 0;

    if ( ( NULL == buf ) || ( 0 == width ) || ( 0 == height ) )
    {
        return;
    }

    // Iterate over all pixel slots
    for ( start = 0; start < ( width * height ); ++start ) 
    {
        // Find the minimum index of this cycle
        min_idx = start;
        idx = ( width - 1 - ( start % width ) ) * height + ( start / width );
        while ( idx != start ) 
        {
            if ( idx < min_idx )
            {
                min_idx = idx;
            }
            idx = ( width - 1 - ( idx % width ) ) * height + ( idx / width );
        }
        if ( min_idx != start ) 
        {
            // Cycle was processed earlier, skip it
            continue;
        }

        // Save the first pixel in tmp, because its location will be overwritten by the next pixel in the cycle.
        memcpy( tmp, &buf[ start * LIGHTRANGER14_PIXEL_SIZE ], LIGHTRANGER14_PIXEL_SIZE );

        cur = start;
        for ( ; ; ) 
        {
            // Compute the next index
            nxt = ( width - 1 - ( cur % width ) ) * height + ( cur / width );
            if ( nxt == start )
            {
                // If the next index wraps back to 'start', stop (cycle complete)
                break;
            }
            // Copy the pixel at 'nxt' into the current slot 'cur'
            memcpy( &buf[ cur * LIGHTRANGER14_PIXEL_SIZE ], &buf[ nxt * LIGHTRANGER14_PIXEL_SIZE ], LIGHTRANGER14_PIXEL_SIZE );
            cur = nxt;
        }
        // Place the originally saved pixel (from 'start') into the final slot
        memcpy( &buf[ cur * LIGHTRANGER14_PIXEL_SIZE ], tmp, LIGHTRANGER14_PIXEL_SIZE );
    }
}

static void lightranger14_log_results ( lightranger14_t *ctx )
{
    uint32_t confidence = 0;
    uint16_t height = LIGHTRANGER14_MAP_HEIGHT;
    log_printf ( &logger, "SysTick: %lu\r\n", ctx->results.systick );
    log_printf ( &logger, "Frame Num: %lu\r\n", ctx->results.frame_num );

    if ( ( LIGHRANGER14_FRAME_STATUS_VALID & ctx->results.frame_status ) &&  
         ( LIGHRANGER14_FRAME_ID_ID_RESULT == ( ctx->results.frame_id & LIGHRANGER14_FRAME_ID_ID_MASK ) ) )
    {
        // Limit height to 16 pixels as 32x32 and 48x32 focal plane modes are divided to two frames of 32x16 and 48x16 pixels
        if ( height > 16 )
        {
            height = 16;
        }

        // Rotate buffer by 90 degrees counter-clockwise because the sensor is mounted rotated by 90 degrees clockwise
        lightranger14_rotate_buf_90_ccw ( ctx->results.payload, LIGHTRANGER14_MAP_WIDTH, height );
        for ( uint16_t cnt = 0; cnt < ctx->results.payload_len; cnt += LIGHTRANGER14_PIXEL_SIZE )
        {
            if ( 0 == ( cnt % ( height * LIGHTRANGER14_PIXEL_SIZE ) ) )
            {
                log_printf ( &logger, "\r\n" );
            }
            if ( ctx->results.payload[ cnt + 2 ] <= LIGHTRANGER14_CONFIDENCE_BREAKPOINT  ) // SNR
            {
                confidence = ctx->results.payload[ cnt + 2 ];
            }
            else
            {
                confidence = LIGHTRANGER14_CONFIDENCE_BREAKPOINT * 
                             pow ( LIGHTRANGER14_CONFIDENCE_EXP_GROWTH_RATE, 
                                   ctx->results.payload[ cnt + 2 ] - LIGHTRANGER14_CONFIDENCE_BREAKPOINT );
            }
        
            if ( confidence > LIGHTRANGER14_CONFIDENCE_THRESHOLD )
            {
                // Distance in millimeters
                log_printf ( &logger, "%.1f\t", 
                             ( ( ( uint16_t ) ctx->results.payload[ cnt + 1 ] << 8 ) | 
                               ( ( uint16_t ) ctx->results.payload[ cnt ] << 0 ) ) / 4.0 );
            }
            else
            {
                log_printf ( &logger, "INV\t" );
            }
        }
    }
    log_printf ( &logger, "\r\n\nTemperature: %.1f degC\r\n", 
                 ( ctx->results.temperature[ 0 ] + 
                   ctx->results.temperature[ 1 ] + 
                   ctx->results.temperature[ 2 ] ) / 3.0 );
    log_printf ( &logger, "Status: 0x%.2X\r\n", ( uint16_t ) ctx->results.frame_status );
    log_printf ( &logger, "-------------------------------\r\n" );
}

// ------------------------------------------------------------------------ END
