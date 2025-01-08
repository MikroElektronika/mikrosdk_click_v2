
---
# TempHum 24 Click

> [TempHum 24 Click](https://www.mikroe.com/?pid_product=MIKROE-5651) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5651&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Temp & Hum 24 Click board by reading the temperature and humidity data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum24

### Example Key Functions

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
