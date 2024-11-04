\mainpage Main Page

---
# TempHum 25 Click

> Temp&Hum 25 Click is a compact add-on board designed for precise temperature and humidity monitoring. This board features the SHT33-DIS-B2.5KS, a high-reliability, third-generation relative humidity and temperature sensor from Sensirion. This sensor offers exceptional accuracy and reliability, with a range of 0-100% RH and -40 to +125°C, and features ISO17025-certified calibration, CMOSens® technology, and NIST-traceability. The board supports the new Click Snap feature, allowing easy detachment of the sensor area for flexible use.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum25_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-25-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum 25 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum 25 Click driver.

#### Standard key functions :

- `temphum25_cfg_setup` Config Object Initialization function.
```c
void temphum25_cfg_setup ( temphum25_cfg_t *cfg );
```

- `temphum25_init` Initialization function.
```c
err_t temphum25_init ( temphum25_t *ctx, temphum25_cfg_t *cfg );
```

#### Example key functions :

- `temphum25_read_serial_num` This function reads the 4-bytes unique serial number by using I2C serial interface.
```c
err_t temphum25_read_serial_num ( temphum25_t *ctx, uint32_t *serial_num );
```

- `temphum25_start_measurement` This function starts the measurement by sending the selected measurement command.
```c
err_t temphum25_start_measurement ( temphum25_t *ctx, uint16_t meas_cmd );
```

- `temphum25_read_measurement` This function reads the temperature and humidity measurements results.
```c
err_t temphum25_read_measurement ( temphum25_t *ctx, float *temperature, float *humidity );
```

## Example Description

> This example demonstrates the use of TempHum 25 Click board by reading the temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the device reset, reads and displays the sensor unique serial number, and then starts the measurements with 1 MPS.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum25_cfg_t temphum25_cfg;  /**< Click config object. */

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
    temphum25_cfg_setup( &temphum25_cfg );
    TEMPHUM25_MAP_MIKROBUS( temphum25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum25_init( &temphum25, &temphum25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    temphum25_reset_device ( &temphum25 );

    uint32_t serial_num = 0;
    if ( TEMPHUM25_OK == temphum25_read_serial_num ( &temphum25, &serial_num ) )
    {
        log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    }

    temphum25_start_measurement ( &temphum25, TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_1 );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature (degC) and the relative humidity (%RH) data and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;
    if ( TEMPHUM25_OK == temphum25_read_measurement ( &temphum25, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum25

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
