/*!
 * \file 
 * \brief SOLAR ENERGY Click example
 * 
 * # Description
 * This application charge the batery when is empty.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - GPIO and start to write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Solar Energy Click board.
 * The following example will charge the battery if it is empty, and stop charging
 * when the battery is full. When battery full status is detected, the device is
 * disabled, but will check battery status every 10 seconds.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "solarenergy.h"

// ------------------------------------------------------------------ VARIABLES

static solarenergy_t solarenergy;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    solarenergy_cfg_t cfg;

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

    solarenergy_cfg_setup( &cfg );
    SOLARENERGY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    solarenergy_init( &solarenergy, &cfg );

    log_printf( &logger, "   Initialization   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, " Charge the battery \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    if ( solarenergy_check_indicator( &solarenergy ) )
    {
        solarenergy_charge_disable( &solarenergy );
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
    else
    {
        solarenergy_charge_enable( &solarenergy );
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
