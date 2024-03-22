/*!
 * @file main.c
 * @brief ADC 24 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 24 Click board 
 * by reading and writing data by using the SPI serial interface 
 * and reading results of AD conversion.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 *
 * ## Application Task
 * The demo application reads the voltage levels 
 * from all 15 analog input channels and displays the results.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc24.h"

static adc24_t adc24;
static log_t logger;
static adc24_ctrl_t ctrl;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc24_cfg_t adc24_cfg;  /**< Click config object. */

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
    adc24_cfg_setup( &adc24_cfg );
    ADC24_MAP_MIKROBUS( adc24_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc24_init( &adc24, &adc24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    ctrl.ch_sel = ADC24_CH_SEL_IN_0;
    ctrl.pm = ADC24_PM_NORMAL;
    ctrl.seq_shadow = ADC24_SEQ_SHADOW_AN_INPUT;
    ctrl.weak = ADC24_WEAK_DOUT_THREE_STATE;
    ctrl.range = ADC24_RANGE_VREF_5V;
    ctrl.coding = ADC24_CODING_BIN;

    log_info( &logger, " Application Task " );
    log_printf( &logger, "_____________\r\n" );
}

void application_task ( void )
{
    uint8_t ch_pos = 0;
    float voltage = 0;
    for ( uint8_t n_cnt = ADC24_CH_SEL_IN_0; n_cnt <= ADC24_CH_SEL_IN_15; n_cnt++ )
    {
        ctrl.ch_sel = n_cnt;
        if ( ADC24_OK == adc24_get_voltage( &adc24, ctrl, &ch_pos, &voltage ) )
        {
            log_printf( &logger, " IN%u : %.3f V\r\n", ( uint16_t ) ch_pos, voltage );
        }
        Delay_ms( 100 );  
    }
    log_printf( &logger, "_____________\r\n" );
    Delay_ms( 1000 );
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
