/*!
 * @file main.c
 * @brief LightRanger9 Click example
 *
 * # Description
 * This example demonstrates the use of LightRanger 9 click board by reading and displaying
 * all four sub-captures data measurements on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads all four sub-captures data approximately every 500ms and logs them to the USB UART
 * in a form of two object 8x8 maps. Other data such as DIE temperature, ambient light, system tick, 
 * etc., are also being displayed.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lightranger9.h"

static lightranger9_t lightranger9;
static log_t logger;

static lightranger9_meas_result_t object_1[ LIGHTRANGER9_OBJECT_MAP_SIZE ];
static lightranger9_meas_result_t object_2[ LIGHTRANGER9_OBJECT_MAP_SIZE ];

/**
 * @brief LightRanger 9 log results function.
 * @details This function parses measurement results to 2 object maps, 
 * and logs the results on the USB UART.
 * @param[in] capture : Capture data object.
 * See #lightranger9_capture_t object definition for detailed explanation.
 * @return None.
 * @note It must be called 4 times for all 4 different input sub-captures.
 */
static void lightranger9_log_results ( lightranger9_capture_t capture );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger9_cfg_t lightranger9_cfg;  /**< Click config object. */

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
    lightranger9_cfg_setup( &lightranger9_cfg );
    LIGHTRANGER9_MAP_MIKROBUS( lightranger9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger9_init( &lightranger9, &lightranger9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER9_ERROR == lightranger9_default_cfg ( &lightranger9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    while ( lightranger9_get_int_pin ( &lightranger9 ) );

    lightranger9_capture_t capture;
    if ( ( LIGHTRANGER9_OK == lightranger9_clear_interrupts ( &lightranger9 ) ) && 
         ( LIGHTRANGER9_OK == lightranger9_get_capture ( &lightranger9, &capture ) ) )
    {
        lightranger9_log_results ( capture );
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

static void lightranger9_log_results ( lightranger9_capture_t capture )
{
    static uint8_t sub_capture_cnt = 0;
    uint8_t result_cnt = 0, row = 0, col = 0;
    for ( result_cnt = 0; result_cnt < LIGHTRANGER9_MAX_MEAS_RESULTS; result_cnt++ ) 
    {
        if ( 8 == ( result_cnt % 9 ) )
        {
            continue;
        }
        row = ( ( ( result_cnt % 9 ) / 2 ) * 2 ) + ( capture.sub_capture / 2 );
        col = ( ( ( result_cnt % 9 ) % 2 ) * 4 ) + ( ( result_cnt % 18 ) / 9 ) + ( ( capture.sub_capture % 2 ) * 2 );
        if ( result_cnt >= ( LIGHTRANGER9_MAX_MEAS_RESULTS / 2 ) )
        {
            object_2 [ ( row * 8 ) + col ].confidence = capture.result[ result_cnt ].confidence;
            object_2 [ ( row * 8 ) + col ].distance_mm = capture.result[ result_cnt ].distance_mm;
        }
        else
        {
            object_1 [ ( row * 8 ) + col ].confidence = capture.result[ result_cnt ].confidence;
            object_1 [ ( row * 8 ) + col ].distance_mm = capture.result[ result_cnt ].distance_mm;
        }
    }
    if ( sub_capture_cnt < LIGHTRANGER9_SUBCAPTURE_3 )
    {
        sub_capture_cnt++;
        return;
    }
    log_printf ( &logger, "\r\n Result number: %u\r\n", ( uint16_t ) capture.result_number );
    log_printf ( &logger, " DIE temperature: %d C\r\n", ( int16_t ) capture.temperature );
    log_printf ( &logger, " Valid results: %u\r\n", ( uint16_t ) capture.valid_results );
    log_printf ( &logger, " Ambient light: %lu\r\n", capture.ambient_light );
    log_printf ( &logger, " Photon count: %lu\r\n", capture.photon_count );
    log_printf ( &logger, " Reference count: %lu\r\n", capture.reference_count );
    log_printf ( &logger, " Sys tick: %.2f s\r\n", capture.sys_tick_sec );
    log_printf ( &logger, "\r\n Object 1 MAP:\r\n" );
    for ( result_cnt = 0; result_cnt < LIGHTRANGER9_OBJECT_MAP_SIZE; result_cnt++ )
    {
        log_printf ( &logger, " %u\t", object_1[ result_cnt ].distance_mm );
        if ( result_cnt % 8 == 7 )
        {
            log_printf ( &logger, "\r\n" );
        }
    }
    log_printf ( &logger, "\r\n Object 2 MAP:\r\n" );
    for ( result_cnt = 0; result_cnt < LIGHTRANGER9_OBJECT_MAP_SIZE; result_cnt++ )
    {
        log_printf ( &logger, " %u\t", object_2[ result_cnt ].distance_mm );
        if ( result_cnt % 8 == 7 )
        {
            log_printf ( &logger, "\r\n" );
        }
    }
    log_printf ( &logger, "\r\n" );
    
    sub_capture_cnt = 0;
    memset ( object_1, 0, sizeof ( object_1 ) );
    memset ( object_2, 0, sizeof ( object_2 ) );
}

// ------------------------------------------------------------------------ END
