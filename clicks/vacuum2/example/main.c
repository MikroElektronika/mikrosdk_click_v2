/*!
 * @file main.c
 * @brief Vacuum 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Vacuum 2 Click board. It showcases how to initialize the device, 
 * perform zero-pressure offset calibration, and measure pressure in Pascals (Pa).
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Vacuum 2 Click driver. The application then performs zero-pressure 
 * offset calibration to ensure accurate pressure measurements. During the calibration, it is crucial to avoid 
 * applying pressure to the sensor.
 *
 * ## Application Task
 * Continuously reads the pressure from the sensor and logs the values in Pascals (Pa).
 *
 * @note
 * The measurable pressure range of the sensor is from -2000 Pa to 2000 Pa.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vacuum2.h"

static vacuum2_t vacuum2;   /**< Vacuum 2 Click driver object. */
static log_t logger;        /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vacuum2_cfg_t vacuum2_cfg;  /**< Click config object. */

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
    vacuum2_cfg_setup( &vacuum2_cfg );
    VACUUM2_MAP_MIKROBUS( vacuum2_cfg, MIKROBUS_1 );
    err_t init_flag = vacuum2_init( &vacuum2, &vacuum2_cfg );
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
    if ( VACUUM2_ERROR == vacuum2_calib_offset ( &vacuum2 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    int16_t pressure = 0;
    if ( VACUUM2_OK == vacuum2_read_pressure ( &vacuum2, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %d Pa\r\n\n", pressure );
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
