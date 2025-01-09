
---
# HDC1000 Click

> [HDC1000 Click](https://www.mikroe.com/?pid_product=MIKROE-1797) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1797&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordevic
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

>
> Demo application code is used for measuring temperature and humidity.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HDC1000

### Example Key Functions

- `hdc1000_cfg_setup` Config Object Initialization function. 
```c
void hdc1000_cfg_setup ( hdc1000_cfg_t *cfg );
``` 
 
- `hdc1000_init` Initialization function. 
```c
err_t hdc1000_init ( hdc1000_t *ctx, hdc1000_cfg_t *cfg );
```

- `hdc1000_default_cfg` Click Default Configuration function. 
```c
void hdc1000_default_cfg ( hdc1000_t *ctx );
```

- `hdc1000_default_cfg` This function executes default configuration for HDC1000 Click. 
```c
 hdc1000_default_cfg ( &hdc1000 );
```
 
- `hdc1000_get_temperature_data` This function gets temperature data from the HDC1000 sensor. 
```c
 hdc1000_get_temperature_data ( &hdc1000 );
```

- `hdc1000_get_humidity_data` This function gets humidity data from the HDC1000 sensor. 
```c
 hdc1000_get_humidity_data ( &hdc1000 );
```

### Application Init

>
> AppInit is used for Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hdc1000_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ---- \r\n\n" );

    //  Click initialization.

    hdc1000_cfg_setup( &cfg );
    HDC1000_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hdc1000_init( &hdc1000, &cfg );
    
    hdc1000_default_cfg( &hdc1000 );
    log_printf( &logger, "---- Start measurement ---- \r\n\n" );
    Delay_ms ( 1000 );
    
}
```

### Application Task

>
> This is an example which demonstrates the usage of HDC1000 Click board.
> HDC1000 measure temperature and humidity, and calculate dewpoint value from the HDC1000 sensor.
> 

```c
void application_task ( void )
{
    temperature = hdc1000_get_temperature_data( &hdc1000 );
    log_printf( &logger, " Temperature : %f C \r\n", temperature );
    
    humidity = hdc1000_get_humidity_data( &hdc1000 );
    log_printf( &logger, " Humidity : %f % \r\n", humidity );

    log_printf( &logger, "----------------------------------- \r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
