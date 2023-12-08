/*!
 * \file 
 * \brief Tilt 2 Click example
 * 
 * # Description
 * This app detection tilt.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * Tilt detection, if the tilt is detected, the message is logs on USBUART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tilt2.h"

// ------------------------------------------------------------------ VARIABLES

static tilt2_t tilt2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    tilt2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    tilt2_cfg_setup( &cfg );
    TILT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tilt2_init( &tilt2, &cfg );
}

void application_task ( void )
{
    uint8_t tilt;
    
    tilt = tilt2_tilt_detection( &tilt2 );
    if ( tilt == TILT2_TILT_DETECTION )
    {
        log_printf( &logger, " Tilt detection.. \r\n" );
        Delay_ms( 300 );
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
