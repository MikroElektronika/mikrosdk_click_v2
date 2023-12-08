/*!
 * \file 
 * \brief Fan4 Click example
 * 
 * # Description
 * Demo application shows basic use of Fan 4 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Increases the output voltage every 500 ms until it reaches the maximum fan voltage.
 * Prints current voltase data on usbuart.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fan4.h"

// ------------------------------------------------------------------ VARIABLES

static fan4_t fan4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fan4_cfg_t cfg;

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

    fan4_cfg_setup( &cfg );
    FAN4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan4_init( &fan4, &cfg );

    fan4_default_cfg( &fan4 );
}

void application_task ( void )
{
    uint16_t voltage;

    //  Task implementation.

    voltage = FAN4_MIN_VOLT_SCALE;

    while ( voltage <= FAN4_MAX_VOLT_SCALE )
    {
        voltage += ( FAN4_DAC_LSB * 4 );
        log_info( &logger, "** Voltage is %d mV", voltage );

        fan4_set_output( &fan4, voltage, FAN4_BOOST_START_TIMER_DIS );
        Delay_ms( 500 );
    }
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
