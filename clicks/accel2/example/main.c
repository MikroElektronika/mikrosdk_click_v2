/*!
 * \file 
 * \brief Accel2 Click example
 * 
 * # Description
 * This application is three-axis accelerometer which embeds.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device. Check sensor ID and initialize Accel 2 click.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Accel 2 click board.
   Measured coordinates (X,Y,Z) are being sent to the UART where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel2.h"

// ------------------------------------------------------------------ VARIABLES

static accel2_t accel2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel2_cfg_t cfg;
	uint8_t cfg_byte = 0;

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

    accel2_cfg_setup( &cfg );
    ACCEL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel2_init( &accel2, &cfg );
	Delay_ms ( 100 );
	accel2_setting( &accel2 );
	Delay_ms ( 100 );
	cfg_byte = accel2_check_id( &accel2 );
	if ( cfg_byte )
	{
		log_info( &logger, "---- ID ERROR ----" );
		for ( ; ; );
	}
	else
	{
		log_info( &logger, "---- ID OK ----" );
	}
}

void application_task ( void )
{
    int16_t value_x;
    int16_t value_y;
    int16_t value_z;

    value_x = accel2_read_xaxis( &accel2 );
    value_y = accel2_read_yaxis( &accel2 );
    value_z = accel2_read_zaxis( &accel2 );

    log_printf( &logger, "Axis X: %d\r\n", value_x );
    log_printf( &logger, "Axis Y: %d\r\n", value_y );
    log_printf( &logger, "Axis Z: %d\r\n", value_z );
    log_printf( &logger, "-------------------------------\r\n" );

    Delay_ms ( 500 );
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
