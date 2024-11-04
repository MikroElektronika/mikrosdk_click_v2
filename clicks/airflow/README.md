\mainpage Main Page

---
# Air Flow Click

> Air Flow Click is a compact add-on board that contains a flow-based 2-in-1 differential pressure sensor. This board features the LHDULTRAM012UB3, LHD ULTRA series micro-flow differential pressure sensor from TE Connectivity Measurement Specialties. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/air_flow_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/air-flow-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the AirFlow Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AirFlow Click driver.

#### Standard key functions :

- `airflow_cfg_setup` Config Object Initialization function.
```c
void airflow_cfg_setup ( airflow_cfg_t *cfg );
```

- `airflow_init` Initialization function.
```c
err_t airflow_init ( airflow_t *ctx, airflow_cfg_t *cfg );
```

- `airflow_default_cfg` Click Default Configuration function.
```c
err_t airflow_default_cfg ( airflow_t *ctx );
```

#### Example key functions :

- `airflow_reset_device` Reset device.
```c
void airflow_reset_device ( airflow_t *ctx )
```

- `airflow_get_differential_pressure` Reads differential pressure.
```c
err_t airflow_get_differential_pressure ( airflow_t *ctx, float *pressure )
```

- `airflow_get_atmospheric_pressure` Reads atmospheric pressure and temperature.
```c
err_t airflow_get_atmospheric_pressure ( airflow_t *ctx, float *pressure, float *temperature );
```

## Example Description

> This example showcases ability for device to read differential 
pressure, atmospheric pressure and ambient temperature.

**The demo application is composed of two sections :**

### Application Init

> Initialize host communication modules (UART, I2C/SPI). Read 
electric signature data from device and logs it to terminal.

```c

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
    Delay_ms ( 100 );
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
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads differential pressure in Pa, atmospheric pressure in mBar 
and ambient temperature in C every 500ms and logs read data.

```c

void application_task ( void ) 
{    
    float pressure_data, temperature_data;
    
    airflow_get_differential_pressure( &airflow, &pressure_data );
    log_printf( &logger, "Differential pressure[Pa]: %.2f\r\n", pressure_data );
    airflow_get_atmospheric_pressure( &airflow, &pressure_data, &temperature_data );
    log_printf( &logger, "Atmospheric pressure[mBar]: %.2f\r\nTemperature[degC]: %.2f\r\n", pressure_data, temperature_data );
    log_printf( &logger, "***********************************************************\r\n" );
    Delay_ms ( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AirFlow

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
