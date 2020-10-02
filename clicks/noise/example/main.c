/*!
 * \file 
 * \brief noise Click example
 * 
 * # Description
 * This example performs noise monitoring and 2D graph 
 * plotting based on measured ambient noise using Noise Click.  
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Device initialization.
 * 
 * ## Application Task  
 * Every 5 ms measure ambient noise and if it's above threshold
 * alarm message is being shown.
 * Monitoring results are being plotted on serial plotter. 
 *
 * *note:* 
 * When ambient noise is above specified threshold, an interrupt
 * is triggered. Default threshold value is set to 0x64 = 52.
 *
 * Additional functions:
 * - void plot_data ( uint16_t data_plot ) - plots 2D graph
 * based on provided ADC value. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "noise.h"

// ------------------------------------------------------------------ VARIABLES

static noise_t noise;
static log_t logger;

static uint16_t adc_value;
static uint16_t plot_time;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void plot_data ( uint16_t data_plot )
{
    log_printf( &logger, "%u,%u\r\n", data_plot, plot_time++ );
    Delay_ms(2);
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    noise_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    noise_cfg_setup( &cfg );
    NOISE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    noise_init( &noise, &cfg );

    noise_default_cfg( &noise );
}

void application_task ( void )
{
    uint8_t interrupt_status;
    interrupt_status = noise_check_int_pin( &noise );

    adc_value = noise_generic_read( &noise );
    plot_data( adc_value );
    Delay_ms( 5 );

    if (interrupt_status == 1)
    {
        log_printf( &logger, " Sound threshold exceeded \r\n" );
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
