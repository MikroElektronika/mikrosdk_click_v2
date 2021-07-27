/*!
 * \file 
 * \brief HeartRate6 Click example
 * 
 * # Description
 * The example demonstrates the use of Heart rate 6 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes interface and performs the device configuration and reset.
 * 
 * ## Application Task  
 * Waits until measurement cycle is finished and data is ready for reading. 
 * Then reads the LED data and performs the data plotting on USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate6.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate6_t heartrate6;
static log_t logger;

static uint16_t led_data_off;
static uint16_t led_data_on;
static uint8_t counter = 200;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heartrate6_cfg_setup( &cfg );
    HEARTRATE6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate6_init( &heartrate6, &cfg );
    Delay_ms( 500 );

    heartrate6_default_cfg( &heartrate6 );
    log_printf( &logger, " Heart rate 6 is initialized. \r\n");
    Delay_ms( 500 );
}

void application_task ( void )
{
    heartrate6_wait_measure( &heartrate6 );
    
    heartrate6_get_data( &heartrate6,  &led_data_off, &led_data_on );
    
    counter++;
    if ( led_data_off < 200 )
    {
        log_printf( &logger, "%u;\r\n", led_data_on );
        counter = 200;
    }
    else if ( counter > 200 )
    {
        log_printf( &logger, "Please place your index finger on the sensor.\r\n" );
        counter = 0;
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
