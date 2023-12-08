/*!
 * \file 
 * \brief Boost 3 Click example
 * 
 * # Description
 * Boost 3 click provides an adjustable output voltage through the onboard
 * potentiometer. The chip is a 700-kHz pulse-width modulating (PWM) step-up 
 * converter with an 85-V switch FET with an input ranging from 2.5 V to 5.5 V. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO and LOG structures, and set CS pin as output.
 * 
 * ## Application Task  
 * Turns ON the device for 10 seconds and then turns it OFF for 3 seconds.
 * It also displays appropriate messages on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost3.h"

// ------------------------------------------------------------------ VARIABLES

static boost3_t boost3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost3_cfg_t cfg;

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

    boost3_cfg_setup( &cfg );
    BOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost3_init( &boost3, &cfg );
}

void application_task ( void )
{
    boost3_dev_enable( &boost3, BOOST3_ENABLE );
        
    log_printf( &logger, "The click board is enabled!\r\n" );
    log_printf( &logger, "Please use the on-board potentiometer" );
    log_printf( &logger, " to adjust the voltage output.\r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 10000 );
    
    boost3_dev_enable( &boost3, BOOST3_DISABLE );
    log_printf( &logger, "The click board is turned OFF!\r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 3000 );
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
