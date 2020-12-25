/*!
 * \file 
 * \brief Angle3 Click example
 * 
 * # Description
 * This application reads data from the angle sensor, calculates it to degrees 
 * and writes it to the terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI,
 * set normal mode and start write log.
 * 
 * ## Application Task  
 * Angle 3 Click communicates with registers via SPI, reads data from the angle
 * sensor, calculates it to degrees and writes it to the terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "angle3.h"

// ------------------------------------------------------------------ VARIABLES

static angle3_t angle3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle3_cfg_t angle3_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init... ----" );

    //  Click initialization.

    angle3_cfg_setup( &angle3_cfg );
    ANGLE3_MAP_MIKROBUS( angle3_cfg, MIKROBUS_1 );
    if ( angle3_init( &angle3, &angle3_cfg ) == ANGLE3_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done ----\n" );
}

void application_task ( void )
{
	static uint16_t angle_value_old = 0;

	if ( angle3_read_error( &angle3 ) )
	{
		uint16_t angle_value = angle3_read_angle_data( &angle3 );;

		if ( angle_value_old != angle_value )
		{
			uint16_t angle_data_degrees = angle3_calculate_degrees( &angle3, angle_value );

			log_printf( &logger, " Angle : %u deg\r\n", angle_data_degrees );

			angle_value_old = angle_value;

			Delay_ms( 1000 );
		}
	}
	else
	{
		log_printf( &logger, " Magnetic Field Too Weak\r\n" );

        angle_value_old = 0;
		Delay_ms( 1000 );
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
