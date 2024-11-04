/*!
 * @file main.c
 * @brief Current 12 Click example
 *
 * # Description
 * This example demonstrates the use of the Current 12 Click board 
 * by reading and displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the results 
 * of the input current, voltage, and power measurements.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current12.h"

static current12_t current12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current12_cfg_t current12_cfg;  /**< Click config object. */

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
    current12_cfg_setup( &current12_cfg );
    CURRENT12_MAP_MIKROBUS( current12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current12_init( &current12, &current12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT12_ERROR == current12_default_cfg ( &current12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_____________________\r\n " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    float meas_data = 0;
    if ( CURRENT12_OK == current12_get_shunt_voltage( &current12, &meas_data ) )
    {
        log_printf( &logger, " Shunt Voltage: %.2f [mV]\r\n ", meas_data );
        Delay_ms ( 100 );
    }

    if ( CURRENT12_OK == current12_get_load_voltage( &current12, &meas_data ) )
    {
        log_printf( &logger, " Load Voltage: %.2f [V]\r\n ", meas_data );
        Delay_ms ( 100 );
    }

    if ( CURRENT12_OK == current12_get_dc_power( &current12, &meas_data ) )
    {
        log_printf( &logger, " DC Power: %.2f [W]\r\n ", meas_data );
        Delay_ms ( 100 );
    }

    if ( CURRENT12_OK == current12_get_current( &current12, &meas_data ) )
    {
        log_printf( &logger, " Current: %.2f [mA]\r\n", meas_data );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "_____________________\r\n " );
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
