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
 * Then reads the LED Data values and performs the data plotting on serial plot, or logging on uart.
 * 
 * *note:* 
 * Uart baud rate should be as high as possible, then data plotting will be better.
 * The new measurement cycle is started when command for measurement starting is sent, or when register 0x57 is read out.
 * Also the pressure on sensor must be same for the all measurement time, if we want to get the valid results.
 * This is very important to device can work properly.
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
static uint32_t i;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void plot_res( uint16_t plot_data )
{
    log_printf( &logger, "%u,%u\r\n", plot_data, ++i );

    if (i == 0xFFFFFFFF)
    {
        i = 0;
    }
}

void log_res()
{
    log_printf( &logger, "LED OFF Data : %u\r\n", led_data_off );

    log_printf( &logger, "LED ON Data : %u\r\n", led_data_on );
}

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
    Delay_ms( 200 );

    //  Click initialization.

    heartrate6_cfg_setup( &cfg );
    Delay_ms( 500 );
    HEARTRATE6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate6_init( &heartrate6, &cfg );
    Delay_ms( 500 );

    heartrate6_default_cfg( &heartrate6 );
    log_printf( &logger, " Heart rate 6 is initialized \r\n");
    i = 0;
    Delay_ms( 500 );
}

void application_task ( void )
{
    heartrate6_wait_measure( &heartrate6 );
    
    heartrate6_get_data( &heartrate6,  &led_data_off, &led_data_on );

    plot_res( led_data_on );
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
