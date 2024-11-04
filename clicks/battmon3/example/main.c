/*!
 * @file main.c
 * @brief BATTMON3 Click example
 *
 * # Description
 * This example demonstrates the use of BATT-MON 3 Click by measuring the battery
 * voltage, current and used capacity, as well as the chip internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialized the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the battery voltage (mV), current (mA), used capacity (mAh) and the chip internal 
 * temperature (Celsius) and displays the results on the USB UART approximately once per second. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "battmon3.h"

static battmon3_t battmon3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon3_cfg_t battmon3_cfg;  /**< Click config object. */

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
    battmon3_cfg_setup( &battmon3_cfg );
    BATTMON3_MAP_MIKROBUS( battmon3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon3_init( &battmon3, &battmon3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON3_ERROR == battmon3_default_cfg ( &battmon3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t voltage;
    int16_t current;
    float temperature, used_capacity;
    if ( BATTMON3_OK == battmon3_read_voltage ( &battmon3, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %u mV\r\n", voltage );
    }
    
    if ( BATTMON3_OK == battmon3_read_current ( &battmon3, &current ) )
    {
        log_printf ( &logger, " Current: %d mA\r\n", current );
    }
    
    if ( BATTMON3_OK == battmon3_read_temperature ( &battmon3, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.3f C\r\n", temperature );
    }
    
    if ( BATTMON3_OK == battmon3_read_used_capacity ( &battmon3, &used_capacity ) )
    {
        log_printf ( &logger, " Used Capacity: %.3f mAh\r\n\n", used_capacity );
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
