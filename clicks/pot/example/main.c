/*!
 * \file 
 * \brief Pot Click example
 * 
 * # Description
 * Click board with the accurate selectable reference voltage output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Performs logger and Click initialization.
 * 
 * ## Application Task  
 * Makes the averaged results by using the desired number of samples of AD conversion.
  The averaged results will be calculated to millivolts [mV] and sent to the uart terminal.
 * 
 * *note:* 
 * The AD conversion will be performed on the analog (AN) pin on the mikrobus 1.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pot.h"

// ------------------------------------------------------------------ VARIABLES

static pot_t pot;
static log_t logger;

#define N_SAMPLES         100
#define ADC_V_REF_MV      1790
#define ADC_12BIT_RESOL   4096
#define ADC_10BIT_RESOL   1024

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pot_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pot_cfg_setup( &cfg );
    POT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pot_init( &pot, &cfg );

}

void application_task ( void )
{
    pot_data_t tmp;
    uint16_t adc_read;
    uint16_t n_samples;
    uint16_t adc_max;
    uint16_t adc_min;
    float adc_avrg;

    //  Task implementation.

    for ( n_samples = 0; n_samples < N_SAMPLES; n_samples++ )
    {
        adc_read = pot_generic_read ( &pot );
        
        if ( n_samples == 0 )
        {
            adc_max = adc_read;
            adc_min = adc_read;
        }

        if ( adc_read > adc_max )
        {
            adc_max = adc_read;
        }

        else if ( adc_read < adc_min )
        {
            adc_min = adc_read;
        }
        
        Delay_ms( 1 );
    }

    adc_avrg = adc_max;
    adc_avrg += adc_min;
    adc_avrg /= 2;
    adc_avrg /= ADC_12BIT_RESOL;
    adc_avrg *= ADC_V_REF_MV;
    adc_read = adc_avrg;
    
    log_printf( &logger, "** AN : %d mV\r\n", adc_read );
    Delay_ms( 1000 );

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
