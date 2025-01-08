
---
# Shake2Wake Click

> [Shake2Wake Click](https://www.mikroe.com/?pid_product=MIKROE-1942) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1942&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This app shows the capabilities of the Shake2Wake Click by
> reading values of an accelerometer.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Shake2Wake

### Example Key Functions

- `shake2wake_cfg_setup` Config Object Initialization function.
```c
void shake2wake_cfg_setup ( shake2wake_cfg_t *cfg ); 
```

- `shake2wake_init` Initialization function.
err_t shake2wake_init ( shake2wake_t *ctx, shake2wake_cfg_t *cfg );

- `shake2wake_default_cfg` Click Default Configuration function.
```c
void shake2wake_default_cfg ( shake2wake_t *ctx );
```

- `shake2wake_get_lo_res_raw_data` This function is used to read 8-bit acceleration data per axis.
```c
void shake2wake_get_lo_res_raw_data ( shake2wake_t *ctx, int8_t *x_val, int8_t *y_val, int8_t *z_val );
```

- `shake2wake_get_raw_data` This function is used to read the 3-axis raw data from the accelerometer.
```c
void shake2wake_get_raw_data ( shake2wake_t *ctx, int16_t *x_val, int16_t *y_val, int16_t *z_val )
```

- `shake2wake_read_temperature` This function is used to read temperature from an internal sensor.
```c
float shake2wake_read_temperature ( shake2wake_t *ctx );
```

### Application Init

> Initalizes device and applies default settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    shake2wake_cfg_t cfg;

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
    shake2wake_cfg_setup( &cfg );
    SHAKE2WAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    shake2wake_init( &shake2wake, &cfg );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "    Shake2Wake  Click     \r\n" );
    log_printf( &logger, "--------------------------\r\n" );

    shake2wake_default_cfg( &shake2wake );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example that shows the capabilities of the Shake2Wake Click by
> reading values of an accelerometer and logging them on USART terminal and,
> in case of an interrupt, it raises voltage on the connector.

```c
void application_task ( void )
{
    float temperature = 0;
    int16_t x_val = 0;
    int16_t y_val = 0;
    int16_t z_val = 0;

    shake2wake_get_raw_data( &shake2wake, &x_val, &y_val, &z_val );
    temperature = shake2wake_read_temperature( &shake2wake );

    log_printf( &logger, "X axis: %d\r\n", x_val );
    log_printf( &logger, "Y axis: %d\r\n", y_val );
    log_printf( &logger, "Z axis: %d\r\n", z_val );
    log_printf( &logger, "Temperature: %.2f degC\r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" );
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
