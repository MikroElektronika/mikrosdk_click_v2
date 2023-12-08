/*!
 * \file 
 * \brief Fan3 Click example
 * 
 * # Description
 * This application controls the fan speed.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click device.
 * 
 * ## Application Task  
 * Cycles through different fan speeds, including 0 - stopped.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fan3.h"

// ------------------------------------------------------------------ VARIABLES

static fan3_t fan3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fan3_cfg_t cfg;

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

    fan3_cfg_setup( &cfg );
    FAN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan3_init( &fan3, &cfg );

    log_printf( &logger, ">>> Initialized...\r\n" );
}

void application_task ( )
{
    log_printf( &logger, "Speed 1...\r\n" );
    fan3_set_speed( &fan3, FAN3_SPEED1 );
    Delay_ms( 4000 );
    log_printf( &logger, "Speed 3...\r\n" );
    fan3_set_speed( &fan3, FAN3_SPEED3 );
    Delay_ms( 4000 );
    log_printf( &logger, "Speed 5...\r\n" );
    fan3_set_speed( &fan3, FAN3_SPEED5 );
    Delay_ms( 4000 );
    log_printf( &logger, "Speed 7...\r\n" );
    fan3_set_speed( &fan3, FAN3_SPEED7 );
    Delay_ms( 4000 );
    log_printf( &logger, "Stopped...\r\n" );
    fan3_set_speed( &fan3, FAN3_STOPPED );
    Delay_ms( 4000 );
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
