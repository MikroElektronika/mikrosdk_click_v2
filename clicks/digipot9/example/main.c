/*!
 * @file main.c
 * @brief DIGIPOT9 Click example
 *
 * # Description
 * This example demonstrates the use of DIGI POT 9 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and makes an initial log.
 *
 * ## Application Task
 * Iterates through the entire wiper range and sets both wipers to 
 * the iterator value once per second. 
 * The current wiper position will be displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot9.h"

static digipot9_t digipot9;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    digipot9_cfg_t digipot9_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    digipot9_cfg_setup( &digipot9_cfg );
    DIGIPOT9_MAP_MIKROBUS( digipot9_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot9_init( &digipot9, &digipot9_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    digipot9_default_cfg ( &digipot9 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint16_t cnt = DIGIPOT9_WIPER_ZERO_SCALE; cnt <= DIGIPOT9_WIPER_FULL_SCALE; cnt += 50 )
    {
        digipot9_set_wiper_1 ( &digipot9, cnt );
        digipot9_set_wiper_2 ( &digipot9, cnt );
        log_printf( &logger, " * Wipers position set to %u *\r\n", cnt );
        
        Delay_ms( 1000 );
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
