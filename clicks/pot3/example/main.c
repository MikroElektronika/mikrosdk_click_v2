/*!
 * \file 
 * \brief Pot3 Click example
 * 
 * # Description
 * This application reads voltage value, calculates it to millivolts and then 
 * logs it to the uart terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes devices module.
 * 
 * ## Application Task  
 * Reads VOUT value calculated to millivolts with 2000 conversions
 * included in one measurement cycle.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pot3.h"

// ------------------------------------------------------------------ VARIABLES

static pot3_t pot3;
static log_t logger;

static uint16_t voltage_mv;
static uint16_t voltage_old;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pot3_cfg_t pot3_cfg;

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

    pot3_cfg_setup( &pot3_cfg );
    POT3_MAP_MIKROBUS( pot3_cfg, MIKROBUS_1 );
    pot3_init( &pot3, &pot3_cfg );

	voltage_old = 0;
}

void application_task ( void )
{
	voltage_mv = pot3_get_vout( &pot3, POT3_VREF_2V, 2000);
	
	if (voltage_mv != voltage_old)
	{
		log_printf(&logger, " VOUT : %d mV\r\n", voltage_mv);
	}

	voltage_old = voltage_mv;
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
