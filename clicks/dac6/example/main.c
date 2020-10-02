/*!
 * \file 
 * \brief Dac6 Click example
 * 
 * # Description
 * DAC 6 click carries 12-bit buffered Digital-to-Analog Converter. It converts digital value 
 * to the corresponding voltage level using external voltage reference. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI driver.
 * 
 * ## Application Task  
 * This example shows capabilities of DAC 6 click by changeing
 * output values from 0 to the maximum output range on all four channels.
 * Output voltage is calculated by using the equation : 
 * Vout = Vrefin * (set_out / 4095).
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac6.h"

// ------------------------------------------------------------------ VARIABLES

static dac6_t dac6;
static log_t logger;

static uint16_t n_cnt;
static float v_out;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    //  Click initialization.

    dac6_cfg_setup( &cfg );
    DAC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac6_init( &dac6, &cfg );
}

void application_task ( void )
{
    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_A;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  A : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }

    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_B;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  B : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }
    
    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_C;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  C : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }

    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_D;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  D : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms( 5000 );
    }
    
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
