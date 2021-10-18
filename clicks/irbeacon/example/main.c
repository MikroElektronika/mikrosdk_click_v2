/*!
 * \file 
 * \brief IrBeacon Click example
 * 
 * # Description
 * This application sets the brightness on Leds.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Enables GPIO and PWM, sets the frequency and duty cycle and enables PWM.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of IR Beacon Click board.
 * It shows how to enable the device and gradualy increase the duty cycle.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irbeacon.h"

// ------------------------------------------------------------------ VARIABLES

static irbeacon_t irbeacon;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irbeacon_cfg_t cfg;

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

    irbeacon_cfg_setup( &cfg );
    IRBEACON_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irbeacon_init( &irbeacon, &cfg );
    irbeacon_pwm_start( &irbeacon );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    irbeacon_enable_mod( &irbeacon );

    for ( float duty_cycle = 0.1; duty_cycle <= 1; duty_cycle += 0.1 )
    {
        irbeacon_set_duty_cycle( &irbeacon, duty_cycle );
        Delay_ms( 1000 );
    }

    irbeacon_disable_mod( &irbeacon );
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
