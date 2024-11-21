/*!
 * @file main.c
 * @brief Step Down 12 Click example
 *
 * # Description
 * This example demonstrates the use of Step Down 12 Click board by
 * changing the output voltage every 3 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Changes the output voltage every 3 seconds from MAX (5.5V) to MIN (1.05V) in steps of 0.5V
 * and displays the currently set voltage output value on the USB UART. It also monitors
 * the power good fault indication.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepdown12.h"

static stepdown12_t stepdown12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown12_cfg_t stepdown12_cfg;  /**< Click config object. */

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
    stepdown12_cfg_setup( &stepdown12_cfg );
    STEPDOWN12_MAP_MIKROBUS( stepdown12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown12_init( &stepdown12, &stepdown12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepdown12_default_cfg ( &stepdown12 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static float vout = STEPDOWN12_VOUT_MAX;

    if ( !stepdown12_get_pg_pin ( &stepdown12 ) )
    {
        log_error( &logger, " Power Good Fault - Vout is below nominal regulation\r\n" );
    }

    if ( STEPDOWN12_OK == stepdown12_set_vout ( &stepdown12, vout ) )
    {
        log_printf( &logger, " Vout: %.3f V\r\n\n", vout );
        vout -= 0.5;
        if ( vout < STEPDOWN12_VOUT_MIN )
        {
            vout = STEPDOWN12_VOUT_MAX;
        }
    }
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
