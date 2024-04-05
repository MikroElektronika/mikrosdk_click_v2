/*!
 * \file 
 * \brief Nano Power Click example
 * 
 * # Description
 * This aplication performs control of the device's voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver.
 * 
 * ## Application Task  
 * Turns device on for 5 seconds and than turns device off for 10 seconds,
 * then the output voltage starts to fall.
 * When input voltage rises from 0.8V to 5.5V,
 * the output voltage rises from 5.1V to 5.25V.
 * When input voltage is less than 0.8V, the output voltage is less than 5V.
 * 
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nanopower.h"

// ------------------------------------------------------------------ VARIABLES

static nanopower_t nanopower;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanopower_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    nanopower_cfg_setup( &cfg );
    NANOPOWER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower_init( &nanopower, &cfg );
}

void application_task ( void )
{
    log_printf(&logger,"Device enabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_ENABLE_DEVICE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf(&logger,"Device disabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_DISABLE_DEVICE );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
