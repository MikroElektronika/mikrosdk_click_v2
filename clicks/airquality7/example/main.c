/*!
 * \file 
 * \brief AirQuality7 Click example
 * 
 * # Description
 * This demo application measures air quality.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and reads revision of the 
 * module. If CRC check is OK allows the program to go on, and if it's not OK,
 * needs to restart the program.
 * 
 * ## Application Task  
 * Reads air quality status every 1500ms and shows the results on serial terminal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "airquality7.h"

// ------------------------------------------------------------------ VARIABLES

static airquality7_t airquality7;
static log_t logger;

uint16_t airquality7_tvoc_ppb;
uint16_t airquality7_co2_ppm;
uint32_t airquality7_res_val_ohm;
airquality7_err_t airquality7_err_code;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality7_cfg_t cfg;
    
    uint8_t airquality7_rev_year       = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_month      = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_day        = AIRQUALITY7_DUMMY;
    uint8_t airquality7_rev_ascii_code = AIRQUALITY7_DUMMY;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality7_cfg_setup( &cfg );
    AIRQUALITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality7_init( &airquality7, &cfg );

    
    airquality7_tvoc_ppb    = AIRQUALITY7_DUMMY;
    airquality7_co2_ppm     = AIRQUALITY7_DUMMY;
    airquality7_res_val_ohm = AIRQUALITY7_DUMMY;

    airquality7_err_code = airquality7_get_revision( &airquality7, &airquality7_rev_year,
                                                     &airquality7_rev_month,
                                                     &airquality7_rev_day,
                                                     &airquality7_rev_ascii_code
                                                     );
    
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        log_printf( &logger, "REVISION: \r\n" );
        log_printf( &logger, " Year: %d \r\n", airquality7_rev_year );
        Delay_ms( 500 );
    
        log_printf( &logger, " Month: %d \r\n", airquality7_rev_month );
        Delay_ms( 500 );
    
        log_printf( &logger, " Day: %d \r\n", airquality7_rev_day );
        Delay_ms( 500 );
    
        log_printf( &logger, " ASCII code for a charter: %d \r\n", airquality7_rev_ascii_code );
    }
    else
    {
        log_printf( &logger, "CRC ERROR READING REVISION. \r\n" );
        Delay_ms( 1000 );
        
        for ( ; ; )
        {
            log_printf( &logger, "PLEASE, RESTART YOUR SYSTEM...\r\n" );
            Delay_ms( 1000 );
            log_printf( &logger, " \r\n \r\n " );
            Delay_ms( 1000 );
        }
    }
    
    log_printf( &logger, "----------------------------------------- \r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    airquality7_err_code = airquality7_get_status( &airquality7, &airquality7_tvoc_ppb, 
                                                   &airquality7_co2_ppm,
                                                   &airquality7_res_val_ohm, 
                                                   AIRQUALITY7_NULL );
        
    
    if ( airquality7_err_code == AIRQUALITY7_ERR_OK )
    {
        uint8_t cnt;

        log_printf( &logger, "\r\n" );

        for ( cnt = 0; cnt < 70; cnt++ )
        {
            log_printf( &logger, " " );
            Delay_ms( 5 );
        }

        log_printf( &logger, "\r\n" );

        log_printf( &logger, " tVOC [ppb] = %d ", airquality7_tvoc_ppb );
        log_printf( &logger, ";  " );

        log_printf( &logger, "CO2 [ppm] = %d ", airquality7_co2_ppm );
        log_printf( &logger, ";  " );

        log_printf( &logger, "Resistor value [ohm] = %ld ", airquality7_res_val_ohm );
    }
    
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
