/*!
 * \file 
 * \brief Airquality2 Click example
 * 
 * # Description
 * This app measure indoor air quality.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Air quality 2 Click board.
 * Read all data information about the indoor air quality
 * from register on the iAQ-Core module, display Prediction Value CO2 [ ppm ],
 * Prediction Value TVOC [ ppb ] and Resistance Value.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 5 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "airquality2.h"

// ------------------------------------------------------------------ VARIABLES

static airquality2_t airquality2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality2_cfg_setup( &cfg );
    AIRQUALITY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality2_init( &airquality2, &cfg );
    
    // Click calibration 
    uint8_t dummy_buffer[ 9 ];
    airquality2_generic_read( &airquality2, dummy_buffer, AIRQUALITY2_READ_ALL );
    
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, "           Air quality 2          \r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t status_info;
    uint16_t value_co2;
    uint16_t value_tvoc;
    int32_t resistance;

    status_info = airquality2_get_all_data( &airquality2, &value_co2, &value_tvoc, &resistance );
    Delay_100ms( );

    if ( status_info == AIRQUALITY2_STATUS_OK )
    {
        log_printf( &logger, "       | Status : OK     |\r\n" );
    }
    if ( status_info == AIRQUALITY2_STATUS_BUSY )
    {
        log_printf( &logger, "       | Status : BUSY   |\r\n" );
    }
    if ( status_info == AIRQUALITY2_STATUS_ERROR )
    {
        log_printf( &logger, "       | Status : ERROR  |\r\n" );
    }
    if ( status_info == AIRQUALITY2_STATUS_RUNIN )
    {
        log_printf( &logger, "       | Status : RUNIN  |\r\n" );
    }

    log_printf( &logger, "----------------------------------\r\n" );

    log_printf( &logger, " CO2        : %u [ ppm ] \r\n", value_co2 );

    log_printf( &logger, " TVOC       : %u [ ppb ] \r\n", value_tvoc );

    log_printf( &logger, " Resistance : %ld [ Ohm ] \r\n", resistance );

    log_printf( &logger, "----------------------------------\r\n" );

    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
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
