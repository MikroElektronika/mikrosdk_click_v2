/*!
 * \file 
 * \brief Proximity 6 Click example
 * 
 * # Description
 * This application demonstrates the use of Proximity 6 Click board by reading
 * and displaying the raw data measurements from 4 photodiode channels.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and performs the Click default configuration.
 * 
 * ## Application Task
 * Reads the raw data measurements from 4 photodiode channels and displays the results
 * on the USB UART every 200ms approximately.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity6.h"

// ------------------------------------------------------------------ VARIABLES

static proximity6_t proximity6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity6_cfg_t proximity6_cfg;  /**< Click config object. */

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
    proximity6_cfg_setup( &proximity6_cfg );
    PROXIMITY6_MAP_MIKROBUS( proximity6_cfg, MIKROBUS_1 );
    if ( PROXIMITY6_ERROR == proximity6_init( &proximity6, &proximity6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY6_ERROR == proximity6_default_cfg ( &proximity6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    proximity6_data_t axis_data;
    if ( PROXIMITY6_OK == proximity6_read_data( &proximity6, &axis_data ) )
    {
        log_printf( &logger, " X1: %u\r\n", axis_data.val_x1 );
        log_printf( &logger, " X2: %u\r\n", axis_data.val_x2 );
        log_printf( &logger, " Y1: %u\r\n", axis_data.val_y1 );
        log_printf( &logger, " Y2: %u\r\n\n", axis_data.val_y2 );
        Delay_ms ( 200 );
    }
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
