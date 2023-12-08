/*!
 * \file 
 * \brief Dac7 Click example
 * 
 * # Description
 * DAC 7 click carries the AD5624R 12-bit buffered Digital-to-Analog Converter 
 * that converts digital value to the corresponding voltage level 
 * using external voltage reference.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * In this example, we adjust the DAC output voltage from 1000 mV to 4000 mV 
 * for the channels, starting from channel A to channel D 
 * and then set the DAC output voltage to 5000 mV for all channels.
 * Results are being sent to UART Terminal where you can track their changes.
 * All data logs write on USB UART changes every 5 sec.
 *  
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac7.h"


// ------------------------------------------------------------------ VARIABLES

uint16_t v_ref_sel;
static dac7_t dac7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac7_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    dac7_cfg_setup( &cfg );
    DAC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac7_init( &dac7, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ------  DAC 7 Click  ------\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    v_ref_sel = DAC7_VREF_5000mV;

    if ( dac7_sw_reset( &dac7 ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "   Software reset   \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }
    
    Delay_ms( 500 );
    log_printf( &logger, "--------------------------\r\n\n" );

    
    if ( dac7_set_power( &dac7, DAC7_PWR_ON_ENABLE, DAC7_SELECT_CHANNEL_ALL ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "   All channel Power On   \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );

        for ( ; ; );
    }

    Delay_ms( 500 );
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_A, 1000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel A : 1000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms( 5000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_B, 2000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel B : 2000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms( 5000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_C, 3000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel C : 3000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }
    
    Delay_ms( 5000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_D, 4000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel D : 4000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms( 5000 );
    log_printf( &logger, "--------------------------\r\n\n" );

    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_ALL, 5000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, " All Channels: 5000 mV \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms( 5000 );
    log_printf( &logger, "--------------------------\r\n\n" );
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
