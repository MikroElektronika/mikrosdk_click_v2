
---
# AccelPressure Click

> [AccelPressure Click](https://www.mikroe.com/?pid_product=MIKROE-6028) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6028&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the AccelPressure Click driver.
> The library initializes and defines the I2C drivers to 
> write and read data from registers, as well as the default configuration 
> for reading the accelerator, pressure, and temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AccelPressure

### Example Key Functions

- `accelpressure_cfg_setup` Config Object Initialization function.
```c
void accelpressure_cfg_setup ( accelpressure_cfg_t *cfg );
```

- `accelpressure_init` Initialization function.
```c
err_t accelpressure_init ( accelpressure_t *ctx, accelpressure_cfg_t *cfg );
```

- `accelpressure_default_cfg` Click Default Configuration function.
```c
err_t accelpressure_default_cfg ( accelpressure_t *ctx );
```

- `accelpressure_get_axes_data` This function reads the accelerometer sensor axes data.
```c
err_t accelpressure_get_axes_data ( accelpressure_t *ctx, accelpressure_axes_t *axes );
```

- `accelpressure_get_pressure` This function reads the sensor pressure data conversion in mbar.
```c
err_t accelpressure_get_pressure ( accelpressure_t *ctx, float *pressure );
```

- `accelpressure_get_temperature` This function reads the conversion of sensor pressure data in degrees Celsius.
```c
err_t accelpressure_get_temperature ( accelpressure_t *ctx, float *temperature );
```

### Application Init

> The initialization of the I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accelpressure_cfg_t accelpressure_cfg;  /**< Click config object. */

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
    accelpressure_cfg_setup( &accelpressure_cfg );
    ACCELPRESSURE_MAP_MIKROBUS( accelpressure_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accelpressure_init( &accelpressure, &accelpressure_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCELPRESSURE_ERROR == accelpressure_default_cfg ( &accelpressure ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}
```

### Application Task

> This example demonstrates the use of the AccelPressure Click board.
> Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis [mg],
> pressure [mBar], and temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    accelpressure_axes_t acc_axis;
    float pressure = 0, temperature = 0;
    if ( ACCELPRESSURE_OK == accelpressure_get_axes_data( &accelpressure, &acc_axis ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
    }
    log_printf( &logger, "_________________\r\n" );
    Delay_ms ( 100 );

    if ( ACCELPRESSURE_OK == accelpressure_get_pressure( &accelpressure, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.2f mbar\r\n", pressure );
    }
    Delay_ms ( 100 );

    if ( ACCELPRESSURE_OK == accelpressure_get_temperature( &accelpressure, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f mbar\r\n", temperature );
    }
    log_printf( &logger, "_________________\r\n" );
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
