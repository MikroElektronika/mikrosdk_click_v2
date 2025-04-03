/*!
 * @file main.c
 * @brief Environment 5 Click example
 *
 * # Description
 * This example demonstrates the use of the Environment 5 Click board, which provides 
 * temperature, humidity, and CO2 concentration measurements. The example initializes 
 * the device, reads sensor IDs, and continuously logs environmental data.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the Environment 5 Click board. It also retrieves 
 * and logs the product and serial numbers of the onboard sensors.
 *
 * ## Application Task
 * Continuously reads and logs temperature (degC) and humidity (%RH), and CO2 concentration 
 * (vol%) from sensors.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "environment5.h"

static environment5_t environment5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment5_cfg_t environment5_cfg;  /**< Click config object. */

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
    environment5_cfg_setup( &environment5_cfg );
    ENVIRONMENT5_MAP_MIKROBUS( environment5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == environment5_init( &environment5, &environment5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ENVIRONMENT5_ERROR == environment5_default_cfg ( &environment5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t stc_prod_num = 0;
    uint32_t stc_serial_msb = 0;
    uint32_t stc_serial_lsb = 0;
    if ( ENVIRONMENT5_OK == environment5_stc_read_id ( &environment5, &stc_prod_num, &stc_serial_msb, &stc_serial_lsb ) )
    {
        log_printf ( &logger, " STC31-C Product number: 0x%.8LX\r\n", stc_prod_num );
        log_printf ( &logger, " STC31-C Serial number: 0x%.8LX%.8LX\r\n", stc_serial_msb, stc_serial_lsb );
    }

    uint32_t sht_serial = 0;
    if ( ENVIRONMENT5_OK == environment5_sht_read_serial ( &environment5, &sht_serial ) )
    {
        log_printf ( &logger, " SHT40 Serial number: 0x%.8LX\r\n", sht_serial );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    float humidity = 0;
    float co2_concentration = 0;

    err_t error_flag = environment5_sht_read_meas_hp ( &environment5, &temperature, &humidity );
    if ( ENVIRONMENT5_OK == error_flag )
    {
        error_flag |= environment5_stc_set_temp ( &environment5, temperature );
        error_flag |= environment5_stc_set_hum ( &environment5, humidity );
        error_flag |= environment5_stc_read_meas ( &environment5, &co2_concentration, NULL );
    }

    if ( ENVIRONMENT5_OK == error_flag )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", humidity );
        log_printf ( &logger, " CO2 in air [0-40]: %.2f vol%%\r\n\n", co2_concentration );
    }

    Delay_ms ( 500 );
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
