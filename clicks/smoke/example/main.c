/*!
 * \file 
 * \brief Smoke Click example
 * 
 * # Description
 * This click includes internal LEDs, photodetectors, optical elements, and low-noise electronics 
 * with ambient light rejection. The sensor can detect a wide variety of smoke particle sizes. 
 * It also has an on-chip temperature sensor for calibrating the temperature dependence of the 
 * particle sensing subsystem. The temperature sensor has an inherent resolution 0.0625°C.
 *
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies "set registers check green values" settings, 
 * "enable FIFO data ready interrupt" and makes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Smoke Click board. It reads reflected green values and
 * temperature from an internal sensor and displays the results on USART terminal.
 * It usualy takes two or three readings in order to get corect readings. Expect big values when you do.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "smoke.h"

// ------------------------------------------------------------------ VARIABLES

static smoke_t smoke;
static log_t logger;

static uint32_t grn_val;
static float temperature;

static char deg_cel[ 3 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    smoke_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    smoke_cfg_setup( &cfg );
    SMOKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smoke_init( &smoke, &cfg );

    smoke_reset( &smoke );
    smoke_default_cfg ( &smoke );

    deg_cel[ 0 ] = 176;
    deg_cel[ 1 ] = 67;
    deg_cel[ 2 ] = 0;

    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, "         Smoke  Click         \r\n" );
    log_printf( &logger, "------------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( smoke_get_intrrupt( &smoke, 1 ) & 0x40 )
    {
        grn_val = smoke_get_green_val( &smoke );
    }
    
    log_printf( &logger, "GREEN LED Pulse Amplitude : %llu\r\n", grn_val );
    log_printf( &logger, "------------------------------\r\n" );
    
    temperature = smoke_read_temp_c( &smoke );
    
    log_printf( &logger, "Read Temperature : %.4f %s\r\n",  temperature, deg_cel );
    log_printf( &logger, "------------------------------\r\n" );

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
