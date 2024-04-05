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
 * If any of conditions are not fullfilled, the device will return 0 or Vref
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
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    log_cfg_t log_cfg;
    adc_cfg_t cfg;

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

    adc_cfg_setup( &cfg );
    ADC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc_init( &adc, &cfg );
}

void application_task( void )
{
    adc_get_single_ended_ch( &adc, ADC_CH0_OR_CH01 );
    adc_get_single_ended_ch( &adc, ADC_CH1_OR_CH10 );
    adc_get_single_ended_ch( &adc, ADC_CH2_OR_CH23 );
    adc_get_single_ended_ch( &adc, ADC_CH3_OR_CH32 );
    adc_get_differential_ch( &adc, ADC_CH0_OR_CH01 );

    log_printf( &logger, "* CH0 = %u mV\r\n", adc.ch0 );
    log_printf( &logger, "* CH1 = %u mV\r\n", adc.ch1 );
    log_printf( &logger, "* CH2 = %u mV\r\n", adc.ch2 );
    log_printf( &logger, "* CH3 = %u mV\r\n", adc.ch3 );
    log_printf( &logger, "* CH0 - CH1 = %d mV\r\n", adc.ch01 );
    log_printf( &logger, "-----------------------------\r\n" );

    Delay_ms ( 1000 );
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
