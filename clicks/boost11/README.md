
---
# Boost 11 Click

> [Boost 11 Click](https://www.mikroe.com/?pid_product=MIKROE-6061) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6061&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Boost 11 Click board 
> by controlling the output state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost11

### Example Key Functions

- `boost11_cfg_setup` Config Object Initialization function.
```c
void boost11_cfg_setup ( boost11_cfg_t *cfg );
```

- `boost11_init` Initialization function.
```c
err_t boost11_init ( boost11_t *ctx, boost11_cfg_t *cfg );
```

- `boost11_active_mode` This function activates the boost operating mode.
```c
void boost11_active_mode ( boost11_t *ctx );
```

- `boost11_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t boost11_read_an_pin_voltage ( boost11_t *ctx, float *data_out );
```

### Application Init

> Initialization of GPIO module, log UART, and activate the boost operating mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    boost11_cfg_t boost11_cfg;  /**< Click config object. */

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
    boost11_cfg_setup( &boost11_cfg );
    BOOST11_MAP_MIKROBUS( boost11_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == boost11_init( &boost11, &boost11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    boost11_active_mode( &boost11 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads measurements of the output voltage level [V].
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float voltage = 0;
    if ( BOOST11_OK == boost11_read_an_pin_voltage ( &boost11, &voltage ) ) 
    {
        log_printf( &logger, " Output Voltage : %.3f[V]\r\n\n", voltage );
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
