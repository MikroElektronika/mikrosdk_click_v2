/*!
 * \file 
 * \brief AcCurrent Click example
 * 
 * # Description
 * This application measures AC current through a conductor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * SPI driver and click initialization.
 * 
 * ## Application Task  
 * Reads the value of AC current and displays it on the USB UART.
 * 
 * ## NOTE
 * An appropriate AC Current sensor needs to be connected to the click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accurrent.h"

// ------------------------------------------------------------------ VARIABLES

static accurrent_t accurrent;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    accurrent_cfg_t cfg;

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
    accurrent_cfg_setup( &cfg );
    ACCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accurrent_init( &accurrent, &cfg );
}

void application_task ( void )
{
    float ac_current = 0;
    ac_current = accurrent_get_ma( &accurrent );
    log_printf( &logger, "Current value: %.3f mA\r\n", ac_current );
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
