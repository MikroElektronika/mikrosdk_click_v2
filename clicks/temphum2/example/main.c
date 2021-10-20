/*!
 * \file 
 * \brief TempHum2 Click example
 * 
 * # Description
 * This application measures temperature and humidity. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, set work mode and Heater
 * 
 * ## Application Task  
 * Reads temperature and humidity and logs values on usbuart for every 500ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum2.h"

// ------------------------------------------------------------------ VARIABLES

static temphum2_t temphum2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum2_cfg_t cfg;

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

    temphum2_cfg_setup( &cfg );
    TEMPHUM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum2_init( &temphum2, &cfg );

    temphum2_default_cfg( &temphum2 );
}

void application_task ( void )
{
    float data_buffer[ 2 ];
    
    temphum2_get_measurement( &temphum2, &data_buffer[ 0 ] );
    
    log_printf( &logger, " --- Temperature : %.2f C \r\n ", data_buffer[ 0 ] );
    log_printf( &logger, " --- Humidity : %.2f RH \r\n ", data_buffer[ 1 ] );
    
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
