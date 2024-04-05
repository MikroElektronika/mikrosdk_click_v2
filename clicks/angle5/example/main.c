/*!
 * \file 
 * \brief Angle5 Click example
 * 
 * # Description
 * Angle 5 click is a magnetic rotational sensor. 
 * It communicates with the target microcontroller over SPI interface.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver.
 * 
 * ## Application Task  
 * Reads the angle position of the magnet and displays the results on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "angle5.h"

// ------------------------------------------------------------------ VARIABLES

static angle5_t angle5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle5_cfg_t cfg;

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

    angle5_cfg_setup( &cfg );
    ANGLE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle5_init( &angle5, &cfg );
}

void application_task ( void )
{
    float new_angle = 0;
    
    new_angle = angle5_read_angle_deg( &angle5 );
    log_printf( &logger, "Angle: %.2f\r\n", new_angle );

    Delay_ms ( 100 );
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
