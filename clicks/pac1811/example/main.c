/*!
 * @file main.c
 * @brief PAC1811 Click example
 *
 * # Description
 * This example demonstrates the use of the PAC1811 Click board for 
 * current, voltage, and power monitoring. The application reads and 
 * logs bus voltage, sense current, power values, as well as min/max 
 * and average measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and PAC1811 Click driver, then applies the 
 * default configuration.
 *
 * ## Application Task
 * Periodically refreshes the measurements and logs voltage, current, 
 * and power data. Updates are provided every second.
 *
 * @note
 * Ensure that the PAC1811 Click is properly connected to measure the 
 * target load current and supply voltage.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pac1811.h"

static pac1811_t pac1811;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pac1811_cfg_t pac1811_cfg;  /**< Click config object. */

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
    pac1811_cfg_setup( &pac1811_cfg );
    PAC1811_MAP_MIKROBUS( pac1811_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pac1811_init( &pac1811, &pac1811_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PAC1811_ERROR == pac1811_default_cfg ( &pac1811 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    pac1811_data_t meas_data;
    if ( PAC1811_OK == pac1811_refresh ( &pac1811 ) )
    {
        Delay_ms ( 1 );
        if ( PAC1811_OK == pac1811_read_data ( &pac1811, &meas_data ) )
        {
            log_printf ( &logger, " ACC_COUNT: %lu\r\n", meas_data.acc_count );
            log_printf ( &logger, " ACC_DATA: 0x%.6LX%.8LX\r\n", meas_data.acc_data_msb, meas_data.acc_data_lsb );
            log_printf ( &logger, " VBUS: %.3f V\r\n", meas_data.vbus );
            log_printf ( &logger, " ISENSE: %.3f A\r\n", meas_data.isense );
            log_printf ( &logger, " VBUS_AVG: %.3f V\r\n", meas_data.vbus_avg );
            log_printf ( &logger, " ISENSE_AVG: %.3f A\r\n", meas_data.isense_avg );
            log_printf ( &logger, " POWER: %.3f W\r\n", meas_data.power );
            log_printf ( &logger, " VBUS_MIN: %.3f V\r\n", meas_data.vbus_min );
            log_printf ( &logger, " VBUS_MAX: %.3f V\r\n", meas_data.vbus_max );
            log_printf ( &logger, " ISENSE_MIN: %.3f A\r\n", meas_data.isense_min );
            log_printf ( &logger, " ISENSE_MAX: %.3f A\r\n", meas_data.isense_max );
            log_printf ( &logger, " POWER_MIN: %.3f W\r\n", meas_data.power_min );
            log_printf ( &logger, " POWER_MAX: %.3f W\r\n\n", meas_data.power_max );
            Delay_ms ( 1000 );
        }
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
