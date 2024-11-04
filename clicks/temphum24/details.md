
---
# TempHum 24 Click

> Temp&Hum 24 Click is a compact add-on board that measures the surrounding environment's humidity and temperature. This board features the HDC3021, an integrated capacitive-based relative humidity and temperature sensor with a removable tape cover from Texas Instruments. The HDC3021 is characterized by its high accuracy (±0.5%RH and ±0.1°C over a wide operating temperature range) and high resolution, providing 16-bit data to the host controller with a configurable I2C interface. Offset Error Correction reduces RH sensor offset due to aging, exposure to extreme operating conditions, and contaminants to return the device to within accuracy specifications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum24_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-24-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum 24 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum 24 Click driver.

#### Standard key functions :

- `temphum24_cfg_setup` Config Object Initialization function.
```c
void temphum24_cfg_setup ( temphum24_cfg_t *cfg );
```

- `temphum24_init` Initialization function.
```c
err_t temphum24_init ( temphum24_t *ctx, temphum24_cfg_t *cfg );
```

- `temphum24_default_cfg` Click Default Configuration function.
```c
err_t temphum24_default_cfg ( temphum24_t *ctx );
```

#### Example key functions :

- `temphum24_read_temp_and_rh` This function reads the temperature in celsius and the relative humidity level in percents.
```c
err_t temphum24_read_temp_and_rh ( temphum24_t *ctx, float *temp, float *hum );
```

- `temphum24_read_temp_history` This function reads the temperature minimum and maximum values since the beginning of the measurements.
```c
err_t temphum24_read_temp_history ( temphum24_t *ctx, float *temp_min, float *temp_max );
```

- `temphum24_read_rh_history` This function reads the relative humidity minimum and maximum values since the beginning of measurements.
```c
err_t temphum24_read_rh_history ( temphum24_t *ctx, float *hum_min, float *hum_max );
```

## Example Description

> This example demonstrates the use of Temp & Hum 24 Click board by reading the temperature and humidity data.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which resets the device and starts the auto measurement mode with data rate of 1 Hz.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum24_cfg_t temphum24_cfg;  /**< Click config object. */

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
    temphum24_cfg_setup( &temphum24_cfg );
    TEMPHUM24_MAP_MIKROBUS( temphum24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum24_init( &temphum24, &temphum24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM24_ERROR == temphum24_default_cfg ( &temphum24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature (degrees C) and the relative humidity (%RH) data and displays the results on the USB UART approximately once per second.
It also reads and displays the minimum and maximum values measured since the beginning of measurements.

```c
void application_task ( void )
{
    float temp = 0, hum = 0;
    if ( TEMPHUM24_OK == temphum24_read_temp_and_rh ( &temphum24, &temp, &hum ) )
    {
        float min_temp = 0, max_temp = 0;
        float min_rh = 0, max_rh = 0;
        log_printf ( &logger, " Temperature: %.2f C\r\n", temp );
        if ( TEMPHUM24_OK == temphum24_read_temp_history ( &temphum24, &min_temp, &max_temp ) )
        {
            log_printf ( &logger, " MIN: %.2f C\r\n MAX: %.2f C\r\n", min_temp, max_temp );
        }
        log_printf ( &logger, "\r\n Humidity: %.1f %%RH\r\n", hum );
        if ( TEMPHUM24_OK == temphum24_read_rh_history ( &temphum24, &min_rh, &max_rh ) )
        {
            log_printf ( &logger, " MIN: %.1f %%RH\r\n MAX: %.1f %%RH\r\n", min_rh, max_rh );
        }
        log_printf ( &logger, "----------------------\r\n" );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum24

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
