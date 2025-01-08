
---
# HW Monitor Click

> [HW Monitor Click](https://www.mikroe.com/?pid_product=MIKROE-5684) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5684&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the HW Monitor Click board&trade;.
> The demo application monitors analog voltage inputs and local temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HWMonitor

### Example Key Functions

- `hwmonitor_cfg_setup` Config Object Initialization function.
```c
void hwmonitor_cfg_setup ( hwmonitor_cfg_t *cfg );
```

- `hwmonitor_init` Initialization function.
```c
err_t hwmonitor_init ( hwmonitor_t *ctx, hwmonitor_cfg_t *cfg );
```

- `hwmonitor_default_cfg` Click Default Configuration function.
```c
err_t hwmonitor_default_cfg ( hwmonitor_t *ctx );
```

- `hwmonitor_get_analog_inputs` HW Monitor gets analog inputs voltage function.
```c
err_t hwmonitor_get_analog_inputs ( hwmonitor_t *ctx, uint8_t in_pos, float *voltage );
```

- `hwmonitor_get_temperature` HW Monitor gets temperature function.
```c
err_t hwmonitor_get_temperature ( hwmonitor_t *ctx, float *temperature );
```

- `hwmonitor_set_config` HW Monitor set the configuration function.
```c
err_t hwmonitor_set_config ( hwmonitor_t *ctx, hwmonitor_config_t config );
```

### Application Init

> The initialization of the I2C module, log UART and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor_cfg_t hwmonitor_cfg;  /**< Click config object. */

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
    hwmonitor_cfg_setup( &hwmonitor_cfg );
    HWMONITOR_MAP_MIKROBUS( hwmonitor_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor_init( &hwmonitor, &hwmonitor_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR_ERROR == hwmonitor_default_cfg ( &hwmonitor ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This example displays the Analog Voltage Inputs (IN0-IN6) [mV] 
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float temperature, voltage;
    for ( uint8_t in_pos = 0; in_pos < 7; in_pos++ )
    {
        if ( HWMONITOR_OK == hwmonitor_get_analog_inputs( &hwmonitor, in_pos, &voltage ) )
        {
            log_printf( &logger, "IN %d: %.1f mV\r\n", ( uint16_t ) in_pos, voltage );
            Delay_ms ( 100 );
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    if ( HWMONITOR_OK == hwmonitor_get_temperature ( &hwmonitor, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.3f [deg c]\r\n", temperature );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "--------------------------\r\n" );
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
