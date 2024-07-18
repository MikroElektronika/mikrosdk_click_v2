/*!
 * @file main.c
 * @brief VCP Monitor 6 Click example
 *
 * # Description
 * This library contains API for the VCP Monitor 6 Click driver 
 * for measurements of the voltage, current, power, energy, charge, and die temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the results of the input bus voltage, 
 * current, power, energy, charge accumulation measurements, and die temperature.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vcpmonitor6.h"

static vcpmonitor6_t vcpmonitor6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor6_cfg_t vcpmonitor6_cfg;  /**< Click config object. */

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
    vcpmonitor6_cfg_setup( &vcpmonitor6_cfg );
    VCPMONITOR6_MAP_MIKROBUS( vcpmonitor6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == vcpmonitor6_init( &vcpmonitor6, &vcpmonitor6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VCPMONITOR6_ERROR == vcpmonitor6_default_cfg ( &vcpmonitor6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float app_buf = 0;
    if ( VCPMONITOR6_OK == vcpmonitor6_get_bus_voltage( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Voltage: %.2f [V]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_current( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Current: %.2f [mA]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_power( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Power: %.2f [W]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_energy( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Energy: %.2f [kJ]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_charge( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Charge: %.2f [C]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR6_OK == vcpmonitor6_get_temperature( &vcpmonitor6, &app_buf ) )
    {
        log_printf( &logger, " Temperature: %.2f [degC]\r\n", app_buf );
        Delay_ms ( 50 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 1000 );
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
