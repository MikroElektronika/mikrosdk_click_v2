/*!
 * @file main.c
 * @brief IR Grid 5 Click example
 *
 * # Description
 * This example demonstrates the use of the IR Grid 5 Click board by 
 * reading and displaying the sensor temperature as well as the 
 * object temperature image from the 32x24 pixel array.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the log interface and the IR Grid 5 Click driver.
 * Reads and displays the device ID and firmware version.
 *
 * ## Application Task
 * Reads the sensor internal temperature and the object temperature image 
 * from the pixel array and displays them on the USB UART terminal every 500ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irgrid5.h"

static irgrid5_t irgrid5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid5_cfg_t irgrid5_cfg;  /**< Click config object. */

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
    irgrid5_cfg_setup( &irgrid5_cfg );
    IRGRID5_MAP_MIKROBUS( irgrid5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid5_init( &irgrid5, &irgrid5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGRID5_ERROR == irgrid5_default_cfg ( &irgrid5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint16_t device_id[ 4 ] = { 0 };
    if ( IRGRID5_OK == irgrid5_get_device_id ( &irgrid5, device_id ) )
    {
        log_printf ( &logger, " Device ID: %.4X%.4X%.4X%.4X\r\n", 
                     device_id[ 0 ], device_id[ 1 ], device_id[ 2 ], device_id[ 3 ] );
    }

    uint8_t fw_ver[ 3 ] = { 0 };
    if ( IRGRID5_OK == irgrid5_get_fw_version ( &irgrid5, fw_ver ) )
    {
        log_printf ( &logger, " FW version: %u.%u.%u\r\n", 
                     ( uint16_t ) fw_ver[ 0 ], ( uint16_t ) fw_ver[ 1 ], ( uint16_t ) fw_ver[ 2 ] );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float sensor_temp = 0;
    float obj_image[ IRGRID5_NUM_PIXELS ] = { 0 };
    if ( IRGRID5_OK == irgrid5_get_measurement ( &irgrid5, obj_image, &sensor_temp ) )
    {
        log_printf( &logger, " Sensor temperature: %.1f degC\r\n", sensor_temp );
        log_printf( &logger, "--- Object temperature image ---\r\n" );
        for ( uint16_t pixel_cnt = 0; pixel_cnt < IRGRID5_NUM_PIXELS; pixel_cnt++ ) 
        {
            log_printf( &logger, "%.1f ", obj_image[ pixel_cnt ] );
            if ( 31 == ( pixel_cnt % 32 ) ) 
            {
                log_printf( &logger, "\r\n" );
            }
        }
        log_printf( &logger, "--------------------------------\r\n" );
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

// ------------------------------------------------------------------------ END
