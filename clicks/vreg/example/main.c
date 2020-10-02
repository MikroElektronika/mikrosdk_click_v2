/*!
 * \file 
 * \brief Vreg Click example
 * 
 * # Description
 * The design is based on the well-known LM317-M circuit, with the addition of a 12-bit DAC, 12-bit ADC, and an Operational Amplifier.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - SPI, set output voltage.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of VREG click board.
   VREG click communicates with the device via SPI driver set DAC value and get ADC value.
   Results are being sent to the Usart Terminal where you can track their changes.
   All data logs write on usb uart changes for every 1 sec.
 * 
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
    log_printf( &logger, " Stop  Measuring " );
    Delay_1sec( );

    log_printf( &logger, " Set Out Voltage " );
    vreg_set_out_voltage( &vreg, 600 );
    Delay_1sec( );

    log_printf( &logger, " Start Measuring " );
    vreg_start_measuring( &vreg );
    Delay_1sec( );
}

void application_task ( void )
{
    ch_reg = vreg_get_adc( &vreg, VREG_CHANNEL_0 );
   
    log_printf( &logger, " CH Reg  : %d \r\n", ch_reg );
    
    Delay_10ms( );

    ch_in = vreg_get_adc( &vreg, VREG_CHANNEL_1 );
    
    log_printf( &logger, " CH In   : %d \r\n ", ch_in );
    
    Delay_10ms( );

    ch_out = vreg_get_adc( &vreg, VREG_CHANNEL_2 );
    
    log_printf( &logger, " CH Out  : %d \r\n", ch_out );
    
    Delay_1sec( );
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
