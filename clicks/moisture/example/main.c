/*!
 * \file 
 * \brief Moisture Click example
 * 
 * # Description
 * The demo application displays relative moisture measurement using Moisture click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes Driver and sets moisture gain, offset data and clock divider
 * and performs calibration of the device. We advise you not to touch,
 * or expose sensor to moisture during the calibration.
 *
 * ## Application Task
 * The device measure moisture and displays data in percentage every 500ms.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "moisture.h"

// ------------------------------------------------------------------ VARIABLES

static moisture_t moisture;
static log_t logger;

static uint8_t moisture_data;
static uint16_t data_res;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    moisture_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    moisture_cfg_setup( &cfg );
    MOISTURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    moisture_init( &moisture, &cfg );
    Delay_ms( 100 );

    moisture_soft_reset( &moisture );
    Delay_ms( 100 );

    data_res = moisture_read_word( &moisture, MOISTURE_REG_DEVICE_ID );

    if ( ( data_res != MOISTURE_FDC2112_ID ) && ( data_res != MOISTURE_FDC2212_ID ) )
    {
        log_printf( &logger, "---- Comunication ERROR!!! ---- \r\n" );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, "---- Comunication OK!!! ---- \r\n" );
    }

    moisture_cfg( &moisture, MOISTURE_OUTPUT_GAIN_x16, MOISTURE_DEFAULT_OFFSET, MOISTURE_CLOCK_DIVIDERS_x10 );
    moisture_default_cfg( &moisture );

    log_printf( &logger, " --- Calibration start --- \r\n" );
    moisture_cal( &moisture );
    Delay_ms( 1000 );

    log_printf( &logger, " --- Calibration finishing --- \r\n" );
}

void application_task ( void )
{
    moisture_data = moisture_get_data( &moisture  );
    log_printf( &logger, " Moisture data : %d \r\n", moisture_data );
    Delay_ms( 500 );
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
