
---
# Temp&Hum 18 Click

> Temp&Hum 18 Click is a compact add-on board that represents temperature and humidity sensing solutions. This board features the HS3003, a highly accurate, fully calibrated relative humidity and temperature sensor from Renesas. It features proprietary sensor-level protection, ensuring high reliability and long-term stability. Integrated calibration and temperature-compensation logic provides fully corrected RH and temperature values via standard I2C output. No user calibration of the output data is required. The high accuracy, fast measurement response time, and long-term stability make this Click board™ ideal for various temperature and humidity-related applications and a vast number of applications ranging from portable devices to products designed for harsh environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temphum18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temphum-18-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the TempHum18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempHum18 Click driver.

#### Standard key functions :

- `temphum18_cfg_setup` Config Object Initialization function.
```c
void temphum18_cfg_setup ( temphum18_cfg_t *cfg );
```

- `temphum18_init` Initialization function.
```c
err_t temphum18_init ( temphum18_t *ctx, temphum18_cfg_t *cfg );
```

- `temphum18_default_cfg` Click Default Configuration function.
```c
err_t temphum18_default_cfg ( temphum18_t *ctx );
```

#### Example key functions :

- `temphum18_get_temp_hum` Temp&Hum 18 get temperature and humidity function.
```c
err_t temphum18_get_temp_hum ( temphum18_t *ctx, uint8_t resolution, float *temperature, float *humidity );
```

- `temphum18_wake_up` Temp&Hum 18 wake up function.
```c
err_t temphum18_wake_up ( temphum18_t *ctx );
```

- `temphum18_get_raw_data` Temp&Hum 18 get raw data function.
```c
err_t temphum18_get_raw_data ( temphum18_t *ctx, uint8_t resolution, int16_t *temp, uint16_t *hum, uint8_t *status );
```

## Example Description

> This library contains API for the Temp&Hum 18 Click driver.
> This demo application shows an example of 
> relative humidity and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, 
> the app display retrieves the sensor parameters 
> such as temperature and relative humidity.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum18_cfg_t temphum18_cfg;  /**< Click config object. */

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
    temphum18_cfg_setup( &temphum18_cfg );
    TEMPHUM18_MAP_MIKROBUS( temphum18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum18_init( &temphum18, &temphum18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM18_ERROR == temphum18_default_cfg ( &temphum18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a Temp&Hum 18 Click board™.
> Logs the temperature [ degree Celsius ] and relative humidity [ % ] data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static float temperature;
    static float humidity;
    
    if ( temphum18_get_temp_hum( &temphum18, TEMPHUM18_RESOLUTION_14_BITS, &temperature, &humidity ) == TEMPHUM18_STATUS_VALID_DATA ) 
    {
        log_printf( &logger, "  Temperature : %.02f C\r\n  Humidity    : %.02f %%\r\n", temperature, humidity );
    } 
    else 
    {
        log_printf( &logger, "     Measurement Error\r\n\tStale Data\r\n" );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
