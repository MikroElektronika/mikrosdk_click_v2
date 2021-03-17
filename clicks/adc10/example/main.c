/*!
 * @file main.c
 * @brief ADC 10 Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the ADC 10 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - UART,
 * select analog input channel 0, perform a hardware and software reset
 * and set the default device configuration, also, write a log.
 *
 * ## Application Task
 * In this example, we monitor and display
 * 24-bits of data ( from 0 to 8388607 ) of ADC and voltage ( from 0 mV to 2048 mV )
 * on the selected channel ( CH-0, CH-1, CH-2 or CH-3 ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes approximately for every 1 sec.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc10.h"

static adc10_t adc10;
static log_t logger;

static uint8_t select_ch;
static int32_t out_data;
static float voltage;

void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc10_cfg_t adc10_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n-------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    adc10_cfg_setup( &adc10_cfg );
    ADC10_MAP_MIKROBUS( adc10_cfg, MIKROBUS_1 );
    err_t init_flag  = adc10_init( &adc10, &adc10_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    select_ch = ADC10_ANALOG_INPUT_CH_3;
    
    // Hardware reset.
    
    adc10_hw_reset( &adc10 );
    Delay_ms( 100 );
    
    // Software reset.
    
    adc10_reset( &adc10 );
    Delay_ms( 1000 );

    // Click default configuration.
    
    adc10_default_cfg ( &adc10 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) {   
    adc10_start_sync( &adc10 );
    Delay_ms( 1 );

    while ( adc10_check_drdy( &adc10 ) == ADC10_NEW_DATA_NOT_READY );

    out_data = adc10_get_ch_output( &adc10, select_ch );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  ADC CH-%u : %.0f\r\n", ( uint16_t ) select_ch, ( float ) out_data );

    voltage = adc10_calc_voltage( &adc10, out_data, ADC10_VREF_INTERNAL, ADC10_GAIN_1 );
    log_printf( &logger, "  Voltage  : %.2f mV\r\n", voltage );
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
