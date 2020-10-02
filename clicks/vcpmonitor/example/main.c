/*!
 * \file 
 * \brief VCPmonitor Click example
 * 
 * # Description
 * The VCP Monitor Click is add-on board power monitor system. This Click board is 
 * based on precision digital current and power monitor with low-drift, integrated 
 * precision shunt resistor. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, check device ID 
 * and manufacture ID, start default configuration.
 * 
 * ## Application Task  
 * Reads Current, Voltage and Power data. 
 * This data logs to USB UART every 1500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vcpmonitor.h"

// ------------------------------------------------------------------ VARIABLES

static vcpmonitor_t vcpmonitor;
static log_t logger;
static uint16_t manufacture_id;
static uint16_t did_id;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    vcpmonitor_cfg_setup( &cfg );
    VCPMONITOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor_init( &vcpmonitor, &cfg );
    
    vcpmonitor_get_id_value( &vcpmonitor, &manufacture_id, &did_id );
    log_printf( &logger, ">> Manufacture ID: 0x%d\r\n", manufacture_id );
    log_printf( &logger, ">> Device ID: 0x%d\r\n", did_id );
    
    vcpmonitor_default_cfg(&vcpmonitor );
    log_printf( &logger, ">> Default config...\r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    float current_data;
    float voltage_data;
    float power_data;
    
    current_data = vcpmonitor_get_current( &vcpmonitor );
   
    log_printf( &logger, ">> Current data: %.2f\r\n", current_data );
    log_printf( &logger, " mA\r\n" );
     
    voltage_data = vcpmonitor_get_voltage( &vcpmonitor );
    log_printf( &logger, ">> Voltage data:%.2f\r\n ", voltage_data );
    log_printf( &logger, " mV\r\n" );
    
    power_data = vcpmonitor_get_power( &vcpmonitor );
    log_printf( &logger, ">> Power data: %.2f\r\n", power_data );
    log_printf( &logger, " mW\r\n" );
    
    log_printf( &logger, " ------------------------------- \r\n" );
    Delay_ms( 1500 );
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
