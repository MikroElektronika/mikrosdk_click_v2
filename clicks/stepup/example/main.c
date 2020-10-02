/*!
 * \file 
 * \brief StepUp Click example
 * 
 * # Description
 * This application enables usage of DC-DC step-up (boost) regulator.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI driver, sets config word, initializes the device, sets and log output value
 * 
 * ## Application Task  
 * Simulates user input via UART terminal, if 'user' enters + or - output value is increased or decreased respectively
 * 
 * *note:* 
 * Additional Functions :
 * 
 * stepup_logPercent() - calls 'stepup_getPercent()' function to get output
 * value in expressed as percentage and logs that value.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stepup.h"

// ------------------------------------------------------------------ VARIABLES

static stepup_t stepup;
static log_t logger;
uint16_t out_value;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void stepup_log_percent( uint16_t out_val )
{
    float out_percent;

    out_percent = stepup_get_percent( out_val );
    log_printf( &logger, "> output set to : %.2f %%\r\n", out_percent );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stepup_cfg_t cfg;
    

    out_value = 4095;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    stepup_cfg_setup( &cfg );
    STEPUP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stepup_init( &stepup, &cfg );

    Delay_ms( 100 );

    stepup_default_cfg( &stepup, out_value );
    stepup_log_percent( out_value );
    log_printf( &logger, "> app init done\r\n" );
}

void application_task ( void )
{
    uint8_t i;

    //  Task implementation.

    for ( i = 0; i < 8; i++ )
    {
        if ( out_value < 4095 )
        {
            out_value++;
        }
        stepup_set_out( &stepup, out_value );
        stepup_log_percent( out_value );
        Delay_ms( 250 );
    }

    for ( i = 0; i < 14; i++ )
    {
        if ( out_value > 0 )
        {
            out_value--;
        }
        stepup_set_out( &stepup, out_value );
        stepup_log_percent( out_value );
        Delay_ms( 250 );
    }
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
