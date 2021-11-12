/*!
 * @file main.c
 * @brief DAQ Click example
 *
 * # Description
 * This example showcases ability of the device to read ADC 
 * data and calculate voltage for set configuration.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (SPI, UART) and
 * additional pins for controling device. Resets device and
 * then configures default configuration and sets read range
 * by setting gain to +-12V. In the end reads vendor and 
 * device ID to confirm communication.
 *
 * ## Application Task
 * Reads ADC data and calculates voltage from it, every 0.3 seconds.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "daq.h"

static daq_t daq;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    daq_cfg_t daq_cfg;  /**< Click config object. */

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
    daq_cfg_setup( &daq_cfg );
    DAQ_MAP_MIKROBUS( daq_cfg, MIKROBUS_1 );
    err_t init_flag  = daq_init( &daq, &daq_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    if ( daq_default_cfg ( &daq ) ) 
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t id = 0;
    daq_generic_read( &daq, DAQ_REG_VENDOR_H, &id, 1 );
    log_printf( &logger, " > Vendor: \t0x%.2X", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_VENDOR_L, &id, 1 );
    log_printf( &logger, "%.2X\r\n", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_PRODUCT_ID_H, &id, 1 );
    log_printf( &logger, " > ID: \t\t0x%.2X", ( uint16_t )id );
    daq_generic_read( &daq, DAQ_REG_PRODUCT_ID_L, &id, 1 );
    log_printf( &logger, "%.2X\r\n", ( uint16_t )id );
    Delay_ms( 1000 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    int32_t adc_data = 0;
    float voltage = 0.0;
    daq_read_data( &daq, &adc_data );
    daq_calculate_voltage( &daq, adc_data, &voltage );
    
    log_printf( &logger, " > Data: %ld\r\n", adc_data );
    log_printf( &logger, " > Voltage: %.2f\r\n", voltage );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 300 );  
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
