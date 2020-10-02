/*!
 * \file main.c
 * \brief ADC Click example
 *
 * # Description
 * This example demonstrates the use of ADC Click board.
 * The all channels can be configured as single-ended or pseudo-differential
 * pair.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver, performs the reference voltage selection and
 * initializes UART console for results logging.
 *
 * ## Application Task
 * Reads voltage level of channels 0 and 1 in the both configurations,
 * single-ended and pseudo-differential pair, every 1 second.
 * All channels results will be calculated to millivolts [mV].
 *
 * *note:*
 * In single-ended mode the all channels must be in the range from Vss (GND)
 * to Vref (3V3 by default).
 * In pseudo-differential mode the IN- channel must be in the range from
 * (Vss - 100mV) to (Vss + 100mV). The IN+ channel must be in the range from
 * IN- to (Vref + IN-).
 * If any of conditions are not satisfied, the device will return 0 or Vref
 * voltage level, and measurements are not valid.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc.h"


// ------------------------------------------------------------------ VARIABLES

static adc_t adc;
static log_t console;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    adc_cfg_t adc_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    adc_cfg_setup( &adc_cfg );
    ADC_MAP_MIKROBUS( adc_cfg, MIKROBUS_1 );
    adc_init( &adc, &adc_cfg );

    //  UART console initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.baud = 57600;
    console_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &console, &console_cfg );
    log_info( &console, "* * *  ADC initialization done  * * *" );
    log_info( &console, "*************************************" );
}

void application_task( void )
{
    adc_get_single_ended_ch( &adc, ADC_CH0_OR_CH01 );
    adc_get_single_ended_ch( &adc, ADC_CH1_OR_CH10 );
    adc_get_differential_ch( &adc, ADC_CH0_OR_CH01 );
    adc_get_differential_ch( &adc, ADC_CH1_OR_CH10 );

    log_printf( &console, "* CH0 = %d mV\r\n", adc.ch0 );
    log_printf( &console, "* CH1 = %d mV\r\n", adc.ch1 );
    log_printf( &console, "* CH0 - CH1 = %d mV\r\n", adc.ch01 );
    log_printf( &console, "* CH1 - CH0 = %d mV\r\n\n", adc.ch10 );

    Delay_ms( 1000 );
}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
