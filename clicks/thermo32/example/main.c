/*!
 * @file main.c
 * @brief Thermo 32 Click example
 *
 * # Description
 * This example demonstrates how to read temperature data and detect ALERT
 * events using the Thermo 32 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Thermo 32 Click for temperature
 * measurement.
 *
 * ## Application Task
 * Reads the temperature value periodically and logs an ALERT message when
 * the alert pin becomes active.
 *
 * @note
 * The temperature is measured once per second. An alert condition becomes active when
 * the temperature exceeds THERMO32_TEMP_LIMIT_HIGH or drops below THERMO32_TEMP_LIMIT_LOW.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo32.h"

#ifndef MIKROBUS_POSITION_THERMO32
    #define MIKROBUS_POSITION_THERMO32 MIKROBUS_1
#endif

static thermo32_t thermo32;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo32_cfg_t thermo32_cfg;  /**< Click config object. */

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
    thermo32_cfg_setup( &thermo32_cfg );
    THERMO32_MAP_MIKROBUS( thermo32_cfg, MIKROBUS_POSITION_THERMO32 );
    if ( I2C_MASTER_ERROR == thermo32_init( &thermo32, &thermo32_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO32_ERROR == thermo32_default_cfg ( &thermo32 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    if ( !thermo32_get_alert_pin ( &thermo32 ) )
    {
        log_printf ( &logger, " ALERT Detected!\r\n" );
        thermo32_clear_alert ( &thermo32 );
    }
    if ( THERMO32_OK == thermo32_get_temp ( &thermo32, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
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
