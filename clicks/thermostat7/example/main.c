/*!
 * @file main.c
 * @brief Thermostat 7 Click example
 *
 * # Description
 * This example demonstrates the use of Thermostat 7 Click board by reading
 * and displaying the temperature in Celsius and whether the
 * temperature limit has been passed.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the temperature and alarm status from the sensor every second
 * and logs both over UART.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "thermostat7.h"

#ifndef MIKROBUS_POSITION_THERMOSTAT7
    #define MIKROBUS_POSITION_THERMOSTAT7 MIKROBUS_1
#endif

static thermostat7_t thermostat7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat7_cfg_t thermostat7_cfg;  /**< Click config object. */

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
    thermostat7_cfg_setup( &thermostat7_cfg );
    THERMOSTAT7_MAP_MIKROBUS( thermostat7_cfg, MIKROBUS_POSITION_THERMOSTAT7 );
    if ( I2C_MASTER_ERROR == thermostat7_init( &thermostat7, &thermostat7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMOSTAT7_ERROR == thermostat7_default_cfg ( &thermostat7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " HIGH limit   : %.2f C\r\n", THERMOSTAT7_DEFAULT_TEMP_HIGH );
    log_printf( &logger, " LOW limit    : %.2f C\r\n", THERMOSTAT7_DEFAULT_TEMP_LOW );
    log_printf( &logger, " CRIT limit   : %.2f C\r\n", THERMOSTAT7_DEFAULT_TEMP_CRITICAL );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    uint8_t alarm_status = 0;

    if ( THERMOSTAT7_OK == thermostat7_read_temperature( &thermostat7, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    }

    if ( THERMOSTAT7_OK == thermostat7_read_alarm_status( &thermostat7, &alarm_status ) )
    {
        if ( THERMOSTAT7_ALARM_NONE == alarm_status )
        {
            log_printf( &logger, " Status: OK - relay is OFF.\r\n\n" );
        }
        else
        {
            if ( alarm_status & THERMOSTAT7_ALARM_TCRIT )
            {
                log_printf( &logger, " Status: CRITICAL - relay is ON.\r\n\n" );
            }
            else if ( alarm_status & THERMOSTAT7_ALARM_HIGH )
            {
                log_printf( &logger, " Status: HIGH alarm - relay is ON.\r\n\n" );
            }
            else if ( alarm_status & THERMOSTAT7_ALARM_LOW )
            {
                log_printf( &logger, " Status: LOW alarm - relay is ON.\r\n\n" );
            }
        }
    }

    Delay_ms( 1000 );
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
