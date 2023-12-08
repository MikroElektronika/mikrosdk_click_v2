/*!
 * @file main.c
 * @brief ADC15 Click example
 *
 * # Description
 * This example showcases ability of the click board to 
 * read adc data from 2 different channels. It's also configuratable
 * to read data in different output rate, resolutions( word/data len ),
 * and gain.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (SPI, UART) and additional
 * pins for control of the device. Sets default configuration, that 
 * sets gain of 1 for both channels(+/-1.2V range) and word/data length
 * of 24bit. In the end reads device ID.
 *
 * ## Application Task
 * Waits for data ready signal and reads voltage value of both channels,
 * and logs read status and channel voltage level.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc15.h"
#include "math.h"

static adc15_t adc15;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc15_cfg_t adc15_cfg;  /**< Click config object. */

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
    adc15_cfg_setup( &adc15_cfg );
    ADC15_MAP_MIKROBUS( adc15_cfg, MIKROBUS_1 );
    err_t init_flag  = adc15_init( &adc15, &adc15_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Communication Init. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    } 

    if ( adc15_default_cfg ( &adc15 ) )
    {
        log_error( &logger, " Default configuration. " );
        for( ; ; );
    }
    
    uint16_t reg_val;
    adc15_reg_read( &adc15, ADC15_REG_ID, &reg_val );
    log_printf( &logger, " > ID: 0x%.4X\r\n", reg_val );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    while ( adc15_data_ready( &adc15 ) );
    float channel1 = 0;
    float channel2 = 0;
    uint16_t status = 0;
    if ( !adc15_read_voltage( &adc15, &status, &channel1, &channel2 ) )
    {
        log_printf( &logger, " > Status: 0x%.4X\r\n", status );
        log_printf( &logger, " > V ch1: %.3f\r\n", channel1 );
        log_printf( &logger, " > V ch2: %.3f\r\n", channel2 );    
        log_printf( &logger, "************************\r\n" );
        Delay_ms( 1000 );
    }
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
