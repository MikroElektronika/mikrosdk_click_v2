/*!
 * \file 
 * \brief HallCurrent5 Click example
 * 
 * # Description
 * The demo application reads ADC value and current value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device and ADC Init.
 * 
 * ## Application Task  
 * Reads current value in mA and this data logs to USBUART every 500ms.
 * 
 * *note:* 
 * Before the start of the program you have to set the starting voltage on AN pin.
 * First, measure the voltage in mV on AN pin, when electronic load isn't connected to the Click board, 
 * and pass that value as an input parameter of the voltage initialization function.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent5.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent5_t hallcurrent5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent5_cfg_t cfg;

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

    hallcurrent5_cfg_setup( &cfg );
    HALLCURRENT5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent5_init( &hallcurrent5, &cfg );

    // CLICK INIT
    hallcurrent5_set_init_voltage( &hallcurrent5, 450 );
    Delay_100ms();
}

void application_task ( void )
{
    float current;
  
    current = hallcurrent5_get_current( &hallcurrent5 );

    log_printf( &logger, " Current : %f \r\n", current );

    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
