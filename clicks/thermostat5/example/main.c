/*!
 * @file main.c
 * @brief Thermostat 5 Click Example.
 *
 * # Description
 * This library contains API for the Thermostat 5 Click driver 
 * for temperature measurement and relay control.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C or ADC module and log UART set the relay to an OFF state.
 *
 * ## Application Task
 * The demo application measures temperature in degrees Celsius.
 * If the temperature increases above 30 degrees Celsius, 
 * the relay will turn ON, otherwise it will turn OFF.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @note
 * For temperature measurement, we used Semitec 103AT-2 NTC Thermistors. 
 * - Beta parameter:  3435 K	
 * - Resistance:      10 kOhms	
 * - Tolerance:	      1 %
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermostat5.h"

// Demo temperature limit for relay control
#define THERMOSTAT5_TEMPERATURE_LIMIT    30.0

static thermostat5_t thermostat5;   /**< Thermostat 5 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat5_cfg_t thermostat5_cfg;  /**< Click config object. */

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
    thermostat5_cfg_setup( &thermostat5_cfg );
    THERMOSTAT5_MAP_MIKROBUS( thermostat5_cfg, MIKROBUS_1 );
    err_t init_flag = thermostat5_init( &thermostat5, &thermostat5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    thermostat5_set_relay( &thermostat5, THERMOSTAT5_RELAY_OFF );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    float temperature = 0;
    if ( THERMOSTAT5_OK == thermostat5_get_temperature( &thermostat5, &temperature ) )
    {
        log_printf( &logger, " Temperatur : %.2f [degC]\r\n", temperature );
        if ( THERMOSTAT5_TEMPERATURE_LIMIT < temperature )
        {
            thermostat5_set_relay( &thermostat5, THERMOSTAT5_RELAY_ON );
            log_printf( &logger, " Relay: ON\r\n" );
        }
        else
        {
            thermostat5_set_relay( &thermostat5, THERMOSTAT5_RELAY_OFF );
            log_printf( &logger, " Relay: OFF\r\n" );
        }
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
