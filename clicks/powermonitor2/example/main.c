/*!
 * @file main.c
 * @brief Power Monitor 2 Click example
 *
 * # Description
 * This example demonstrates the use of Power Monitor 2 click by reading and displaying
 * the power consumption at 3V3 and 5V of the connected click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the voltage, current, and power measurements from U2 and U3 sensors averaged
 * from 20 samples and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "powermonitor2.h"

static powermonitor2_t powermonitor2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    powermonitor2_cfg_t powermonitor2_cfg;  /**< Click config object. */

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
    powermonitor2_cfg_setup( &powermonitor2_cfg );
    POWERMONITOR2_MAP_MIKROBUS( powermonitor2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == powermonitor2_init( &powermonitor2, &powermonitor2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( POWERMONITOR2_ERROR == powermonitor2_default_cfg ( &powermonitor2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    powermonitor2_data_t pm_3v3, pm_5v;

    powermonitor2_set_address ( &powermonitor2, powermonitor2.address_3v3 );
    if ( POWERMONITOR2_OK == powermonitor2_read_data_avg ( &powermonitor2, POWERMONITOR2_DEFAULT_NUM_CONV, &pm_3v3 ) )
    {
        log_printf( &logger, " --- 3V3 Power Monitor ---\r\n" );
        log_printf( &logger, " Voltage: %.3f V\r\n", pm_3v3.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", pm_3v3.current );
        log_printf( &logger, " Power: %.2f W\r\n", pm_3v3.power );
        log_printf( &logger, " -------------------------\r\n" );
    }
    
    powermonitor2_set_address ( &powermonitor2, powermonitor2.address_5v );
    if ( POWERMONITOR2_OK == powermonitor2_read_data_avg ( &powermonitor2, POWERMONITOR2_DEFAULT_NUM_CONV, &pm_5v ) )
    {
        log_printf( &logger, " ---- 5V Power Monitor ---\r\n" );
        log_printf( &logger, " Voltage: %.3f V\r\n", pm_5v.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", pm_5v.current );
        log_printf( &logger, " Power: %.2f W\r\n", pm_5v.power );
        log_printf( &logger, " -------------------------\r\n" );
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
