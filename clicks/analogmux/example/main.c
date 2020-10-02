/*!
 * \file 
 * \brief AnalogMUX Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Analog MUX click module. The
 * click switches one of the 16 inputs to 1 output and the adc values can be read on the COM (AN)
 * pin. RST, PWM, CS and INT are used as control output pins. An external power supply is requ-
 * ired in order to make this demo work. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function first provides the arithmetic mean of 10 measurements on channel 0 (AN0) and 
 * then calculates the voltage value using that result. It shows both values in the UART console
 * and does so every 2 seconds. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "analogmux.h"

// ------------------------------------------------------------------ VARIABLES

static analogmux_t analogmux;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    analogmux_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    Delay_100ms( );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    analogmux_cfg_setup( &cfg );
    ANALOGMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    analogmux_init( &analogmux, &cfg );

    analogmux_set_channel( &analogmux, ANALOGMUX_CHANNEL_0 );
    log_printf( &logger, " ** ADC configured **\r\n" );
}

void application_task ( void )
{
    analogmux_data_t tmp;
    uint8_t cnt;
    float val;

    tmp = 0;
    
    for ( cnt = 0; cnt < 10; cnt++ )
    {
        tmp += analogmux_generic_read( &analogmux );
    }

    val = tmp / 10.0;
    
    log_printf( &logger, " ** ADC value : %.2f\r\n", val );

    val = analogmux_generic_read_voltage( &analogmux );

    log_printf( &logger, " ** Voltage: %.2f\r\n", val );
    log_printf( &logger, " ----------\r\n" );

    Delay_ms( 2000 );
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
