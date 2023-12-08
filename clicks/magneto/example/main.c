/*!
 * \file 
 * \brief Magneto Click example
 * 
 * # Description
 * MAGNETO Click carries contactless magnetic angle position sensor which delivers precise angle measurements down to 0.05º in 14-bit resolution.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * Magneto Click communicates with register via SPI by write and read from register and calculate float angle value. 
 * Results are being sent to the UART Terminal where you can track their changes. 
 * All data logs on USB UART for aproximetly every 2 sec.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneto.h"

float angle_value;

// ------------------------------------------------------------------ VARIABLES

static magneto_t magneto;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    magneto_cfg_setup( &cfg );
    MAGNETO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto_init( &magneto, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----- MAGNETO Click ---- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    if ( magneto_get_state( &magneto ) != 1 )
    {
        log_printf( &logger, " -- Initialization done --\r\n" );
    }
    else
    {
        log_printf( &logger, " -------- ERROR ! --------\r\n" );
    }

    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    angle_value = magneto_get_angle( &magneto );
    log_printf( &logger, "  [ANGLE] : %0.3f \r\n", angle_value );
    
    Delay_ms ( 500 );
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
