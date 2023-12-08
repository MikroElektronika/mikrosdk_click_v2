/*!
 * \file 
 * \brief Counter Click example
 * 
 * # Description
 * This application measures the speed and the position of the DC motor shafts.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and configures the click board.
 * 
 * ## Application Task  
 * Reads data from the CNTR register and calculates the speed of the motor in Rad/s.
 * All data is being displayed on the USB UART terminal where you can track their changes.
 * The CNTR is a software configurable 8, 16, 24 or 32-bit up/down counter which
 * counts the up/down pulses resulting from the quadrature clocks applied at the
 * A and B inputs, or alternatively, in non-quadrature mode, pulses applied at the A input.
 * 
 * ## NOTE
 * An appropriate motor with optical encoder needs to be connected to the click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "counter.h"

// ------------------------------------------------------------------ VARIABLES

static counter_t counter;
static log_t logger;

static int32_t count;
static int32_t count_old;
static float speed;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    counter_cfg_t cfg;

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

    counter_cfg_setup( &cfg );
    COUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    counter_init( &counter, &cfg );

    counter_default_cfg( &counter );
    Delay_ms( 300 );
}

void application_task ( void )
{
    count = counter_read_cntr( &counter );
    log_printf( &logger, "Counter: %ld\r\n",  count );
    speed = ( float ) ( count - count_old ) / 3600.0;
    speed *= 6.283185;
    log_printf( &logger, "Speed: %.4f Rad/s\r\n",  speed );
    count_old = count;
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
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
