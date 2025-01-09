
---
# TempHum 19 Click

> [TempHum 19 Click](https://www.mikroe.com/?pid_product=MIKROE-4922) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4922&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Temp & Hum 19 Click board by reading the temperature and humidity data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum19

### Example Key Functions

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
