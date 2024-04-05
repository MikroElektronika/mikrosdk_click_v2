/*!
 * @file main.c
 * @brief Charger 26 Click Example.
 *
 * # Description
 * This example demonstrates the use of Charger 26 click board by enabling the device
 * and then reading and displaying the charger status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the device, sets the output 
 * voltage to 4.2 V and charging current to 100 mA.
 *
 * ## Application Task
 * Tracking charging status, as soon as charging stops, device output is disabled.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "charger26.h"

static charger26_t charger26;   /**< Charger 26 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger26_cfg_t charger26_cfg;  /**< Click config object. */

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
    charger26_cfg_setup( &charger26_cfg );
    CHARGER26_MAP_MIKROBUS( charger26_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger26_init( &charger26, &charger26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger26_default_cfg ( &charger26 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Connect input power and battery. \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Enableing output. \r\n" );
    charger26_enable_output ( &charger26, CHARGER26_ENABLE_OUTPUT );
    
    while ( CHARGER26_PIN_STATE_LOW != charger26_get_chg_state( &charger26 ) )
    {
        log_printf( &logger, " Check connection. \r\n" );
        Delay_ms ( 1000 );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( CHARGER26_PIN_STATE_LOW == charger26_get_chg_state( &charger26 ) )
    {
        log_printf( &logger, " Battery is charging. \r\n" );
    }
    else
    {
        log_printf( &logger, " Battery isn't charging, disabling output. \r\n" );
        charger26_enable_output ( &charger26, CHARGER26_DISABLE_OUTPUT );
        for ( ; ; );
    }
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
