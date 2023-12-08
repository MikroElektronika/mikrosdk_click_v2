/*!
 * \file 
 * \brief Lem Click example
 * 
 * # Description
 * Demo app measures and displays current by using LEM click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI, LOG and click drivers.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the LEM click by measuring 
 * current passing through the conductor placed through the hole on the sensor.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lem.h"

// ------------------------------------------------------------------ VARIABLES

static lem_t lem;
static log_t logger;
static float current;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lem_cfg_t cfg;

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

    lem_cfg_setup( &cfg );
    LEM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lem_init( &lem, &cfg );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      LEM Click      \r\n" );
    log_printf( &logger, "---------------------\r\n" );
}

void application_task ( void )
{
    current = lem_get_current( &lem, LEM_MILIAMP_COEF );
    
    log_printf( &logger, " Current : %.2f mA \r\n", current );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 1000 );
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
