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
 * This function initializes and configures the logger and the click board.
 * 
 * ## Application Task  
 * Sets the PWM frequency then reads the voltage from VO pin and logs all data on USB UART.
 * 
 * ## NOTE
 * In order to set PWM frequency below 1 kHz, the user will probably need to lower the main MCU clock frequency.
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
static float voltage;
static uint32_t fin;

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
    
    fin = 10000;
    
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( fin > 120000 )
        fin = 10000;
    hztov2_fin_set( &hztov2, fin );
    log_printf( &logger, "Frequency: %lu Hz \r\n", fin );
    Delay_ms( 100 );
    
    voltage = hztov2_read_voltage( &hztov2 );
    log_printf( &logger, "Voltage: %.2f V \r\n", voltage );
    
    fin += 10000;
    Delay_ms( 2000 );
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
