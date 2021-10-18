/*!
 * \file 
 * \brief Pressure3 Click example
 * 
 * # Description
 * This application is digital barometric pressure sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device, set default configuration and start to write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Pressure 3 Click board.
     Measured pressure and temperature data from the DPS310 sensor on Pressure 3 click board.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 3 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure3.h"

// ------------------------------------------------------------------ VARIABLES

static pressure3_t pressure3;
static log_t logger;

static pressure3_coeff_t coeff_struct;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    pressure3_cfg_t cfg;

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

    pressure3_cfg_setup( &cfg );
    PRESSURE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure3_init( &pressure3, &cfg );
    pressure3_default_cfg( &pressure3 );
}

void application_task ( )
{
    float pressure;
    float temperature;

    pressure3_get_t_p_data( &pressure3, &temperature, &pressure, &coeff_struct );
    
    log_printf( &logger, " * Pressure: %.2f mbar * \r\n", pressure );
    log_printf( &logger, " * Temperature: %.2f C * \r\n", temperature );
    log_printf( &logger, " ----------------------- \r\n" );

    Delay_ms( 3000 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
