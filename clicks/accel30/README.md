
---
# Accel 30 Click

> [Accel 30 Click](https://www.mikroe.com/?pid_product=MIKROE-5550) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5550&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Accel 30 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel30

### Example Key Functions

- `accel30_cfg_setup` Config Object Initialization function.
```c
void accel30_cfg_setup ( accel30_cfg_t *cfg );
```

- `accel30_init` Initialization function.
```c
err_t accel30_init ( accel30_t *ctx, accel30_cfg_t *cfg );
```

- `accel30_default_cfg` Click Default Configuration function.
```c
err_t accel30_default_cfg ( accel30_t *ctx );
```

- `accel30_get_axis` Accel 30 get accel data function.
```c
err_t accel30_get_axis ( accel30_t *ctx, accel30_axis_t *acc_axis );
```

- `accel30_set_resolution_ctrl` Accel 30 set resolution control function.
```c
err_t accel30_set_resolution_ctrl ( accel30_t *ctx, accel30_resolution_t resolution );
```

- `accel30_set_mode` Accel 30 set operating mode function.
```c
err_t accel30_set_mode ( accel30_t *ctx, accel30_op_mode_t mode );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel30_cfg_t accel30_cfg;  /**< Click config object. */

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
    accel30_cfg_setup( &accel30_cfg );
    ACCEL30_MAP_MIKROBUS( accel30_cfg, MIKROBUS_1 );
    err_t init_flag = accel30_init( &accel30, &accel30_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ACCEL30_ERROR == accel30_default_cfg ( &accel30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "       Accel Data       \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 ); 
}
```

### Application Task

> This example demonstrates the use of the Accel 30 Click board&trade;.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static accel30_axis_t axis;
    if ( ACCEL30_OK == accel30_get_axis( &accel30, &axis ) )
    {
        log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "------------------------\r\n" );    
    }
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
