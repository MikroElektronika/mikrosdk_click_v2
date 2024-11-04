\mainpage Main Page

---
# TempHum 19 Click

> Temp&Hum 19 Click is a compact add-on board that represents temperature and humidity sensing solution. This board features the BPS240, a highly accurate relative humidity and temperature sensor from Bourns. This sensor, characterized by its high accuracy (±2% from 20% to 80%RH (±4% over entire humidity range)) and high resolution, provides 10-bit data to the host controller with a configurable I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum 19 Click driver.

#### Standard key functions :

- `temphum19_cfg_setup` Config Object Initialization function.
```c
void temphum19_cfg_setup ( temphum19_cfg_t *cfg );
```

- `temphum19_init` Initialization function.
```c
err_t temphum19_init ( temphum19_t *ctx, temphum19_cfg_t *cfg );
```

- `temphum19_default_cfg` Click Default Configuration function.
```c
err_t temphum19_default_cfg ( temphum19_t *ctx );
```

#### Example key functions :

- `temphum19_restart_chip` This function restarts the chip by toggling the EN pin state.
```c
void temphum19_restart_chip ( temphum19_t *ctx );
```

- `temphum19_set_mode_reg` This function programs the mode register with a desired mode value, and stores it to the ctx->detection_mode variable.
```c
err_t temphum19_set_mode_reg ( temphum19_t *ctx, uint8_t mode );
```

- `temphum19_read_data` This function reads temperature and humidity raw data and converts them to Celsius and Percents respectfully.
```c
err_t temphum19_read_data ( temphum19_t *ctx, float *temperature, float *humidity );
```

## Example Description

> This example demonstrates the use of Temp & Hum 19 Click board by reading the temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum19_cfg_t temphum19_cfg;  /**< Click config object. */

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
    temphum19_cfg_setup( &temphum19_cfg );
    TEMPHUM19_MAP_MIKROBUS( temphum19_cfg, MIKROBUS_1 );
    
    if ( I2C_MASTER_ERROR == temphum19_init( &temphum19, &temphum19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM19_ERROR == temphum19_default_cfg ( &temphum19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature (Celsius) and humidity (Percents) data and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature, humidity;
    if ( TEMPHUM19_OK == temphum19_read_data ( &temphum19, &temperature, &humidity ) ) 
    {
        log_printf ( &logger, " Temperature: %.1f C\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%\r\n\n", humidity );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
