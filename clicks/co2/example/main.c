/*!
 * \file 
 * \brief CO2 Click example
 * 
 * # Description
 * This application enables usage of very accurate CO sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and performs the device configuration for properly working.
 * 
 * ## Application Task  
 * Gets CO (Carbon Monoxide) data as ppm value every 300 miliseconds.
 * Results will be logged on UART. The CO value range is from 0 to 1000 ppm.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "co2.h"

// ------------------------------------------------------------------ VARIABLES

static co2_t co2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    co2_cfg_t cfg;
    uint8_t temp_w;
    
    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    co2_cfg_setup( &cfg );
    CO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    co2_init( &co2, &cfg );

    Delay_ms( 500 );

    temp_w = CO2_WRITE_MODE;
    co2_generic_write( &co2, CO2_LOCK_REG, &temp_w, 1 );
    temp_w = CO2_STANDBY_MODE;
    co2_generic_write( &co2, CO2_MODECN_REG, &temp_w, 1 );
    temp_w = CO2_3500_OHM_TIA_RES | CO2_100_OHM_LOAD_RES;
    co2_generic_write( &co2, CO2_TIACN_REG, &temp_w, 1 );
    temp_w = CO2_VREF_EXT | CO2_50_PERCENTS_INT_ZERO | CO2_BIAS_POL_NEGATIVE | CO2_0_PERCENTS_BIAS;
    co2_generic_write( &co2, CO2_REFCN_REG, &temp_w, 1 );
    
    log_printf( &logger, "CO 2 is initialized\r\n\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    float co2_value;
   
    co2_wait_i2c_ready( &co2 );
    co2_get_co2_ppm( &co2, &co2_value );
    
    log_printf( &logger, "CO : %.2f ppm\r\n", co2_value );
    Delay_ms( 300 );
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
