/*!
 * \file 
 * \brief HDC1000 Click example
 * 
 * # Description
 * Demo application code is used for measuring temperature and humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * AppInit is used for Logger and Click initialization.
 * 
 * ## Application Task  
 * This is an example which demonstrates the usage of HDC1000 Click board.
 * HDC1000 measure temperature and humidity, and calculate dewpoint value from the HDC1000 sensor.
 * 
 * \author Mihajlo Djordevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hdc1000.h"

// ------------------------------------------------------------------ VARIABLES

static hdc1000_t hdc1000;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hdc1000_cfg_t cfg;

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

    hdc1000_cfg_setup( &cfg );
    HDC1000_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hdc1000_init( &hdc1000, &cfg );
    
    log_printf( &logger, "-- Configurating --\r\n" );
    hdc1000_default_cfg( &hdc1000 );
    Delay_ms ( 100 );
    log_printf( &logger, "-- Start measurement --\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void )
{
    float humidity;
    float temperature;
    
    temperature = hdc1000_get_temperature_data( &hdc1000 );
    log_printf( &logger, " Temperature : %0.2f degC\r\n", temperature );
    
    humidity = hdc1000_get_humidity_data( &hdc1000 );
    log_printf( &logger, " Humidity    : %0.2f %%\r\n", humidity );

    log_printf( &logger, "-----------------------\r\n" );

    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
