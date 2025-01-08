
---
# Temp Hum Click

> [TempHum Click](https://www.mikroe.com/?pid_product=MIKROE-1971) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1971&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures temperature and humidity, with temperature in range of 0 - 60 deg.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempHum

### Example Key Functions

- `temphum_cfg_setup` Config Object Initialization function. 
```c
void temphum_cfg_setup ( temphum_cfg_t *cfg );
``` 
 
- `temphum_init` Initialization function. 
```c
err_t temphum_init ( temphum_t *ctx, temphum_cfg_t *cfg );
```

- `temphum_default_cfg` Click Default Configuration function. 
```c
void temphum_default_cfg ( temphum_t *ctx );
```

- Function gets temperature value in degrees Celsius [ �C ]
  and humidity value in percentage [ % ] by reading from the
  two target 8-bit register address of HTS221 sensor on Temp&Hum Click
  and converts it by performing linear interpolation on read data.
> void temphum_get_temp_hum ( temphum_t *ctx, float *temperature, float *humidity );

- Function get temperature value in degrees Celsius [ �C ]
  from HTS221 sensor on Temp&Hum Click.
> float temphum_get_temperature( temphum_t *ctx );

- Function get humidity value in percentage [ % ]
  from HTS221 sensor on Temp&Hum Click.
> float temphum_get_humidity( temphum_t *ctx );

### Application Init

>  Initialization driver enable's - I2C,
>  set default configuration and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum_cfg_setup( &cfg );
    TEMPHIM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum_init( &temphum, &cfg );

    temphum_default_cfg( &temphum );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      Temp&Hum Click      \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "       Initializing       \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms ( 100 );
}
```

### Application Task

> This is a example which demonstrates the use of TempAndHum Click board.
> Measured temperature and humidity data from the HTS221 sensor.
> Convert temperature data to degrees Celsius [ �C ] and humidity data to percentarg [ % ].
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 3 sec.

```c
void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float humidity;

    temperature = temphum_get_temperature( &temphum );

    humidity = temphum_get_humidity( &temphum );

    log_printf( &logger, " Temperature :  %.2f C\r\n", temperature );

    log_printf( &logger, " Humidity    : %.2f %%\r\n", humidity );

    log_printf( &logger, "--------------------------\r\n" );
    
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
