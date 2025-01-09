
---
# Barometer 5 Click

> [Barometer 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4924) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4924&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Barometer 5 Click driver.
> The demo application reads and calculate temperature and pressure data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer5

### Example Key Functions

- `barometer5_cfg_setup` Config Object Initialization function.
```c
void barometer5_cfg_setup ( barometer5_cfg_t *cfg );
```

- `barometer5_init` Initialization function.
```c
err_t barometer5_init ( barometer5_t *ctx, barometer5_cfg_t *cfg );
```

- `barometer5_default_cfg` Click Default Configuration function.
```c
err_t barometer5_default_cfg ( barometer5_t *ctx );
```

- `barometer5_get_data` Barometer 5 get data function.
```c
err_t barometer5_get_data ( barometer5_t *ctx, float *temperature, float *pressure );
```

- `barometer5_get_pressure` Barometer 5 get pressure data function.
```c
err_t barometer5_get_pressure ( barometer5_t *ctx, float *pressure );
```

- `barometer5_get_temperature` Barometer 5 get temperature data function.
```c
err_t barometer5_get_temperature ( barometer5_t *ctx, float *temperature );
```

### Application Init

> Initializes I2C driver and log UART.
> After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer5_cfg_t barometer5_cfg;  /**< Click config object. */

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
    barometer5_cfg_setup( &barometer5_cfg );
    BAROMETER5_MAP_MIKROBUS( barometer5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer5_init( &barometer5, &barometer5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER5_ERROR == barometer5_default_cfg ( &barometer5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the Barometer 5 Click board&trade;.
> In this example, display the Pressure ( mBar ) and Temperature ( degree Celsius ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static float temperature;
    static float pressure;
    
    if ( barometer5_get_data( &barometer5, &temperature, &pressure ) == BAROMETER5_OK )
    {
        log_printf( &logger, " Pressure    : %.2f mbar   \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C      \r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );
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
