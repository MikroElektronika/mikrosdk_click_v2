
---
# Accel Click

> [Accel Click](https://www.mikroe.com/?pid_product=MIKROE-1194) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1194&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel Click board by reading and displaying the accelerometer data (X, Y, and Z axis).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel

### Example Key Functions

- `accel_cfg_setup` Config Object Initialization function.
```c
void accel_cfg_setup ( accel_cfg_t *cfg );
```

- `accel_init` Initialization function.
```c
err_t accel_init ( accel_t *ctx, accel_cfg_t *cfg );
```

- `accel_default_cfg` Click Default Configuration function.
```c
void accel_default_cfg ( accel_t *ctx );
```

- `accel_read_x_axis` Function reads X axis value from Accel.
```c
int16_t accel_read_x_axis ( accel_t *ctx );
```
 
- `accel_read_y_axis` Function reads Y axis value from Accel.
```c
int16_t accel_read_y_axis ( accel_t *ctx );
```

- `accel_read_z_axis` Function reads Z axis value from Accel.
```c
int16_t accel_read_z_axis ( accel_t *ctx );
```

### Application Init

> Initializes SPI/I2C driver and settings data read format, power mode, FIFO control and baud rate ( 100Hz default ).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel_cfg_t cfg;

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

    accel_cfg_setup( &cfg );
    ACCEL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel_init( &accel, &cfg );

    accel_generic_read( &accel, ACCEL_REG_DEVID, &tmp, 1 );

    if ( tmp == ACCEL_DEVID )
    {
        log_printf( &logger, "---- Comunication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Comunication ERROR!!! ----\r\n" );
        for ( ; ; );
    }
    accel_default_cfg ( &accel );
}
```

### Application Task

> Reads X, Y and Z axis and logs on usbuart every 100 ms.

```c
void application_task ( void )
{
    val_x = accel_read_x_axis( &accel );
    log_printf( &logger, "Axis X : %.3f g\r\n", val_x / ACCEL_DATA_RES_LSB_PER_G );

    val_y = accel_read_y_axis( &accel );
    log_printf( &logger, "Axis Y : %.3f g\r\n", val_y / ACCEL_DATA_RES_LSB_PER_G );

    val_z = accel_read_z_axis( &accel );
    log_printf( &logger, "Axis Z : %.3f g\r\n", val_z / ACCEL_DATA_RES_LSB_PER_G );

    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 100 );
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
