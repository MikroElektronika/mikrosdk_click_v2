/*!
 * \file 
 * \brief Accel7 Click example
 * 
 * # Description
 * This example shows how data from all three axes is collected, processed and later
 * displayed in the logger module.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This is where the logger and the Click modules get initialised and configured.
 * 
 * ## Application Task  
 * This is where the data gets collected, processed and printed out.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel7.h"

// ------------------------------------------------------------------ VARIABLES

static accel7_t accel7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init (  )
{
    log_cfg_t log_cfg;
    accel7_cfg_t cfg;

    uint8_t resolution = ACCEL7_DATA_RESP_14bit;
    uint8_t range = ACCEL7_RANGE_8g;

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

    accel7_cfg_setup( &cfg );
    ACCEL7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel7_init( &accel7, &cfg );
    accel7_default_cfg( &accel7, resolution, range );

    Delay_ms ( 100 );
}

void application_task (  )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;

    x_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_X );
    y_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_Y );
    z_axis = accel7_get_axis( &accel7, ACCEL7_AXIS_Z );

    log_printf( &logger, "X axis: %d\r\n", x_axis );
    log_printf( &logger, "Y axis: %d\r\n", y_axis );
    log_printf( &logger, "Z axis: %d\r\n", z_axis );   
    
    log_printf( &logger, "------------------\r\n" );

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
