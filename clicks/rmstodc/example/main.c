/*!
 * \file 
 * \brief RmstoDc Click example
 * 
 * # Description
 * This application convert the RMS of the input signal into a DC voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and turns ON the device.
 * 
 * ## Application Task  
 * Reads averaged DC output voltage calculated to mV and
   sends results to the serial plotter.
 * 
 * Note : The input voltage frequency should be in the range from 50Hz to 250kHz.
 * Also the input voltage amplitude must be lower than 5V.
 * In this conditions the device can convert the RMS signal, in every form, to DC signal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rmstodc.h"

// ------------------------------------------------------------------ VARIABLES

static rmstodc_t rmstodc;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

uint32_t plot_x;
uint16_t out_volt_dc;

void plot_data( uint16_t plot_y )
{
    log_printf( &logger, ", %dl \r\n", plot_y, plot_x );
    
    if ( plot_x == 0xFFFFFFFF )
    {
        plot_x = 0;
    }
    else
    {
        plot_x++;
    }
}

void log_data( )
{
    log_printf( &logger, "DC voltage : %d\r\n", out_volt_dc );
    
    log_printf( &logger, " mV \r\n" );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    rmstodc_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rmstodc_cfg_setup( &cfg );
    RMSTODC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rmstodc_init( &rmstodc, &cfg );
}

void application_task ( void )
{
    out_volt_dc = rms2dc_avrg_vout_adc( &rmstodc, RMS2DC_VCC_3V3, 25 );
    
    log_printf(&logger,"%d mV\n",out_volt_dc);
    
    Delay_ms( 50 );
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
