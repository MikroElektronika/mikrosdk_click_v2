/*!
 * \file 
 * \brief Vacuum Click example
 * 
 * # Description
 * This application measuring absolute pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and calibration of the chip to start measuring.
 * 
 * ## Application Task  
 * Reads vacuum percentage that sensor reads.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vacuum.h"

// ------------------------------------------------------------------ VARIABLES

static vacuum_t vacuum;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vacuum_cfg_t cfg;

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

    vacuum_cfg_setup( &cfg );
    VACCUM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vacuum_init( &vacuum, &cfg );

    vacuum_calibration( &vacuum );
}

void application_task ( void )
{
    float vacuum_data;
    float vacuum_volt;
    float pressure;

    //  Task implementation.

    vacuum_volt = vacuum_get_voltage(  &vacuum );
    log_printf ( &logger, "Vacuum [V] : %.2f\r\n ", vacuum_volt );
    pressure = vacuum_get_pressure(  &vacuum );
    log_printf ( &logger, "Pressure [mBar] : %.2f V\r\n ", pressure );
    vacuum_data = vacuum_get_percentage_of_vacuum(  &vacuum );
    log_printf ( &logger, "Percentage of vacuum [%%] : %.2f : \r\n ", vacuum_data );
    log_printf ( &logger, "------------------------------------------\r\n " );
    Delay_ms( 300 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
