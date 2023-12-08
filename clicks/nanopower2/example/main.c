/*!
 * \file 
 * \brief Nano Power 2 Click example
 * 
 * # Description
 * This application logs the comparators output value on USBUART.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver.
 * 
 * ## Application Task  
 * Checks the comparator's output and logs output value on USBUART.
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nanopower2.h"

// ------------------------------------------------------------------ VARIABLES

static nanopower2_t nanopower2;
static log_t logger;

uint8_t out_check;
uint8_t out_check_prev;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanopower2_cfg_t cfg;

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
    nanopower2_cfg_setup( &cfg );
    NANOPOWER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower2_init( &nanopower2, &cfg );

    log_printf( &logger, "NANO POWER 2 is initialized\r\n" );
    out_check_prev = 2;
}

void application_task ( void )
{
    out_check = nanopower2_check_output( &nanopower2 );
    if ( out_check != out_check_prev )
    {
        log_printf( &logger, "OUT is: %d\r\n", ( uint16_t ) out_check );

        out_check_prev = out_check;
    }
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
