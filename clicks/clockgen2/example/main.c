/*!
 * \file 
 * \brief ClockGen2 Click example
 * 
 * # Description
 * This application enables generation of square waved clock signal in range from 260 kHz to 66,6 MHz
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialization.
 * 
 * ## Application Task  
 * Changes the prescaler and enables/disables the clock output.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "clockgen2.h"

// ------------------------------------------------------------------ VARIABLES

static clockgen2_t clockgen2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen2_cfg_t cfg;

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

    clockgen2_cfg_setup( &cfg );
    CLOCKGEN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen2_init( &clockgen2, &cfg );

    Delay_ms ( 100 );
}

void application_task ( void )
{
    //  Task implementation.

    char i;
     
     for ( i = 5; i< 8; i++ )
     {
       clockgen2_set_prescaler( &clockgen2, i );
       clockgen2_output_enable( &clockgen2, 1 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );

       clockgen2_output_enable( &clockgen2, 0 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );
     }
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
