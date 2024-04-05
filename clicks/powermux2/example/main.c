/*!
 * @file main.c
 * @brief PowerMux2 Click example
 *
 * # Description
 * This library contains API for the Power MUX 2 Click driver. 
 * The Power MUX 2 operates in automatic switchover mode with a priority prioritizing supply 1 
 * when present and quickly switches to supply 2 when supply 1 drops below approximately 6V.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The application init consist of initialization of SPI driver and logger.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Power MUX 2 Click board™. 
 * In this example, we set the resistance of the 100kΩ 
 * for the output current limit of approximately 1.23A 
 * and lower the resistance to 50kΩ, which fits the current limit of 2.25 A. 
 * Results are sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "powermux2.h"

static powermux2_t powermux2;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    powermux2_cfg_t powermux2_cfg;  /**< Click config object.  */

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

    powermux2_cfg_setup( &powermux2_cfg );
    POWERMUX2_MAP_MIKROBUS( powermux2_cfg, MIKROBUS_1 );
    err_t init_flag  = powermux2_init( &powermux2, &powermux2_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " Resistance    ~ 100 kOhm \r\n" );
    log_printf( &logger, " Current Limit ~   1.23 A \r\n" );
    powermux2_set_resistance( &powermux2, 100 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " Resistance    ~  50 kOhm \r\n" );
    log_printf( &logger, " Current Limit ~   2.25 A \r\n" );
    powermux2_set_resistance( &powermux2, 50 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
