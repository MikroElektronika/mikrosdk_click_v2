
---
# Battery Source Click

> [Battery Source Click](https://www.mikroe.com/?pid_product=MIKROE-6090) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6090&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Battery Source Click board, 
 by changing state of the output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BatterySource

### Example Key Functions

- `batterysource_cfg_setup` Config Object Initialization function.
```c
void batterysource_cfg_setup ( batterysource_cfg_t *cfg );
```

- `batterysource_init` Initialization function.
```c
err_t batterysource_init ( batterysource_t *ctx, batterysource_cfg_t *cfg );
```

- `batterysource_set_output` This function is used to set output state of Battery Source Click board.
```c
void batterysource_set_output ( batterysource_t *ctx, uint8_t output_state );
```

### Application Init

> Initializes the driver and disables the output.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    batterysource_cfg_t batterysource_cfg;  /**< Click config object. */

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
    batterysource_cfg_setup( &batterysource_cfg );
    BATTERYSOURCE_MAP_MIKROBUS( batterysource_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == batterysource_init( &batterysource, &batterysource_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    batterysource_set_output( &batterysource, BATTERYSOURCE_DISABLE_OUTPUT );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Enabling output for 5 seconds, then disabling it for 5 seconds.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Output is enabled \r\n" );
    batterysource_set_output( &batterysource, BATTERYSOURCE_ENABLE_OUTPUT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Output is disabled \r\n" );
    batterysource_set_output( &batterysource, BATTERYSOURCE_DISABLE_OUTPUT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
