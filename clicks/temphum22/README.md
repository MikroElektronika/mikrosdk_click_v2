\mainpage Main Page

---
# TempHum 22 click

> Temp&Hum 22 Click is a compact add-on board representing temperature and humidity sensing solution. This board features the SHT41A, a 4th generation automotive-grade relative humidity and temperature sensor from Sensirion. The SHT41A is characterized by its high accuracy (±2% RH and ±0.3°C over a wide operating temperature range) and high resolution providing 16-bit data to the host controller with a configurable I2C interface. Also, it is designed for reliable operation in harsh conditions such as condensing environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum22_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temphum-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum 22 Click driver.

#### Standard key functions :

- `temphum22_cfg_setup` Config Object Initialization function.
```c
void temphum22_cfg_setup ( temphum22_cfg_t *cfg );
```

- `temphum22_init` Initialization function.
```c
err_t temphum22_init ( temphum22_t *ctx, temphum22_cfg_t *cfg );
```

#### Example key functions :

- `temphum22_soft_reset` This function performs the software reset by sending the soft reset command.
```c
err_t temphum22_soft_reset ( temphum22_t *ctx );
```

- `temphum22_read_serial_num` This function reads the 4-bytes unique serial number by using I2C serial interface.
```c
err_t temphum22_read_serial_num ( temphum22_t *ctx, uint32_t *serial_num );
```

- `temphum22_read_measurement_high_precision` This function reads the temperature and humidity measurements with high precision.
```c
err_t temphum22_read_measurement_high_precision ( temphum22_t *ctx, float *temp, float *hum );
```

## Example Description

> This example demonstrates the use of Temp & Hum 22 click board by reading the temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the sensor software reset and then reads and displays the sensor unique serial number.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum22_cfg_t temphum22_cfg;  /**< Click config object. */

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
    temphum22_cfg_setup( &temphum22_cfg );
    TEMPHUM22_MAP_MIKROBUS( temphum22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum22_init( &temphum22, &temphum22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM22_OK == temphum22_soft_reset ( &temphum22 ) )
    {
        log_printf ( &logger, " Software reset\r\n" );
    }
    Delay_1sec ( );
    
    uint32_t serial_num;
    if ( TEMPHUM22_OK == temphum22_read_serial_num ( &temphum22, &serial_num ) )
    {
        log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature (degC) and the relative humidity (%RH) data and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature, humidity;
    if ( TEMPHUM22_OK == temphum22_read_measurement_high_precision ( &temphum22, &temperature, &humidity ) )
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
- Click.TempHum22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
