
---
# Barometer 10 Click

> [Barometer 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5601) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5601&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Barometer 10 Click board&trade;.
> The demo application reads and calculates pressure and temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer10

### Example Key Functions

- `barometer10_cfg_setup` Config Object Initialization function.
```c
void barometer10_cfg_setup ( barometer10_cfg_t *cfg );
```

- `barometer10_init` Initialization function.
```c
err_t barometer10_init ( barometer10_t *ctx, barometer10_cfg_t *cfg );
```

- `barometer10_default_cfg` Click Default Configuration function.
```c
err_t barometer10_default_cfg ( barometer10_t *ctx );
```

- `barometer10_get_pressure` Barometer 10 gets pressure function.
```c
err_t barometer10_get_pressure ( barometer10_t *ctx, float *pressure )
```

- `barometer10_get_temperature` Barometer 10 gets temperature function.
```c
err_t barometer10_get_temperature ( barometer10_t *ctx, float *temperature );
```

### Application Init

> The initialization of the I2C module, log UART and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer10_cfg_t barometer10_cfg;  /**< Click config object. */

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
    barometer10_cfg_setup( &barometer10_cfg );
    BAROMETER10_MAP_MIKROBUS( barometer10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer10_init( &barometer10, &barometer10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER10_ERROR == barometer10_default_cfg ( &barometer10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
}
```

### Application Task

> This example displays the Pressure [mBar] and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float pressure, temperature;
    if ( BAROMETER10_OK == barometer10_get_pressure( &barometer10, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.2f [mbar] \r\n", pressure );
    }
    
    if ( BAROMETER10_OK == barometer10_get_temperature( &barometer10, &temperature ) )
    {
        log_printf( &logger, " Temperature : %.2f [deg c] \r\n", temperature );
    }
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
