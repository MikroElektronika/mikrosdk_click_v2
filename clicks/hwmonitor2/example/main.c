/*!
 * @file main.c
 * @brief HW Monitor 2 Click example
 *
 * # Description
 * This example demonstrates the use of the HW Monitor 2 Click board™.
 * The demo application monitors analog voltage inputs and local temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example displays the Analog Voltage Inputs from CH0 to CH6 [mV] 
 * and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hwmonitor2.h"

static hwmonitor2_t hwmonitor2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor2_cfg_t hwmonitor2_cfg;  /**< Click config object. */

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
    hwmonitor2_cfg_setup( &hwmonitor2_cfg );
    HWMONITOR2_MAP_MIKROBUS( hwmonitor2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor2_init( &hwmonitor2, &hwmonitor2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR2_ERROR == hwmonitor2_default_cfg ( &hwmonitor2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void ) 
{
    static float temperature, voltage;
    for ( uint8_t ch_pos = 0; ch_pos < 7; ch_pos++ )
    {
        if ( HWMONITOR2_OK == hwmonitor2_get_analog_inputs( &hwmonitor2, ch_pos, &voltage ) )
        {
            log_printf( &logger, "CH %d: %.1f mV\r\n", ( uint16_t ) ch_pos, voltage );
            Delay_ms ( 100 );
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    if ( HWMONITOR2_OK == hwmonitor2_get_temperature( &hwmonitor2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.3f [deg c]\r\n", temperature );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "---------------------------\r\n" );
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
