/*!
 * @file main.c
 * @brief CO2 Click example
 *
 * # Description
 * This example showcases ability of Click board. It reads ID's 
 * configures device for operation work and reads CO2 gas 
 * concentration in air and temperature of IC every second.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of host communication modules (UART, I2C). 
 * Checks device and serial ID's from device. Then calls default 
 * configuration function that resets device, self tests it selft 
 * and configures for measuring CO2 concentration from air.
 *
 * ## Application Task
 * Reads air CO2 gas concentration in precentage and IC's 
 * temperature in deg Celzius in span of 1 second and logs 
 * data to UART Terminal.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "co2.h"

#define CO2_AIR_HUMIDITY 40/*< Relative air humidity in % */
#define CO2_AIR_PRESSURE 1008/*< Relative air pressure in mBar */

static co2_t co2;
static co2_cfg_t co2_cfg;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */

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
    co2_cfg_setup( &co2_cfg );
    CO2_MAP_MIKROBUS( co2_cfg, MIKROBUS_1 );
    err_t init_flag = co2_init( &co2, &co2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    init_flag = co2_get_id( &co2 );
    
    if ( ( init_flag < 0 ) && ( co2.device_id != CO2_DEVICE_ID ) )
    {
        log_error( &logger, "ID" );
    }
    else
    {
        log_printf( &logger, " > Device ID: 0x%.8lX\r\n", co2.device_id );
        log_printf( &logger, " > Serial ID: 0x%.8lX%.8lX\r\n", co2.serial_id[ 0 ], co2.serial_id[ 1 ] );
    }
    
    init_flag = co2_default_cfg ( &co2 );
    
    if ( init_flag < 0 )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    //Set reference values for device to calculate gas concentartion.
    if ( CO2_OK != co2_set_reference( &co2, CO2_AIR_HUMIDITY, CO2_AIR_PRESSURE ) )
    {
        log_error( &logger, " Reference values." );
    }
    
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float gas_data = 0;
    float temp_data = 0;
    
    if ( CO2_OK == co2_read_gas( &co2, &gas_data, &temp_data ) )
    {
        log_printf( &logger, " > CO2[%%]: %.2f\r\n", gas_data );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temp_data );
        Delay_ms( 1000 );
    }
    
    Delay_ms( 1 );
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
