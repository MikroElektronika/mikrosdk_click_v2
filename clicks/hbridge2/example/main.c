/*!
 * \file 
 * \brief H BRIDGE 2 Click example
 * 
 * # Description
 * This application controls the speed and direction of motor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and puts the device to enable state,
 * and the GPIO pin to logic high state.
 * 
 * ## Application Task  
 * Demonstrates the control of output pins by put output pins to different states.
 * The outputs be changed after every 3 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hbridge2.h"

// ------------------------------------------------------------------ VARIABLES

static hbridge2_t hbridge2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    hbridge2_cfg_setup( &cfg );
    HBRIDGE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge2_init( &hbridge2, &cfg );

    hbridge2_enable( &hbridge2, HBRIDGE2_ENABLE );
    hbridge2_set_gout( &hbridge2, HBRIDGE2_GOUT_HIGH );
    log_printf( &logger, "H-Bridge 2 is intialized\r\n" );
    Delay_ms ( 200 );
}

void application_task ( void )
{
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_H_OUT2_L );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_L_OUT2_H );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    hbridge2_set_output( &hbridge2, HBRIDGE2_OUT1_Z_OUT2_Z );
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
