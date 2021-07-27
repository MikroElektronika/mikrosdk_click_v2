/*!
 * \file main.c
 * \brief Microwave Click example
 *
 * # Description
 * This is an example which demonstrates the use of Microwave Click board.
 * Microwave click reads ADC results, takes exact amount of samples,
 * calculation of difference between taken samples and reference ADC value, and
 * reports movement if difference is greater/lower than selected threshold value.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the ADC and uart console where the results will be displayed.
 * Also calculates the reference ADC value for Microwave Click board.
 *
 * ## Application Task
 * Reads the AD converted results and compares this results with the previously
 * calculated reference value, taking into account the choosen threshold value
 * which controls the sensor sensitivity. All data is being displayed on the
 * USB UART where you can track their changes.
 * 
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
static log_t logger;

static uint16_t reference;
static uint32_t sum;
static uint16_t old_detector = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    microwave_cfg_t cfg;
    log_cfg_t log_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.
    microwave_cfg_setup( &cfg );
    MICROWAVE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    microwave_init( &microwave, &cfg );
    Delay_ms( 100 );

    log_printf( &logger, " Calibrating the sensor...\r\n" );
    log_printf( &logger, " There must be no movement near the sensor!\r\n" );
    log_printf( &logger, "*********************************************\r\n" );

    Delay_ms( 3000 );
    sum = 0;

    for ( uint8_t cnt = 0; cnt < MICROWAVE_SAMPLES_COUNT_100; cnt++ )
    {
        sum += microwave_generic_read( &microwave );
    }

    reference = sum / MICROWAVE_SAMPLES_COUNT_100;

    log_printf( &logger, " The sensor has been calibrated!\r\n" );
    log_printf( &logger, "** Reference value: %d\r\n", reference );
    log_printf( &logger, "*********************************************\r\n" );
    Delay_ms( 1000 );
}

void application_task( void )
{
    microwave_data_t adc_sample;
    uint16_t detector;
    uint8_t sampler;
    uint8_t cnt = 0;

    sum = 0;

    for ( sampler = 0; sampler < MICROWAVE_SAMPLES_COUNT_100; sampler++ )
    {
        adc_sample = microwave_generic_read( &microwave );
        sum += adc_sample;
        cnt++;
    }

    if ( cnt )
    {
        detector = sum / cnt;

        if ( ( ( detector + MICROWAVE_THRESHOLD_10 ) < reference || 
               ( detector - MICROWAVE_THRESHOLD_10 ) > reference ) && 
                 old_detector != detector )
        {
            log_printf( &logger, "** MOVE DETECTED!\r\n" );
            log_printf( &logger, "** Detector value : %d\r\n", detector );
            log_printf( &logger, "**************************\r\n" );
            old_detector = detector;
            Delay_ms( 100 );
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
