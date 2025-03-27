/*!
 * @file main.c
 * @brief Diff Press 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Diff Press 5 Click board. It showcases how to initialize the device, 
 * calibrate the zero-pressure offset, and read the differential pressure data in Pascals (Pa) from the sensor.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Diff Press 5 Click driver. The application then performs zero-pressure 
 * offset calibration to ensure accurate pressure measurements. During the calibration, it is crucial to avoid 
 * applying pressure to the sensor.
 *
 * ## Application Task
 * Continuously reads the differential pressure from the sensor and logs the values in Pascals (Pa).
 *
 * @note
 * The measurable pressure range of the sensor is 0 to 10000 Pa.
 *
 * @author Stefan Filipovic
 *
 */


#include "board.h"
#include "log.h"
#include "diffpress5.h"

static diffpress5_t diffpress5;   /**< Diff Press 5 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress5_cfg_t diffpress5_cfg;  /**< Click config object. */

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
    diffpress5_cfg_setup( &diffpress5_cfg );
    DIFFPRESS5_MAP_MIKROBUS( diffpress5_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress5_init( &diffpress5, &diffpress5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Calibrating zero pressure offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no pressure is applied to the sensor during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( DIFFPRESS5_ERROR == diffpress5_calib_offset ( &diffpress5 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t pressure = 0;
    if ( DIFFPRESS5_OK == diffpress5_read_pressure ( &diffpress5, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %u Pa\r\n\n", pressure );
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
