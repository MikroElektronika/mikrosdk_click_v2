/*!
 * \file 
 * \brief AnalogMUX Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Analog MUX click module. 
 * The click switches one of the 16 inputs to output so the adc value of that input 
 * can be read on the COM (AN) pin. The RST, PWM, CS and INT are used as control output pins. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function reads ADC value and voltage from channel 0 (AN0) and shows the results 
 * on the USB UART every 2 seconds. 
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
    Delay_100ms( );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    analogmux_cfg_setup( &cfg );
    ANALOGMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    analogmux_init( &analogmux, &cfg );

    analogmux_set_channel( &analogmux, ANALOGMUX_CHANNEL_0 );
    log_printf( &logger, " Channel 0 enabled\r\n" );
    log_printf( &logger, " -------------------\r\n" );
}

void application_task ( void )
{
    uint16_t tmp;
    float val;

    tmp = analogmux_generic_read( &analogmux );
    
    log_printf( &logger, " ADC value : %u\r\n", tmp );

    val = analogmux_generic_read_voltage( &analogmux );

    log_printf( &logger, " Voltage: %.3f mV\r\n", val );
    log_printf( &logger, " -------------------\r\n" );

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
