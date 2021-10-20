/*!
 * \file 
 * \brief Color6 Click example
 * 
 * # Description
 *  Reads values from the X / Y / Z channel and 
 *  converts to ee (input light irradiance regarding to the photodiode�s area
 *  within the conversion time interval) data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 *  Initializes and configuration device for measurement.
 * 
 * ## Application Task  
 *  Reads values from the X / Y / Z channel and 
 *  converts to ee (input light irradiance regarding to the photodiode�s area
 *  within the conversion time interval) data. 
 *  This data logs on USB UART every 2 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color6.h"

// ------------------------------------------------------------------ VARIABLES

static color6_t color6;
static log_t logger;

uint16_t x_data = 0;
uint16_t y_data = 0;
uint16_t z_data = 0;
float ee_data;
float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    color6_cfg_t cfg;

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

    color6_cfg_setup( &cfg );
    COLOR6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color6_init( &color6, &cfg );

    color6_software_reset( &color6 );
    color6_default_cfg ( &color6 );
    color6_go_to_measurement_mode( &color6 );
}

void application_task ( void )
{
    x_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_X_CHANNEL );
    log_printf( &logger, " Channel X :  %d \r\n ", x_data );

    ee_data = color6_converting_to_ee( &color6, COLOR6_MREG_MEASUREMENT_X_CHANNEL, x_data);
    log_printf( &logger, " Ee X channel data:   %f \r\n ", ee_data );

    y_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_Y_CHANNEL );
    log_printf( &logger, " Channel Y :  %d\r\n ", y_data );

    ee_data = color6_converting_to_ee( &color6, COLOR6_MREG_MEASUREMENT_Y_CHANNEL, y_data);
    log_printf( &logger, " Ee Y channel data:   %f \r\n", ee_data );

    z_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_Z_CHANNEL );
    log_printf( &logger, " Channel Z :  %d\r\n ", z_data );

    ee_data = color6_converting_to_ee( &color6, COLOR6_MREG_MEASUREMENT_Z_CHANNEL, z_data);
    log_printf( &logger, " Ee Z channel data:   %f\r\n ", ee_data );

    temperature = color6_get_temperature( &color6 );
    log_printf( &logger, " Temperature :  %f\r\n ", temperature );

    Delay_ms( 2000 );
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
