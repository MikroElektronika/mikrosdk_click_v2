
---
# TempHum 3 Click

> [TempHum 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2937) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2937&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads temperature and humidity data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum3

### Example Key Functions

- `temphum3_cfg_setup` Config Object Initialization function.
```c
void temphum3_cfg_setup ( temphum3_cfg_t *cfg ); 
```

- `temphum3_init` Initialization function.
```c
err_t temphum3_init ( temphum3_t *ctx, temphum3_cfg_t *cfg );
```

- `temphum3_default_cfg` Click Default Configuration function.
```c
void temphum3_default_cfg ( temphum3_t *ctx );
```

- `temphum3_get_temperature` Get temperature value
```c
float temphum3_get_temperature ( temphum3_t *ctx );
```

- `temphum3_get_huminidy` Get humidity value
```c
float temphum3_get_huminidy ( temphum3_t *ctx );
```

- `temphum3_get_max_hum` Get maximum temperature value
```c
float temphum3_get_max_hum ( temphum3_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum3_cfg_t temphum3_cfg;

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

    //  Click initialization.
    temphum3_cfg_setup( &temphum3_cfg );
    TEMPHUM3_MAP_MIKROBUS( temphum3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum3_init( &temphum3, &temphum3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    temphum3_default_cfg( &temphum3 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature and huminidy and logs results to the USB UART every 500 ms.

```c
void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    temperature = temphum3_get_temperature( &temphum3 );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    humidity = temphum3_get_humidity( &temphum3 );
    log_printf( &logger, " Humidity : %.1f %% \r\n", humidity );
    Delay_ms ( 500 );
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
