/*!
 * @file main.c
 * @brief HVAC 2 Click example
 *
 * # Description
 * This example demonstrates the use of HVAC 2 Click board by reading the measurement results
 * of SCD43 (CO2, temperature, humidity) and optionally SEN5x or SEN65 (PM mass concentration, 
 * relative humidity, temperature, VOC and NOx indexes) sensors.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and after that performs the initialization of SCD43 and external sensors 
 * (SEN5x or SEN65). The SEN5x or SEN65 sensors are optional, see the macro definition at the begining
 * of the main.c file.
 * 
 * ## Application Task
 * Reads the measurement results from SCD43 (CO2, temperature, humidity) and optionally from SEN5x
 * or SEN65 sensors (PM mass concentration, relative humidity, temperature, VOC and NOx indexes).
 * The results are being displayed on the USB UART every 5 seconds approximately.
 *
 * @note
 * Make sure the VCC SEL is set to 5V for the SEN5x sensors and to 3V3 for the SEN65 sensor.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hvac2.h"

#ifndef MIKROBUS_POSITION_HVAC2
    #define MIKROBUS_POSITION_HVAC2 MIKROBUS_1
#endif

// External sensor selection
#define HVAC2_EXTERNAL_SENSOR   HVAC2_EXTERNAL_SENSOR_NONE

static hvac2_t hvac2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hvac2_cfg_t hvac2_cfg;  /**< Click config object. */

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
    hvac2_cfg_setup( &hvac2_cfg );
    HVAC2_MAP_MIKROBUS( hvac2_cfg, MIKROBUS_POSITION_HVAC2 );
    if ( I2C_MASTER_ERROR == hvac2_init( &hvac2, &hvac2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf ( &logger, "\r\n ------ SCD43 init ------\r\n" );
    if ( HVAC2_OK == hvac2_scd43_stop_measurement ( &hvac2 ) )
    {
        log_printf ( &logger, " Stop measurement\r\n" );
    }
    uint16_t scd43_serial_num[ 3 ] = { 0 };
    if ( HVAC2_OK == hvac2_scd43_get_serial_num ( &hvac2, scd43_serial_num ) )
    {
        log_printf ( &logger, " Serial number: %.4X%.4X%.4X\r\n", scd43_serial_num[ 0 ], 
                                                                  scd43_serial_num[ 1 ], 
                                                                  scd43_serial_num[ 2 ] );
    }
    if ( HVAC2_OK == hvac2_scd43_start_measurement ( &hvac2 ) )
    {
        log_printf ( &logger, " Start measurement\r\n" );
    }
    log_printf ( &logger, " ------------------------\r\n" );
    
#if ( HVAC2_EXTERNAL_SENSOR == HVAC2_EXTERNAL_SENSOR_SEN5X )
    log_printf ( &logger, "\r\n ------ SEN5x init ------\r\n" );
    if ( HVAC2_OK == hvac2_sen5x_stop_measurement ( &hvac2 ) )
    {
        log_printf ( &logger, " Stop measurement\r\n" );
    }
    uint8_t sen5x_product_name[ 32 ] = { 0 };
    if ( HVAC2_OK == hvac2_sen5x_get_product_name ( &hvac2, sen5x_product_name ) )
    {
        log_printf ( &logger, " Product name: %s\r\n", sen5x_product_name );
    }
    uint8_t sen5x_serial_num[ 32 ] = { 0 };
    if ( HVAC2_OK == hvac2_sen5x_get_serial_num ( &hvac2, sen5x_serial_num ) )
    {
        log_printf ( &logger, " Serial number: %s\r\n", sen5x_serial_num );
    }
    if ( HVAC2_OK == hvac2_sen5x_start_measurement ( &hvac2 ) )
    {
        log_printf ( &logger, " Start measurement\r\n" );
    }
    if ( HVAC2_OK == hvac2_sen5x_start_fan_cleaning ( &hvac2 ) )
    {
        log_printf ( &logger, " Start fan-cleaning\r\n" );
    }
    log_printf ( &logger, " ------------------------\r\n" );
#elif ( HVAC2_EXTERNAL_SENSOR == HVAC2_EXTERNAL_SENSOR_SEN65 )
    log_printf ( &logger, "\r\n ------ SEN65 init ------\r\n" );
    if ( HVAC2_OK == hvac2_sen6x_stop_measurement ( &hvac2 ) )
    {
        log_printf ( &logger, " Stop measurement\r\n" );
    }
    uint8_t sen6x_product_name[ 32 ] = { 0 };
    if ( HVAC2_OK == hvac2_sen6x_get_product_name ( &hvac2, sen6x_product_name ) )
    {
        log_printf ( &logger, " Product name: %s\r\n", sen6x_product_name );
    }
    uint8_t sen6x_serial_num[ 32 ] = { 0 };
    if ( HVAC2_OK == hvac2_sen6x_get_serial_num ( &hvac2, sen6x_serial_num ) )
    {
        log_printf ( &logger, " Serial number: %s\r\n", sen6x_serial_num );
    }
    if ( HVAC2_OK == hvac2_sen6x_start_fan_cleaning ( &hvac2 ) )
    {
        log_printf ( &logger, " Cleaning fan for 10 seconds\r\n" );
        for ( uint8_t delay_cnt = 0; delay_cnt < 10; delay_cnt++ )
        {
            Delay_ms ( 1000 );
        }
    }
    if ( HVAC2_OK == hvac2_sen6x_start_measurement ( &hvac2 ) )
    {
        log_printf ( &logger, " Start measurement\r\n" );
    }
    log_printf ( &logger, " ------------------------\r\n" );
#else
    log_printf ( &logger, "\r\n No external sensors enabled\r\n" );
    log_printf ( &logger, " ------------------------\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    hvac2_scd43_data_t scd43_data;
    if ( HVAC2_OK == hvac2_scd43_read_measurement ( &hvac2, &scd43_data ) )
    {
        log_printf ( &logger, "\r\n --- SCD43 measurement ---\r\n" );
        log_printf ( &logger, " CO2: %u ppm\r\n", scd43_data.co2 );
        log_printf ( &logger, " Temperature: %.2f degC\r\n", scd43_data.temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", scd43_data.humidity );
        log_printf ( &logger, " -------------------------\r\n" );
    }
    
#if ( HVAC2_EXTERNAL_SENSOR == HVAC2_EXTERNAL_SENSOR_SEN5X )
    hvac2_sen5x_data_t sen5x_data;
    if ( HVAC2_OK == hvac2_sen5x_read_measurement ( &hvac2, &sen5x_data ) )
    {
        log_printf ( &logger, "\r\n --- SEN5x measurement ---\r\n" );
        log_printf ( &logger, " PM1.0: %.1f ug/m3\r\n", sen5x_data.pm1_0 );
        log_printf ( &logger, " PM2.5: %.1f ug/m3\r\n", sen5x_data.pm2_5 );
        log_printf ( &logger, " PM4.0: %.1f ug/m3\r\n", sen5x_data.pm4_0 );
        log_printf ( &logger, " PM10: %.1f ug/m3\r\n", sen5x_data.pm10 );
        log_printf ( &logger, " Temperature: %.2f degC\r\n", sen5x_data.temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", sen5x_data.humidity );
        log_printf ( &logger, " VOC: %.1f\r\n", sen5x_data.voc );
        log_printf ( &logger, " NOx: %.1f\r\n", sen5x_data.nox );
        log_printf ( &logger, " -------------------------\r\n" );
    }
#elif ( HVAC2_EXTERNAL_SENSOR == HVAC2_EXTERNAL_SENSOR_SEN65 )
    hvac2_sen65_data_t sen65_data;
    if ( HVAC2_OK == hvac2_sen65_read_measurement ( &hvac2, &sen65_data ) )
    {
        log_printf ( &logger, "\r\n --- SEN65 measurement ---\r\n" );
        log_printf ( &logger, " PM1.0: %.1f ug/m3\r\n", sen65_data.pm1_0 );
        log_printf ( &logger, " PM2.5: %.1f ug/m3\r\n", sen65_data.pm2_5 );
        log_printf ( &logger, " PM4.0: %.1f ug/m3\r\n", sen65_data.pm4_0 );
        log_printf ( &logger, " PM10: %.1f ug/m3\r\n", sen65_data.pm10 );
        log_printf ( &logger, " Temperature: %.2f degC\r\n", sen65_data.temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", sen65_data.humidity );
        log_printf ( &logger, " VOC: %.1f\r\n", sen65_data.voc );
        log_printf ( &logger, " NOx: %.1f\r\n", sen65_data.nox );
        log_printf ( &logger, " -------------------------\r\n" );
    }
#endif
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
