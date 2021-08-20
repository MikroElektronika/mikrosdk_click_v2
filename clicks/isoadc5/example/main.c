/*!
 * @file main.c
 * @brief ISOADC5 Click example
 *
 * # Description
 * This example demonstrates the use of ISO ADC 5 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and makes an initial log.
 *
 * ## Application Task
 * Reads the voltage from all input channels and displays the values of 
 * each channel on the USB UART approximately every second.
 *
 * @note
 * The voltage input range is from 0 to 48V.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "isoadc5.h"

static isoadc5_t isoadc5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    isoadc5_cfg_t isoadc5_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    isoadc5_cfg_setup( &isoadc5_cfg );
    ISOADC5_MAP_MIKROBUS( isoadc5_cfg, MIKROBUS_1 );
    err_t init_flag  = isoadc5_init( &isoadc5, &isoadc5_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float v_ain1 = 0, v_ain2 = 0, v_ain3 = 0, v_ain4 = 0;
    err_t error_flag = isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_1, &v_ain1 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_2, &v_ain2 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_3, &v_ain3 );
    error_flag |= isoadc5_read_voltage( &isoadc5, ISOADC5_ADC_FILTERED, ISOADC5_ADC_CHANNEL_4, &v_ain4 );
    
    if ( ISOADC5_OK == error_flag )
    {
        log_printf( &logger, " AIN 1 voltage: %.3f V\r\n", v_ain1 );
        log_printf( &logger, " AIN 2 voltage: %.3f V\r\n", v_ain2 );
        log_printf( &logger, " AIN 3 voltage: %.3f V\r\n", v_ain3 );
        log_printf( &logger, " AIN 4 voltage: %.3f V\r\n\r\n", v_ain4 );
        Delay_ms( 1000 );
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
