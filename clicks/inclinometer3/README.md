
---
# Inclinometer 3 Click

> [Inclinometer 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6050) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6050&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the Inclinometer 3 Click driver.
> The library initializes and defines the SPI drivers to 
> write and read data from registers, as well as the default configuration 
> for the reading accelerator and temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer3

### Example Key Functions

- `inclinometer3_cfg_setup` Config Object Initialization function.
```c
void inclinometer3_cfg_setup ( inclinometer3_cfg_t *cfg );
```

- `inclinometer3_init` Initialization function.
```c
err_t inclinometer3_init ( inclinometer3_t *ctx, inclinometer3_cfg_t *cfg );
```

- `inclinometer3_default_cfg` Click Default Configuration function.
```c
err_t inclinometer3_default_cfg ( inclinometer3_t *ctx );
```

- `inclinometer3_get_axes` This function reads the accelerometer sensor axes data by using SPI serial interface.
```c
err_t inclinometer3_get_axes ( inclinometer3_t *ctx, float *x_axes, float *y_axes );
```

- `inclinometer3_get_temperature` This function reads the temperature measurement data by using SPI serial interface.
```c
err_t inclinometer3_get_temperature ( inclinometer3_t *ctx, float *temperature );
```

### Application Init

> The initialization of the SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer3_cfg_t inclinometer3_cfg;  /**< Click config object. */

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
    inclinometer3_cfg_setup( &inclinometer3_cfg );
    INCLINOMETER3_MAP_MIKROBUS( inclinometer3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == inclinometer3_init( &inclinometer3, &inclinometer3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER3_ERROR == inclinometer3_default_cfg ( &inclinometer3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ________________________ \r\n" );
}
```

### Application Task

> This example demonstrates the use of the Inclinometer 3 Click board.
> Measures and displays acceleration data for the XY-axis [mg] 
> and temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float temperature = 0, x_axes = 0, y_axes = 0;
    if ( ( INCLINOMETER3_OK == inclinometer3_get_temperature( &inclinometer3, &temperature ) ) && 
         ( INCLINOMETER3_OK == inclinometer3_get_axes( &inclinometer3, &x_axes, &y_axes ) ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", x_axes );
        log_printf( &logger, " Accel Y: %.2f mg\r\n\r\n", y_axes );
        log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
        log_printf( &logger, " ________________________ \r\n" );
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
