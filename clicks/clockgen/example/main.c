/*!
 * \file 
 * \brief ClockGen Click example
 * 
 * # Description
 * Clock Gen Click represent a replacement for crystals, crystal oscillators, VCXOs, phase-locked 
 * loops (PLLs), and fanout buffers. This Click features an I2C configurable clock generator 
 * based on a PLL + high resolution MultiSynth fractional divider architecture which can generate
 * any frequency up to 200 MHz with 0 ppm error. The chip on Click is capable of generating 
 * synchronous or free-running non-integer related clock frequencies at each of its outputs 
 * (CLK0, CLK1, and CLK2), enabling one device to synthesize clocks for multiple clock domains in a design.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configures device to default function that enables clock 0 and disables all others.
 * 
 * ## Application Task  
 * Changes 4 different frequency in span of 5 seconds.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "clockgen.h"

// ------------------------------------------------------------------ VARIABLES

static clockgen_t clockgen;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen_cfg_t cfg;
    
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

    clockgen_cfg_setup( &cfg );
    CLOCKGEN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen_init( &clockgen, &cfg );

    clockgen_default_cfg( &clockgen );
    
    Delay_ms ( 500 );
}

void application_task ( void )
{
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    clockgen_set_frequency( &clockgen, CLOCKGEN_CLOCK_0, CLOCKGEN_PLLA, 5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
