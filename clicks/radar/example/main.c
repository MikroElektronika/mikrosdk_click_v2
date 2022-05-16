/*!
 * @file main.c
 * @brief Radar Click Example.
 *
 * # Description
 * This example demonstrates the use of Radar click board by reading and parsing 
 * events as well as the module internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the detection event and then displays on the USB UART the distance of detected 
 * object, accuracy, elapsed time since last reset, and the module internal temperature.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "radar.h"

static radar_t radar;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    radar_cfg_t radar_cfg;  /**< Click config object. */

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
    radar_cfg_setup( &radar_cfg );
    RADAR_MAP_MIKROBUS( radar_cfg, MIKROBUS_1 );
    if ( UART_ERROR == radar_init( &radar, &radar_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RADAR_ERROR == radar_default_cfg ( &radar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t evt_id, evt_payload_size, evt_payload[ 16 ];
    if ( RADAR_OK == radar_get_event ( &radar, &evt_id, evt_payload, &evt_payload_size ) )
    {
        if ( RADAR_CMD_ID_DETECT_IN_EVT == evt_id )
        {
            log_printf( &logger, " EVENT: IN\r\n" );
            radar_float_bytes_t distance;
            memcpy ( distance.b_data, &evt_payload[ 8 ], 4 );
            radar_float_ieee_to_mchip ( &distance.f_data );
            log_printf( &logger, " Target distance: %.3f m\r\n", distance.f_data );
            memcpy ( distance.b_data, &evt_payload[ 12 ], 4 );
            radar_float_ieee_to_mchip ( &distance.f_data );
            log_printf( &logger, " Accuracy (+/-): %.3f m\r\n", distance.f_data );
        }
        else
        {
            log_printf( &logger, " EVENT: OUT\r\n" );
        }
        uint32_t evt_time = ( ( uint32_t ) evt_payload[ 3 ] << 24 ) | ( ( uint32_t ) evt_payload[ 2 ] << 16 ) | 
                            ( ( uint16_t ) evt_payload[ 1 ] << 8 ) | evt_payload[ 0 ];
        log_printf( &logger, " Elapsed time: %.2f s\r\n", evt_time / 1000.0 );
        float temperature;
        if ( RADAR_OK == radar_get_temperature ( &radar, &temperature ) )
        {
            log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
        }
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
