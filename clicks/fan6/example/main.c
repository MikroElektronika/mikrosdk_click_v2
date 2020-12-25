/*!
 * \file 
 * \brief Fan6 Click example
 * 
 * # Description
 * This demo application reads tachometer value which is calculated as rpm value, and reads
 * temperature of external diode in celsius value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device configuration.
 * 
 * ## Application Task  
 * Reads tachometer value which is calculated as rpm value, and reads
 * temperature of external diode in celsius value. All this results logs on USB UART. Repeats operation
 * every 500 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fan6.h"

// ------------------------------------------------------------------ VARIABLES

static fan6_t fan6;
static log_t logger;

static uint32_t tachometer;
static uint8_t duty_cycle = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fan6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fan6_cfg_setup( &cfg );
    FAN6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan6_init( &fan6, &cfg );
    
    fan6_enable_device( &fan6, 1 );
    Delay_ms( 500 );
    
    fan6_default_cfg( &fan6 );
    tachometer = 0;
}

void application_task ( void )
{
    float temp_diode;

    temp_diode = fan6_get_temperature( &fan6, FAN6_INTERNAL_TEMP_READ_REG );
    log_printf( &logger, "Temperature of DIODE is: %f - Cels \r\n", temp_diode );
    
    fan6_set_pwm_mode( &fan6, duty_cycle );
    
    duty_cycle += 5;
    
    tachometer = fan6_read_tachometer( &fan6 );
    log_printf( &logger, "Tachometer value is: %lu rpm \r\n", tachometer );
    log_printf( &logger, "---------------------------------------- \r\n", tachometer );
    
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
