/*!
 * @file main.c
 * @brief Compass7 Click example
 *
 * # Description
 * This example demonstrates the use of Compass 7 click board by reading and displaying
 * the magnetic field strength of 3-axis as well as the temperature measurements in Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Starts the single magnetic measurement and reads the magnetic field strength of 3-axis in Gauss,
 * then starts the temperature measurement and reads the temperature in Celsius. 
 * The results are being displayed on the USB UART every 100ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "compass7.h"

static compass7_t compass7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass7_cfg_t compass7_cfg;  /**< Click config object. */

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
    compass7_cfg_setup( &compass7_cfg );
    COMPASS7_MAP_MIKROBUS( compass7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == compass7_init( &compass7, &compass7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS7_ERROR == compass7_default_cfg ( &compass7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    compass7_magnetic_flux_t magnetic_flux;
    float temperature;
    if ( ( COMPASS7_OK == compass7_set_measurement_mode ( &compass7, COMPASS7_MEAS_SINGLE_M ) ) &&
         ( COMPASS7_OK == compass7_get_magnetic_flux ( &compass7, &magnetic_flux ) ) )
    {
        log_printf ( &logger, " X: %.2f G\r\n", magnetic_flux.x_axis );
        log_printf ( &logger, " Y: %.2f G\r\n", magnetic_flux.y_axis );
        log_printf ( &logger, " Z: %.2f G\r\n", magnetic_flux.z_axis );
    }
    if ( ( COMPASS7_OK == compass7_set_measurement_mode ( &compass7, COMPASS7_MEAS_SINGLE_T ) ) &&
         ( COMPASS7_OK == compass7_get_temperature ( &compass7, &temperature ) ) )
    {
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    Delay_ms ( 100 );
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
