/*!
 * \file 
 * \brief Mic33153 Click example
 * 
 * # Description
 * This app enables step-down (buck) converter.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver.
 * 
 * ## Application Task  
 * Activates the output voltage of the device, writes DAC value witch sets
 * output voltage to 2V, and checks PG (Power Good) pin witch compares output voltage with his
 * steady state voltage. MIC33153 click is tested on load with current output value of 20mA.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic33153.h"

// ------------------------------------------------------------------ VARIABLES

static mic33153_t mic33153;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic33153_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mic33153_cfg_setup( &cfg );
    MIC33153_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic33153_init( &mic33153, &cfg );
    Delay_ms( 100 );
}

void application_task ( void )
{
    mic33153_enable_out( &mic33153, MIC33153_OUT_ENABLE );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_1000MV );
    log_printf( &logger, "Output voltage set to 1000mV\r\n" );
    Delay_ms(2000);
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_1500MV );
    log_printf( &logger, "Output voltage set to 1500mV\r\n" );
    Delay_ms(2000);
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_2000MV );
    log_printf( &logger, "Output voltage set to 2000mV\r\n" );
    Delay_ms(2000);
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_2500MV );
    log_printf( &logger, "Output voltage set to 2500mV\r\n" );
    Delay_ms(2000);
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_3000MV );
    log_printf( &logger, "Output voltage set to 3000mV\r\n" );
    Delay_ms(2000);
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_3200MV );
    log_printf( &logger, "Output voltage set to 3200mV\r\n" );
    Delay_ms(2000);
    
    mic33153_write_dac ( &mic33153, MIC33153_MAX_VOLTAGE_3550MV );
    log_printf( &logger, "Output voltage set to 3550mV\r\n" );
    Delay_ms(2000);
    
    log_printf( &logger, "-----------------------------------\r\n" );
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
