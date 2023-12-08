/*!
 * \file 
 * \brief Angle Click example
 * 
 * # Description
 * Angle click is a precise Hall-effect angle sensing click board that can be used to measure the rotational angle 
 * of the magnetic field in the X-Y plane above it (parallel to the surface of the click), through the whole range of 360°.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver intialization and Angle settings mode.
 * 
 * ## System Initialization  
 * Intializes I2C module.
 * 
 * ## Application Task  
 * Reads encoded Angle in degreeses and Magnetic data in gauss.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "angle.h"

// ------------------------------------------------------------------ VARIABLES

static angle_t angle;
static log_t logger;

uint16_t angle_val;
uint16_t magnetics_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle_cfg_t cfg;

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

    angle_cfg_setup( &cfg );
    ANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle_init( &angle, &cfg );
    angle_default_cfg ( &angle );
}

void application_task ( void )
{
    angle_val = angle_get_angle( &angle );
    log_printf( &logger, "Angle :%d \r\n", angle_val );
    
    magnetics_val = angle_get_magnetics( &angle );
    log_printf( &logger, "Magnetics :%d \r\n", magnetics_val );
    
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
