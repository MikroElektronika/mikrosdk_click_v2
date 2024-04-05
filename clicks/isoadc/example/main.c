/*!
 * @file main.c
 * @brief ISO ADC Click example
 *
 * # Description
 * This example demonstrates the use of ISO ADC click board by reading
 * the shunt voltage, current, and power.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the external voltage reference.
 *
 * ## Application Task
 * Reads a 10 samples of a shunt voltage measurement, then averages and calculates
 * the current and power from it. All data is displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "isoadc.h"

static isoadc_t isoadc;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc_cfg_t isoadc_cfg;  /**< Click config object. */

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
    isoadc_cfg_setup( &isoadc_cfg );
    ISOADC_MAP_MIKROBUS( isoadc_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc_init( &isoadc, &isoadc_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    isoadc_set_vext ( &isoadc, ISOADC_VEXT_5V );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    float avg_voltage = 0;
    uint16_t avg_cnt = 0; 

    log_printf( &logger, " --- MEASUREMENT IN PROGRESS ---\r\n" );
    log_info( &logger, "Keep the load and power supply stable during the measurement process\r\n" );

    while ( avg_cnt < ISOADC_VOLTAGE_NUM_AVERAGES )
    {
        if ( ISOADC_OK == isoadc_read_voltage ( &isoadc, &voltage ) )
        {
            avg_voltage += voltage;
            avg_cnt++;
        }
    }
    voltage = avg_voltage / ISOADC_VOLTAGE_NUM_AVERAGES;
    log_printf( &logger, " Shunt Voltage: %.1f mV\r\n", voltage );
    log_printf( &logger, " Current: %.3f mA\r\n", isoadc_get_current ( voltage ) );
    log_printf( &logger, " Power: %.3f W\r\n", isoadc_get_power ( &isoadc, voltage ) );
    log_printf( &logger, "-------------------------\r\n\n" );
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
