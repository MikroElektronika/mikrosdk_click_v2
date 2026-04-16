/*!
 * @file main.c
 * @brief Thermo 10 Click example
 *
 * # Description
 * This example demonstrates how to read temperature data and detect ALERT
 * events using the Thermo 10 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Thermo 10 Click for temperature
 * measurement.
 *
 * ## Application Task
 * Reads the temperature value periodically and logs an ALERT message when
 * the alert pin becomes active.
 *
 * @note
 * The temperature is measured every 200 ms. An alert condition occurs when
 * the temperature rises above THERMO10_TEMP_LIMIT_HIGH and clears when it
 * falls below THERMO10_TEMP_LIMIT_LOW.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo10.h"

#ifndef MIKROBUS_POSITION_THERMO10
    #define MIKROBUS_POSITION_THERMO10 MIKROBUS_1
#endif

static thermo10_t thermo10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo10_cfg_t thermo10_cfg;  /**< Click config object. */

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
    thermo10_cfg_setup( &thermo10_cfg );
    THERMO10_MAP_MIKROBUS( thermo10_cfg, MIKROBUS_POSITION_THERMO10 );
    if ( I2C_MASTER_ERROR == thermo10_init( &thermo10, &thermo10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO10_ERROR == thermo10_default_cfg ( &thermo10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    if ( !thermo10_get_alert_pin ( &thermo10 ) )
    {
        log_printf ( &logger, " ALERT Detected!\r\n" );
    }
    if ( THERMO10_OK == thermo10_get_temp ( &thermo10, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
    }
    Delay_ms ( 200 );
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
