/*!
 * @file main.c
 * @brief Hall Current 19 Click Example.
 *
 * # Description
 * This example demonstrates the use of Hall Current 19 Click board
 * by reading and displaying the current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and set the zero voltage reference.
 *
 * ## Application Task
 * The demo application reads the current measurements [A] and displays the results.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent19.h"

static hallcurrent19_t hallcurrent19;   /**< Hall Current 19 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent19_cfg_t hallcurrent19_cfg;  /**< Click config object. */

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
    hallcurrent19_cfg_setup( &hallcurrent19_cfg );
    HALLCURRENT19_MAP_MIKROBUS( hallcurrent19_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == hallcurrent19_init( &hallcurrent19, &hallcurrent19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Turn off the load current in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( HALLCURRENT19_OK == hallcurrent19_set_zero_ref( &hallcurrent19 ) )
    {
        log_printf( &logger, " Process complete!\r\n");
    }
    else
    {
        log_error( &logger, " Zero reference." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( HALLCURRENT19_OK == hallcurrent19_get_current ( &hallcurrent19, &voltage ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", voltage );
        Delay_ms ( 1000 );
    }
    if ( HALLCURRENT19_OCD_ACTIVE == hallcurrent19_get_oc1( &hallcurrent19 ) )
    {
        log_printf( &logger, " Current over 7A \r\n" );
    }
    if ( HALLCURRENT19_OCD_ACTIVE == hallcurrent19_get_oc2( &hallcurrent19 ) )
    {
        log_printf( &logger, " Current over 17.5A \r\n" );
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
