/*!
 * \file 
 * \brief Manometer2 Click example
 * 
 * # Description
 * This application is digital pressure sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * initialization Manometer 2 sensor MS5525DSO-SB001GS by read coeffitient value
 * and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Manometer 2 Click board.
 * Measured pressure and temperature value from sensor, calculate pressure [ PSI ] and temperature [ �C ],
 * results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 3 sec when the data value changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "manometer2.h"

// ------------------------------------------------------------------ VARIABLES

static manometer2_t manometer2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    manometer2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    manometer2_cfg_setup( &cfg );
    MANOMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    manometer2_init( &manometer2, &cfg );

    manometer2_read_coef( &manometer2 );
    log_printf( &logger, "        Initialization \r\n" );
    log_printf( &logger, "----------------------------- \r\n" );
    Delay_100ms( );
}

void application_task (  )
{
    float temperature;
    float pressure;

    temperature = manometer2_get_temperature( &manometer2, MANOMETER2_CONVERT_4096 );
    Delay_10ms( );

    pressure = manometer2_get_pressure( &manometer2, MANOMETER2_CONVERT_4096 );
    Delay_10ms( );

    log_printf( &logger, " Pressure :  %.2f PSI \r\n", pressure );
    log_printf( &logger, " Temperature: %.2f C \r\n", temperature );
    log_printf( &logger, "----------------------------- \r\n" );

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
