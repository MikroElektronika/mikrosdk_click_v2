/*!
 * \file 
 * \brief VcpMonitor3 Click example
 * 
 * # Description
 * VCP Monitor 3 Click show it's full usage by reading current, voltage, power, die temperature 
 * and voltage at DVCC using SPI or I2C communication protocol.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI or I2C driver and sets up the device.
 * 
 * ## Application Task  
 * This example shows capabilities of VCP Monitor 3 Click board
 * by reading current, voltage, power, die temperature and 
 * voltage at DVCC and displaying the results via USART terminal.
 * 
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vcpmonitor3.h"

// ------------------------------------------------------------------ VARIABLES

static vcpmonitor3_t vcpmonitor3;
static log_t logger;

static float cur_data;
static float volt_data;
static float pow_data;
static float die_temp;
static float volt_vcc;

static char deg_cel[ 3 ] = { 176, 67, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vcpmonitor3_cfg_setup( &cfg );
    VCPMONITOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor3_init( &vcpmonitor3, &cfg );

    vcpmonitor3_default_cfg( &vcpmonitor3 );
}

void application_task ( void )
{
    cur_data = vcpmonitor3_read_i( &vcpmonitor3 );
    log_printf( &logger, "Current : %.2f A\r\n", cur_data );

    pow_data = vcpmonitor3_read_p( &vcpmonitor3 );
    log_printf( &logger, "Power : %.2f W\r\n", pow_data );

    volt_data = vcpmonitor3_read_v( &vcpmonitor3 );
    log_printf( &logger, "Voltage : %.2f V\r\n", volt_data );

    die_temp = vcpmonitor3_read_temp( &vcpmonitor3 );
    log_printf( &logger, "Die Temperature : %.2f %s\r\n", die_temp, deg_cel );

    volt_vcc = vcpmonitor3_read_vcc( &vcpmonitor3 );
    log_printf( &logger, "Voltage at DVCC : %.2f V\r\n", volt_vcc );

    log_printf( &logger, " ------------------------------- \r\n" );
    Delay_ms( 1000 );
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
