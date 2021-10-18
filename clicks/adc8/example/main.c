/*!
 * \file 
 * \brief Adc8 Click example
 * 
 * # Description
 * The demo app shows voltage measurement across all singles and different channels.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Reads voltage from each channel one by one and the voltage difference 
 * between specified channels.
 * 
 * *note:* 
 * On the input channel AIN0, AIN1, AIN2 and AIN3 sets maximum voltage 
 * GND - 0.3V < VIN > VDD + 0.3V
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc8.h"

// ------------------------------------------------------------------ VARIABLES

static adc8_t adc8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc8_cfg_setup( &cfg );
    ADC8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc8_init( &adc8, &cfg );

    adc8_default_cfg( &adc8 );
    log_info( &logger, "---- ADC start ----" );
}

void application_task ( void )
{
    adc8_single_volt_t single_volt;
    adc8_diff_volt_t diff_volt;

    log_printf( &logger, "\r\n-----------------------------------" );

    // Single channel
    adc8_get_single_channel( &adc8, &single_volt );

    log_printf( &logger, "\r\n>>> SINGLE CHANNEL <<<<\r\n" );
    log_printf( &logger, "- CH 0: %.2f\r\n", single_volt.ch_0 );
    log_printf( &logger, "- CH 1: %.2f\r\n", single_volt.ch_1 );
    log_printf( &logger, "- CH 2: %.2f\r\n", single_volt.ch_2 );
    log_printf( &logger, "- CH 3: %.2f\r\n", single_volt.ch_3 );

    // Diff channel

    adc8_get_diff_channel( &adc8, &diff_volt );

    log_printf( &logger, "\r\n>>> DIFF CHANNEL <<<<\r\n" );
    log_printf( &logger, "- CH(0-1): %.2f\r\n", diff_volt.ch_0_1 );
    log_printf( &logger, "- CH(0-3): %.2f\r\n", diff_volt.ch_0_3 );
    log_printf( &logger, "- CH(1-3): %.2f\r\n", diff_volt.ch_1_3 );
    log_printf( &logger, "- CH(2-3): %.2f\r\n", diff_volt.ch_2_3 );

    Delay_ms( 1000 );
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
