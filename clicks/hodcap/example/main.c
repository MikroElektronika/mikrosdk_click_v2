/*!
 * @file main.c
 * @brief HOD CAP Click example
 *
 * # Description
 * This library contains API for the HOD CAP Click driver. 
 * The demo application sets the sensor configuration 
 * and detects the changes in capacity by measuring 
 * the relative change of the impedance for each channel.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the HOD CAP Click board™.
 * The demo application measures the relative change of the impedance 
 * and displays I and Q data per channel.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hodcap.h"

static hodcap_t hodcap;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hodcap_cfg_t hodcap_cfg;  /**< Click config object. */

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
    hodcap_cfg_setup( &hodcap_cfg );
    HODCAP_MAP_MIKROBUS( hodcap_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hodcap_init( &hodcap, &hodcap_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HODCAP_ERROR == hodcap_default_cfg ( &hodcap ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "________________________\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{ 
    static uint16_t i_data, q_data;
    log_printf( &logger, " \tI/Q data \r\n" );
    for ( uint8_t sen_num = 0; sen_num < HODCAP_TOTAL_NUMBER_OF_CHANNELS; sen_num++ )
    {
        if ( HODCAP_OK == hodcap_mux_channel_selection ( &hodcap, sen_num ) )
        {
            if ( ( HODCAP_OK == hodcap_wait_adc_data_ready( &hodcap ) ) &&
                 ( HODCAP_OK == hodcap_get_i_q_data( &hodcap, &i_data, &q_data ) ) )
            {
                log_printf( &logger, " SEN%d -> ", ( uint16_t ) sen_num );
                log_printf( &logger, " I : %u |", i_data );
                log_printf( &logger, " Q : %u \r\n", q_data );       
                Delay_ms( 100 );
            }
        }
    }
    log_printf( &logger, "________________________\r\n" );
    Delay_ms( 2000 );
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
