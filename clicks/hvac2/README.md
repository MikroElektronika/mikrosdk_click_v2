
---
# HVAC 2 Click

> [HVAC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6951) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6951&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of HVAC 2 Click board by reading the measurement results
of SCD43 (CO2, temperature, humidity) and optionally SEN5x or SEN65 (PM mass concentration, 
relative humidity, temperature, VOC and NOx indexes) sensors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HVAC2

### Example Key Functions

- `hvac2_cfg_setup` Config Object Initialization function.
```c
void hvac2_cfg_setup ( hvac2_cfg_t *cfg );
```

- `hvac2_init` Initialization function.
```c
err_t hvac2_init ( hvac2_t *ctx, hvac2_cfg_t *cfg );
```

- `hvac2_scd43_get_serial_num` This function reads the SCD43 48-bit unique serial number in form of 3 data words.
```c
err_t hvac2_scd43_get_serial_num ( hvac2_t *ctx, uint16_t *serial_num );
```

- `hvac2_scd43_start_measurement` This function starts a periodic measurement of SCD43 device by issuing a desired command for it.
```c
err_t hvac2_scd43_start_measurement ( hvac2_t *ctx );
```

- `hvac2_scd43_read_measurement` This function checks if the SCD43 data is ready and then reads the CO2, temperature, and humidity measurements.
```c
err_t hvac2_scd43_read_measurement ( hvac2_t *ctx, hvac2_scd43_data_t *scd43_data );
```

### Application Init

> Initializes the driver and after that performs the initialization of SCD43 and external sensors 
(SEN5x or SEN65). The SEN5x or SEN65 sensors are optional, see the macro definition at the begining
of the main.c file.

```c
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
```

### Application Task

> Reads the measurement results from SCD43 (CO2, temperature, humidity) and optionally from SEN5x
or SEN65 sensors (PM mass concentration, relative humidity, temperature, VOC and NOx indexes).
The results are being displayed on the USB UART every 5 seconds approximately.

```c
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
```

### Note

> Make sure the VCC SEL is set to 5V for the SEN5x sensors and to 3V3 for the SEN65 sensor.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
