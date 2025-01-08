
---
# Gyro 3 Click

> [Gyro 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3449) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3449&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example checks if new data is available on all three axes, If yes then reads and logs their values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro3

### Example Key Functions

- `gyro3_cfg_setup` Config Object Initialization function. 
```c
void gyro3_cfg_setup ( gyro3_cfg_t *cfg );
``` 
 
- `gyro3_init` Initialization function. 
```c
err_t gyro3_init ( gyro3_t *ctx, gyro3_cfg_t *cfg );
```

- `gyro3_default_cfg` Click Default Configuration function. 
```c
void gyro3_default_cfg ( gyro3_t *ctx );
```

- `gyro3_get_temp` This function reads value stored in temperature register (26h). 
```c
void gyro3_get_temp ( gyro3_t *ctx, uint8_t *temperature_value );
```

- `gyro3_get_fifo_data_level` This function reads data level value in FIFO register from FIFO SRC register (2Fh) and stores result in fifo_data_level. 
```c
void gyro3_get_fifo_data_level ( gyro3_t *ctx, uint8_t * fifo_data_level );
```

- `gyro3_get_axes` This function reads values from XYZ axes registers and converts them to degrees per second value. 
```c
void gyro3_get_axes ( gyro3_t *ctx, float *x_axis, float *y_axis, float *z_axis, uint8_t measurement_range );
```




### Application Init

> Initialize I2C driver, basic device configuration, I2C interface, LOG interface and GPIO pins.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro3_cfg_t cfg;

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

    gyro3_cfg_setup( &cfg );
    GYRO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro3_init( &gyro3, &cfg );
    gyro3_default_cfg( &gyro3 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Check if new data is available on all three axes, If yes then read and log their values.

```c
void application_task ( void )
{
    //  Task implementation.

    gyro3_get_status( &gyro3, &status_register );

    if ((status_register & GYRO3_ZYX_NEW_DATA_MASK) == GYRO3_ZYX_NEW_DATA_MASK)
    {

        gyro3_get_axes( &gyro3, &x_axis, &y_axis, &z_axis, GYRO3_MEAS_RANGE_2000 );

        log_printf( &logger, "\r\nx_axis : %.2f %s\t", x_axis, degrees_per_second );
        log_printf( &logger, "y_axis : %.2f %s\t", y_axis, degrees_per_second );
        log_printf( &logger, "z_axis : %.2f %s\r\n", z_axis, degrees_per_second );      
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
