/*!
 * \file 
 * \brief Pressure8 Click example
 * 
 * # Description
 * This application reads pressure data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device and logger module, reset device and set PSI range.
 * 
 * ## Application Task  
 * Reads Pressure data and this data logs every 1 sec.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure8.h"

// ------------------------------------------------------------------ VARIABLES

static pressure8_t pressure8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure8_cfg_t cfg;

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

    pressure8_cfg_setup( &cfg );
    PRESSURE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure8_init( &pressure8, &cfg );

    pressure8_device_reset( &pressure8 );
    pressure8_set_psi_range( 0, 25 );
}

void application_task ( void )
{
    float pressure_data;
    
    pressure_data = pressure8_get_pressure( &pressure8, PRESSURE8_DATA_IN_mBar );
    log_printf( &logger, "--- Pressure data : %f mBar\r\n", pressure_data );

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
