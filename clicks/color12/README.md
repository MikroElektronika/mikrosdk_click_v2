
---
# Color 12 Click

> [Color 12 Click](https://www.mikroe.com/?pid_product=MIKROE-5724) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5724&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Color 12 Click driver.
> The demo application sets sensor configuration 
> and reads and displays RGB/IR measurement results.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color12

### Example Key Functions

- `color12_cfg_setup` Config Object Initialization function.
```c
void color12_cfg_setup ( color12_cfg_t *cfg );
```

- `color12_init` Initialization function.
```c
err_t color12_init ( color12_t *ctx, color12_cfg_t *cfg );
```

- `color12_default_cfg` Click Default Configuration function.
```c
err_t color12_default_cfg ( color12_t *ctx );
```

- `color12_get_color_data` Color 12 gets the color measurement result function.
```c
err_t color12_get_color_data ( color12_t *ctx, color12_color_sel_t color_sel, uint16_t *color_data );
```

- `color12_set_config` Color 12 sets the configuration function.
```c
err_t color12_set_config ( color12_t *ctx, color12_config_t config );
```

- `color12_get_config` Color 12 gets the configuration function.
```c
err_t color12_get_config ( color12_t *ctx, color12_config_t *config );
```

### Application Init

> Initialization of I2C module and log UART.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color12_cfg_t color12_cfg;  /**< Click config object. */

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
    color12_cfg_setup( &color12_cfg );
    COLOR12_MAP_MIKROBUS( color12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color12_init( &color12, &color12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR12_ERROR == color12_default_cfg ( &color12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Color 12 Click board&trade;.
> Reads and displays the results of the RGB/IR measurements.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_RED, &color_data ) )
    {
        log_printf( &logger, " Red : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_GREEN, &color_data ) )
    {
        log_printf( &logger, " Green : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_BLUE, &color_data ) )
    {
        log_printf( &logger, " Blue : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_IR, &color_data ) )
    {
        log_printf( &logger, " IR : %u\r\n", color_data );
    }
    log_printf( &logger, " ---------------------- \r\n" );
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
