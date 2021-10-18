/*!
 * \file 
 * \brief Thermostat Click example
 * 
 * # Description
 * This application regulates value of temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, soft reset sesnor, set default configuration and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Thermostat Click board.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermostat.h"


static thermostat_t thermostat;
static log_t logger;


void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat_cfg_t cfg;

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

    //  Click initialization.

    thermostat_cfg_setup( &cfg );
    THERMOSTAT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermostat_init( &thermostat, &cfg );

    thermostat_soft_reset( &thermostat );
    Delay_ms( 100 );
    log_printf( &logger, "     Configuration    \r\n");

    thermostat_set_configuration( &thermostat, THERMOSTAT_DEFAULT_CONFIG );
    Delay_ms( 100 );
    log_printf( &logger, "----------------------\r\n" );
}

void application_task ( void )
{

    float temperature;
    float limit_max = 25.0;
    float limit_min = 15.0;

    temperature = thermostat_get_temperature( &thermostat );

    log_printf( &logger, " Temperature : %.2f \r\n", temperature );

    if ( ( temperature < limit_max ) && ( temperature > limit_min ) )
    { 
        thermostat_switch_on(  &thermostat  );
    }
    else
    {   
        thermostat_switch_off(  &thermostat  );
        log_printf( &logger, "----------------------\r\n" );
    }
    Delay_ms( 2000 );
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
