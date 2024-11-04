/*!
 * \file 
 * \brief HallCurrent4 Click example
 * 
 * # Description
 * Demo application shows is reading current data in mA using Hall current 4 Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Reads Current value in mA and logs this data to USBUART every 1 sec.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent4.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent4_t hallcurrent4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent4_cfg_t cfg;

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

    hallcurrent4_cfg_setup( &cfg );
    HALLCURRENT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent4_init( &hallcurrent4, &cfg );
}

void application_task ( void )
{
    float current;

    current = hallcurrent4_get_current_data( &hallcurrent4 );

    log_printf( &logger, " >> Current value: %.2f mA\r\n", current );
    log_printf( &logger, " ------------------------- \r\n" );
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
