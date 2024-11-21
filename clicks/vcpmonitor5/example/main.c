/*!
 * @file main.c
 * @brief VCP Monitor 5 Click example
 *
 * # Description
 * This library contains API for the VCP Monitor 5 Click driver 
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
#include "vcpmonitor5.h"

static vcpmonitor5_t vcpmonitor5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor5_cfg_t vcpmonitor5_cfg;  /**< Click config object. */

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
    vcpmonitor5_cfg_setup( &vcpmonitor5_cfg );
    VCPMONITOR5_MAP_MIKROBUS( vcpmonitor5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == vcpmonitor5_init( &vcpmonitor5, &vcpmonitor5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VCPMONITOR5_ERROR == vcpmonitor5_default_cfg ( &vcpmonitor5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float app_buf = 0;
    if ( VCPMONITOR5_OK == vcpmonitor5_get_bus_voltage( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Voltage: %.2f [V]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_current( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Current: %.2f [mA]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_power( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Power: %.2f [W]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_energy( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Energy: %.2f [kJ]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_charge( &vcpmonitor5, &app_buf ) )
    {
        log_printf( &logger, " Charge: %.2f [C]\r\n", app_buf );
        Delay_ms ( 50 );
    }

    if ( VCPMONITOR5_OK == vcpmonitor5_get_temperature( &vcpmonitor5, &app_buf ) )
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
