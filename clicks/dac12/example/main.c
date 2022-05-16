/*!
 * @file main.c
 * @brief DAC12 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 12 click board by changing 
 * the outputs voltage level every 2 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the output voltage of all channels every 2 seconds and logs the voltage value on the USB UART.
 * It will go through the entire voltage range taking into account the number of steps which is defined below.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac12.h"

#define NUMBER_OF_STEPS    20  // The number of steps by which the entire voltage range will be divided. 

static dac12_t dac12;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac12_cfg_t dac12_cfg;  /**< Click config object. */

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
    dac12_cfg_setup( &dac12_cfg );
    DAC12_MAP_MIKROBUS( dac12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac12_init( &dac12, &dac12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    DAC12_SET_DATA_SAMPLE_EDGE;
    
    if ( DAC12_ERROR == dac12_default_cfg ( &dac12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float step = DAC12_INTERNAL_VREF / NUMBER_OF_STEPS;
    float output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC12_OK == dac12_set_channel_voltage ( &dac12, DAC12_SELECT_CHANNEL_ALL, output_voltage ) )
        {
            log_printf( &logger, " All channels output voltage set to %.3f V\r\n", output_voltage );
            output_voltage += step;
            Delay_ms( 2000 );
        }
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
