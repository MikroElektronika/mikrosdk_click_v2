/*!
 * \file 
 * \brief AirQuality3 Click example
 * 
 * # Description
 * The demo application shows air quality measurement.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * Call the procedure the wakeup function of the chip.
 * 
 * ## Application Task  
 * Reads CO2 and TVOC value in the air and logs this data on the USBUART.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "airquality3.h"

// ------------------------------------------------------------------ VARIABLES

static airquality3_t airquality3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality3_cfg_t cfg;

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

    airquality3_cfg_setup( &cfg );
    AIRQUALITY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality3_init( &airquality3, &cfg );

    // Wake-up click procedure

    airquality3_set_power( &airquality3, AIRQUALITY3_POWER_STATE_ON );
    airquality3_hardware_reset( &airquality3 );
    airquality3_app_function( &airquality3, AIRQUALITY3_APP_START );

    airquality3_default_cfg( &airquality3 );

    Delay_ms ( 500 );
    log_info( &logger, "---- Start measurement ----" );
}

void application_task ( void )
{
    airquality3_air_data_t air_data;

    //  Task implementation.

    airquality3_get_co2_and_tvoc ( &airquality3, &air_data );
    log_printf( &logger, "\r\n---- AirQuality data ----\r\n" );
    log_printf( &logger, ">> CO2 data is %d ppm.\r\n", air_data.co2 );
    log_printf( &logger, ">> TVOC data is %d ppb.\r\n", air_data.tvoc );

    Delay_1sec( );
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
