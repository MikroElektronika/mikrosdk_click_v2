
---
# Accel 17 Click

> [Accel 17 Click](https://www.mikroe.com/?pid_product=MIKROE-4855) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4855&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases ability of the device to read
x, y axis orientation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel17

### Example Key Functions

- `accel17_cfg_setup` Config Object Initialization function.
```c
void accel17_cfg_setup ( accel17_cfg_t *cfg );
```

- `accel17_init` Initialization function.
```c
err_t accel17_init ( accel17_t *ctx, accel17_cfg_t *cfg );
```

- `accel17_default_cfg` Click Default Configuration function.
```c
err_t accel17_default_cfg ( accel17_t *ctx );
```

- `accel17_get_axes_data` Accel data reading.
```c
err_t accel17_get_axes_data ( accel17_t *ctx, accel17_axes_t *axes );
```

- `accel17_generic_read` Reading function.
```c
err_t accel17_generic_read ( accel17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

- `accel17_generic_write` Writing function.
```c
err_t accel17_generic_write ( accel17_t *ctx, uint8_t reg, uint8_t tx_data );
```

### Application Init

> Initialization of communication modules(I2C, UART), and
configures device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel17_cfg_t accel17_cfg;  /**< Click config object. */

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
    accel17_cfg_setup( &accel17_cfg );
    ACCEL17_MAP_MIKROBUS( accel17_cfg, MIKROBUS_1 );
    err_t init_flag = accel17_init( &accel17, &accel17_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    accel17_default_cfg ( &accel17 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads axis data and calculates it and logs result every 300ms.

```c
void application_task ( void ) 
{
    accel17_axes_t axes;
    accel17_get_axes_data ( &accel17, &axes );
    log_printf( &logger, " > X[degree]: %.2f\r\n > Y[degree]: %.2f\r\n", axes.x, axes.y );
    log_printf( &logger, "*********************************\r\n" );
    Delay_ms ( 300 );
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
