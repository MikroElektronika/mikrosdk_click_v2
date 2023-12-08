/*!
 * \file 
 * \brief Comass2 Click example
 * 
 * # Description
 * The example prepares the device for a new measurement and reads and displays data from all three axes.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes and configures the click and logger modules.
 * 
 * ## Application Task  
 * Reads and displays data from all three axes every two seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "compass2.h"

// ------------------------------------------------------------------ VARIABLES

static compass2_t compass2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    compass2_cfg_t cfg;

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

    compass2_cfg_setup( &cfg );
    COMPASS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass2_init( &compass2, &cfg );

    compass2_reset( &compass2 );
    Delay_ms( 100 );

    compass2_default_cfg( &compass2 );
    Delay_ms( 100 );
}

void application_task ( )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;
    
    compass2_new_measurement( &compass2 );
    
    log_printf( &logger, " --- Axis ---\r\n" );

    x_axis = compass2_get_axis_data( &compass2, COMPASS2_X_AXIS );
    y_axis = compass2_get_axis_data( &compass2, COMPASS2_Y_AXIS );
    z_axis = compass2_get_axis_data( &compass2, COMPASS2_Z_AXIS );
    
    log_printf( &logger, "X: %d\r\n", x_axis );
    log_printf( &logger, "Y: %d\r\n", y_axis );
    log_printf( &logger, "Z: %d\r\n", z_axis );

    log_printf( &logger, "----------------\r\n" );
    
    Delay_ms( 2000 );
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
