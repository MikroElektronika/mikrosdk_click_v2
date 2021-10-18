/*!
 * \file 
 * \brief Angle4 Click example
 * 
 * # Description
 * This application enables use of angular magnetic rotary sensor, which can be used as a rotary encoder.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver intialization, standard configurations and start measurement
 * 
 * ## Application Task  
 * Reads Angle in degreeses and logs data to USBUART every 200 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "angle4.h"

// ------------------------------------------------------------------ VARIABLES

static angle4_t angle4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle4_cfg_t cfg;

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

    angle4_cfg_setup( &cfg );
    ANGLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle4_init( &angle4, &cfg );

    angle4_default_cfg( &angle4, ANGLE4_CCFG2_DIR_COUNTER_CLOCKWISE_ROTATION,\
                                 ANGLE4_CCFG2_ABS_RESOLUTION_14bit );
    log_printf( &logger, " --- Start measurement \r\n");

    angle4_start_mesuremenet( &angle4 );
}

void application_task ( void )
{
    //  Task implementation.

    uint16_t angle_value;

    angle4_get_new_angle( &angle4, &angle_value );
    log_printf( &logger, " Angle : %d deg\r\n", angle_value );
    Delay_ms( 200 );
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
