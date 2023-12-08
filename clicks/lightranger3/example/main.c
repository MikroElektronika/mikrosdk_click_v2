/*!
 * \file 
 * \brief LightRanger3 Click example
 * 
 * # Description
 * This app precisely measure distance without making actual contact.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and configuration chip.
 * 
 * ## Application Task  
 * Includes measurements, reads distance, and logs distance to USBUART for every 300 ms.
 * Distance measurement at distances ranging from 100 mm to 2000 mm.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lightranger3.h"

// ------------------------------------------------------------------ VARIABLES

static lightranger3_t lightranger3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger3_cfg_t cfg;
    uint8_t init_status;

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

    lightranger3_cfg_setup( &cfg );
    LIGHTRANGER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger3_init( &lightranger3, &cfg );

    init_status = lightranger3_device_init( &lightranger3 );

    if ( init_status == 0 )
    {
        log_printf( &logger, " --- Device init successfully --- \r\n " );
    }
    else
    {
        log_printf( &logger, " ---  Device init error --- \r\n " );
    }
}

void application_task ( void )
{
    uint16_t distance;

    lightranger3_take_single_measurement( &lightranger3 );
    
    distance = lightranger3_get_distance( &lightranger3 );

    log_printf( &logger, "Distance = %u mm \r\n ", distance );

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
