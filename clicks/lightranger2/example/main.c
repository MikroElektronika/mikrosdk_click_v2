/*!
 * \file 
 * \brief LightRanger2 Click example
 * 
 * # Description
 * This example collects data from the sensor, calculates it, and then logs the 
 * results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver,
 * enable Vl6180X sensor, hardware reset and sets default configuration of
 * Vl6180X, also write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of LightRanger 2 Click board.
 * Measures the distance of the object from the sensor.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 1 sec when the data value changes.
 * 

 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lightranger2.h"

// ------------------------------------------------------------------ VARIABLES

static lightranger2_t lightranger2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger2_cfg_t cfg;

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

    lightranger2_cfg_setup( &cfg );
    LIGHTRANGER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger2_init( &lightranger2, &cfg );
    lightranger2_default_cfg( &lightranger2 );
    
    lightranger2_start_continuous( &lightranger2, 0 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint16_t distance;
    
    distance = lightranger2_get_range_continuous( &lightranger2 );
    Delay_ms( 10 );
    
    if ( distance )
    {
        log_printf( &logger, "Distance: %u mm \r\n", distance );
        Delay_ms( 100 );
    }
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
