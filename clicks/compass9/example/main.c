/*!
 * @file main.c
 * @brief Compass 9 Click example
 *
 * # Description
 * This example demonstrates the use of the Compass 9 Click board.
 * It periodically measures and logs the magnetic flux density on
 * the X, Y, and Z axes, as well as the ambient temperature values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, checks communication, and applies the default configuration.
 *
 * ## Application Task
 * Reads and logs the magnetic flux density for all 3 axes in Gauss and 
 * the temperature in degrees Celsius every 200 ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "compass9.h"

static compass9_t compass9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass9_cfg_t compass9_cfg;  /**< Click config object. */

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
    compass9_cfg_setup( &compass9_cfg );
    COMPASS9_MAP_MIKROBUS( compass9_cfg, MIKROBUS_1 );
    err_t init_flag = compass9_init( &compass9, &compass9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS9_ERROR == compass9_default_cfg ( &compass9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    compass9_magnetic_flux_t magnetic_flux;
    float temperature = 0;
    if ( COMPASS9_OK == compass9_start_measurement ( &compass9, COMPASS9_MEAS_SINGLE_M ) )
    {
        if ( COMPASS9_OK == compass9_get_magnetic_flux ( &compass9, &magnetic_flux ) )
        {
            log_printf ( &logger, " X: %.2f G\r\n", magnetic_flux.x_axis );
            log_printf ( &logger, " Y: %.2f G\r\n", magnetic_flux.y_axis );
            log_printf ( &logger, " Z: %.2f G\r\n", magnetic_flux.z_axis );
        }
    }
    if ( COMPASS9_OK == compass9_start_measurement ( &compass9, COMPASS9_MEAS_SINGLE_T ) )
    {
        if ( COMPASS9_OK == compass9_get_temperature ( &compass9, &temperature ) )
        {
            log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
        }
    }
    Delay_ms ( 200 );
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
