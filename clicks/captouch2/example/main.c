/*!
 * \file 
 * \brief CapTouch2 Click example
 * 
 * # Description
 * The demo application shows the button reading and checking.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Reset device and settings the click in the default configuration.
 * 
 * ## Application Task  
 * Calls function to check touch detection (is interrupt occured) and shows message on
 * USB UART on which input touch is detected or on which input touch is released. 
 * Also turns on LED on which linked input interrupt occured.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "captouch2.h"

// ------------------------------------------------------------------ VARIABLES

static captouch2_t captouch2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch2_cfg_t cfg;

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

    captouch2_cfg_setup( &cfg );
    CAPTOUCH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch2_init( &captouch2, &cfg );

    captouch2_reset( &captouch2 );
    Delay_ms( 200 );
    captouch2_default_cfg( &captouch2 );
    Delay_ms( 100 );
    log_info( &logger, ">> Cap Touch 2 is initialized " );
}

void application_task ( void )
{
    uint8_t cnt;
    uint8_t sensor_results[ 6 ];

    captouch2_detect_touch( &captouch2, &sensor_results[ 0 ] );
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( sensor_results[ cnt ] == 1 )
        {
            log_printf( &logger, "Input %d is touchedr\r\n", cnt + 1 );
        }
        else if ( sensor_results[ cnt ] == 2 )
        {
            log_printf( &logger, "Input %d is released\r\n", cnt + 1 );
        }
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
