/*!
 * \file 
 * \brief ThermoJ Click example
 * 
 * # Description
 * This app measured temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Thermo J Click board.
 * Measured temperature data from the MCP9600 sensor on Thermo J click board.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 3 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermoj.h"

// ------------------------------------------------------------------ VARIABLES

static thermoj_t thermoj;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermoj_cfg_t cfg;
    uint8_t check_data_ready;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thermoj_cfg_setup( &cfg );
    THERMOJ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermoj_init( &thermoj, &cfg );

    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Thermo J  Click      \r\n" );
    log_printf( &logger, "---------------------------\r\n" );

    Delay_ms( 100 );

    log_printf( &logger, "    Driver  Initialized    \r\n" );
    log_printf( &logger, "---------------------------\r\n" );

    check_data_ready =  thermoj_check_data_ready( &thermoj );

    if ( check_data_ready )
    {
        log_printf( &logger, "    Conversion Complete    \r\n" );
    }
    else
    {
        log_printf( &logger, "  Writing - has no effect  \r\n" );
    }

    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, " Set thermocouple type:  J \r\n" );

    thermoj_set_thermocouple_type( &thermoj, THERMOJ_THERMOCOUPLE_TYPE_J );
    Delay_ms( 1000 );

    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    float temperature;
    char deg_cel[ 4 ];

    deg_cel[ 0 ] = 32;
    deg_cel[ 1 ] = 176;
    deg_cel[ 2 ] = 67;
    deg_cel[ 3 ] = 0;

    temperature = thermoj_get_temperature( &thermoj );

    log_printf( &logger, " Temperature : %f %c \r\n", temperature, deg_cel );
    log_printf( &logger, "---------------------------\r\n" );

    Delay_ms( 3000 );
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
