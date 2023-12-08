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
 * Initiaizes the driver, and checks the communication by reading the device and manufacture IDs.
 * After that, performs the device default configuration.
 * 
 * ## Application Task  
 * Displays the voltage, current, and power measured by the sensor on the USB UART every 2 seconds.
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
    log_info( &logger, "---- Application Init ----" );
    
    vcpmonitor_cfg_setup( &cfg );
    VCPMONITOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor_init( &vcpmonitor, &cfg );
    
    if ( VCPMONITOR_OK == vcpmonitor_get_id_value( &vcpmonitor, &manufacture_id, &did_id ) )
    {
        log_printf( &logger, ">> Manufacture ID: 0x%.4X\r\n", manufacture_id );
        log_printf( &logger, ">> Device ID: 0x%.4X\r\n", did_id );
    }
    else
    {
        log_error( &logger, " WRONG ID READ! " );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
    
    vcpmonitor_default_cfg(&vcpmonitor );
    Delay_ms( 500 );
}

void application_task ( void )
{
    float current_data;
    float voltage_data;
    float power_data;
    
    current_data = vcpmonitor_get_current( &vcpmonitor );
    log_printf( &logger, ">> Current : %.2f mA\r\n", current_data );
     
    voltage_data = vcpmonitor_get_voltage( &vcpmonitor );
    log_printf( &logger, ">> Voltage : %.2f mV\r\n", voltage_data );
    
    power_data = vcpmonitor_get_power( &vcpmonitor );
    log_printf( &logger, ">> Power : %.2f mW\r\n", power_data );
    
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 2000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
