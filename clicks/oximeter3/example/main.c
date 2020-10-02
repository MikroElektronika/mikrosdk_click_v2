/*!
 * \file 
 * \brief Oximeter3 Click example
 * 
 * # Description
 * This demo app is ambient light sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Check id status, configures device for previous selected mode.
 * 
 * ## Application Task  
 * Appliction measures values of heart rate or proximity and als value. 
 * It depends of selected device mode.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oximeter3.h"

// ------------------------------------------------------------------ VARIABLES

static oximeter3_t oximeter3;
static log_t logger;

uint8_t dev_mode = 0;
uint16_t rd_val = 0;
char demo_txt[ 30 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter3_cfg_t cfg;

    uint8_t dev_status;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    oximeter3_cfg_setup( &cfg );
    OXIMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter3_init( &oximeter3, &cfg );

    dev_status = oximeter3_generic_read( &oximeter3, OXIMETER3_REG_PRODUCT_ID );
    
    if ( dev_status != OXIMETER3_ID_VAL )
    {
        log_printf( &logger, " *****  ERROR!  ***** \r\n" );
        for ( ; ; );
    }

    dev_mode = OXIMETER3_HEART_RATE;

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                           OXIMETER3_CMD_MEASUREMENT_DISABLE );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT,
                            OXIMETER3_LED_CURR_MAX );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_RATE,
                            OXIMETER3_PROX_RATE_125_MPS );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_PROX_MODULATOR_TIMING,
                            OXIMETER3_PROX_TIMING_FREQ_390p625_KHZ );

    oximeter3_generic_write( &oximeter3, OXIMETER3_REG_COMMAND,
                            OXIMETER3_CMD_MEASUREMENT_ENABLE |
                            OXIMETER3_CMD_PROX_PERIODIC_MEASUREMENT_ENABLE |
                            OXIMETER3_CMD_ALS_PERIODIC_MEASUREMENT_ENABLE );

    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        oximeter3_generic_write( &oximeter3, OXIMETER3_REG_LED_CURRENT, 12 );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
}

void application_task ( void )
{
    if ( OXIMETER3_HEART_RATE == dev_mode )
    {
        rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
        log_printf( &logger, "%d, \r\n", rd_val );
        Delay_ms( 3000 );
    }
    else
    {
        rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_PROX );
        log_printf( &logger, " * Proximity: %d \r\n", rd_val );
        
        rd_val = oximeter3_read_value( &oximeter3, OXIMETER3_ALS );
        log_printf( &logger, " * ALS: %d \r\n", rd_val );
        
        log_printf( &logger, "******************** \r\n" );
        
        Delay_ms( 5000 );
    }
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
