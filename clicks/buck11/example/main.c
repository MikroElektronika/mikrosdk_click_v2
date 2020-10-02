/*!
 * \file 
 * \brief Buck11 Click example
 * 
 * # Description
 * This aplication control voltage using Buck 11.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C serial interface and selects the desired VDD voltage value
 * and VOUT value resolution (to get VOUT value in Volts).
 * 
 * ## Application Task  
 * Reads the averaged VOUT voltage calculated to Volts by performing a 30 conversions
 * in one measurement cycle. The measured results will be showed on the uart terminal every 300 milliseconds.
 * 
 * *note:* 
 * The user should measure the VDD voltage value and enter this measured value to the function as VDD value to get
 * more accurate measurement. This VDD voltage is used as reference voltage for the AD conversion.
 * 
 * The input voltage (VIN) range is from 4.2V to 60V.
 * The output current (IOUT) value should not be greater than 1.5A.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck11.h"

// ------------------------------------------------------------------ VARIABLES

static buck11_t buck11;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    uint8_t vout_resol;
    log_cfg_t log_cfg;
    buck11_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck11_cfg_setup( &cfg );
    BUCK11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck11_init( &buck11, &cfg );

    Delay_ms( 500 );
    
    buck11_set_vdd_value( 4.935 );
    vout_resol = BUCK11_VOUT_VOLTS;
    
    log_printf( &logger, "** Buck 11 is initialized ** \r\n" );
    log_printf( &logger, "************************************* \r\n" );
    Delay_ms( 200 );
}

void application_task ( )
{
    float vout_value;
    uint8_t vout_resol;

    vout_value = buck11_get_averaged_vout( &buck11, vout_resol, 30 );

    log_printf( &logger, "VOUT: %f", vout_value );
    
    if ( vout_resol == BUCK11_VOUT_VOLTS )
    {
        log_printf( &logger, " V \r\n" );
    }
    else
    {
        log_printf( &logger, " mV \r\n" );
    }
    
    log_printf( &logger, "************************************* \r\n" );
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
