/*!
 * \file 
 * \brief Ambient4 Click example
 * 
 * # Description
 * This application is a light intensity-sensing and measuring.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device and power ON chip and set resolution mode.
 * 
 * ## Application Task  
 * Read ambient light in [lx] and logs data to USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient4.h"

// ------------------------------------------------------------------ VARIABLES

static ambient4_t ambient4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient4_cfg_t cfg;

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

    ambient4_cfg_setup( &cfg );
    AMBIENT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient4_init( &ambient4, &cfg );
    
    ambient4_device_reset( &ambient4 );
    Delay_ms( 1000 );
    ambient4_default_cfg ( &ambient4 );
    
}

void application_task ( void )
{
    uint16_t read_value;
    
    read_value = ambient4_read_data( &ambient4 );
    log_printf( &logger, " Ambient light: %d lx\r\n", read_value );
    Delay_ms( 1000 );
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
