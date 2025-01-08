
---
# Accel 21 Click

> [Accel 21 Click](https://www.mikroe.com/?pid_product=MIKROE-5530) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5530&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Accel 21 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel21

### Example Key Functions

- `accel21_cfg_setup` Config Object Initialization function.
```c
void accel21_cfg_setup ( accel21_cfg_t *cfg );
```

- `accel21_init` Initialization function.
```c
err_t accel21_init ( accel21_t *ctx, accel21_cfg_t *cfg );
```

- `accel21_default_cfg` Click Default Configuration function.
```c
err_t accel21_default_cfg ( accel21_t *ctx );
```

- `accel21_set_config` Accel 21 set config function.
```c
err_t accel21_set_config ( accel21_t *ctx, accel21_config_t config );
```

- `accel21_get_axis` Accel 21 get accel data function.
```c
err_t accel21_get_axis ( accel21_t *ctx, accel21_axis_t *acc_axis );
```

- `accel21_get_temperature` Accel 21 get temperature function.
```c
err_t accel21_get_temperature ( accel21_t *ctx, float *temperature );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app executes a default configuration,
> checks communication and device ID. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel21_cfg_t accel21_cfg;  /**< Click config object. */

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
    accel21_cfg_setup( &accel21_cfg );
    ACCEL21_MAP_MIKROBUS( accel21_cfg, MIKROBUS_1 );
    err_t init_flag = accel21_init( &accel21, &accel21_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL21_ERROR == accel21_default_cfg ( &accel21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( ACCEL21_ERROR == accel21_check_id ( &accel21 ) )
    {
        log_printf( &logger, " Communication ERROR \r\n" );
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

> This example demonstrates the use of the Accel 21 Click board&trade;.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static accel21_axis_t axis;
    accel21_get_axis( &accel21, &axis );
    log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n", axis.x, axis.y, axis.z );
    log_printf( &logger, "------------------------\r\n" );
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
