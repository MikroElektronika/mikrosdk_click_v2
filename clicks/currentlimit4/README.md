
---
# Current Limit 4 Click

> [Current Limit 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5900) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5900&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This library contains API for the Current Limit 4 Click driver 
> for the current limiting to a certain value and 
> displays the sources a current proportional to the load current [A].

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit4

### Example Key Functions

- `currentlimit4_cfg_setup` Config Object Initialization function.
```c
void currentlimit4_cfg_setup ( currentlimit4_cfg_t *cfg );
```

- `currentlimit4_init` Initialization function.
```c
err_t currentlimit4_init ( currentlimit4_t *ctx, currentlimit4_cfg_t *cfg );
```

- `currentlimit4_default_cfg` Click Default Configuration function.
```c
err_t currentlimit4_default_cfg ( currentlimit4_t *ctx );
```

- `currentlimit4_set_limit` Current Limit 4 set current limit function.
```c
err_t currentlimit4_set_limit ( currentlimit4_t *ctx, currentlimit4_limit_t current_limit );
```

- `currentlimit4_get_current` Current Limit 4 get current function.
```c
err_t currentlimit4_get_current ( currentlimit4_t *ctx, float *current );
```

- `currentlimit4_get_power_good` Current Limit 4 power good indication function.
```c
uint8_t currentlimit4_get_power_good ( currentlimit4_t *ctx );
```

### Application Init

> Initialization of I2C and ADC module and log UART.
> After driver initialization, the app executes a default configuration 
> and set the minimum current limit threshold to 1.0 [A].

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit4_cfg_t currentlimit4_cfg;  /**< Click config object. */

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
    currentlimit4_cfg_setup( &currentlimit4_cfg );
    CURRENTLIMIT4_MAP_MIKROBUS( currentlimit4_cfg, MIKROBUS_1 );
    err_t init_flag = currentlimit4_init( &currentlimit4, &currentlimit4_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT4_ERROR == currentlimit4_default_cfg ( &currentlimit4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Current Limit 4 Click board&trade;. 
> The demo application displays the source current proportional to the load current
> and an appropriate message when the current reaches the limit.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float current = 0;
    if ( CURRENTLIMIT4_OK == currentlimit4_get_current( &currentlimit4, &current ) ) 
    {
        if ( CURRENTLIMIT4_POWER_GOOD == currentlimit4_get_power_good( &currentlimit4 ) )
        {
            log_printf( &logger, " Current : %.3f [A]\r\n", current );
        }
        else
        {
            log_printf( &logger, " Input voltage is lower then undervoltage protection threshold.\r\n" );
        }
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
