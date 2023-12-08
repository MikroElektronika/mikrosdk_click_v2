/*!
 * \file 
 * \brief No2 Click example
 * 
 * # Description
 * This application measures NO2.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and device configuration.
 * 
 * ## Application Task  
 * Gets NO2 (Nitrogen dioxide) data as ppm value and logs to USBUART every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "no2.h"

// ------------------------------------------------------------------ VARIABLES

static no2_t no2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    no2_cfg_t cfg;

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

    no2_cfg_setup( &cfg );
    NO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    no2_init( &no2, &cfg );

    no2_default_cfg( &no2 );

    log_printf( &logger, "NO2 is initialized \r\n" );
    Delay_ms( 300 );
}

void application_task ( void )
{
    float no2_value;

    no2_value = no2_get_no_2_ppm( &no2 );
    log_printf( &logger, "NO2 value : %.2f ppm \r\n", no2_value );
    Delay_ms( 500 );
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
