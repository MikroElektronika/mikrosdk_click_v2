/*!
 * \file 
 * \brief LightMixSens Click example
 * 
 * # Description
 * This example show usage of Light Mix Sens Click. It switches the IR light for separate and 
 * measure sectar of RGB lights. Click also measure proximity from the object using light source.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes all necessary peripherals and pins, initializes I2C driver and performs 
 * the Click board default configuration to allow ALS/Color and Proximity measurements.
 * 
 * ## Application Task  
 * Waits until ALS/Color integration cycle was done and then reads the entire measurement.
 * The all results will be sent to the selected UART terminal.
 * 
 * ## Additional Functions :
 * - prox_app - This is application function which determines the proximity results.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lightmixsens.h"

// ------------------------------------------------------------------ VARIABLES

static lightmixsens_t lightmixsens;
static log_t logger;

static uint16_t lightmixsens_cdata;
static uint16_t lightmixsens_rdata;
static uint16_t lightmixsens_gdata;
static uint16_t lightmixsens_bdata;
static uint8_t lightmixsens_pdata;
char prox_str[ 20 ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void prox_app ( )
{
    float prox;
    uint8_t cnt;
    
    prox = lightmixsens_pdata;
    prox /= 255;
    prox *= 16;
    
    for ( cnt = 0; cnt < ( uint8_t ) prox; cnt++ )
    {
        prox_str[ cnt ] = '|';
    }
    
    prox_str[ cnt ] = 0;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightmixsens_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lightmixsens_cfg_setup( &cfg );
    LIGHTMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightmixsens_init( &lightmixsens, &cfg );

    lightmixsens_default_cfg( &lightmixsens );

    lightmixsens_cdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_rdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_gdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_bdata = LIGHTMIXSENS_DUMMY_DATA;
    lightmixsens_pdata = LIGHTMIXSENS_DUMMY_DATA;

    log_printf( &logger, "*  Light mix-sens click initialization done.  *\r\n" );
}

void application_task ( void )
{
    lightmixsens_wait_atime( &lightmixsens );
    
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_CDATA, &lightmixsens_cdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_RDATA, &lightmixsens_rdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_GDATA_IRDATA, &lightmixsens_gdata );
    lightmixsens_read_word( &lightmixsens, LIGHTMIXSENS_REG_BDATA, &lightmixsens_bdata );
    lightmixsens_read_byte( &lightmixsens, LIGHTMIXSENS_REG_PDATA, &lightmixsens_pdata );
    
    log_printf( &logger, "- Clear light:  %d lx\r\n", lightmixsens_cdata );
    log_printf( &logger, "- Red light:    %d lx\r\n", lightmixsens_rdata );
    log_printf( &logger, "- Green light:  %d lx\r\n", lightmixsens_gdata );
    log_printf( &logger, "- Blue light:   %d lx\r\n", lightmixsens_bdata );
    
    prox_app( );
    log_printf( &logger, "** Proximity:   %s\r\n", prox_str );
    
    log_printf( &logger, "\r\n" );
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
