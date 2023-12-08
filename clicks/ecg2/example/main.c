/*!
 * @file main.c
 * @brief ECG2 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the ECG 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI and UART communication, configures INT pin as INPUT, RST pin as OUTPUT, CS pin as 
 * OUTPUT and PWM pin as OUTPUT. Initializes SPI driver, initializes ECG2 click, sends START and 
 * RDATAC opcodes.
 *
 * ## Application Task
 * Captures readings from channel and plots data to serial plotter.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ecg2.h"

static ecg2_t ecg2;
static log_t logger;
uint32_t time;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg2_cfg_t ecg2_cfg;  /**< Click config object. */

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
    ecg2_cfg_setup( &ecg2_cfg );
    ECG2_MAP_MIKROBUS( ecg2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ecg2_init( &ecg2, &ecg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    SET_SPI_DATA_SAMPLE_EDGE;
    
    if ( ECG2_ERROR == ecg2_default_cfg ( &ecg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    ecg2_send_command( &ecg2, ECG2_START_CONVERSION );
    Delay_ms( 100 );
    ecg2_send_command( &ecg2, ECG2_ENABLE_READ_DATA_CONT_MODE );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{   
    uint16_t ecg_an = 0;
    ecg2_read_channel_data( &ecg2, 5, &ecg_an );
    log_printf( &logger, " %.6u, %.8lu \r\n", ecg_an, time );
    time += 5;
    Delay_ms( 5 );   
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
