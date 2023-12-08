/*!
 * @file main.c
 * @brief HallCurrent10 Click example
 *
 * # Description
 * This library contains API for Hall Current 10 Click driver.
 * The demo application reads ADC value, ADC voltage and current value.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Hall Current 10 Click board™.
 * In this example, we read and display the ADC values and current ( mA ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent10.h"

static hallcurrent10_t hallcurrent10;
static log_t logger;
static uint16_t adc_data;
static float current;
static float adc_voltage;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent10_cfg_t hallcurrent10_cfg;  /**< Click config object. */

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
    hallcurrent10_cfg_setup( &hallcurrent10_cfg );
    HALLCURRENT10_MAP_MIKROBUS( hallcurrent10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hallcurrent10_init( &hallcurrent10, &hallcurrent10_cfg ) ) 
    {
        log_info( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    hallcurrent10_read_adc( &hallcurrent10, &adc_data );
    log_printf( &logger, " ADC Value   : %d \r\n", adc_data );
    Delay_ms( 100 );
    
    hallcurrent10_get_adc_voltage( &hallcurrent10, &adc_voltage );
    log_printf( &logger, " ADC Voltage : %.2f mV \r\n", adc_voltage );
    log_printf( &logger, "- - - - - - - - - - -  - -\r\n" );
    Delay_ms( 100 );
    
    hallcurrent10_get_current ( &hallcurrent10, &current );
    log_printf( &logger, " Current     : %.2f mA \r\n", current );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
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
