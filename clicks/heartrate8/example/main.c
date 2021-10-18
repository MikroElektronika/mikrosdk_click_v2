/*!
 * \file 
 * \brief HeartRate8 Click example
 * 
 * # Description
 * This example demonstrates the use of Hearth rate 8 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Performs the device reset, after which the device configuration can be performed. The device is configured to work in Single Measurement Mode with LED pulsing.
 * The driver which is selected is driver for the GREEN LED Data.
 * 
 * ## Application Task  
 * Sends command to start measurement cycle, then waits until measurement cycle is finished.
 * When measurement cycle is done, gets LED ON and LED OFF Data for the selected LED driver (GREEN or IR LED) and performs data
 * plotting on serial plotter every 35ms.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate8.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate8_t heartrate8;
static log_t logger;

static uint8_t int_check;
static uint16_t led_data_on;
static uint16_t led_data_off;
static uint32_t i;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void plot_res( uint16_t plot_data )
{
    log_printf( &logger, "%u,%u\n", plot_data, ++i );

    if ( i == 0xFFFFFFFF )
    {
        i = 0;
    }
    Delay_ms( 35 );
}

void log_res( )
{
    log_printf( &logger, "LED ON Data : %u      ", led_data_on );
    
    log_printf( &logger, "LED OFF Data : %u\n", led_data_off );
    
    Delay_ms( 100 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate8_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heartrate8_cfg_setup( &cfg );
    HEARTRATE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate8_init( &heartrate8, &cfg );
    heartrate8_default_cfg( &heartrate8 );
    i = 0;
}

void application_task ( void )
{
    heartrate8_start_measure( &heartrate8 );
    
    int_check = heartrate8_check_int( &heartrate8 );
    while ( int_check != HEARTRATE8_INT_ACTIVE )
    {
        int_check = heartrate8_check_int( &heartrate8 );
    }
    
    heartrate8_get_data( &heartrate8, HEARTRATE8_GREEN_DATA_GET, &led_data_on, &led_data_off );
    plot_res( led_data_on );
    int_check = heartrate8_int_clear( &heartrate8 );
    
    Delay_ms( 5 );
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
