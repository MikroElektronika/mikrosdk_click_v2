/*!
 * \file 
 * \brief Magneto2 Click example
 * 
 * # Description
 * This application collects data from the sensor, calculates the position of
 * the absolute rotary angle and then logs it.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and start write log.
 * 
 * ## Application Task  
 * Magneto 2 Click communicates with register via SPI by read from register
 * and calculates position of absolute rotary angle float value.
 * Results are being sent to the Uart Terminal where you can track their changes.
 * All data logs on usb uart when magnetic field is detected.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneto2.h"

// ------------------------------------------------------------------ VARIABLES

static magneto2_t magneto2;
static log_t logger;

static float angle_value_old;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto2_cfg_t cfg;

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

    magneto2_cfg_setup( &cfg );
    MAGNETO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto2_init( &magneto2, &cfg );

    angle_value_old = -1;
}

void application_task ( void )
{
    float angle_value = 0;
    angle_value = magneto2_read_angle( &magneto2 );
    Delay_ms( 100 );

    if ( angle_value_old != angle_value )
    {
        if ( angle_value != -1 )
        {
            if ( angle_value != 0 )
            {
                log_printf( &logger, "Angle %f deg\r\n", angle_value );
            }
            else
            {
                log_printf( &logger, "Magnetic field too weak\r\n" );
            }
        }
        angle_value_old = angle_value;
        Delay_ms(1000);
    }

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
