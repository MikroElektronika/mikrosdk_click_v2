/*!
 * \file 
 * \brief Rng Click example
 * 
 * # Description
 * This Click is a random number generator. The device contain potentiometer which control voltage
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
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
