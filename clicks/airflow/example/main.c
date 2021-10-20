/*!
 * @file main.c
 * @brief AirFlow Click example
 *
 * # Description
 * This example showcases ability for device to read differential 
 * pressure, atmospheric pressure and ambient temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialize host communication modules (UART, I2C/SPI). Read 
 * electric signature data from device and logs it to terminal.
 *
 * ## Application Task
 * Reads differential pressure in Pa, atmospheric pressure in mBar 
 * and ambient temperature in C every 500ms and logs read data.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "airflow.h"

static airflow_t airflow;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airflow_cfg_t airflow_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    airflow_cfg_setup( &airflow_cfg );
    AIRFLOW_MAP_MIKROBUS( airflow_cfg, MIKROBUS_1 );
    err_t init_flag  = airflow_init( &airflow, &airflow_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    airflow_reset_device( &airflow );
    
    if ( airflow_default_cfg ( &airflow ) < 0 )
    {
        log_error( &logger, " Read" );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, "Firmware version: %d.%d\r\n", ( int16_t )airflow.major_fw_ver, ( int16_t )airflow.minor_fw_ver );
        //part number
        log_printf( &logger, "Part number: " );
        for ( uint8_t pn = 0; pn < 11; pn++ )
            log_printf( &logger, "%c", airflow.part_number[ pn ] );
        log_printf( &logger, "\r\n" );
        //lot number
        log_printf( &logger, "Lot number: " );
        for ( uint8_t pn = 0; pn < 7; pn++ )
            log_printf( &logger, "%c", airflow.lot_number[ pn ] );
        log_printf( &logger, "\r\n" );
        //pressure range
        log_printf( &logger, "Pressure range: %d\r\n", airflow.pressure_range );
        //output type
        log_printf( &logger, "Output type: %c\r\n", airflow.output_type );
        //scale factor
        log_printf( &logger, "Scale factor: %d\r\n", airflow.scale_factor );
        //calibration id
        log_printf( &logger, "Calibration ID: %s\r\n", airflow.calibration_id );
        //week
        log_printf( &logger, "Week: %d\r\n", ( int16_t )airflow.week );
        //year
        log_printf( &logger, "Year: %d\r\n", ( int16_t )airflow.year );
        //sequence number
        log_printf( &logger, "Sequence number: %d\r\n", airflow.sequence_number );
    }
    Delay_ms( 2000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{    
    float pressure_data, temperature_data;
    
    airflow_get_differential_pressure( &airflow, &pressure_data );
    log_printf( &logger, "Differential pressure[Pa]: %.2f\r\n", pressure_data );
    airflow_get_atmospheric_pressure( &airflow, &pressure_data, &temperature_data );
    log_printf( &logger, "Atmospheric pressure[mBar]: %.2f\r\nTemperature[degC]: %.2f\r\n", pressure_data, temperature_data );
    log_printf( &logger, "***********************************************************\r\n" );
    Delay_ms( 500 );
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
