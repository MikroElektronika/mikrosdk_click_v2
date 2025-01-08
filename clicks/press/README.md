
---
# PRESS Click

> [PRESS Click](https://www.mikroe.com/?pid_product=MIKROE-5862) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5862&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PRESS Click board&trade; by reading and displaying
> the pressure, temperature and Qvar measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PRESS

### Example Key Functions

- `press_cfg_setup` Config Object Initialization function.
```c
void press_cfg_setup ( press_cfg_t *cfg );
```

- `press_init` Initialization function.
```c
err_t press_init ( press_t *ctx, press_cfg_t *cfg );
```

- `press_default_cfg` Click Default Configuration function.
```c
err_t press_default_cfg ( press_t *ctx );
```

- `press_get_measurement_data` PRESS gets the measurement data function.
```c
err_t press_get_measurement_data ( press_t *ctx, float *pressure, float *temperature );
```

- `press_get_ah_qvar_data` PRESS gets the AH/Qvar data function.
```c
err_t press_get_ah_qvar_data ( press_t *ctx, float *ah_qvar );
```

- `press_sw_reset` PRESS software reset function.
```c
err_t press_sw_reset ( press_t *ctx );

```

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    press_cfg_t press_cfg;  /**< Click config object. */

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
    press_cfg_setup( &press_cfg );
    PRESS_MAP_MIKROBUS( press_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == press_init( &press, &press_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESS_ERROR == press_default_cfg ( &press ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    
#if ( EXAMPLE_MODE == EXAMPLE_MODE_PRESS_TEMP )
    log_printf( &logger, " Pressure and Temperature\r\n" );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_SWIPE_SENSING )
    if ( PRESS_OK == press_config_ah_qvar( &press, PRESS_AH_QVAR_ENABLE ) )
    {
        log_printf( &logger, " Swipe sensing\r\n" );
    }
    else
    {
        log_error( &logger, " Qvar configuration.\r\n" );
        for ( ; ; );
    }
#endif
    log_printf( &logger, " ______________________ \r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> The demo application shows the module working depending on the example mode:
> - EXAMPLE_MODE_PRESS_TEMP: Reads and displays the Pressure [mBar] and Temperature [degree Celsius] data.
> - EXAMPLE_MODE_SWIPE_SENSING: Detect a touch or a swipe.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#if ( EXAMPLE_MODE == EXAMPLE_MODE_PRESS_TEMP )
    example_pressure_temperature( );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_SWIPE_SENSING )
    example_swipe_sensing( );
#endif
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
