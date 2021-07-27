/*!
 * \file 
 * \brief Rng Click example
 * 
 * # Description
 * This click is a random number generator. The device contain potentiometer which control voltage
 * so it generates a sequence of numbers or symbols that cannot be reasonably predicted better 
 * by a random chance. Random number generators have applications in gambling, statistical sampling,
 * computer simulation, cryptography, completely randomized design, and various other areas. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, then sets configuration and voltage reference.
 * 
 * ## Application Task  
 * It reads ADC value from AIN0 channel then converts it to voltage and 
 * displays the result on USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rng.h"

// ------------------------------------------------------------------ VARIABLES

static rng_t rng;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rng_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rng_cfg_setup( &cfg );
    RNG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rng_init( &rng, &cfg );

    rng_default_cfg( &rng );
}

void application_task ( void )
{
    float voltage;

    voltage = rng_get_voltage( &rng );

    log_printf( &logger, "Voltage from AIN0: %.2f mV\r\n", voltage );
    log_printf( &logger, "-----------------------\r\n" );
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
