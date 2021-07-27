/*!
 * \file 
 * \brief Vreg Click example
 * 
 * # Description
 * This is an example that demonstrates the use of VREG click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and sets output voltage.
 * 
 * ## Application Task  
 * Reads ADC data from all 3 channels, converts those values to voltage 
 * and displays the results on USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vreg.h"

// ------------------------------------------------------------------ VARIABLES

static vreg_t vreg;
static log_t logger;

static uint16_t ch_reg;
static uint16_t ch_in;
static uint16_t ch_out;
static float voltage;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vreg_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vreg_cfg_setup( &cfg );
    VREG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vreg_init( &vreg, &cfg );

    vreg_stop_measuring( &vreg );
    log_printf( &logger, " Stop Measuring \r\n" );
    Delay_1sec( );

    log_printf( &logger, " Set Out Voltage \r\n" );
    vreg_set_out_voltage( &vreg, 600 );
    Delay_1sec( );

    log_printf( &logger, " Start Measuring \r\n" );
    vreg_start_measuring( &vreg );
    Delay_1sec( );
}

void application_task ( void )
{
    ch_reg = vreg_get_adc( &vreg, VREG_CHANNEL_0 );
    voltage = ch_reg / 182.0;
   
    log_printf( &logger, " CH Reg  : %.2f V\r\n", voltage );
    
    Delay_10ms( );

    ch_in = vreg_get_adc( &vreg, VREG_CHANNEL_2 );
    voltage = ch_in / 182.0;
    
    log_printf( &logger, " CH In   : %.2f V\r\n ", voltage );
    
    Delay_10ms( );
    
    ch_out = vreg_get_adc( &vreg, VREG_CHANNEL_1 );
    voltage = ch_out / 182.0;
    
    log_printf( &logger, " CH Out  : %.2f  V\r\n", voltage );
    
    Delay_1sec( );
    log_printf( &logger, " ---------------------- \r\n" );
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
