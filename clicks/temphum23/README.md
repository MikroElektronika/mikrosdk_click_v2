\mainpage Main Page

---
# TempHum 23 Click

> Temp&Hum 23 Click is a compact add-on board representing temperature and humidity sensing solution. This board features the SHT45, a 4th generation ultra-low-power relative humidity and temperature sensor from Sensirion. The SHT45 is characterized by its high accuracy (±1% RH and ±0.1°C over a wide operating temperature range) and high resolution providing 16-bit data to the host controller with a configurable I2C interface. Also, it is designed for reliable operation in harsh conditions such as condensing environments. This Click board™ is perfectly suitable for high-volume applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum23_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-23-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum 23 Click driver.

#### Standard key functions :

- `temphum23_cfg_setup` Config Object Initialization function.
```c
void temphum23_cfg_setup ( temphum23_cfg_t *cfg );
```

- `temphum23_init` Initialization function.
```c
err_t temphum23_init ( temphum23_t *ctx, temphum23_cfg_t *cfg );
```

#### Example key functions :

- `temphum23_soft_reset` This function performs the software reset by sending the soft reset command.
```c
err_t temphum23_soft_reset ( temphum23_t *ctx );
```

- `temphum23_read_serial_num` This function reads the 4-bytes unique serial number by using I2C serial interface.
```c
err_t temphum23_read_serial_num ( temphum23_t *ctx, uint32_t *serial_num );
```

- `temphum23_read_measurement_high_precision` This function reads the temperature and humidity measurements with high precision.
```c
err_t temphum23_read_measurement_high_precision ( temphum23_t *ctx, float *temp, float *hum );
```

## Example Description

> This example demonstrates the use of Temp & Hum 23 Click board by reading the temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the sensor software reset and then reads and displays the sensor unique serial number.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum23_cfg_t temphum23_cfg;  /**< Click config object. */

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
    temphum23_cfg_setup( &temphum23_cfg );
    TEMPHUM23_MAP_MIKROBUS( temphum23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum23_init( &temphum23, &temphum23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM23_OK == temphum23_soft_reset ( &temphum23 ) )
    {
        log_printf ( &logger, " Software reset\r\n" );
    }
    Delay_1sec ( );
    
    uint32_t serial_num;
    if ( TEMPHUM23_OK == temphum23_read_serial_num ( &temphum23, &serial_num ) )
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
    if ( TEMPHUM23_OK == temphum23_read_measurement_high_precision ( &temphum23, &temperature, &humidity ) )
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
- Click.TempHum23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
