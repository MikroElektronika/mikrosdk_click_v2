/*!
 * @file main.c
 * @brief Thermostat 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Thermostat 2 click board by reading
 * and displaying the temperature in Celsius and turning the relay on/off 
 * depending on the temperature value.
 * DS1820, DS18S20 and DS18B20 chips can be used in this example. 
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and displays the temperature measured by the click board on the UART Terminal.
 * If the temperature goes beneath the THERMOSTAT2_TEMPERATURE_LIMIT, 
 * the relay will be turned off while otherwise it will be turned on. 
 * In both cases an appropriate message will be displayed on the terminal. 
 *
 * @author Aleksandra Cvjetićanin 
 *
 */

#include "board.h"
#include "log.h"
#include "thermostat2.h"

static thermostat2_t thermostat2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat2_cfg_t thermostat2_cfg;  /**< Click config object. */

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
    thermostat2_cfg_setup( &thermostat2_cfg );
    THERMOSTAT2_MAP_MIKROBUS( thermostat2_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thermostat2_init( &thermostat2, &thermostat2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMOSTAT2_ERROR == thermostat2_default_cfg ( &thermostat2 ) )
    {
        log_error( &logger, " Default config." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t relay_state = 0xFF;
    float temperature;
    
    if ( THERMOSTAT2_OK == thermostat2_read_temperature ( &thermostat2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n ", temperature );
    }
    
    if ( temperature < THERMOSTAT2_TEMPERATURE_LIMIT )
    {
        if ( relay_state != THERMOSTAT2_RELAY_ON )
        {
            log_info( &logger, " Relay is ON.\r\n " );
            thermostat2_relay_state ( &thermostat2, THERMOSTAT2_RELAY_ON );
            relay_state = THERMOSTAT2_RELAY_ON;
        }
    }
    else 
    {
        if ( relay_state != THERMOSTAT2_RELAY_OFF )
        {
            log_info( &logger, " Relay is OFF.\r\n" );
            thermostat2_relay_state ( &thermostat2, THERMOSTAT2_RELAY_OFF );
            relay_state = THERMOSTAT2_RELAY_OFF;
        }
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
