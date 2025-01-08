
---
# eFuse 5 Click

> [eFuse 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5599) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5599&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the eFuse 5 Click driver.
> This driver provides the functions to set the current limiting conditions 
> to provide the threshold of the fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse5

### Example Key Functions

- `efuse5_cfg_setup` Config Object Initialization function.
```c
void efuse5_cfg_setup ( efuse5_cfg_t *cfg );
```

- `efuse5_init` Initialization function.
```c
err_t efuse5_init ( efuse5_t *ctx, efuse5_cfg_t *cfg );
```

- `efuse5_default_cfg` Click Default Configuration function.
```c
err_t efuse5_default_cfg ( efuse5_t *ctx );
```

- `efuse5_set_current_limit` eFuse 5 set the current limit function.
```c
err_t efuse5_set_current_limit ( efuse5_t *ctx, efuse5_current_limit_t current_limit );
```

- `efuse5_set_resistance` eFuse 5 set the resistance function.
```c
err_t efuse5_set_resistance ( efuse5_t *ctx, uint16_t res_ohm );
```

- `efuse5_get_fault` eFuse 5 gets fault condition state function.
```c
uint8_t efuse5_get_fault ( efuse5_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse5_cfg_t efuse5_cfg;  /**< Click config object. */

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
    efuse5_cfg_setup( &efuse5_cfg );
    EFUSE5_MAP_MIKROBUS( efuse5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == efuse5_init( &efuse5, &efuse5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE5_ERROR == efuse5_default_cfg( &efuse5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the eFuse 5 Click board&trade;.
> In this example, the app sets the current limit to 600 mA for 10 seconds 
> and then sets the current limit to 1200 mA for the next 10 seconds
> to protect the electrical circuit against excessive current.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( EFUSE5_OK == efuse5_set_current_limit( &efuse5, EFUSE5_CURRENT_LIMIT_600_mA ) )
    {
        log_printf( &logger, "  Current limit:  600 mA   \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( EFUSE5_OK == efuse5_set_current_limit( &efuse5, EFUSE5_CURRENT_LIMIT_1200_mA ) )
    {
        log_printf( &logger, "  Current limit: 1200 mA   \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
