/*!
 * @file main.c
 * @brief Hall Current 16 Click example
 *
 * # Description
 * This example demonstrates the use of Hall Current 16 Click board 
 * by reading and displaying the current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The app reads the current measurements [A] and displays the results.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent16.h"

static hallcurrent16_t hallcurrent16;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent16_cfg_t hallcurrent16_cfg;  /**< Click config object. */

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
    hallcurrent16_cfg_setup( &hallcurrent16_cfg );
    HALLCURRENT16_MAP_MIKROBUS( hallcurrent16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hallcurrent16_init( &hallcurrent16, &hallcurrent16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( HALLCURRENT16_ERROR == hallcurrent16_default_cfg ( &hallcurrent16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------- \r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    static float current = 0.0;
    if ( HALLCURRENT16_OK == hallcurrent16_get_current( &hallcurrent16, &current ) )
    {
        log_printf( &logger, " Current : %.3f A \r\n", current );
    }
    log_printf( &logger, " -------------------- \r\n" );
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
