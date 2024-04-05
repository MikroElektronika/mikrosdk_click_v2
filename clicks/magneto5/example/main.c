/*!
 * \file 
 * \brief Magneto5 Click example
 * 
 * # Description
 * This application is is a very accurate and reliable magnetic sensor device.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and set measurement mode and channel.
 * 
 * ## Application Task  
 * Reads X / Y / Z data axis and logs to USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneto5.h"

// ------------------------------------------------------------------ VARIABLES

static magneto5_t magneto5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto5_cfg_t cfg;

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

    magneto5_cfg_setup( &cfg );
    MAGNETO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto5_init( &magneto5, &cfg );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    float x_axis;
    float y_axis;
    float z_axis;

    //  Task implementation.

    x_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_X, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- X axis : %.2f \r\n ", x_axis );

    y_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_Y, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- Y axis : %.2f \r\n ",  y_axis );

    z_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_Z, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- Z axis : %.2f \r\n ", z_axis );
    log_printf ( &logger, "-------------------------\r\n " );
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
