/*!
 * \file 
 * \brief Proximity5 Click example
 * 
 * # Description
 * This application enables usage of the proximity and ablient light sensing.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configures the micro controller for communication
 * and initializes the click board. 
 * 
 * ## Application Task  
 * The proximity data is read from the sensor and it is printed
 * to the UART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity5.h"

// ------------------------------------------------------------------ VARIABLES

static proximity5_t proximity5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity5_cfg_t cfg;

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

    proximity5_cfg_setup( &cfg );
    PROXIMITY5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity5_init( &proximity5, &cfg );

    proximity5_default_cfg( &proximity5 );
}

void application_task ( void )
{
    //  Task implementation.

    uint16_t bff[ 4 ];

    proximity5_get_values( &proximity5, bff );
 
    log_printf( &logger, "PS1 %d  ", bff[ 0 ] );
    
    log_printf( &logger, "PS2 %d  ", bff[ 1 ] );
    
    log_printf( &logger, "PS3 %d \r\n\r\n", bff[ 2 ] );

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
