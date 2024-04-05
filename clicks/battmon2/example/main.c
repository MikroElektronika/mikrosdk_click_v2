/*!
 * @file main.c
 * @brief BATTMON2 Click example
 *
 * # Description
 * This example demonstrates the use of BATT-MON 2 click board by monitoring
 * the measurements of battery voltage, current, capacity, percentage, time-to-empty or time-to-full,
 * as well as the chip internal temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and checks the communication by reading and verifying the device ID.
 *
 * ## Application Task
 * Reads and displays on the USB UART the measurements of battery voltage, current, capacity, percentage, 
 * time-to-empty or time-to-full, as well as the chip internal temperature approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "battmon2.h"

static battmon2_t battmon2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon2_cfg_t battmon2_cfg;  /**< Click config object. */

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
    battmon2_cfg_setup( &battmon2_cfg );
    BATTMON2_MAP_MIKROBUS( battmon2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon2_init( &battmon2, &battmon2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON2_ERROR == battmon2_check_communication ( &battmon2 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage, capacity, percentage, current, die_temp;
    if ( BATTMON2_OK == battmon2_get_battery_voltage ( &battmon2, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %.1f mV \r\n", voltage );
    }
    if ( BATTMON2_OK == battmon2_get_battery_current ( &battmon2, &current ) )
    {
        log_printf ( &logger, " Current: %.1f mA \r\n", current );
    }
    if ( BATTMON2_OK == battmon2_get_battery_capacity ( &battmon2, &capacity ) )
    {
        log_printf ( &logger, " Capacity: %.1f mAh \r\n", capacity );
    }
    if ( BATTMON2_OK == battmon2_get_battery_percentage ( &battmon2, &percentage ) )
    {
        log_printf ( &logger, " Percentage: %.1f %% \r\n", percentage );
    }
    if ( current > 0 )
    {
        uint32_t time_to_full;
        if ( BATTMON2_OK == battmon2_get_battery_ttf ( &battmon2, &time_to_full ) )
        {
            log_printf ( &logger, " Time to full: %uh %umin %usec \r\n", ( uint16_t ) ( time_to_full / 3600 ), 
                                                                         ( uint16_t ) ( time_to_full % 3600 ) / 60,
                                                                         ( uint16_t ) ( time_to_full % 60 ) );
        }
    }
    else if ( current < 0 )
    {
        uint32_t time_to_empty;
        if ( BATTMON2_OK == battmon2_get_battery_tte ( &battmon2, &time_to_empty ) )
        {
            log_printf ( &logger, " Time to empty: %uh %umin %usec \r\n", ( uint16_t ) ( time_to_empty / 3600 ), 
                                                                          ( uint16_t ) ( time_to_empty % 3600 ) / 60,
                                                                          ( uint16_t ) ( time_to_empty % 60 ) );
        }
    }
    if ( BATTMON2_OK == battmon2_get_die_temperature ( &battmon2, &die_temp ) )
    {
        log_printf ( &logger, " Internal temperature: %.2f C \r\n\n", die_temp );
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
