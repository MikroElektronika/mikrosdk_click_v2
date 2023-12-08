/*!
 * @file main.c
 * @brief Current 4 Click Example.
 *
 * # Description
 * This example showcases the ability of the Current 4 Click board.
 * It configures Host MCU for communication and reads the voltage 
 * of AN pin and calculates current on load output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of the communication modules(ADC and UART).
 *
 * ## Application Task
 * In span on 500ms reads voltage and calculates the current on load.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current4.h"

static current4_t current4;   /**< Current 4 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current4_cfg_t current4_cfg;  /**< Click config object. */

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
    current4_cfg_setup( &current4_cfg );
    CURRENT4_MAP_MIKROBUS( current4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == current4_init( &current4, &current4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current4_load_current = 0;

    if ( ADC_ERROR != current4_read_load_current ( &current4, &current4_load_current ) ) 
    {
        log_printf( &logger, " > Load current : %.2f[A]\r\n", current4_load_current );
        log_printf( &logger, "**********************\r\n" );
    }

    Delay_ms( 500 );
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
