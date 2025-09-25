/*!
 * @file main.c
 * @brief Environment 6 Click example
 *
 * # Description
 * This example demonstrates the use of the Environment 6 Click board, which integrates 
 * a high-precision environmental sensor for measuring temperature, humidity, pressure, 
 * and gas resistance. The application initializes the device and periodically reads 
 * and logs all available environmental parameters via UART.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the Environment 6 Click. It sets up 
 * communication and applies the default configuration to the sensor.
 *
 * ## Application Task
 * Continuously reads temperature (degC), humidity (%RH), pressure (mBar), and gas 
 * resistance (Ohms) if enabled, then logs the measured values every second.
 *
 * @note
 * The BME690 sensor on this Click board provides raw gas resistance data only.
 * To calculate indoor air quality (IAQ), VOC index, CO2 equivalents, and similar
 * environmental parameters, Bosch Sensortec BSEC (Bosch Software Environmental Cluster) 
 * algorithm must be integrated separately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "environment6.h"

static environment6_t environment6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment6_cfg_t environment6_cfg;  /**< Click config object. */

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
    environment6_cfg_setup( &environment6_cfg );
    ENVIRONMENT6_MAP_MIKROBUS( environment6_cfg, MIKROBUS_1 );
    err_t init_flag = environment6_init( &environment6, &environment6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ENVIRONMENT6_ERROR == environment6_default_cfg ( &environment6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    environment6_data_t meas_res;
    if ( ENVIRONMENT6_OK == environment6_get_data ( &environment6, &meas_res ) )
    {
        log_printf( &logger, " Temperature : %.2f degC\r\n", meas_res.temperature );
        log_printf( &logger, " Humidity : %.2f %%\r\n", meas_res.humidity );
        log_printf( &logger, " Pressure : %.1f mBar\r\n", meas_res.pressure );
        if ( environment6.gas_conf.enable )
        {
            log_printf( &logger, " Gas Resistance : %.1f Ohms\r\n", meas_res.gas_resistance );
        }
        log_printf( &logger, "--------------------------------\r\n" );
        Delay_ms ( 1000 );
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
