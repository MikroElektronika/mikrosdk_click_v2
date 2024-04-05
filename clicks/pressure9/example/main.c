/*!
 * \file 
 * \brief Pressure9 Click example
 * 
 * # Description
 * The demo application displays the pressure and temperature 
 * measurement using Pressure 9 click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization the driver, test comunication, and performs the click
 * default configuration.
 *
 * ## Application Task
 * Reads Temperature data in [C] and Pressure data in [mBar] and this 
 * data logs to the USB UART every 2 sec.
 *
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure9.h"

// ------------------------------------------------------------------ VARIABLES

static pressure9_t pressure9;
static log_t logger;

static float temperature;
static float pressure;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure9_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    //  Click initialization.
    pressure9_cfg_setup( &cfg );
    PRESSURE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure9_init( &pressure9, &cfg );
    Delay_ms ( 100 );

    // Test comunication
    uint8_t product_id = 0;
    pressure9_generic_read( &pressure9, PRESSURE9_REG_PRODUCT_ID, &product_id, 1 );
    if ( PRESSURE9_PRODUCT_ID != product_id )
    {
        log_error( &logger, "Read product ID." );
        for ( ; ; );
    }

    pressure9_default_cfg( &pressure9 );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    pressure = pressure9_get_pressure_data( &pressure9 );
    log_printf( &logger, " Pressure: %.2f mBar\r\n", pressure );

    temperature = pressure9_get_temperature_data( &pressure9 );
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
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
