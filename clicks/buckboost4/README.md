
---
# Buck-Boost 4 Click

> [Buck-Boost 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5924) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5924&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Buck-Boost 4 Click board&trade;.
> This driver provides functions for device configurations and for the output voltage setting.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost4

### Example Key Functions

- `buckboost4_cfg_setup` Config Object Initialization function.
```c
void buckboost4_cfg_setup ( buckboost4_cfg_t *cfg );
```

- `buckboost4_init` Initialization function.
```c
err_t buckboost4_init ( buckboost4_t *ctx, buckboost4_cfg_t *cfg );
```

- `buckboost4_default_cfg` Click Default Configuration function.
```c
err_t buckboost4_default_cfg ( buckboost4_t *ctx );
```

- `buckboost4_set_vout` Buck-Boost 4 set the output voltage function.
```c
err_t buckboost4_set_vout ( buckboost4_t *ctx, float vout_v );
```

- `buckboost4_set_vref` Buck-Boost 4 set internal reference voltage function.
```c
err_t buckboost4_set_vref ( buckboost4_t *ctx, float vref_mv );
```

- `buckboost4_fault_indicator` Buck-Boost 4 check fault indicator function.
```c
uint8_t buckboost4_fault_indicator ( buckboost4_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buckboost4_cfg_t buckboost4_cfg;  /**< Click config object. */

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
    buckboost4_cfg_setup( &buckboost4_cfg );
    BUCKBOOST4_MAP_MIKROBUS( buckboost4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buckboost4_init( &buckboost4, &buckboost4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCKBOOST4_ERROR == buckboost4_default_cfg ( &buckboost4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "____________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application sets the desired output voltage 
> by cycling through a couple of voltage values.
> Results are sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t vout = 1; vout < 21; vout++ )
    {
        if ( BUCKBOOST4_OK == buckboost4_set_vout( &buckboost4, ( float ) vout ) )
        {
            log_printf( &logger, " Vout: %dV\r\n", ( uint16_t ) vout );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
    log_printf( &logger, "____________\r\n" );
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
