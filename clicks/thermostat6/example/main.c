/*!
 * @file main.c
 * @brief Thermostat 6 Click Example.
 *
 * # Description
 * This example demonstrates the use of Thermostat 6 Click board by reading
 * the temperature level set using an on-board potentiometer and the temperature
 * from the NTC Thermistor 10k Cylindrical Probe (B57500M0103A005) which is connected
 * to the input, and also displaying the relay state. If the set temperature level
 * is lower than the temperature read from NTC, then the relay switches ON.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the temperature level set using an on-board potentiometer and the temperature
 * from the NTC Thermistor 10k Cylindrical Probe (B57500M0103A005) connected to the input,
 * and displays the relay state. If the set temperature level is lower than the temperature
 * read from NTC, then the relay switches ON.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermostat6.h"

static thermostat6_t thermostat6;   /**< Thermostat 6 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat6_cfg_t thermostat6_cfg;  /**< Click config object. */

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
    thermostat6_cfg_setup( &thermostat6_cfg );
    THERMOSTAT6_MAP_MIKROBUS( thermostat6_cfg, MIKROBUS_1 );
    err_t init_flag = thermostat6_init( &thermostat6, &thermostat6_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( THERMOSTAT6_OK == thermostat6_get_an_pin_v_avg ( &thermostat6, &voltage, THERMOSTAT6_ADC_NUM_SAMPLES_50 ) ) 
    {
        log_printf( &logger, " Set temperature : %.2f[degC]\r\n", thermostat6_get_temperature ( voltage ) );
    }
    if ( THERMOSTAT6_OK == thermostat6_get_adc_v_avg ( &thermostat6, &voltage, THERMOSTAT6_ADC_NUM_SAMPLES_50 ) ) 
    {
        log_printf( &logger, " Read temperature : %.2f[degC]\r\n", thermostat6_get_temperature ( voltage ) );
    }
    if ( thermostat6_get_relay_pin ( &thermostat6 ) )
    {
        log_printf( &logger, " Set temperature is lower than read temperature! Relay: ON\r\n\n" );
    }
    else
    {
        log_printf( &logger, " Set temperature is higher than read temperature! Relay: OFF\r\n\n" );
    }
    Delay_ms ( 1000 );
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
