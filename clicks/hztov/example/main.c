/*!
 * \file 
 * \brief HzToV Click example
 * 
 * # Description
 * This click accepts a signal with the frequency within a range between 10Hz and 10kHz 
 * on the input and generates DC voltage with the level corresponding to the input frequency, 
 * ranging from 0V to 10V, with a highly linear response. This signal is further passed through 
 * the operational amplifier, in order to scale it down to a level acceptable by the MCU.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO and PWM initialization.
 * 
 * ## Application Task  
 * Alternates between different output voltages.
 * 
 * *note:* 
 * Output voltage may vary, depending on the offset potentiometer on board the click.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hztov.h"

// ------------------------------------------------------------------ VARIABLES

static hztov_t hztov;
static log_t logger;
static hztov_cfg_t cfg;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    //hztov_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hztov_cfg_setup( &cfg );
    HZTOV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov_init( &hztov, &cfg );
}

void application_task ( void )
{
    hztov_set_output_voltage( &hztov, &cfg, 5000 );        //5 V output
    Delay_ms( 3000 );
    hztov_set_output_voltage( &hztov, &cfg, 2500 );        //2.5 V output
    Delay_ms( 3000 );
    hztov_set_output_voltage( &hztov, &cfg, 1000 );        //1 V output
    Delay_ms( 3000 );
    hztov_set_output_voltage( &hztov, &cfg, 500 );         //0.5 V output
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
