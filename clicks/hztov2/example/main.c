/*!
 * \file 
 * \brief HzToV2 Click example
 * 
 * # Description
 * This app converts input frequency to a DC voltage output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Power on the click board and initilaize device.
 * 
 * ## Application Task  
 * Voltage reading is done from the analog pin and the conversion
 * result is sent to UART terminal.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hztov2.h"

// ------------------------------------------------------------------ VARIABLES

static hztov2_t hztov2;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

float hztov2_adc_read ( hztov2_t *ctx )
{
     float tmp;
     tmp = (float)hztov2_generic_read( &hztov2 );
     tmp *= 3.3;
     tmp /= 4095.0;
     return tmp;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hztov2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hztov2_cfg_setup( &cfg );
    HZTOV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov2_init( &hztov2, &cfg );
    hztov2_en_pin( &hztov2, 1 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    hztov2_data_t tmp;
    float voltage;
    
    tmp = hztov2_generic_read ( &hztov2 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms( 1000 );

    voltage = hztov2_adc_read( &hztov2 );
    if ( voltage < 0.99 )
    {
      voltage = voltage * 1000.0;
      log_printf( &logger, "Voltage: %f mV \r\n", voltage );
    }
    else
    {
        log_printf( &logger, "Voltage: %f V \r\n", voltage );
    }

    Delay_ms(100);
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
