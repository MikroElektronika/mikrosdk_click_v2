/*!
 * \file 
 * \brief AMRCurent Click example
 * 
 * # Description
 * This application integrated bi-directional analog output current sensors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializations driver init.
 * 
 * ## Application Task  
 * Reading ADC data and converted current mA data from device and logs it to device.
 * 
 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "amrcurent.h"

// ------------------------------------------------------------------ VARIABLES

static amrcurent_t amrcurent;
static log_t logger;
uint16_t read_adc_val;
float read_curr_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    amrcurent_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    amrcurent_cfg_setup( &cfg );
    AMRCURENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    amrcurent_init( &amrcurent, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    read_adc_val = amrcurrent_read_value ( &amrcurent );
    log_printf( &logger, " - ADC value: %d\r\n ", read_adc_val );
    
    Delay_ms( 100 );

    read_curr_val = amrcurrent_get_current (  &amrcurent );
    log_printf( &logger, " - Current value: %f\r\n ", read_curr_val );
    
    Delay_ms( 5000 );
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
