/*!
 * @file main.c
 * @brief DIGIPOT8 Click example
 *
 * # Description
 * This example demonstrates the use of DIGI POT 8 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and makes an initial log.
 *
 * ## Application Task
 * Iterates through the entire wiper range and sets all wipers to 
 * the iterator value each second. 
 * The current wiper position will be displayed on USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot8.h"

static digipot8_t digipot8;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot8_cfg_t digipot8_cfg;  /**< Click config object. */

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

    digipot8_cfg_setup( &digipot8_cfg );
    DIGIPOT8_MAP_MIKROBUS( digipot8_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot8_init( &digipot8, &digipot8_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t cnt = DIGIPOT8_WIPER_POSITION_MIN; cnt < DIGIPOT8_WIPER_POSITION_MAX; cnt += 5 )
    {
        digipot8_set_wiper_1 ( &digipot8, cnt );
        digipot8_set_wiper_2 ( &digipot8, cnt );
        digipot8_set_wiper_3 ( &digipot8, cnt );
        digipot8_set_wiper_4 ( &digipot8, cnt );
        digipot8_set_wiper_5 ( &digipot8, cnt );
        digipot8_set_wiper_6 ( &digipot8, cnt );
        log_printf( &logger, " * All wipers position set to %d *\r\n", ( uint16_t ) cnt );
        
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
