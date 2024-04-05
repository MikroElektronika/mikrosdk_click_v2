/*!
 * \file 
 * \brief Proximity 3 Click example
 * 
 * # Description
 * This application reads the raw ALS and proximity data from
 * Proximity 3 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and performs the click default configuration.
 * 
 * ## Application Task  
 * Reads the raw ALS and proximity data and displays the results on the USB UART
 * every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity3.h"

// ------------------------------------------------------------------ VARIABLES

static proximity3_t proximity3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity3_cfg_t proximity3_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    proximity3_cfg_setup( &proximity3_cfg );
    PROXIMITY3_MAP_MIKROBUS( proximity3_cfg, MIKROBUS_1 );
    if ( PROXIMITY3_ERROR == proximity3_init( &proximity3, &proximity3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY3_ERROR == proximity3_default_cfg ( &proximity3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t proximity = 0;
    uint16_t als = 0;
    
    proximity = proximity3_read_proximity( &proximity3 );
    log_printf( &logger, " Proximity: %u\r\n", proximity );

    als = proximity3_read_als( &proximity3 );
    log_printf( &logger, " ALS: %u\r\n", als );

    log_printf( &logger, "-----------------\r\n" );
    Delay_ms ( 500 );
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
