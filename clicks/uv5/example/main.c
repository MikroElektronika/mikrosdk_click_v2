/*!
 * @file main.c
 * @brief UV 5 Click example
 *
 * # Description
 * This example demonstrates the use of UV 5 click board by measuring 
 * the light irradiance of the UVA, UVB and UVC.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, and performs the click default configuration.
 *
 * ## Application Task
 * Measuring light irradiance level by reading data from the UV 5 click board 
 * approximately every 4 seconds and displaying it using UART Serial terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "uv5.h"

#define OUTCONV         4.194304    /* Conversion time duration expressed as the number of clock counts within this time
                                       based on the default configuration. */
#define FSRE_UVA        1248        /* Full Scale Range of detectable input light irradiance Ee of the UVA channel
                                       based on the default configuration. */
#define FSRE_UVB        1632        /* Full Scale Range of detectable input light irradiance Ee of the UVB channel
                                       based on the default configuration. */
#define FSRE_UVC        784         /* Full Scale Range of detectable input light irradiance Ee of the UVC channel
                                       based on the default configuration. */

static uv5_t uv5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uv5_cfg_t uv5_cfg;  /**< Click config object. */

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
    uv5_cfg_setup( &uv5_cfg );
    UV5_MAP_MIKROBUS( uv5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == uv5_init( &uv5, &uv5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UV5_ERROR == uv5_default_cfg ( &uv5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temp_data; 
    uint16_t uv_raw_data; 
    float uv_data; 
    
    if ( uv5_get_rdy_pin( &uv5 ) == 1 )
    {
        uv5_temperature_read( &uv5, &temp_data );
        log_printf( &logger, " Temp: %.2f degC\r\n", temp_data );

        uv5_channel_uva_read( &uv5, &uv_raw_data );
        uv_data = ( float ) ( ( FSRE_UVA / OUTCONV ) * uv_raw_data );
        log_printf( &logger, " UVA: %.2f uW/cm2 \r\n", uv_data );
        
        uv5_channel_uvb_read( &uv5, &uv_raw_data );
        uv_data = ( float ) ( ( FSRE_UVB / OUTCONV ) * uv_raw_data );
        log_printf( &logger, " UVB: %.2f uW/cm2 \r\n", uv_data );
        
        uv5_channel_uvc_read( &uv5, &uv_raw_data );
        uv_data = ( float ) ( ( FSRE_UVC / OUTCONV ) * uv_raw_data );
        log_printf( &logger, " UVC: %.2f uW/cm2 \r\n", uv_data );
        log_printf( &logger, " =================== \r\n" );
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
