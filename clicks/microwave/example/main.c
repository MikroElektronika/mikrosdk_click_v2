/*!
 * \file main.c
 * \brief Microwave Click example
 *
 * # Description
 *
 * This is an example which demonstrates the use of Microwave Click board.
 * Microwave click reads ADC results, takes exact amount of samples,
 * calculation of difference between taken samples and reference ADC value, and
 * reports movement if difference is greater than selected threshold value.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the ADC and uart console where the results will be showed.
 * Also calculates the reference ADC value for Microwave Click board.
 *
 * ## Application Task
 * Reads the AD converted results and compares this results with the previously
 * calculated reference value, taking into account the choosen threshold value.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "microwave.h"

// ------------------------------------------------------------------ VARIABLES

static microwave_t microwave;
static log_t console;

static uint8_t cnt;
static uint16_t reference;
static uint32_t sum;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    microwave_cfg_t microwave_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    microwave_cfg_setup( &microwave_cfg );
    MICROWAVE_MAP_MIKROBUS( microwave_cfg, MIKROBUS_1 );
    microwave_init( &microwave, &microwave_cfg );

    //  UART console module initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.baud = 9600;
    console_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &console, &console_cfg );
    log_printf( &console, "***************************************\r\n" );
    log_printf( &console, "***  Microwave initialization done  ***\r\n" );
    log_printf( &console, "***************************************\r\n" );

    sum = 0;

    for (cnt = 0; cnt < MICROWAVE_SAMPLES_COUNT_100; cnt++)
    {
        sum += microwave_generic_read( &microwave );
    }

    reference = sum / MICROWAVE_SAMPLES_COUNT_100;

    log_printf( &console, "** Reference value is %d\r\n", reference );
    log_printf( &console, "***************************************\r\n" );
}

void application_task( void )
{
    microwave_data_t adc_sample;
    uint16_t detector;
    uint8_t sampler;

    sum = 0;
    cnt = 0;

    for ( sampler = 0; sampler < MICROWAVE_SAMPLES_COUNT_100; sampler++ )
    {
        adc_sample = microwave_generic_read( &microwave );

        if ( adc_sample < reference )
        {
            sum += adc_sample;
            cnt++;
        }
    }

    if ( cnt )
    {
        detector = sum / cnt;

        if ( ( detector + MICROWAVE_THRESHOLD_50 ) < reference)
        {
            log_printf( &console, "** Detected move is %d\r\n", detector );
        }
    }
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
