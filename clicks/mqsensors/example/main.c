/*!
 * \file 
 * \brief MqSensors Click example
 * 
 * # Description
 * The demo application shows the reading of the adc 
 * values given by the sensors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Reads the adc value and prints in two forms (DEC and HEX)
 *
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mqsensors.h"

// ------------------------------------------------------------------ VARIABLES

static mqsensors_t mqsensors;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mqsensors_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mqsensors_cfg_setup( &cfg );
    MQSENSORS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mqsensors_init( &mqsensors, &cfg );
}

void application_task ( void )
{
    mqsensors_data_t tmp;
    
    //  Task implementation.
    
    tmp = mqsensors_generic_read ( &mqsensors );
    log_printf
    ( 
        &logger, 
        "** ADC value : [DEC]: %d, [HEX]: 0x%x \r\n", 
        tmp, 
        tmp
    );
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
