/*!
 * @file main.c
 * @brief VCPMonitor4 Click example
 *
 * # Description
 * This example application showcases ability of Click board
 * to be configured for different readings and read temperature, 
 * voltage, current and power.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (SPI, UART) and 
 * additional alert pin. Reads Manufacturer and Device ID,
 * Configurates device for reading all device measurements.
 *
 * ## Application Task
 * In span of 500ms reads and calculates data for IC temperature,
 * Bus voltage in V, Shunt voltage in mV, and current and power for device.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vcpmonitor4.h"

static vcpmonitor4_t vcpmonitor4;
static log_t logger;

float current_lsb;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor4_cfg_t vcpmonitor4_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    vcpmonitor4_cfg_setup( &vcpmonitor4_cfg );
    VCPMONITOR4_MAP_MIKROBUS( vcpmonitor4_cfg, MIKROBUS_1 );
    err_t init_flag  = vcpmonitor4_init( &vcpmonitor4, &vcpmonitor4_cfg );
    VCPMONITOR4_SET_DATA_SAMPLE_EDGE
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint32_t temp_data = 0;
    vcpmonitor4_generic_read( &vcpmonitor4, VCPMONITOR4_REG_MANUFACTURER_ID, &temp_data );
    log_printf( &logger, " > Manufacturer ID: \t0x%.4X\r\n", temp_data );
    
    vcpmonitor4_generic_read( &vcpmonitor4, VCPMONITOR4_REG_DEVICE_ID, &temp_data );
    log_printf( &logger, " > Device ID: \t\t0x%.4X\r\n", temp_data );
    
    vcpmonitor4_default_cfg ( &vcpmonitor4 );
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float read_data;
    vcpmonitor4_get_temperature( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Temperature:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_vbus( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Vbus[V]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_vshunt( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Vshunt[mV]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_current( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Current[A]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_power( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Power[W]:\t%.2f \r\n", read_data );
    log_printf( &logger, "*************************\r\n" );
    
    Delay_ms( 500 );
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
