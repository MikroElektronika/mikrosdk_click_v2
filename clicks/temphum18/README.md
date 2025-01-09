
---
# Temp&Hum 18 Click

> [TempHum 18 Click](https://www.mikroe.com/?pid_product=MIKROE-4892) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4892&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Temp&Hum 18 Click driver.
> This demo application shows an example of 
> relative humidity and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum18

### Example Key Functions

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

> This is an example that shows the use of a Temp&Hum 18 Click board&trade;.
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
