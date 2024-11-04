
---
# APC1 Sensor Demo

> APC1 Air Quality Sensor Bundle - Experience advanced air quality monitoring with our bundle solution, merging the ScioSense APC1 Air Quality sensor and the MIKROE Terminal Click board™. This dynamic combination creates a compact and precise system that measures PM levels, VOCs, temperature, humidity, and more. Explore this bundle to build an effective monitoring solution perfect for ensuring healthy indoor spaces or contributing to broader air quality research efforts.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/apc1sensor.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/apc1-air-quality-sensor-bundle)

---


#### Demo library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C/UART type


# Software Support

We provide a library for the APC1 Sensor Demo
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for APC1 Sensor Demo driver.

#### Standard key functions :

- `apc1sensor_cfg_setup` Config Object Initialization function.
```c
void apc1sensor_cfg_setup ( apc1sensor_cfg_t *cfg );
```

- `apc1sensor_init` Initialization function.
```c
err_t apc1sensor_init ( apc1sensor_t *ctx, apc1sensor_cfg_t *cfg );
```

- `apc1sensor_default_cfg` Demo Default Configuration function.
```c
err_t apc1sensor_default_cfg ( apc1sensor_t *ctx );
```

#### Example key functions :

- `apc1sensor_start_measurement` This function starts measurement by setting the device to measurement mode.
```c
err_t apc1sensor_start_measurement ( apc1sensor_t *ctx );
```

- `apc1sensor_read_info` This function reads the device name, serial number, and firmware version.
```c
err_t apc1sensor_read_info ( apc1sensor_t *ctx, apc1sensor_info_t *info );
```

- `apc1sensor_read_measurement` This function reads the measurement 64-bytes output structure data.
```c
err_t apc1sensor_read_measurement ( apc1sensor_t *ctx, apc1sensor_measurement_t *measurement );
```

## Example Description

> This example demonstrates the use of APC1 Air Quality Sensor Bundle by reading measurement results (PM1.0, PM2.5, PM10, TVOC, eCO2, AQI, temperature, relative humidity, etc.).

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the sensor default configuration, and reads the sensor name, serial number, and firmware version.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    apc1sensor_cfg_t apc1sensor_cfg;  /**< Demo config object. */

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

    // Sensor initialization.
    apc1sensor_cfg_setup( &apc1sensor_cfg );
    APC1SENSOR_MAP_MIKROBUS( apc1sensor_cfg, MIKROBUS_1 );
    if ( APC1SENSOR_OK != apc1sensor_init( &apc1sensor, &apc1sensor_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( APC1SENSOR_OK != apc1sensor_default_cfg ( &apc1sensor ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    apc1sensor_info_t info;
    if ( APC1SENSOR_OK == apc1sensor_read_info ( &apc1sensor, &info ) )
    {
        log_printf ( &logger, " Module name: %s\r\n", info.module_name );
        log_printf ( &logger, " Serial number: " );
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            log_printf ( &logger, "%.2X", ( uint16_t ) info.serial_num[ cnt ] );
        }
        log_printf ( &logger, "\r\n FW version: %.2X%.2X\r\n", 
                     ( uint16_t ) info.fw_version[ 0 ], ( uint16_t ) info.fw_version[ 1 ] );
    }
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the measurement results and displays all data on the USB UART once per second.

```c
void application_task ( void )
{
    apc1sensor_measurement_t meas;
    if ( APC1SENSOR_OK == apc1sensor_read_measurement ( &apc1sensor, &meas ) )
    {
        log_printf ( &logger, "--- MEASUREMENT RESULTS ---\r\n" );
        log_printf ( &logger, " PM1.0: %u ug/m3\r\n", meas.pm1_0 );
        log_printf ( &logger, " PM2.5: %u ug/m3\r\n", meas.pm2_5 );
        log_printf ( &logger, " PM10: %u ug/m3\r\n", meas.pm10 );
        log_printf ( &logger, " PM1.0 in air: %u ug/m3\r\n", meas.pm1_0_air );
        log_printf ( &logger, " PM2.5 in air: %u ug/m3\r\n", meas.pm2_5_air );
        log_printf ( &logger, " PM10 in air: %u ug/m3\r\n", meas.pm10_air );
        log_printf ( &logger, " # particles >0.3um: %u\r\n", meas.part_over_0_3um );
        log_printf ( &logger, " # particles >0.5um: %u\r\n", meas.part_over_0_5um );
        log_printf ( &logger, " # particles >1.0um: %u\r\n", meas.part_over_1_0um );
        log_printf ( &logger, " # particles >2.5um: %u\r\n", meas.part_over_2_5um );
        log_printf ( &logger, " # particles >5.0um: %u\r\n", meas.part_over_5_0um );
        log_printf ( &logger, " # particles >10um: %u\r\n", meas.part_over_10um );
        log_printf ( &logger, " TVOC: %u ppb\r\n", meas.tvoc );
        log_printf ( &logger, " eCO2: %u ppm\r\n", meas.eco2 );
        log_printf ( &logger, " T-comp: %.1f degC\r\n", meas.t_comp );
        log_printf ( &logger, " RH-comp: %.1f %%\r\n", meas.rh_comp );
        log_printf ( &logger, " T-raw: %.1f degC\r\n", meas.t_raw );
        log_printf ( &logger, " RH-raw: %.1f %%\r\n", meas.rh_raw );
        log_printf ( &logger, " RS0: %lu Ohm\r\n", meas.rs0 );
        log_printf ( &logger, " RS2: %lu Ohm\r\n", meas.rs2 );
        log_printf ( &logger, " RS3: %lu Ohm\r\n", meas.rs3 );
        log_printf ( &logger, " AQI: %u\r\n", ( uint16_t ) meas.aqi );
        log_printf ( &logger, " Version: 0x%.2X\r\n", ( uint16_t ) meas.version );
        log_printf ( &logger, " Error code: 0x%.2X\r\n", ( uint16_t ) meas.error_code );
        log_printf ( &logger, "---------------------------\r\n" );
    }
    Delay_ms ( 1000 );
}
```

## Note

> By default, the I2C communication interface is selected in the library,
which is compatible with APC1001J sensor. If you are using an UART version
of the sensor (APC1001U) refer to the apc1sensor_drv_interface_sel function
description in order to properly change the interface selection in the library.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.APC1Sensor

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
