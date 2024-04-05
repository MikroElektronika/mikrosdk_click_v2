/*!
 * @file main.c
 * @brief Buck 19 Click example
 *
 * # Description
 * This example demonstrates the use of Buck 19 click board by
 * iterating through the entire output voltage range.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the output voltage every 3 seconds and displays on the USB UART
 * the currently set voltage output value.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck19.h"

static buck19_t buck19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck19_cfg_t buck19_cfg;  /**< Click config object. */

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
    buck19_cfg_setup( &buck19_cfg );
    BUCK19_MAP_MIKROBUS( buck19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck19_init( &buck19, &buck19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK19_ERROR == buck19_default_cfg ( &buck19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static float vout = BUCK19_VOUT_MIN;
    if ( BUCK19_OK == buck19_set_vout ( &buck19, vout ) )
    {
        log_printf ( &logger, " VOUT: %.2f V\r\n\n", vout );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    vout += 0.5f;
    if ( vout > ( BUCK19_VOUT_MAX + BUCK19_FLOAT_COMPARE_TOLERANCE ) )
    {
        vout = BUCK19_VOUT_MIN;
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
