/*!
 * \file 
 * \brief MagneticRotary Click example
 * 
 * # Description
 * On every 500 miliseconds reads a magnetic field angle calculated to degrees for channel A
 * in Single-Ended Mode and logs results on uart terminal. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes peripherals, pins, SPI interface for communication with the device.
 * 
 * ## Application Task  
 * Reads a magnetic field angle calculated to degrees for channel A
 * in Single-Ended Mode and logs results on uart terminal.
 * Repeats operation every 500 milliseconds.
 * Note : The angle can be measured in the range from -90 to 90 degrees.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneticrotary.h"

// ------------------------------------------------------------------ VARIABLES

static magneticrotary_t magneticrotary;
static log_t logger;

static double magn_angle;
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneticrotary_cfg_t cfg;

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

    magneticrotary_cfg_setup( &cfg );
    MAGNETICROTARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneticrotary_init( &magneticrotary, &cfg );
    log_info(&logger, "Magnetic rotary successufully initialized!\r\n");

}

void application_task ( void )
{
    //  Task implementation.

    magn_angle = magnrotary_get_field_angle( 
                                            &magneticrotary, MAGNROTARY_CHA_POS_GND_NEG | 
                                                             MAGNROTARY_MSB_ZEROS_ORDER );
    
    log_printf( &logger, "Angle:    %.2lf \r\n ", magn_angle );
    
    Delay_ms( 500 );
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
