/*!
 * @file main.c
 * @brief Charger Click Example.
 *
 * # Description
 * This example demonstrates the use of Charger click board by monitoring
 * the battery charging status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the click default configuration, calibrates
 * the zero current charging offset, and resets the elapsed time counter.
 *
 * ## Application Task
 * Reads the chip internal temperature, battery and system VDD, battery charging
 * current, and the elapsed time counter, approximately once per second. All data
 * are displayed on the USB UART where you can track their changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger.h"

static charger_t charger;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger_cfg_t charger_cfg;  /**< Click config object. */

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
    charger_cfg_setup( &charger_cfg );
    CHARGER_MAP_MIKROBUS( charger_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == charger_init( &charger, &charger_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER_ERROR == charger_default_cfg ( &charger ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, "\r\n Zero current calibration process\r\n" );
    log_printf( &logger, " Keep the battery disconnected in the next 5 seconds\r\n" );
    Delay_ms ( 3000 );
    if ( CHARGER_ERROR == charger_calibrate_current ( &charger ) )
    {
        log_error( &logger, " Calibration." );
        for ( ; ; );
    }
    log_printf( &logger, " Calibration done!\r\n\n" );

    if ( CHARGER_OK == charger_write_elapsed_time ( &charger, 0 ) )
    {
        log_printf( &logger, " Elapsed time reset done!\r\n\n" );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    float batt_vdd = 0;
    float system_vdd = 0;
    float current = 0;
    uint32_t elapsed_time = 0;
    if ( CHARGER_OK == charger_read_temperature ( &charger, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );
    }
    if ( CHARGER_OK == charger_read_batt_vdd ( &charger, &batt_vdd ) )
    {
        log_printf( &logger, " Battery VDD: %.3f V\r\n", batt_vdd );
    }
    if ( CHARGER_OK == charger_read_system_vdd ( &charger, &system_vdd ) )
    {
        log_printf( &logger, " System VDD: %.3f V\r\n", system_vdd );
    }
    if ( CHARGER_OK == charger_read_current ( &charger, &current ) )
    {
        log_printf( &logger, " Charging current: %.3f A\r\n", current );
    }
    if ( CHARGER_OK == charger_read_elapsed_time ( &charger, &elapsed_time ) )
    {
        log_printf( &logger, " Elapsed time: %lu s\r\n\n", elapsed_time );
    }
    Delay_ms ( 1000 );
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
