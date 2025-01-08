
---
# Gyro 5 Click

> [Gyro 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3669) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3669&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application shows temperature and gyroscope axes values

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro5

### Example Key Functions

- `gyro5_cfg_setup` Config Object Initialization function. 
```c
void gyro5_cfg_setup ( gyro5_cfg_t *cfg );
``` 
 
- `gyro5_init` Initialization function. 
```c
err_t gyro5_init ( gyro5_t *ctx, gyro5_cfg_t *cfg );
```

- `gyro5_default_cfg` Click Default Configuration function. 
```c
void gyro5_default_cfg ( gyro5_t *ctx );
```

- `gyro5_get_axes` Getting gyroscope axes values. 
```c
void gyro5_get_axes ( gyro5_t *ctx, float *x_axis, float *y_axis, float *z_axis );
```
 
- `gyro5_get_temperature` Getting temperature value. 
```c
void gyro5_get_temperature ( gyro5_t *ctx, float *temperature );
```

- `gyro5_default_cfg` Click Default Configuration function. 
```c
void gyro5_default_cfg ( gyro5_t *ctx );
```

### Application Init

> Initializes GPIO pins, I2C and LOG modules.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro5_cfg_t cfg;

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

    gyro5_cfg_setup( &cfg );
    GYRO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro5_init( &gyro5, &cfg );
    gyro5_default_cfg ( &gyro5 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "      Gyro 5 Click\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Application Task

> Checks data ready INT, gets temperature and axes data and LOGs those values

```c
void application_task ( void )
{
    //  Task implementation.
    
    data_ready_flag = gyro5_int_status( &gyro5, GYRO5_INT_DATA_RDY );
    
    if ( data_ready_flag == GYRO5_STATUS_INT_DATA_RDY )
    {
        gyro5_get_temperature( &gyro5, &temperature_value );
        Delay_ms ( 10 );
        gyro5_get_axes(  &gyro5, &x_axis_value, &y_axis_value, &z_axis_value );
        Delay_ms ( 10 );
        log_printf( &logger, " Temperature = %.2f C\r\n", temperature_value );
        log_printf( &logger, " X axis = %.2f deg/s\r\n", x_axis_value );
        log_printf( &logger, " Y axis = %.2f deg/s\r\n", y_axis_value );
        log_printf( &logger, " Z axis = %.2f deg/s\r\n", z_axis_value );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms ( 1000 );
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
