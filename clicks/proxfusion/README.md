
---
# ProxFusion Click

> [ProxFusion Click](https://www.mikroe.com/?pid_product=MIKROE-2920) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2920&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This demo-app reads and displays touch events using ProxFusion Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ProxFusion

### Example Key Functions

- `proxfusion_cfg_setup` Config Object Initialization function.
```c
void proxfusion_cfg_setup ( proxfusion_cfg_t *cfg ); 
```

- `proxfusion_init` Initialization function.
```c
err_t proxfusion_init ( proxfusion_t *ctx, proxfusion_cfg_t *cfg );
```

- `proxfusion_default_cfg` Click Default Configuration function.
```c
err_t proxfusion_default_cfg ( proxfusion_t *ctx );
```

- `proxfusion_get_touch` Touch event
```c
uint8_t proxfusion_get_touch ( proxfusion_t *ctx );
```

- `proxfusion_set_system_reg` Sets system register
```c
err_t proxfusion_set_system_reg ( proxfusion_t *ctx, uint8_t cfg );
```

- `proxfusion_set_event_reg` Selecting events
```c
err_t proxfusion_set_event_reg ( proxfusion_t *ctx, uint8_t cfg );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proxfusion_cfg_t proxfusion_cfg;  /**< Click config object. */

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
    proxfusion_cfg_setup( &proxfusion_cfg );
    PROXFUSION_MAP_MIKROBUS( proxfusion_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proxfusion_init( &proxfusion, &proxfusion_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXFUSION_ERROR == proxfusion_default_cfg ( &proxfusion ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
} 
```

### Application Task

> Checks if a new touch event occurred and prints(logs) event message on usbuart.

```c
void application_task ( void )
{
    uint8_t touch = proxfusion_get_touch( &proxfusion );
    if ( 1 == touch )
    {
        log_printf( &logger, " Touch button 1 is pressed\r\n" );
    }
    else if ( 2 == touch )
    {
        log_printf( &logger, " Touch button 2 is pressed\r\n" );
    }
    else if ( 3 == touch )
    {
        log_printf( &logger, " Both touch buttons are pressed\r\n" );
    }
    Delay_ms ( 100 );
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
