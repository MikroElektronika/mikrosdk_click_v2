/*!
 * \file 
 * \brief Magneticlinear Click example
 * 
 * # Description
 * This application reads magnetics linear data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Device initialization.
 * 
 * ## Application Task  
 * Reads magnetic linear data and logs it to USB UART every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneticlinear.h"

// ------------------------------------------------------------------ VARIABLES

static magneticlinear_t magneticlinear;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneticlinear_cfg_t cfg;

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

    magneticlinear_cfg_setup( &cfg );
    MAGNETICLINEAR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneticlinear_init( &magneticlinear, &cfg );
}

void application_task ( void )
{
    uint16_t magnetic_data;
    
    magnetic_data = magneticlinear_read_data( &magneticlinear );

    log_printf( &logger, " Magnetic Linear data : %u\r\n", magnetic_data );
    Delay_ms( 500 );
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
