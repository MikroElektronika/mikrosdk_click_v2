/*!
 * \file 
 * \brief Shake2Wake Click example
 * 
 * # Description
 * This app shows the capabilities of the Shake2Wake click by
 * reading values of an accelerometer.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device and applies default settings.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the Shake2Wake click by
 * reading values of an accelerometer and logging them on USART terminal and, in case of an interrupt, it
 * raises voltage on the connector.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "shake2wake.h"

// ------------------------------------------------------------------ VARIABLES

static shake2wake_t shake2wake;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    shake2wake_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    shake2wake_cfg_setup( &cfg );
    SHAKE2WAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    shake2wake_init( &shake2wake, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "    Shake2Wake  Click     \r\n" );
    log_printf( &logger, "--------------------------\r\n" );

    shake2wake_default_cfg( &shake2wake );
}

void application_task ( void )
{
    float temperature;
    int16_t x_val;
    int16_t y_val;
    int16_t z_val;

    shake2wake_get_raw_data( &shake2wake, &x_val, &y_val, &z_val );
    temperature = shake2wake_read_temperature( &shake2wake );

    log_printf( &logger, "X axis: %d\r\n", x_val );
    log_printf( &logger, "Y axis: %d\r\n", y_val );
    log_printf( &logger, "Z axis: %d\r\n", z_val );
    log_printf( &logger, "Temperature: %f \r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
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
