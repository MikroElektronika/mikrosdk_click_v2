/*!
 * \file 
 * \brief Angle2 Click example
 * 
 * # Description
 * This example showcases how to configure and use the Angle 2 click. This click senses
 * the magnetic field along the horizontal plane using an array of Hal effect sensors.
 * The module uses advanced Spinaxis technology based on a direct angle sampling app-
 * roach in order to provide reliable data quickly.                                         
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules. Additional con-
 * figuring is done in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function reads angle data from the click module and displays that data using the
 * UART console every 200 miliseconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "angle2.h"

// ------------------------------------------------------------------ VARIABLES

static angle2_t angle2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    angle2_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    angle2_cfg_setup( &cfg );
    ANGLE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle2_init( &angle2, &cfg );

    Delay_ms ( 300 );
    angle2_default_cfg( &angle2 );
    Delay_ms ( 200 );

    log_printf( &logger, " * Angle 2 initialized * \r\n" );
}

void application_task ( )
{
    double angle;

    angle = angle2_get_angle( &angle2 );

    log_printf( &logger, " Angle: %.2f deg\r\n", angle );

    Delay_ms ( 200 );
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
