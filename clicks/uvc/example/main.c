/*!
 * \file 
 * \brief Uvc Click example
 * 
 * # Description
 * This click is capable of measuring UVC spectrum in the range of 220nm up to 280nm and light 
 * intensity from 0mW/cm² up to 9.3mW/cm². With high sensitivity and good solar blindness, 
 * it can be used for monitoring sterilization lamps.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and I2C module
 * 
 * ## Application Task  
 * Reads sensor raw data and calculating voltage and power data.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uvc.h"

// ------------------------------------------------------------------ VARIABLES

static uvc_t uvc;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uvc_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uvc_cfg_setup( &cfg );
    UVC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvc_init( &uvc, &cfg );
}

void application_task ( void )
{
    uint16_t raw_data;
    float voltage;
    float power;
    
    raw_data = uvc_read_raw_data( &uvc );
    log_printf( &logger, "Raw data: %d\r\n", raw_data );
    
    voltage = uvc_get_voltage( &uvc );
    log_printf( &logger, "Voltage: %.4f mV\r\n", voltage );

    power = uvc_calculate_power( voltage );
    log_printf( &logger, "Power: %.4f mV/cm2", power );

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 1500 );
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
