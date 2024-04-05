/*!
 * @file main.c
 * @brief HW Monitor Click example
 *
 * # Description
 * This example demonstrates the use of the HW Monitor Click board™.
 * The demo application monitors analog voltage inputs and local temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example displays the Analog Voltage Inputs (IN0-IN6) [mV] 
 * and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hwmonitor.h"

static hwmonitor_t hwmonitor;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor_cfg_t hwmonitor_cfg;  /**< Click config object. */

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
    hwmonitor_cfg_setup( &hwmonitor_cfg );
    HWMONITOR_MAP_MIKROBUS( hwmonitor_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor_init( &hwmonitor, &hwmonitor_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR_ERROR == hwmonitor_default_cfg ( &hwmonitor ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void ) 
{
    static float temperature, voltage;
    for ( uint8_t in_pos = 0; in_pos < 7; in_pos++ )
    {
        if ( HWMONITOR_OK == hwmonitor_get_analog_inputs( &hwmonitor, in_pos, &voltage ) )
        {
            log_printf( &logger, "IN %d: %.1f mV\r\n", ( uint16_t ) in_pos, voltage );
            Delay_ms ( 100 );
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    if ( HWMONITOR_OK == hwmonitor_get_temperature ( &hwmonitor, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.3f [deg c]\r\n", temperature );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "--------------------------\r\n" );
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
