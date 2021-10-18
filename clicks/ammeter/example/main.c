/*!
 * \file 
 * \brief Ammeter Click example
 * 
 * # Description
 * Demo app measures and displays current by using Ammeter click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI, LOG and click drivers.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the Ammeter click by 
 * measuring amperage in miliampers. Ammeter click board can be used to saftly 
 * measure current up to 1A both AC and DC, in the case of AC, 
 * for peak to peak value.
 * 
 * *note:* 
 * It is important to notice that this click board has its' own electronic 
 * circuit, and may not be powered from the same source which we are measuring.
 * Result will not be correct in that case.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ammeter.h"

// ------------------------------------------------------------------ VARIABLES

static ammeter_t ammeter;
static log_t logger;
static float amperage;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ammeter_cfg_t cfg;

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

    ammeter_cfg_setup( &cfg );
    AMMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ammeter_init( &ammeter, &cfg );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Ammeter  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void )
{
    amperage = ammeter_amperage( &ammeter );
    log_printf( &logger, " Current: %.2f mA\r\n", amperage );
    
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 1000 );
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
