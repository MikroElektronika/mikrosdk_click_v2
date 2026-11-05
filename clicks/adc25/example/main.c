/*!
 * @file main.c
 * @brief ADC 25 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 25 Click board by reading
 * voltage and current levels from input channels in a continuous sequence and
 * displaying the results over UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for the sequencer to complete a full sequence, reads all
 * 8 conversion results and logs each channel voltage[V] or current[mA] over UART.
 * Results are updated once per second.
 *
 * @note
 * The absolute input voltage range on each channel is -20.5V to +20.5V.
 * Do not apply voltages outside this range to the analog inputs.
 * 
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "adc25.h"

#ifndef MIKROBUS_POSITION_ADC25
    #define MIKROBUS_POSITION_ADC25 MIKROBUS_1
#endif

static adc25_t adc25;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc25_cfg_t adc25_cfg;  /**< Click config object. */

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
    adc25_cfg_setup( &adc25_cfg );
    ADC25_MAP_MIKROBUS( adc25_cfg, MIKROBUS_POSITION_ADC25 );
    if ( SPI_MASTER_ERROR == adc25_init( &adc25, &adc25_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC25_ERROR == adc25_default_cfg ( &adc25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage[ ADC25_NUM_SEQ_STEPS ] = { 0 };

    if ( ADC25_OK == adc25_get_voltage_seq( &adc25, voltage, ADC25_NUM_SEQ_STEPS ) )
    {
        log_printf( &logger, " TB1 AIN0 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 0 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB1 AIN1 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 1 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB2 AIN6 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 2 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB2 AIN7 (Single-Ended Current): %.2f [mA]\r\n", voltage[ 3 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB3 AIN8-AIN9   (Diff Voltage):  %.2f [V]\r\n",  voltage[ 4 ] );
        log_printf( &logger, " TB4 AIN10-AIN11 (Diff Voltage):  %.2f [V]\r\n",  voltage[ 5 ] );
        log_printf( &logger, " TB5 AIN12-AIN13 (Diff Current):  %.2f [mA]\r\n", voltage[ 6 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " TB6 AIN14-AIN15 (Diff Current):  %.2f [mA]\r\n", voltage[ 7 ] / ADC25_SHUNT_RES_OHM * ADC25_CONV_MILI );
        log_printf( &logger, " -----------------------------------\r\n" );
    }
    else
    {
        log_error( &logger, " Read timeout." );
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
