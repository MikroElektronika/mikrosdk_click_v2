/*!
 * \file 
 * \brief TouchKey4 Click example
 * 
 * # Description
 * This demo performs touch & release detection click functionality.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Device and driver initialization.
 * 
 * ## Application Task  
 * Calls function to check touch detection (is interrupt occured) and shows message on
 * USB UART if touch is detected or if touch is released on enabled inputs.
 *
 * *note:*
 * <pre>
 * TouchKey 4 is configured to work in Combo mode (Active and Standby mode). Input 1 is
 * enabled in Active mode, input 3 is enabled in Standby mode, and input 2 is enabled to
 * work in both modes. In this example the interrupt will be generated when touch is
 * detected and when touch is released. Also input 2 will generate interrupt as long
 * as the touch is detected (press and hold event), while input 1 and input 3 will
 * generate interrupt only once on one touch detection, after which the touch will be 
 * released. Standby mode should be used when fewer sensor inputs are enabled, and when
 * they are programmed to have more sensitivity.
 * Somethimes it is neccessary to reset board if click doesn't work. 
 * </pre>
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "touchkey4.h"

// ------------------------------------------------------------------ VARIABLES

static touchkey4_t touchkey4;
static log_t logger;

static uint8_t sensor_results[ 3 ];
static uint8_t cnt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    touchkey4_cfg_setup( &cfg );
    TOUCHKEY4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey4_init( &touchkey4, &cfg );

    touchkey4_default_cfg( &touchkey4 );

}

void application_task ( void )
{
    touchkey4_detect_touch( &touchkey4, sensor_results );
    for (cnt = 0; cnt < 3; cnt++)
    {
        if (sensor_results[ cnt ] == 1)
        {
            if (cnt == 0)
            {
                log_info( &logger, "Input 1 is touched\r\n" );
            }
            else if (cnt == 1)
            {
                log_info( &logger, "Input 2 is touched\r\n" );
            }
            else
            {
                log_info( &logger, "Input 3 is touched\r\n" );
            }
        }
		else if (sensor_results[ cnt ] == 2)
		{
            if (cnt == 0)
            {
                log_info( &logger, "Input 1 is released\r\n" );
            }
            else if (cnt == 1)
            {
                log_info( &logger, "Input 2 is released\r\n" );
            }
            else
            {
                log_info( &logger, "Input 3 is released\r\n" );
            }
        }
    }
    Delay_ms(300);
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
