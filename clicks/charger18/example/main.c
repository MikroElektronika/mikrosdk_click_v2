/*!
 * @file main.c
 * @brief Charger 18 Click Example.
 *
 * # Description
 * This example demonstrates the use of Charger 18 click board by controlling
 * the status of the charger as well as the LDO and BUCK regulators.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the chip with the charger, LDO and BUCK regulators disabled.
 *
 * ## Application Task
 * This function enables the charger, BUCK and LDO in the span of 25 seconds, and displays
 * the status of each feature on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger18.h"

static charger18_t charger18;   /**< Charger 18 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger18_cfg_t charger18_cfg;  /**< Click config object. */

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
    charger18_cfg_setup( &charger18_cfg );
    CHARGER18_MAP_MIKROBUS( charger18_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger18_init( &charger18, &charger18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger18_power_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " POWER   : ON\r\n" );
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " CHARGER : OFF\r\n" );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " BUCK    : OFF\r\n" );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " LDO     : OFF\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " CHARGER : ON\r\n" );
    Delay_ms( 10000 );
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " CHARGER : OFF\r\n" );
    Delay_ms( 3000 );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " BUCK    : ON\r\n" );
    Delay_ms( 3000 );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " BUCK    : OFF\r\n" );
    Delay_ms( 3000 );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " LDO     : ON\r\n" );
    Delay_ms( 3000 );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " LDO     : OFF\r\n\n" );
    Delay_ms( 3000 );
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
